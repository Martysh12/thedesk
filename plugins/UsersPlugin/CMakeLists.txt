cmake_minimum_required(VERSION 3.4.0)

find_package(Qt6 REQUIRED COMPONENTS Widgets DBus)
find_package(libcontemporary)
find_package(PolkitQt6-1)

set(SOURCES
    onboarding/onboardingusers.cpp
    plugin.cpp
    settings/adduserdialog.cpp
    settings/changepassworddialog.cpp
    settings/changerealnamedialog.cpp
    settings/deleteuserdialog.cpp
    settings/lockuserdialog.cpp
    settings/user.cpp
    settings/usersmodel.cpp
    settings/userspane.cpp
    settings/usertypedialog.cpp

    onboarding/onboardingusers.ui
    settings/adduserdialog.ui
    settings/changepassworddialog.ui
    settings/changerealnamedialog.ui
    settings/deleteuserdialog.ui
    settings/lockuserdialog.ui
    settings/userspane.ui
    settings/usertypedialog.ui
)

set(HEADERS
    onboarding/onboardingusers.h
    plugin.h
    settings/adduserdialog.h
    settings/changepassworddialog.h
    settings/changerealnamedialog.h
    settings/deleteuserdialog.h
    settings/lockuserdialog.h
    settings/user.h
    settings/usersmodel.h
    settings/userspane.h
    settings/usertypedialog.h
)

set(PLUGIN_NAME users)
add_plugin_td(${PLUGIN_NAME})
target_sources(plugin-${PLUGIN_NAME} PRIVATE ${SOURCES} ${HEADERS})

IF(${PolkitQt6-1_FOUND})
    target_link_libraries(plugin-${PLUGIN_NAME} PolkitQt6-1::Core)
    target_compile_definitions(plugin-${PLUGIN_NAME} PRIVATE HAVE_POLKITQT)
ENDIF()

target_link_libraries(plugin-${PLUGIN_NAME} Qt6::Widgets Qt6::DBus libcontemporary libthedesk)
