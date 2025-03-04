project(locker VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets DBus Sql PrintSupport)
find_package(libcontemporary REQUIRED)
find_package(libtdesktopenvironment REQUIRED)

set(SOURCES
        main.cpp
        mainwindow.cpp mainwindow.ui
    )

set(HEADERS
        mainwindow.h
    )

add_executable(locker ${SOURCES} ${HEADERS})

set_target_properties(locker PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in
        MACOSX_BUNDLE_GUI_IDENTIFIER com.vicr123.locker
        WIN32_EXECUTABLE TRUE
        CNTP_DATA_SUBDIR locker)

cntp_init(locker 20)
cntp_translate(locker)
cntp_target_name(locker "td-locker")

target_link_libraries(locker Qt6::Widgets Qt6::DBus Qt6::Sql Qt6::PrintSupport libcontemporary libtdesktopenvironment libthedesk)
target_include_directories(locker PUBLIC ../libthedesk/)

install(TARGETS locker
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
        BUNDLE DESTINATION /Applications)
