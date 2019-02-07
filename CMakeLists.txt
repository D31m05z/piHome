project(piHome)

find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)

# TODO: use find_package
#find_package(wiringPi REQUIRED)

add_executable(${PROJECT_NAME}
    src/sensors/dht11.cpp
    src/sensors/mq135.cpp
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} glfw3 ::imgui wiringPi)
