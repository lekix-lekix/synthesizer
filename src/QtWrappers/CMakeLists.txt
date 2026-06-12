add_library(wrappers STATIC
    QtSynthWrapper.cpp
    QtEnvWrapper.cpp
    # QtOscWrapper.cpp
)

target_include_directories(wrappers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(wrappers PRIVATE dsp Qt6::Quick)