cmake_minimum_required(VERSION 3.16)

project(qtjluna VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appqtjluna
    main.cpp
)

qt_add_qml_module(appqtjluna
    URI qtjluna
    VERSION 1.0
    QML_FILES Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqtjluna PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqtjluna
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqtjluna
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appqtjluna
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

find_library(jluna REQUIRED
        NAMES jluna
        PATHS "D:/jjluna/lib"
)

target_link_libraries(appqtjluna PRIVATE
        "${jluna}"
        "C:/soft_using/julia-1.10.2/lib/libjulia.dll.a"
)
target_include_directories(appqtjluna PRIVATE
        "D:/jjluna/include/jluna"
        "C:/soft_using/julia-1.10.2/include/julia"
)
target_compile_features(appqtjluna PRIVATE cxx_std_20)