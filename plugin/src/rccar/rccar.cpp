#include "rccar/rccar.h"

#include <memory>
#include <thread>
#include <imgui.h>
#include <SDL3/SDL.h>
#include <telebot/telebot.h>
#include <telebot/events.h>
#include <telebot/utils/logging.h>
#include <telebot/cli/cli.h>
#include <telebot/utils/stun.h>

namespace rccar {

namespace log = telebot::utils::logging;
namespace stun = telebot::utils::stun;

static telebot::plugins::Plugin* self;
static bool main_window_open = false;
static stun::Client* client;
static std::vector<std::string> list;

struct ClientListener : public stun::ClientListener {
    void onList(stun::Client* client, const std::vector<std::string>& list) {
        for (const auto& item : list) {
            log::info("{}", item);
        }
    }
};

static std::shared_ptr<ClientListener> client_listener = std::make_shared<ClientListener>();

static void imgui_plugin(const telebot::plugins::Plugin& plugin) {
    if (plugin.getId() != self->getId()) {
        return;
    }

    if (ImGui::Button("Main Window")) {
        main_window_open = !main_window_open;
    }
}

static void post_imgui_build() {
    if (!main_window_open) {
        return;
    }

    ImGui::Begin(self->getName().c_str());

    if (ImGui::CollapsingHeader("Stun Client")) {
        if (client == nullptr) {
            static char _ip[16] = "127.0.0.1";
            static int port = 3478;
            static char _name[32] = "RCCarClient";

            ImGui::InputText("IP", _ip, 16);
            ImGui::InputInt("Port", &port);
            ImGui::InputText("Name", _name, 32);

            if (ImGui::Button("Connect")) {
                std::thread t([]() {
                    log::info("Connecting to STUN server...");

                    /*std::string ip = _ip;
                    std::string name = _name;

                    client = new stun::Client(client_listener, "musca");
                    client->connect("127.0.0.1", 3478);*/
                });
            }
        }

        if (client != nullptr) {
            if (ImGui::Button("Disconnect")) {
                client->disconnect();
                //delete client;
                //client = nullptr;
            }

            ImGui::SeparatorText("List");

            /*for (const auto& item : list) {
                ImGui::Text("%s", item.c_str());
            }*/
        }
    }

    ImGui::End();
}

void main(const telebot::plugins::Plugin& plugin) {
    self = telebot::plugins::loaded_plugins[plugin.getId()];

    telebot::events::imgui_plugin.connect(&imgui_plugin);
    telebot::events::post_imgui_build.connect(&post_imgui_build);

    log::info("Loaded {}!", plugin.getName());

    /*std::thread t = std::thread([]() {
        log::info("Connecting to STUN server...");
    });*/

    std::thread t = std::thread([](void* ptr) {
        log::info("Connecting to STUN server...");

        return 0;
    });

    std::this_thread::sleep_for(std::chrono::seconds(5));
}

} // namespace rccar
