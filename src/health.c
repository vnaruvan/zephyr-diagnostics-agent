#include <stddef.h>
#include "health.h"

void health_init(struct health_state *state, int threshold)
{
    if (state == NULL) {
        return;
    }

    state->sensor_value = 0;
    state->threshold = threshold;
    state->error_count = 0;
    state->status = HEALTH_OK;
}

void health_update(struct health_state *state, int sensor_value)
{
    if (state == NULL) {
        return;
    }

    state->sensor_value = sensor_value;

    if (sensor_value > state->threshold) {
        state->status = HEALTH_WARN;
        state->error_count++;
    } else {
        state->status = HEALTH_OK;
    }
}

void health_reset(struct health_state *state)
{
    if (state == NULL) {
        return;
    }

    state->sensor_value = 0;
    state->error_count = 0;
    state->status = HEALTH_OK;
}
