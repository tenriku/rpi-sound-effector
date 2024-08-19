CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(audio_process CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(portaudio REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(AudioProcess
  PRIVATE
    portaudio
)

target_link_libraries(SharedAudioProcess
  PRIVATE
    portaudio
)