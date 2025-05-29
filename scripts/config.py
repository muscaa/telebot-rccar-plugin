from utils.package import *
from utils import platform as p

NAME: str = "telebot-template-plugin"
EXECUTABLE: Executable = Executable("telebot_sdk/telebot")

PACKAGE_LIBRARIES: list[Lib] = [
]
PACKAGE_OTHER: list[File] = [
    File("LICENSE"),
    File("NOTICE"),
]
PLUGIN_JSON: dict = {
    "id": NAME,
    "name": NAME,
    "author": "muscaa",
    "version": "1.0.0",
    "description": "A template plugin for telebot",
    "plugin_lib": NAME,
    "plugin_main": "ttp::main",
    "plugin_main_cli": "ttp::main_cli",
}
