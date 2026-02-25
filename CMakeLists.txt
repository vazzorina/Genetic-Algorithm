cmake_minimum_required(VERSION 3.16)

project(geneticAlgorithm VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    Charts
)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appgeneticAlgorithm
    main.cpp
)

qt_add_qml_module(appgeneticAlgorithm
    URI geneticAlgorithm
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        datageneration.h
        datageneration.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appgeneticAlgorithm PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appgeneticAlgorithm
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appgeneticAlgorithm
    PRIVATE
        Qt6::Quick
        Qt6::Charts
)

include(GNUInstallDirs)
install(TARGETS appgeneticAlgorithm
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
