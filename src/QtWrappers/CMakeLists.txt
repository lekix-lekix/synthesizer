add_library(wrappers STATIC
    QtSynthWrapper.cpp
    QtEnvWrapper.cpp
    QtOscWrapper.cpp
    QtVcaWrapper.hpp QtVcaWrapper.cpp
    QtMixer4Wrapper.hpp QtMixer4Wrapper.cpp

    # QtOscWrapper.cpp
)

target_sources(wrappers PRIVATE
    QtEnvWrapper.hpp
    QtSynthWrapper.hpp
    QtOscWrapper.hpp
)

target_include_directories(wrappers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(wrappers PRIVATE dsp Qt6::Quick)