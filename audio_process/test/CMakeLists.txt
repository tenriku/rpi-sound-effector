add_executable(AudioProcess main.cc)
target_link_libraries(AudioProcess
  PRIVATE
    dsp
)

add_library(SharedAudioProcess
  SHARED
    main.cc
)
target_link_libraries(SharedAudioProcess
  PRIVATE
    dsp
)
