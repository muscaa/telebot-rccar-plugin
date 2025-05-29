#pragma once

#include <vector>
#include <string>
#include <telebot/api.h>
#include <telebot/plugins.h>

namespace rccar {

EXPORT int main_cli(const telebot::plugins::Plugin& plugin);

EXPORT void main(const telebot::plugins::Plugin& plugin);

} // namespace ttp
