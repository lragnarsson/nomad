cmake_minimum_required(VERSION 3.20)
project(nomad)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH "/Users/lage/Development/cmake/Modules/;${CMAKE_MODULE_PATH}")
set(GLSLC /Users/lage/VulkanSDK/1.2.189.0/macOS/bin/glslc)

# Find all cpp source files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp)
message(STATUS "Found Source files:\n ${SOURCE_FILES}")

# Find all cpp header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h)
message(STATUS "Found Header files: ${HEADER_FILES}")

# Find all shader files
file(GLOB_RECURSE SHADER_FILES
        ${CMAKE_SOURCE_DIR}/src/genom/shaders/*)
message(STATUS "Found shader files: ${SHADER_FILES}")


# Libraries:
find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

set(LIBS Vulkan::Vulkan glfw glm::glm)
message(STATUS "Found all libraries: ${LIBS}")
include_directories("${CMAKE_SOURCE_DIR}/lib/tinyobjloader")
include_directories("${CMAKE_SOURCE_DIR}/lib/FastNoiseLite")
include_directories("${CMAKE_SOURCE_DIR}/lib/Spline")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS FALSE
        )

######################
#------SHADERS-------#
######################
function(add_shader TARGET SHADER)
    find_program(GLSLC glslc)

    set(current-shader-path ${CMAKE_CURRENT_SOURCE_DIR}/src/genom/shaders/${SHADER})
    set(current-output-path ${CMAKE_BINARY_DIR}/shaders/${SHADER}.spv)

    # Add a custom command to compile GLSL to SPIR-V.
    get_filename_component(current-output-dir ${current-output-path} DIRECTORY)
    file(MAKE_DIRECTORY ${current-output-dir})

    add_custom_command(
            OUTPUT ${current-output-path}
            COMMAND ${GLSLC} ${current-shader-path} -o ${current-output-path}
            DEPENDS ${current-shader-path}
            IMPLICIT_DEPENDS CXX ${current-shader-path}
            VERBATIM)

    # Make sure our build depends on this output.
    set_source_files_properties(${current-output-path} PROPERTIES GENERATED TRUE)
    target_sources(${TARGET} PRIVATE ${current-output-path})
endfunction(add_shader)

foreach (shader ${SHADER_FILES})
    get_filename_component(p ${shader} NAME)
    message(STATUS "Building shader ${p}, ${TARGET}")
    add_shader(${PROJECT_NAME} ${p})
endforeach ()
