cmake_minimum_required(VERSION 3.16)

project(devkeyboard LANGUAGES CXX)

find_package(Fcitx5Core REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(devkeyboard SHARED
    src/devkeyboard.cpp
)

target_compile_features(devkeyboard PRIVATE cxx_std_17)

target_include_directories(devkeyboard PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(devkeyboard PRIVATE
    Fcitx5::Core
    OpenSSL::SSL
    OpenSSL::Crypto
)

set_target_properties(devkeyboard PROPERTIES
    PREFIX ""
)

include(GNUInstallDirs)

install(TARGETS devkeyboard
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/fcitx5"
)

install(FILES conf/devkeyboard-addon.conf
    DESTINATION share/fcitx5/addon
)

install(FILES conf/devkeyboard-im.conf
    DESTINATION share/fcitx5/inputmethod
)