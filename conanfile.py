from conans import ConanFile, CMake, tools


class EnpitsuConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    # default_options = {"shared": True, "fPIC": True}
    generators = "cmake", "cmake_find_package"
    requires = 'glfw/3.3.8', 'glad/0.1.36'

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin

