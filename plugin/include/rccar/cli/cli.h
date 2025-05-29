#pragma once

#include <telebot/api.h>
#include <telebot/plugins.h>

namespace rccar::cli {

EXPORT int main_cli(const telebot::plugins::Plugin& plugin);

} // namespace rccar::cli
