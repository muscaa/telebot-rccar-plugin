import zipfile
import os

import config
from utils import platform as p
from utils import project

def combine():
    print(f"Packaging {project.get_package_zip_name_crossplatform()}...")

    added_files = set()
    with zipfile.ZipFile(f"build/{project.get_package_zip_name_crossplatform()}", "w", zipfile.ZIP_DEFLATED) as zip_cp:
        for file in os.listdir("build"):
            if file.startswith(f"{config.NAME}-") and file.endswith(".zip"):
                with zipfile.ZipFile(f"build/{file}", "r") as zip:
                    for entry in zip.infolist():
                        if entry.filename not in added_files:
                            added_files.add(entry.filename)
                            zip_cp.writestr(entry, zip.read(entry.filename))
    
    for file in added_files:
        print(file)
    