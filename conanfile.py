import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd
from conan.tools.files import copy, rmdir


class BluksRecipe(ConanFile):
    name = "bluks"
    version = "0.0.1"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    @property
    def _min_cppstd(self):
        return '20'

    def requirements(self):
        self.requires("battery-embed/1.2.19")
        self.requires("stb/cci.20240531")
        self.requires("glfw/3.4")
        self.requires("glm/1.0.1")

    def layout(self):
        cmake_layout(self)

    def validate(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, self._min_cppstd)

    def configure(self):
        pass

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
