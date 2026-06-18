#include "diagnostics.h"

static struct health_state current_health;
static int simulated_sensor_value = 60;

void diagnostics_init(int threshold)
{
    simulated_sensor_value = 60;
    health_init(&current_health, threshold);
}

void diagnostics_tick(void)
{
    simulated_sensor_value += 5;

    if (simulated_sensor_value > 100) {
        simulated_sensor_value = 50;
    }

    health_update(&current_health, simulated_sensor_value);
}

void diagnostics_reset(void)
{
    simulated_sensor_value = 60;
    health_reset(&current_health);
}

void diagnostics_inject_error(void)
{
    health_force_error(&current_health);
}

void diagnostics_set_threshold(int threshold)
{
    health_set_threshold(&current_health, threshold);
}

struct health_state diagnostics_get_state(void)
{
    return current_health;
}

const char *diagnostics_status_to_string(enum health_status status)
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
