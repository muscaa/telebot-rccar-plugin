import subprocess

from utils import project

def build():
    print("Building...")

    subprocess.run(["cmake", "--preset", f"{project.get_triplet()}"])
    subprocess.run(["cmake", "--build", "--preset", f"{project.get_triplet()}"])
