# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Fbschedular_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Fbschedular_autogen.dir\\ParseCache.txt"
  "Fbschedular_autogen"
  )
endif()
