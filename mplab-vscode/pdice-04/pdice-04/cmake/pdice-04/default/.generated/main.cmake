include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(pdice_04_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(pdice_04_default_default_XC8_FILE_TYPE_assemble)
add_library(pdice_04_default_default_XC8_assemble OBJECT ${pdice_04_default_default_XC8_FILE_TYPE_assemble})
    pdice_04_default_default_XC8_assemble_rule(pdice_04_default_default_XC8_assemble)
    list(APPEND pdice_04_default_library_list "$<TARGET_OBJECTS:pdice_04_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(pdice_04_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(pdice_04_default_default_XC8_assemblePreprocess OBJECT ${pdice_04_default_default_XC8_FILE_TYPE_assemblePreprocess})
    pdice_04_default_default_XC8_assemblePreprocess_rule(pdice_04_default_default_XC8_assemblePreprocess)
    list(APPEND pdice_04_default_library_list "$<TARGET_OBJECTS:pdice_04_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(pdice_04_default_default_XC8_FILE_TYPE_compile)
add_library(pdice_04_default_default_XC8_compile OBJECT ${pdice_04_default_default_XC8_FILE_TYPE_compile})
    pdice_04_default_default_XC8_compile_rule(pdice_04_default_default_XC8_compile)
    list(APPEND pdice_04_default_library_list "$<TARGET_OBJECTS:pdice_04_default_default_XC8_compile>")

endif()


# Main target for this project
add_executable(pdice_04_default_image_UJ58F_rH ${pdice_04_default_library_list})

set_target_properties(pdice_04_default_image_UJ58F_rH PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${pdice_04_default_output_dir}")
target_link_libraries(pdice_04_default_image_UJ58F_rH PRIVATE ${pdice_04_default_default_XC8_FILE_TYPE_link})
# Add the link options from the rule file.
pdice_04_default_link_rule( pdice_04_default_image_UJ58F_rH)



