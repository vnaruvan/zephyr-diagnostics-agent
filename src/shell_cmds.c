#include <errno.h>
#include <stdlib.h>

#include <zephyr/shell/shell.h>
#include <zephyr/sys/util.h>

#include "diagnostics.h"

static int cmd_health_status(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    struct health_state state = diagnostics_get_state();

    shell_print(sh, "health=%s sensor=%d threshold=%d updates=%u errors=%u",
                diagnostics_status_to_string(state.status),
                state.sensor_value,
                state.threshold,
                state.update_count,
                state.error_count);

    return 0;
}

static int cmd_health_reset(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    diagnostics_reset();

    shell_print(sh, "health state reset");

    return 0;
}

static int cmd_health_inject_error(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    diagnostics_inject_error();

    struct health_state state = diagnostics_get_state();

    shell_print(sh, "injected error: health=%s errors=%u",
                diagnostics_status_to_string(state.status),
                state.error_count);

    return 0;
}

static int cmd_health_threshold(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 2) {
        shell_error(sh, "usage: health threshold <value>");
        return -EINVAL;
    }

    int threshold = (int)strtol(argv[1], NULL, 10);

    diagnostics_set_threshold(threshold);

    shell_print(sh, "threshold set to %d", threshold);

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(health_cmds,
    SHELL_CMD(status, NULL, "Show health status", cmd_health_status),
    SHELL_CMD(reset, NULL, "Reset health state", cmd_health_reset),
    SHELL_CMD(inject_error, NULL, "Inject simulated error", cmd_health_inject_error),
    SHELL_CMD(threshold, NULL, "Set threshold: health threshold <value>", cmd_health_threshold),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(health, &health_cmds, "Health diagnostics commands", NULL);
