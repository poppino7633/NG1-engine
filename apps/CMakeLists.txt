add_executable(app main.cpp)

target_link_libraries(app PRIVATE Engine)
target_compile_definitions(app PUBLIC 
    $<$<CONFIG:Debug>:
        DEBUG=1
    >
)
