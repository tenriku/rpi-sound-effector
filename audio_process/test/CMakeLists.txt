add_executable(AudioProcess main.cc)
target_include_directories(AudioProcess
  PUBLIC
    main.hh
)
target_link_libraries(AudioProcess
  PUBLIC
    config
)

add_library(SharedAudioProcess
  SHARED
    main.cc
)
target_include_directories(SharedAudioProcess
  PUBLIC
    main.hh
)
target_link_libraries(SharedAudioProcess
  PUBLIC
    config
)
