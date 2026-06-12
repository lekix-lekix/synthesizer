add_library(dsp STATIC
    Synth.cpp
    AudioModules/AudioModule.cpp
    AudioModules/Mixer_4/Mixer_4.cpp
    AudioModules/Osc/Osc.cpp
    AudioModules/Vca/Vca.cpp
    Modulators/Modulator.cpp
    Modulators/Envelope/Envelope.cpp
)

target_include_directories(dsp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/AudioModules
    ${CMAKE_CURRENT_SOURCE_DIR}/AudioModules/Mixer_4
    ${CMAKE_CURRENT_SOURCE_DIR}/AudioModules/Osc
    ${CMAKE_CURRENT_SOURCE_DIR}/AudioModules/Vca
    ${CMAKE_CURRENT_SOURCE_DIR}/Modulators
    ${CMAKE_CURRENT_SOURCE_DIR}/Modulators/Envelope
)

