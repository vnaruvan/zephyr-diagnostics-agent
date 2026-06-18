#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include "health.h"

LOG_MODULE_REGISTER(diagnostics_agent, LOG_LEVEL_INF);

static struct health_state health;
static int simulated_sensor_value = 60;

static void diagnostics_work_handler(struct k_work *work);
static void diagnostics_timer_handler(struct k_timer *timer);

K_WORK_DEFINE(diagnostics_work, diagnostics_work_handler);
K_TIMER_DEFINE(diagnostics_timer, diagnostics_timer_handler, NULL);

static const char *status_to_string(enum health_status status)
{
    switch (status) {
    case HEALTH_OK:
        return "OK";
    case HEALTH_WARN:
        return "WARN";
    case HEALTH_ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

static void diagnostics_timer_handler(struct k_timer *timer)
{
    ARG_UNUSED(timer);
    k_work_submit(&diagnostics_work);
}

static void diagnostics_work_handler(struct k_work *work)
{
    ARG_UNUSED(work);

    simulated_sensor_value += 5;

    if (simulated_sensor_value > 100) {
        simulated_sensor_value = 50;
    }

    health_update(&health, simulated_sensor_value);

    printk("health=%s sensor=%d threshold=%d errors=%u\n",
           status_to_string(health.status),
           health.sensor_value,
           health.threshold,
           health.error_count);

    if (health.status == HEALTH_OK) {
        LOG_INF("health=%s sensor=%d threshold=%d errors=%u",
                status_to_string(health.status),
                health.sensor_value,
                health.threshold,
                health.error_count);
    } else {
        LOG_WRN("health=%s sensor=%d threshold=%d errors=%u",
                status_to_string(health.status),
                health.sensor_value,
                health.threshold,
                health.error_count);
    }
}

int main(void)
{
    printk("starting Zephyr diagnostics agent\n");
    LOG_INF("starting Zephyr diagnostics agent");

    health_init(&health, 75);

    printk("health monitor initialized with threshold=%d\n", health.threshold);
    LOG_INF("health monitor initialized with threshold=%d", health.threshold);

    k_timer_start(&diagnostics_timer, K_SECONDS(1), K_SECONDS(1));

    while (1) {
        k_sleep(K_SECONDS(10));
    }

    return 0;
}
