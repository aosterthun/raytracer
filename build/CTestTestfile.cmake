# CMake generated Testfile for 
# Source directory: /home/arne/Repositories/programmiersprachen-raytracer
# Build directory: /home/arne/Repositories/programmiersprachen-raytracer/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(tests "/home/arne/Repositories/programmiersprachen-raytracer/build/build/Release/tests")
SUBDIRS(external/glfw-3.0.3)
SUBDIRS(framework)
SUBDIRS(source)
SUBDIRS(tests)
