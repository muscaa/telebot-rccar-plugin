#include "rccar/rccar.h"

#include <memory>
#include <imgui.h>
#include <telebot/events.h>
#include <telebot/utils/logging.h>
#include <telebot/utils/stun.h>

namespace rccar {

namespace log = telebot::utils::logging;
namespace stun = telebot::utils::stun;

static telebot::plugins::Plugin* self;
static bool main_window_open = false;
static std::unique_ptr<stun::Client> client;
static std::vector<std::string> list;

struct ClientListener : public stun::ClientListener {
    void onList(stun::Client* client, const std::vector<std::string>& list) {
        rccar::list = list;
    }

    void onLinkRequest(stun::Client* client, const std::string& from) {
        log::info("Accepted link request from {}", from);
        sendC2SLinkResponse(client, from, true);
    }

    void onLinkAccepted(stun::Client* client, const std::string& name, const std::string& ip, uint16_t port) {
        log::info("Link accepted: {} @ {}:{}", name, ip, port);
    }

    void onLinkDeclined(stun::Client* client, const std::string& name, const std::string& message) {
        log::info("Link declined: {} - {}", name, message);
    }
};

static std::shared_ptr<ClientListener> listener;

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
        if (client == nullptr || !client->isConnected()) {
            static char _ip[16] = "127.0.0.1";
            static int port = 3478;
            static char _name[32] = "RCCarClient";

            ImGui::InputText("IP", _ip, 16);
            ImGui::InputInt("Port", &port);
            ImGui::InputText("Name", _name, 32);

            if (ImGui::Button("Connect")) {
                std::string ip = _ip;
                std::string name = _name;

                log::info("Connecting to {}:{} as {}...", ip, port, name);

                listener = std::make_shared<ClientListener>();
                client = std::make_unique<stun::Client>(listener, name);
                client->connect(ip, port);
            }
        }

        if (client != nullptr && client->isConnected()) {
            if (ImGui::Button("Disconnect")) {
                client->disconnect();
            }

            ImGui::SeparatorText("List");

            for (const auto& name : list) {
                ImGui::PushID(name.c_str());
                ImGui::Text("%s", name.c_str());
                ImGui::SameLine();

                if (ImGui::Button("Link")) {
                    listener->sendC2SLinkRequest(client.get(), name);
                }
                ImGui::PopID();
            }
        }
    }

    ImGui::End();
}

void main(const telebot::plugins::Plugin& plugin) {
    self = telebot::plugins::loaded_plugins[plugin.getId()];

    telebot::events::imgui_plugin.connect(&imgui_plugin);
    telebot::events::post_imgui_build.connect(&post_imgui_build);

    log::info("Loaded {}!", plugin.getName());
}

} // namespace rccar
