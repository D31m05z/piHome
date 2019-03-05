cmake_minimum_required(VERSION 3.12)

project(piHome)

find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
find_package(raspicam REQUIRED)

# TODO: use find_package
find_package(wiringPi QUIET)

add_executable(${PROJECT_NAME}
    src/sensors/camera.cpp
    src/sensors/ipcamera.cpp
    src/sensors/raspicamera.cpp

    src/networks/server.cpp
    src/networks/client.cpp

    src/piHome.cpp
    src/main.cpp

    include/pihome/sensors/camera.h
    include/pihome/sensors/dht11.h
    include/pihome/sensors/ipcamera.h
    include/pihome/sensors/mq135.h
    include/pihome/sensors/pir.h
    include/pihome/sensors/raspicamera.h
    include/pihome/sensors/sensor.h

    include/pihome/networks/client.h
    include/pihome/networks/server.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/gen>
    PUBLIC $<INSTALL_INTERFACE:include>
)

if(wiringPi_FOUND)
    target_sources(${PROJECT_NAME}
        src/sensors/dht11.cpp
        src/sensors/mq135.cpp
        src/sensors/pir.cpp
    )
    target_link_libraries(${PROJECT_NAME} wiringPi)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DHAVE_WIRING_PI)
endif()

# TODO: raspicam use target install
target_link_libraries(${PROJECT_NAME} glfw3 ::imgui ${raspicam_LIBS})

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION lib)
