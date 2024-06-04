from conans import ConanFile, CMake, tools
import os


class RabbitMQLibConan(ConanFile):
    name = "usb_devices_monitor"
    version = "0.0.0"
    exports_sources = ["src/*", "CMakeLists.txt", "include/*", "test/*", "cmake/*"]
    settings = "os", "compiler", "build_type", "arch"
    requires = ()
    build_requires = (
        "nlohmann_json/3.11.3",
        "gtest/1.10.0"
    )
    generators = "cmake", "make", "gcc"

    yes = ["YES", "ON", "1"]

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self.test in self.yes:
            self.run("cmake --build . --target test")

    def package(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
