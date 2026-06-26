add_library(dsp STATIC
    AudioModules/Mixer_4/Mixer_4.cpp
    AudioModules/Vco/Vco.cpp
    AudioModules/Vca/Vca.cpp
    Modulators/Env/Env.cpp
)

target_sources(dsp PRIVATE
    constants.hpp
    AudioModules/AudioModule.hpp
    AudioModules/Vco/Vco.hpp
    AudioModules/Vca/Vca.hpp
    AudioModules/Mixer_4/Mixer_4.hpp
    Modulators/Env/Env.hpp
    dsp.hpp
)

target_include_directories(dsp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)