# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appsynth_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appsynth_autogen.dir/ParseCache.txt"
  "appsynth_autogen"
  "src/QtWrappers/CMakeFiles/wrappers_autogen.dir/AutogenUsed.txt"
  "src/QtWrappers/CMakeFiles/wrappers_autogen.dir/ParseCache.txt"
  "src/QtWrappers/wrappers_autogen"
  "src/dsp/CMakeFiles/dsp_autogen.dir/AutogenUsed.txt"
  "src/dsp/CMakeFiles/dsp_autogen.dir/ParseCache.txt"
  "src/dsp/dsp_autogen"
  )
endif()
