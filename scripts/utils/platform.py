import platform

WINDOWS = "windows"
LINUX = "linux"
MACOS = "macos"
PLATFORMS = [WINDOWS, LINUX, MACOS]

_system = platform.system().lower()
if _system == "windows":
    SYSTEM = WINDOWS
    EXT = ".exe"
    LIB_EXT = ".dll"
elif _system == "linux":
    SYSTEM = LINUX
    EXT = ""
    LIB_EXT = ".so"
elif _system == "darwin":
    SYSTEM = MACOS
    EXT = ""
    LIB_EXT = ".dylib"
else:
    SYSTEM = "unknown"
    EXT = ".unknown"
    LIB_EXT = ".unknown"

X64 = "x64"
ARM64 = "arm64"
ARCHITECTURES = [X64, ARM64]

_arch = platform.machine().lower()
if _arch in ("x86_64", "amd64"):
    ARCH = X64
elif _arch in ("arm64", "aarch64"):
    ARCH = ARM64
else:
    ARCH = "unknown"
