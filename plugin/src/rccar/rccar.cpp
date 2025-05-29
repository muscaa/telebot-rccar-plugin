#include "rccar/rccar.h"

#include <telebot/telebot.h>
#include <telebot/events.h>
#include <telebot/utils/logging.h>
#include <telebot/cli/cli.h>
#include <imgui.h>

namespace rccar {

namespace log = telebot::utils::logging;

static telebot::plugins::Plugin* self;
static bool main_window_open = false;

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

    ImGui::End();
}

void main(const telebot::plugins::Plugin& plugin) {
    self = telebot::plugins::loaded_plugins[plugin.getId()];

    telebot::events::imgui_plugin.connect(&imgui_plugin);
    telebot::events::post_imgui_build.connect(&post_imgui_build);

    log::info("Loaded {}!", plugin.getName());
}

} // namespace rccar
