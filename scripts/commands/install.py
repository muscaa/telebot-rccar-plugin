import os
import shutil

import config
from utils import project
from commands import build
from commands import package

def install():
    build.build()
    package.package()

    print(f"Installing {project.get_package_zip_name()}...")

    install_dir = os.path.dirname(f"build/{project.get_triplet()}/{project.CONFIGURATION}/{config.EXECUTABLE.get_path()}") + "/plugins"
    os.makedirs(install_dir, exist_ok=True)

    shutil.copy(f"build/{project.get_package_zip_name()}", install_dir)
