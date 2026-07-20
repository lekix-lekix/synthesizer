cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(synth_pcbuild mainQt.cpp Synth.cpp Synth.hpp rtaudio/RtAudio.cpp)

# set(QML_IMPORT_PATH ${CMAKE_BINARY_DIR}/ui/qml/modules/ CACHE STRING "" FORCE)
list(APPEND QML_IMPORT_PATH "${CMAKE_SOURCE_DIR}/ui/qml/modules")
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} CACHE STRING "" FORCE)

set(CMAKE_AUTOMOC ON)

target_include_directories(synth_pcbuild PRIVATE
    ui
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(qml_singletons
    ui/qml/singletons/CablesSingleton.qml
    ui/qml/singletons/CanvasSingleton.qml
)

set(qml_modules
    ui/qml/modules/Vco.qml
    ui/qml/modules/Vca.qml
    ui/qml/modules/Jack.qml
    ui/qml/modules/Env.qml
    ui/qml/modules/VSlider.qml
    ui/qml/modules/Mixer4.qml
    ui/qml/modules/ModulesMenu.qml
)

set(js_files
    ui/js/cables.js
)

set_source_files_properties(${qml_singletons}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(synth_pcbuild
    URI synth
    QML_FILES
        ${qml_singletons}
        ${qml_modules}
        ${js_files}
        ui/qml/Main.qml
    SOURCES
        Patch.hpp
        ui/InputHandler.hpp
        ui/InputHandler.cpp
        QML_FILES ui/qml/modules/Knob.qml
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
