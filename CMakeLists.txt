cmake_minimum_required(VERSION 3.19)
project(AlterLaunch LANGUAGES CXX)
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.steam/steam/compatibilitytools.d/AlterLaunch" CACHE PATH "Install path" FORCE)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(AlterLaunch
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(AlterLaunch
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS AlterLaunch
    BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}
)

install(FILES compatibilitytool.vdf toolmanifest.vdf
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)

qt_generate_deploy_app_script(
    TARGET AlterLaunch
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
