#include "rccar/cli/cli.h"

#include <string>
#include <vector>
#include <memory>
#include <telebot/utils/logging.h>
#include <telebot/cli/cli.h>
#include <telebot/utils/stun.h>

namespace rccar::cli {

namespace log = telebot::utils::logging;
namespace stun = telebot::utils::stun;

static void stun_server(int port) {
    log::info("Starting STUN server on port {}", port);

    stun::Server* server = new stun::Server(std::make_shared<stun::ServerListener>());
    server->start(port);

    while (server->isRunning()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main_cli(const telebot::plugins::Plugin& plugin) {
    const std::vector<std::string>& args = telebot::cli::args;

    if (args.size() < 3 || args[2] == "--help") {
        log::info("Usage: {} {} <--help|--stun-server>", args[0], args[1]);
        return 1;
    }

    if (args[2] == "--stun-server") {
        if (args.size() < 4) {
            log::info("Usage: {} {} --stun-server <port>", args[0], args[1]);
            return 1;
        }

        int port = 0;
        try {
            port = std::stoi(args[3]);

            if (port < 1 || port > 65535) {
                log::info("Port number must be between 1 and 65535");
                return 1;
            }
        } catch (const std::invalid_argument& e) {
            log::info("Invalid port number: {}", args[3]);
            return 1;
        } catch (const std::out_of_range& e) {
            log::info("Port number out of range: {}", args[3]);
            return 1;
        }

        stun_server(port);
    } else {
        log::info("Unknown option: {}", args[2]);
        return 1;
    }

    return 0;
}

} // namespace rccar::cli
