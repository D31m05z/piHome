cmake_minimum_required(VERSION 3.7)

project(app)

if(NOT TARGET core)
  find_package(core REQUIRED)
endif()
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    piHome.cpp
    piHome.h
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -DGLFW_INCLUDE_ES2)

target_link_libraries(${PROJECT_NAME} PRIVATE ::core glfw3 ::imgui)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION lib)
