/**
 * Copyright (C) 2020. VeriSilicon Holdings Co., Ltd.
 * All rights reserved.
 *
 * @file vpi_sw_timer.h
 * @brief public head file of sw timer
 * @author Lucas Wang <lucas.wang@verisilicon.com>
 */

#ifndef __VPI_SW_TIMER_H__
#define __VPI_SW_TIMER_H__
/* Standard includes. */
#include <stdint.h>
#include <stdbool.h>
#include "vs_conf.h"
#include "vpi_error.h"
#include "os_adapter.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup SW_TIMER
 *  - SW Timer API.
 *  @ingroup VPI
 *  @{
 */

/**
 * @brief SW Timer return value
 */
#define TIMER_ERROR VPI_ERR_GENERIC
#define TIMER_OK VPI_SUCCESS
#define INVALID_TIMER NULL

/**
 * @brief The calling task should be held in the Blocked state to wait for the
 * start command to be successfully sent to the timer command queue, should the
 * queue already be full when vpi_timer_*() was called.
 */
#define WAIT_FOREVER ((uint32_t)-1)

/**
 * @brief SW Timer trigger modes
 */
enum VsTimerType {
    VS_TIMER_SW_ONE_SHOT, /**< One shot mode, trigger once */
    VS_TIMER_SW_REPEAT, /**< Repeat mode, trigger repeatedly */
    VS_TIMER_SW_ALARM, /**< Alarm mode, used for wakeup */
};

/**
 * @brief SW Timer interrupt callback handler
 */
typedef void (*VsTimerHandler)(void *self);

/**
 * @brief Initialize SW timer
 * @return Return result
 * @retval TIMER_OK for succeed, TIMER_ERROR for failure
 */
int vpi_timer_init(void);

/**
 * @brief Create a SW timer
 * @param timer_name The text name that is assigned to the timer
 * @param type The timer trigger modes, @see VsTimerType
 * @param timer_id The identifier that is assigned to the timer being created
 * @param timeout_ms The timer timeout times
 * @param handler The timer interrupt callback handler
 * @return Return result
 * @retval Created timer handle for succeed, INVALID_TIMER for failure
 */
void *vpi_timer_create(char *timer_name, uint32_t type, void *timer_id,
                       uint64_t timeout_ms, VsTimerHandler handler);

/**
 * @brief Start a SW timer
 * @param sw_timer The handle of the timer being started/restarted
 * @param times_to_wait The timeout waiting time for sending queue
 * @return Return result
 * @retval TIMER_OK for succeed, TIMER_ERROR for failure
 */
int vpi_timer_start(void *sw_timer, uint32_t times_to_wait);

/**
 * @brief Stop a SW timer
 * @param sw_timer The handle of the timer being stopped
 * @param times_to_wait The timeout waiting time for sending queue
 * @return Return result
 * @retval TIMER_OK for succeed, TIMER_ERROR for failure
 */
int vpi_timer_stop(void *sw_timer, uint32_t times_to_wait);

/**
 * @brief Delete a SW timer
 * @param sw_timer The handle of the timer being deleted
 * @param times_to_wait The timeout waiting time for sending queue
 * @return Return result
 * @retval TIMER_OK for succeed, TIMER_ERROR for failure
 */
int vpi_timer_delete(void *sw_timer, uint32_t times_to_wait);

/**
 * @brief Reset a SW timer
 * @param sw_timer The handle of the timer being reset
 * @param times_to_wait The timeout waiting time for sending queue
 * @return Return result
 * @retval TIMER_OK for succeed, TIMER_ERROR for failure
 */
int vpi_timer_reset(void *sw_timer, uint32_t times_to_wait);

/**
 * @brief Start a SW timer from ISR
 * @param sw_timer The handle of the timer being started/restarted
 * @return Return result
 * @retval TIMER_OK for succeed, TIMER_ERROR for failure
 */
int vpi_timer_start_from_isr(void *sw_timer);

/**
 * @brief Stop a SW timer from ISR
 * @param sw_timer The handle of the timer being stopped
 * @return Return result
 * @retval TIMER_OK for succeed, TIMER_ERROR for failure
 */
int vpi_timer_stop_from_isr(void *sw_timer);

/**
 * @brief Reset a SW timer from ISR
 * @param sw_timer The handle of the timer being reset
 * @return Return result
 * @retval TIMER_OK for succeed, TIMER_ERROR for failure
 */
int vpi_timer_reset_from_isr(void *sw_timer);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __VPI_SW_TIMER_H__ */
