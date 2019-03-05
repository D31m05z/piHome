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
    src/piHome.cpp
    src/main.cpp
)

if(wiringPi_FOUND)
    target_sources(${PROJECT_NAME}
            src/sensors/dht11.cpp
            src/sensors/mq135.cpp
            src/sensors/pir.cpp)
    target_link_libraries(${PROJECT_NAME} wiringPi)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DHAVE_WIRING_PI)
endif()

# TODO: raspicam use target install
target_link_libraries(${PROJECT_NAME} glfw3 ::imgui ${raspicam_LIBS})

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION lib)
