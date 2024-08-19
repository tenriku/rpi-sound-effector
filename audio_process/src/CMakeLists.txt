add_library(dsp
  SHARED
    ${PROJECT_SOURCE_DIR}/src/_dsp.cc
    ${PROJECT_SOURCE_DIR}/src/basic.cc
)

target_include_directories(dsp
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
)