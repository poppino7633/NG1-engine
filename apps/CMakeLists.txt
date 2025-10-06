
file(GLOB SOURCE_LIST "./*.cpp" "./primitives/*.cpp" "./*.c")

add_executable(app ${SOURCE_LIST} )

target_link_libraries(app PRIVATE Engine)
target_compile_definitions(app PUBLIC 
    $<$<CONFIG:Debug>:
        DEBUG=1
    >
)

add_custom_command( 
  TARGET app POST_BUILD
  COMMAND $(CMAKE_COMMAND) -E copy_directory
    $(CMAKE_SOURCE_DIR)/apps/shaders $<TARGET_FILE_DIR:app>/shaders
  COMMENT "Copying shaders" VERBATIM
)
