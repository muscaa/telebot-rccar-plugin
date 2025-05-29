from utils import platform as p

class File:
    def __init__(self,
                 path: str,
                 path_to: str = None,
                 platforms: list[str] = p.PLATFORMS,
                 architectures: list[str] = p.ARCHITECTURES):
        self.path = path
        self.path_to = path_to
        self.platforms = platforms
        self.architectures = architectures

    def is_valid(self) -> bool:
        return p.SYSTEM in self.platforms and p.ARCH in self.architectures

    def get_path(self) -> str:
        return self.path
    
    def get_path_to(self) -> str:
        return self.path_to if self.path_to else self.get_path()
    
class Lib(File):
    def get_path(self):
        return f"{self.path}{p.LIB_EXT}"
    
    def get_path_to(self) -> str:
        return f"{self.path_to}{p.LIB_EXT}" if self.path_to else self.get_path()

class Executable(Lib):
    def get_path(self):
        return f"{self.path}{p.EXT}"
    
    def get_path_to(self) -> str:
        return f"{self.path_to}{p.EXT}" if self.path_to else self.get_path()
