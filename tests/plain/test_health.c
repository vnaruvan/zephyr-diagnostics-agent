#include <assert.h>

#include "health.h"

int main(void)
{
    struct health_state state;

    health_init(&state, 75);
    assert(state.threshold == 75);
    assert(state.sensor_value == 0);
    assert(state.update_count == 0);
    assert(state.error_count == 0);
    assert(state.status == HEALTH_OK);

    health_update(&state, 60);
    assert(state.sensor_value == 60);
    assert(state.update_count == 1);
    assert(state.error_count == 0);
    assert(state.status == HEALTH_OK);

    health_update(&state, 90);
    assert(state.sensor_value == 90);
    assert(state.update_count == 2);
    assert(state.error_count == 1);
    assert(state.status == HEALTH_WARN);

    health_force_error(&state);
    assert(state.error_count == 2);
    assert(state.status == HEALTH_ERROR);

    health_reset(&state);
    assert(state.sensor_value == 0);
    assert(state.update_count == 0);
    assert(state.error_count == 0);
    assert(state.status == HEALTH_OK);

    health_set_threshold(&state, 50);
    assert(state.threshold == 50);

    return 0;
}
