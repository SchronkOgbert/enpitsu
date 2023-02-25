from conans import ConanFile, CMake


class EnpitsuConan(ConanFile):
    version = 0.1
    name = "enpitsu"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    # default_options = {"shared": True, "fPIC": True}
    generators = "cmake", "cmake_find_package"
    requires = 'glfw/3.3.8', 'glad/0.1.36', 'stb/cci.20220909', 'glm/cci.20220420', 'plog/1.1.9'
    exports_sources = "CMakeLists.txt", "include/*", "src/*"
    build_policy = "missing"

    def configure(self):
        if self.settings.compiler == "Visual Studio":
            del self.settings.compiler.runtime

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin
        self.copy("*.lib", dst="bin", src="lib")

    def build(self):
        cmake_debug = CMake(self, build_type="Debug")
        cmake_debug.configure()
        cmake_debug.build()

    def package(self):
        self.copy('*.h', dst="include/enpitsu", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

