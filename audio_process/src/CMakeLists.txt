add_library(config
  SHARED
    ${PROJECT_SOURCE_DIR}/src/config.cc
    ${PROJECT_SOURCE_DIR}/src/basic.cc
)

target_include_directories(config
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
)