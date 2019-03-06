cmake_minimum_required(VERSION 3.7)

project(zero)

if(NOT TARGET core)
  find_package(core REQUIRED)
endif()

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ::core)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION lib)
