file(GLOB HEADER_LIST "${NG1_SOURCE_DIR}/include/modern/*.hpp")
file(GLOB SOURCE_LIST "./*.cpp" "./*.c")

add_library(Engine SHARED ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(Engine PUBLIC ../include ../extern/glfw/include/)
target_link_libraries(Engine PUBLIC glfw)
