add_library(wrappers STATIC
    QtSynthWrapper.cpp
    QtEnvWrapper.cpp
    QtVcoWrapper.cpp
    QtVcaWrapper.cpp
    QtMixer4Wrapper.cpp
    QtWrappers.hpp
)

target_sources(wrappers PRIVATE
    QtEnvWrapper.hpp
    QtSynthWrapper.hpp
    QtVcoWrapper.hpp
    QtVcaWrapper.hpp
    QtMixer4Wrapper.hpp
)

target_include_directories(wrappers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(wrappers PUBLIC
    dsp
    Qt6::Quick
)