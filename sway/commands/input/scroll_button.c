#include <string.h>
#include <strings.h>
#include <errno.h>
#include "sway/config.h"
#include "sway/commands.h"
#include "sway/input/input-manager.h"

struct cmd_results *input_cmd_scroll_button(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "scroll_button", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	struct input_config *ic = config->handler_context.input_config;
	if (!ic) {
		return cmd_results_new(CMD_FAILURE, "scroll_button",
			"No input device defined.");
	}

	errno = 0;
	char *endptr;
	int scroll_button = strtol(*argv, &endptr, 10);
	if (endptr == *argv && scroll_button == 0) {
		return cmd_results_new(CMD_INVALID, "scroll_button",
				"Scroll button identifier must be an integer.");
	}
	if (errno == ERANGE) {
		return cmd_results_new(CMD_INVALID, "scroll_button",
				"Scroll button identifier out of range.");
	}
	if (scroll_button < 0) {
		return cmd_results_new(CMD_INVALID, "scroll_button",
				"Scroll button identifier cannot be negative.");
	}
	ic->scroll_button = scroll_button;

	return cmd_results_new(CMD_SUCCESS, NULL, NULL);
}
