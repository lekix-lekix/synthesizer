file(REMOVE_RECURSE
  "DrawDemo/main.qml"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/drawdemo_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
