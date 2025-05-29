#include "rccar/cli/cli.h"

#include <telebot/utils/logging.h>
#include <telebot/cli/cli.h>

namespace rccar::cli {

namespace log = telebot::utils::logging;

int main_cli(const telebot::plugins::Plugin& plugin) {
    log::info("Plugin {} main CLI called with {} args", plugin.getId(), telebot::cli::args.size());
    return 0;
}

} // namespace rccar::cli
