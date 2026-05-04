cmake_minimum_required(VERSION 3.28)

project(scion-test-hello-world VERSION 1.0.0 LANGUAGES CXX)

# the following line is commented because the scion library is already present (this file was included by scion's CMakeLists.txt)
# in your client program, you need it
# find_package(scion REQUIRED)

add_executable(scion-test-hello-world sources/main.cpp)
target_link_libraries(scion-test-hello-world PUBLIC scion::scion)
