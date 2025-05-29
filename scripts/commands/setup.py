import zipfile
import os
import shutil
import sys
import textwrap
import re

def filename_to_dirname(filename):
    name, _ = os.path.splitext(filename)
    name = re.sub(r'[^0-9a-zA-Z_]', '_', name)
    if name and name[0].isdigit():
        name = f"_{name}"
    return name

def setup():
    print("Removing old SDKs...")
    for file in os.listdir("sdks/"):
        if os.path.isdir(f"sdks/{file}"):
            shutil.rmtree(f"sdks/{file}")

    sys.path.insert(0, os.path.abspath("sdks/"))

    for file in os.listdir("sdks/"):
        if os.path.isfile(f"sdks/{file}") and file.endswith(".zip"):
            print(f"Extracting {file}...")

            sdk_name = filename_to_dirname(file)
            with zipfile.ZipFile(f"sdks/{file}", "r") as zip:
                zip.extractall(f"sdks/{sdk_name}")

            print(f"Running {sdk_name} setup...")
            code = f"""
            from {sdk_name}.setup import main
            main()
            """
            exec(textwrap.dedent(code))
