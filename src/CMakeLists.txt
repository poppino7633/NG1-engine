file(GLOB HEADER_LIST "${NG1_SOURCE_DIR}/include/modern/*.hpp")
file(GLOB SOURCE_LIST "./*.cpp" "./*.c")

add_library(Engine SHARED ${SOURCE_LIST} ${HEADER_LIST})

target_compile_definitions(Engine PUBLIC 
    $<$<CONFIG:Debug>:
        DEBUG=1
    >
)

target_include_directories(Engine PUBLIC ../include ../extern/glfw/include ../extern/glm/glm)
target_link_libraries(Engine PUBLIC glfw glm)
