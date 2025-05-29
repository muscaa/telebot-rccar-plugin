from utils.package import *
from utils import platform as p

NAME: str = "rccar-plugin"
EXECUTABLE: Executable = Executable("telebot_sdk/telebot")

PACKAGE_LIBRARIES: list[Lib] = [
]
PACKAGE_OTHER: list[File] = [
    File("LICENSE"),
    File("NOTICE"),
]
PLUGIN_JSON: dict = {
    "id": "rccar",
    "name": "RC Car",
    "author": "muscaa",
    "version": "1.0.0",
    "description": "A telebot plugin for controlling an RC car.",
    "plugin_lib": NAME,
    "plugin_main": "rccar::main",
    "plugin_main_cli": "rccar::cli::main_cli",
}
