project(piHome)

find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
find_package(raspicam REQUIRED)

# TODO: use find_package
#find_package(wiringPi REQUIRED)

add_executable(${PROJECT_NAME}
    src/sensors/dht11.cpp
    src/sensors/mq135.cpp
    src/sensors/pir.cpp
    src/sensors/camera.cpp
    src/piHome.cpp
    src/main.cpp
)

# TODO: raspicam use target install
target_link_libraries(${PROJECT_NAME} glfw3 ::imgui wiringPi ${raspicam_LIBS})

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION lib)
