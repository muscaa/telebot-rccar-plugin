import zipfile
import os
import json

import config
from utils import platform as p
from utils import project

def package():
    print(f"Packaging {project.get_package_zip_name()}...")

    added_files = {}
    with zipfile.ZipFile(f"build/{project.get_package_zip_name()}", "w", zipfile.ZIP_DEFLATED) as zip:
        zip.writestr("plugin.json", json.dumps(config.PLUGIN_JSON))
        added_files["plugin.json"] = "plugin.json"

        for file in config.PACKAGE_OTHER:
            if file.is_valid():
                src = file.get_path()
                dst = file.get_path_to()
                zip.write(src, dst)
                added_files[src] = dst

        for dir in config.PACKAGE_DIRS:
            build_dir = f"build/{project.get_triplet()}/{project.CONFIGURATION}/{dir}"

            for root, _, files in os.walk(build_dir):
                for file in files:
                    src = os.path.join(root, file)
                    if src not in added_files:
                        ignored = False
                        for lib in config.PACKAGE_LIBRARIES_IGNORE:
                            if lib.is_valid():
                                print(f"{file} : {lib.get_path()}")
                                if file == lib.get_path():
                                    ignored = True
                                    break

                        if not ignored:
                            dst = os.path.relpath(os.path.join(root, f"({p.SYSTEM}-{p.ARCH}){file}"), build_dir)
                            zip.write(src, dst)
                            added_files[src] = dst

    for src, dst in added_files.items():
        print(f"{src} -> {dst}")
    