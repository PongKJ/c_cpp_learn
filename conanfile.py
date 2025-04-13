# This file is managed by Conan, contents will be overwritten.
# To keep your changes, remove these comment lines, but the plugin won't be able to modify your requirements

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, cmake_layout


class ConanApplication(ConanFile):
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()

    def requirements(self):
        # requirements = self.conan_data.get("requirements", [])
        # for requirement in requirements:
        #     self.requires(requirement)
        self.requires("fmt/10.2.1")
        self.requires("gtest/1.15.0")
        self.requires("spdlog/1.14.1")
        self.requires("jsoncpp/1.9.6")
        self.requires("dbg-macro/0.5.1")
        self.requires("boost/1.86.0")
        self.requires("cli11/2.4.2")
        self.requires("qt/6.7.3")

    def configure(self):
        self.options["qt"].with_x11 = False
