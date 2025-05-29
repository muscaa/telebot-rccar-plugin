import subprocess
import os

import config
from utils import project

def run():
    print("Running...")

    if os.path.exists(f"build/{project.get_triplet()}/{project.CONFIGURATION}/{config.EXECUTABLE.get_path()}"):
        subprocess.run([f"build/{project.get_triplet()}/{project.CONFIGURATION}/{config.EXECUTABLE.get_path()}"])
    else:
        print("No build found.")
