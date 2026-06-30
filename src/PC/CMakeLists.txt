cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(synth_pcbuild mainQt.cpp Synth.cpp Synth.hpp rtaudio/RtAudio.cpp)

target_include_directories(synth_pcbuild PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

qt_add_qml_module(synth_pcbuild
    URI synth
    QML_FILES
        ui/Main.qml
        ui/Vco.qml
        ui/Vca.qml
        ui/Jack.qml
        ui/Env.qml
        ui/VSlider.qml
        ui/Mixer4.qml
        SOURCES Patch.hpp
        QML_FILES ui/ModulesMenu.qml
)

add_subdirectory(QtWrappers)

# ─── RtAudio backend ───────────────────────────────────────────────
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(PULSE libpulse-simple)
    pkg_check_modules(ALSA alsa)

    if(PULSE_FOUND)
        message(STATUS "RtAudio backend: PulseAudio")
        target_compile_definitions(synth_pcbuild PRIVATE __LINUX_PULSE__)
        target_include_directories(synth_pcbuild PRIVATE ${PULSE_INCLUDE_DIRS})
        target_link_libraries(synth_pcbuild PRIVATE ${PULSE_LIBRARIES})
    elseif(ALSA_FOUND)
        message(STATUS "RtAudio backend: ALSA")
        target_compile_definitions(synth_pcbuild PRIVATE __LINUX_ALSA__)
        target_include_directories(synth_pcbuild PRIVATE ${ALSA_INCLUDE_DIRS})
        target_link_libraries(synth_pcbuild PRIVATE ${ALSA_LIBRARIES})
    else()
        message(FATAL_ERROR "Aucun backend audio trouvé")
    endif()
elseif(APPLE)
    message(STATUS "RtAudio backend: CoreAudio")
    target_compile_definitions(synth_pcbuild PRIVATE __MACOSX_CORE__)
    target_link_libraries(synth_pcbuild PRIVATE "-framework CoreAudio" "-framework CoreFoundation")
elseif(WIN32)
    message(STATUS "RtAudio backend: WASAPI")
    target_compile_definitions(synth_pcbuild PRIVATE __WINDOWS_WASAPI__)
    target_link_libraries(synth_pcbuild PRIVATE ole32 winmm ksuser mfplat mf mfuuid wmcodecdspuuid)
endif()
# ───────────────────────────────────────────────────────────────────

target_include_directories(synth_pcbuild PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    rtaudio
)

target_link_libraries(synth_pcbuild PRIVATE Qt6::Quick dsp wrappers)

set_target_properties(synth_pcbuild PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS synth_pcbuild
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
