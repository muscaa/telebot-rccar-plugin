import config
from utils import platform as p

CONFIGURATION = "release"

def get_triplet() -> str:
    return f"{p.ARCH}-{p.SYSTEM}-{CONFIGURATION}"

def get_package_zip_name() -> str:
    return f"{config.NAME}.zip"
