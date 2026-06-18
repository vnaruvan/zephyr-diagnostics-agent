#ifndef HEALTH_H
#define HEALTH_H

#include <stdint.h>

enum health_status {
    HEALTH_OK = 0,
    HEALTH_WARN = 1,
    HEALTH_ERROR = 2
};

struct health_state {
    int sensor_value;
    int threshold;
    uint32_t update_count;
    uint32_t error_count;
    enum health_status status;
};

void health_init(struct health_state *state, int threshold);
void health_update(struct health_state *state, int sensor_value);
void health_reset(struct health_state *state);
void health_force_error(struct health_state *state);
void health_set_threshold(struct health_state *state, int threshold);

#endif
