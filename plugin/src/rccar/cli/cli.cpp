#include "rccar/cli/cli.h"

#include <string>
#include <vector>
#include <telebot/utils/logging.h>
#include <telebot/cli/cli.h>
#include <telebot/utils/stun.h>

namespace rccar::cli {

namespace log = telebot::utils::logging;
namespace stun = telebot::utils::stun;

int main_cli(const telebot::plugins::Plugin& plugin) {
    const std::vector<std::string>& args = telebot::cli::args;

    if (args.size() <= 2 || args[2] == "--help") {
        log::info("Usage: {} {} <--help|--stun-server>", args[0], args[1]);
        return 1;
    }

    if (args[2] == "--stun-server") {

    }

    return 0;
}

} // namespace rccar::cli
