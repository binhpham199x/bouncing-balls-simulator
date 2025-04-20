cmake_minimum_required(VERSION 3.19)
project(BallsSimulator LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

qt_add_executable(BallsSimulator
    WIN32 MACOSX_BUNDLE
    ${SRC_DIR}/main.cpp

    ${SRC_DIR}/controllers/BaseController.h
    ${SRC_DIR}/controllers/BaseController.cpp

    ${SRC_DIR}/views/BaseView.h
    ${SRC_DIR}/views/BaseView.cpp

    ${SRC_DIR}/models/Ball.h
    ${SRC_DIR}/models/Ball.cpp
)


target_include_directories(BallsSimulator PUBLIC ${SRC_DIR})

target_link_libraries(BallsSimulator
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--subsystem,console")
endif()


include(GNUInstallDirs)

install(TARGETS BallsSimulator
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET BallsSimulator
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})