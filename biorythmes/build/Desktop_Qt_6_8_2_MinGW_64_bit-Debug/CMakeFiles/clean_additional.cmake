# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\biorythms_take5_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\biorythms_take5_autogen.dir\\ParseCache.txt"
  "biorythms_take5_autogen"
  )
endif()
