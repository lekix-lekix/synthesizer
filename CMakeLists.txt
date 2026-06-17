cmake_minimum_required(VERSION 3.16)
project(synth VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.10)

add_subdirectory(src/dsp)
add_subdirectory(src/QtWrappers)

qt_add_executable(appsynth src/mainQt.cpp rtaudio/RtAudio.cpp)

qt_add_qml_module(appsynth
    URI synth
    QML_FILES
        src/ui/Main.qml
        src/ui/Osc.qml
        QML_FILES src/ui/VCA.qml
        QML_FILES src/ui/Jack.qml
        QML_FILES src/ui/Env.qml
        QML_FILES src/ui/VSlider.qml
)

# ─── RtAudio backend ───────────────────────────────────────────────
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(PULSE libpulse-simple)
    pkg_check_modules(ALSA alsa)

    if(PULSE_FOUND)
        message(STATUS "RtAudio backend: PulseAudio")
        target_compile_definitions(appsynth PRIVATE __LINUX_PULSE__)
        target_include_directories(appsynth PRIVATE ${PULSE_INCLUDE_DIRS})
        target_link_libraries(appsynth PRIVATE ${PULSE_LIBRARIES})
    elseif(ALSA_FOUND)
        message(STATUS "RtAudio backend: ALSA")
        target_compile_definitions(appsynth PRIVATE __LINUX_ALSA__)
        target_include_directories(appsynth PRIVATE ${ALSA_INCLUDE_DIRS})
        target_link_libraries(appsynth PRIVATE ${ALSA_LIBRARIES})
    else()
        message(FATAL_ERROR "Aucun backend audio trouvé")
    endif()
elseif(APPLE)
    message(STATUS "RtAudio backend: CoreAudio")
    target_compile_definitions(appsynth PRIVATE __MACOSX_CORE__)
    target_link_libraries(appsynth PRIVATE "-framework CoreAudio" "-framework CoreFoundation")
elseif(WIN32)
    message(STATUS "RtAudio backend: WASAPI")
    target_compile_definitions(appsynth PRIVATE __WINDOWS_WASAPI__)
    target_link_libraries(appsynth PRIVATE ole32 winmm ksuser mfplat mf mfuuid wmcodecdspuuid)
endif()
# ───────────────────────────────────────────────────────────────────

target_include_directories(appsynth PRIVATE rtaudio)
target_link_libraries(appsynth PRIVATE Qt6::Quick dsp wrappers)

set_target_properties(appsynth PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS appsynth
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
