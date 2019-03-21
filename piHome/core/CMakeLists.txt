cmake_minimum_required(VERSION 3.7)

project(core)

find_package(raspicam REQUIRED)
find_package(wiringPi QUIET)

set(${PROJECT_NAME}_PUBLIC_HEADERS
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

add_library(${PROJECT_NAME}
    src/sensors/camera.cpp
    src/sensors/ipcamera.cpp
    src/sensors/raspicamera.cpp

    src/networks/server.cpp
    src/networks/client.cpp

    ${${PROJECT_NAME}_PUBLIC_HEADERS}
)

add_library(::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/gen>
    PUBLIC $<INSTALL_INTERFACE:include>
)

set(libs ::raspicam)

set(wiringPi_FOUND 0)

if(wiringPi_FOUND)
	target_sources(${PROJECT_NAME} PRIVATE
        src/sensors/dht11.cpp
        src/sensors/mq135.cpp
        src/sensors/pir.cpp
    )
    list(APPEND libs wiringPi)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DHAVE_WIRING_PI)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${libs})

configure_file(${PROJECT_NAME}-config.cmake.in ${PROJECT_NAME}-config.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake DESTINATION lib/cmake/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets DESTINATION lib)
install(DIRECTORY include DESTINATION .)
install(EXPORT ${PROJECT_NAME}-targets NAMESPACE :: DESTINATION lib/cmake/${PROJECT_NAME})
