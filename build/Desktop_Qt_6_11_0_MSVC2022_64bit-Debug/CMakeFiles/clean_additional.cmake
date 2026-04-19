# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Susovan_Image_Editor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Susovan_Image_Editor_autogen.dir\\ParseCache.txt"
  "Susovan_Image_Editor_autogen"
  )
endif()
