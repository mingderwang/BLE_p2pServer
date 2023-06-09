/**
  ******************************************************************************
  * @file    ll_sys_dp_slp.c
  * @author  MCD Application Team
  * @brief   Link Layer IP system interface deep sleep management
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "linklayer_plat.h"
#if defined(MAC)
#include "stm32wbaxx.h"
#include "llhwc_cmn.h"
#endif
#include "ll_sys.h"
#include "ll_intf.h"

/* Link Layer deep sleep status */
uint8_t is_Radio_DeepSleep = 0U;

/* Link Layer deep sleep timer */
os_timer_id radio_dp_slp_tmr_id = NULL;


/**
  * @brief  Initialize ressources to handle deep sleep entry/exit
  * @param  None
  * @retval LL_SYS status
  */
ll_sys_status_t ll_sys_dp_slp_init(void)
{
  ll_sys_status_t return_status = LL_SYS_ERROR;
  
  /* Create link layer timer for handling IP DEEP SLEEP mode */
  radio_dp_slp_tmr_id = os_timer_create((t_timer_callbk)ll_sys_dp_slp_wakeup_evt_clbk, os_timer_once, NULL);

  if (radio_dp_slp_tmr_id != NULL)
  {
    return_status = LL_SYS_OK;
  }
  
  return return_status;
}

/**
  * @brief  The Link Layer IP enters deep sleep mode
  * @param  dp_slp_duration    deep sleep duration in us
  * @retval LL_SYS status
  */
ll_sys_status_t ll_sys_dp_slp_enter(uint32_t dp_slp_duration){
  ble_stat_t cmd_status = GENERAL_FAILURE;
  int32_t os_status = GENERAL_FAILURE;
  ll_sys_status_t return_status = LL_SYS_ERROR;
  
  /* Check if deep sleep timer has to be started */
  if(dp_slp_duration < LL_DP_SLP_NO_WAKEUP)
  {
    /* Start deep sleep timer */
    os_status = os_timer_start(radio_dp_slp_tmr_id, LL_INTERNAL_TMR_US_TO_STEPS(dp_slp_duration));
  }
  
  else 
  {
    /* No timer started */
    os_status = SUCCESS;
  }
  
  if(os_status == SUCCESS)
  {
    /* Switch Link Layer IP to DEEP SLEEP mode */
#if defined(BLE)
    /* BLE & Concurrent use case */
    cmd_status = ll_intf_le_set_dp_slp_mode(DEEP_SLEEP_ENABLE);
#elif defined(MAC)
    cmd_status = llhwc_cmn_set_dp_slp_mode(DEEP_SLEEP_ENABLE);
#else
 #error "neither MAC not BLE defined"
#endif
    if(cmd_status == SUCCESS){
      is_Radio_DeepSleep = 1U;
      return_status = LL_SYS_OK;
    }
  }

  return return_status;
}

/**
  * @brief  The Link Layer IP exits deep sleep mode
  * @param  None
  * @retval LL_SYS status
  */
ll_sys_status_t ll_sys_dp_slp_exit(void){
  ble_stat_t cmd_status = GENERAL_FAILURE;
  ll_sys_status_t return_status = LL_SYS_ERROR;

  /* Disable radio interrupt */
  LINKLAYER_PLAT_DisableRadioIT();

  if(!is_Radio_DeepSleep)
  {
    /* Radio not in sleep mode */
    return_status = LL_SYS_OK;
  }
  else
  {
    /* Stop the deep sleep wake-up timer if running */
    if(os_get_tmr_state(radio_dp_slp_tmr_id) != (os_timer_state)osTimerStopped)
    {
      os_timer_stop(radio_dp_slp_tmr_id);
    }
    
    /* Switch Link Layer IP to SLEEP mode (by deactivate DEEP SLEEP mode) */
#if defined(BLE)
    /* BLE & Concurrent use case */
    cmd_status = ll_intf_le_set_dp_slp_mode(DEEP_SLEEP_DISABLE);
#elif defined(MAC)
    cmd_status = llhwc_cmn_set_dp_slp_mode(DEEP_SLEEP_DISABLE);
#else
 #error "neither MAC not BLE defined"
#endif
    if(cmd_status == SUCCESS)
    {
      is_Radio_DeepSleep = 0U;
      return_status = LL_SYS_OK;
    }
  }
  
  /* Re-enable radio interrupt */
  LINKLAYER_PLAT_EnableRadioIT();
  
  return return_status;
}

/**
  * @brief  Link Layer deep sleep wake-up timer callback
  * @param  ptr_arg    pointer passed through the callback
  * @retval LL_SYS status
  */
void ll_sys_dp_slp_wakeup_evt_clbk(void const *ptr_arg){
  int32_t os_status = GENERAL_FAILURE;

  /* Stop the Link Layer IP DEEP SLEEP wake-up timer */
  os_status = os_timer_stop(radio_dp_slp_tmr_id);
  if(os_status != SUCCESS){
    return;
  }

  /* Link Layer IP exits from DEEP SLEEP mode */
//  LL_GPIO_DEEP_SLEEP_DISABLE_from_irq_set();
  ll_sys_dp_slp_exit();
//  LL_GPIO_DEEP_SLEEP_DISABLE_from_irq_reset();
}