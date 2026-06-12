# cmake_minimum_required(VERSION 3.16)

# project(synth VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Qt6 REQUIRED COMPONENTS Quick)

# qt_standard_project_setup(REQUIRES 6.10)

# file(GLOB_RECURSE HEADERS includes/*.hpp)

# qt_add_executable(appsynth
#     main.cpp
#     rtaudio/RtAudio.cpp
#     src/AudioModule.cpp
#     src/Envelope.cpp
#     src/Osc.cpp
#     src/Synth.cpp
#     src/Vca.cpp
#     src/Mixer_4.cpp
#     src/Modulator.cpp
# )

# qt_add_qml_module(appsynth
#     URI synth
#     QML_FILES
#         Main.qml
#         SOURCES QtSynthWrapper.h QtSynthWrapper.cpp
# )

# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# set_target_properties(appsynth PROPERTIES
# #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appsynth
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# target_include_directories(appsynth PRIVATE includes)

# target_sources(appsynth PRIVATE ${HEADERS})

# target_link_libraries(appsynth
#     PRIVATE Qt6::Quick
# )

# install(TARGETS appsynth
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# cmake_minimum_required(VERSION 3.16)
# project(synth VERSION 0.1 LANGUAGES CXX)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Qt6 REQUIRED COMPONENTS Quick)
# qt_standard_project_setup(REQUIRES 6.10)

# file(GLOB_RECURSE HEADERS includes/*.hpp)

# qt_add_executable(appsynth
#     main.cpp
#     rtaudio/RtAudio.cpp
#     src/AudioModule.cpp
#     src/Envelope.cpp
#     src/Osc.cpp
#     src/Synth.cpp
#     src/Vca.cpp
#     src/Mixer_4.cpp
#     src/Modulator.cpp
# )

# qt_add_qml_module(appsynth
#     URI synth
#     QML_FILES
#         Main.qml
#         SOURCES QtSynthWrapper.hpp QtSynthWrapper.cpp
#         SOURCES QtEnvWrapper.hpp QtEnvWrapper.cpp
# )

# # ─── RtAudio backend ───────────────────────────────────────────────
# if(UNIX AND NOT APPLE)
#     # Linux : on essaie PulseAudio en priorité, puis ALSA
#     find_package(PkgConfig REQUIRED)

#     pkg_check_modules(PULSE libpulse-simple)
#     pkg_check_modules(ALSA alsa)

#     if(PULSE_FOUND)
#         message(STATUS "RtAudio backend: PulseAudio")
#         target_compile_definitions(appsynth PRIVATE __LINUX_PULSE__)
#         target_include_directories(appsynth PRIVATE ${PULSE_INCLUDE_DIRS})
#         target_link_libraries(appsynth PRIVATE ${PULSE_LIBRARIES})
#     elseif(ALSA_FOUND)
#         message(STATUS "RtAudio backend: ALSA")
#         target_compile_definitions(appsynth PRIVATE __LINUX_ALSA__)
#         target_include_directories(appsynth PRIVATE ${ALSA_INCLUDE_DIRS})
#         target_link_libraries(appsynth PRIVATE ${ALSA_LIBRARIES})
#     else()
#         message(FATAL_ERROR "Aucun backend audio trouvé (installez libpulse-dev ou libasound2-dev)")
#     endif()

# elseif(APPLE)
#     message(STATUS "RtAudio backend: CoreAudio")
#     target_compile_definitions(appsynth PRIVATE __MACOSX_CORE__)
#     target_link_libraries(appsynth PRIVATE "-framework CoreAudio" "-framework CoreFoundation")

# elseif(WIN32)
#     message(STATUS "RtAudio backend: WASAPI")
#     target_compile_definitions(appsynth PRIVATE __WINDOWS_WASAPI__)
#     target_link_libraries(appsynth PRIVATE ole32 winmm ksuser mfplat mf mfuuid wmcodecdspuuid)
# endif()
# # ───────────────────────────────────────────────────────────────────

# target_include_directories(appsynth PRIVATE includes rtaudio)
# target_sources(appsynth PRIVATE ${HEADERS})

# target_link_libraries(appsynth PRIVATE Qt6::Quick)

# set_target_properties(appsynth PROPERTIES
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# install(TARGETS appsynth
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

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
