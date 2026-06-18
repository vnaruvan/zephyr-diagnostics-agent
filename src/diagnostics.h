#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "health.h"

void diagnostics_init(int threshold);
void diagnostics_tick(void);
void diagnostics_reset(void);
void diagnostics_inject_error(void);
void diagnostics_set_threshold(int threshold);
struct health_state diagnostics_get_state(void);
const char *diagnostics_status_to_string(enum health_status status);

#endif
