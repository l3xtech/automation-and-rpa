cmake_minimum_required(VERSION 3.22.1)
project(OpenTelemetry VERSION 0.1.0)

set(VCPKG_ROOT "../../../../images/extras/vcpkg")
set(CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed")
find_package(OpenTelemetry REQUIRED HINTS ~/repos/private_repos/core-calc/images/extras/vcpkg/installed/x64-linux/include/)

add_executable(CollectorTestGrpc
  ./collectorTestGrpc.cpp
)

target_link_libraries(CollectorTestGrpc OpenTelemetry::opentelemetry)

add_executable(CollectorTestHttp
  ./collectorTestHttp.cpp
)

target_link_libraries(CollectorTestHttp OpenTelemetry::opentelemetry)
