#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include "diagnostics.h"

LOG_MODULE_REGISTER(diagnostics_agent, LOG_LEVEL_INF);

static void diagnostics_work_handler(struct k_work *work);
static void diagnostics_timer_handler(struct k_timer *timer);

K_WORK_DEFINE(diagnostics_work, diagnostics_work_handler);
K_TIMER_DEFINE(diagnostics_timer, diagnostics_timer_handler, NULL);

static void diagnostics_timer_handler(struct k_timer *timer)
{
    ARG_UNUSED(timer);

    k_work_submit(&diagnostics_work);
}

static void diagnostics_work_handler(struct k_work *work)
{
    ARG_UNUSED(work);

    diagnostics_tick();

    struct health_state state = diagnostics_get_state();

    printk("health=%s sensor=%d threshold=%d updates=%u errors=%u\n",
           diagnostics_status_to_string(state.status),
           state.sensor_value,
           state.threshold,
           state.update_count,
           state.error_count);

    if (state.status == HEALTH_OK) {
        LOG_INF("health=%s sensor=%d threshold=%d updates=%u errors=%u",
                diagnostics_status_to_string(state.status),
                state.sensor_value,
                state.threshold,
                state.update_count,
                state.error_count);
    } else if (state.status == HEALTH_WARN) {
        LOG_WRN("health=%s sensor=%d threshold=%d updates=%u errors=%u",
                diagnostics_status_to_string(state.status),
                state.sensor_value,
                state.threshold,
                state.update_count,
                state.error_count);
    } else {
        LOG_ERR("health=%s sensor=%d threshold=%d updates=%u errors=%u",
                diagnostics_status_to_string(state.status),
                state.sensor_value,
                state.threshold,
                state.update_count,
                state.error_count);
    }
}

int main(void)
{
    printk("starting Zephyr diagnostics agent\n");
    LOG_INF("starting Zephyr diagnostics agent");

    diagnostics_init(75);

    struct health_state state = diagnostics_get_state();

    printk("health monitor initialized with threshold=%d\n", state.threshold);
    LOG_INF("health monitor initialized with threshold=%d", state.threshold);

    k_timer_start(&diagnostics_timer, K_SECONDS(1), K_SECONDS(1));

    while (1) {
        k_sleep(K_SECONDS(10));
    }

    return 0;
}
