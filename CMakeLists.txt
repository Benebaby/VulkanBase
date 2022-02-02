cmake_minimum_required(VERSION 3.7)
project(VulkanBase VERSION 1.0.0)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
IF(APPLE)
    add_definitions(-Wno-nullability-completeness)
    add_definitions(-Wno-deprecated)
ENDIF()


add_compile_definitions(SHADER_PATH="${PROJECT_SOURCE_DIR}/src/shaders" TEXTURE_PATH="${PROJECT_SOURCE_DIR}/assets/textures" MODEL_PATH="${PROJECT_SOURCE_DIR}/assets/models" ASSET_PATH="${PROJECT_SOURCE_DIR}/assets")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
ENDIF()

file(GLOB SOURCES
    src/*.h
    src/*.hpp
    src/*.cpp
    lib/imgui/*.cpp
    lib/imgui/*.h
    lib/imgui/backends/imgui_impl_glfw.h
    lib/imgui/backends/imgui_impl_glfw.cpp
    lib/imgui/backends/imgui_impl_vulkan.h
    lib/imgui/backends/imgui_impl_vulkan.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

#add vulkan
find_package(Vulkan REQUIRED)
IF (Vulkan_FOUND)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Vulkan_LIBRARIES})
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIR})
ELSE()
    message(ERROR "Vulkan SDK has to be installed")
ENDIF()


#add glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

#add glm
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glm)
target_link_libraries(${CMAKE_PROJECT_NAME} glm)

#add vma
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/VulkanMemoryAllocator)
target_link_libraries(${CMAKE_PROJECT_NAME} VulkanMemoryAllocator)

#add tinygltf
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/tinygltf)
target_link_libraries(${CMAKE_PROJECT_NAME} tinygltf)

#add imgui, stb
include_directories(${PROJECT_SOURCE_DIR}/lib/imgui)
include_directories(${PROJECT_SOURCE_DIR}/lib/imgui/backends)
include_directories(${PROJECT_SOURCE_DIR}/lib/stb)

#add glslang
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glslang)
target_link_libraries(${CMAKE_PROJECT_NAME} glslang SPIRV)

# add gdcm
# FIND_PACKAGE(GDCM CONFIG REQUIRED PATHS ${PROJECT_SOURCE_DIR}/lib/gdcm)
set(GDCM_BUILD_TESTING OFF)
set(GDCM_DOCUMENTATION OFF)
set(GDCM_BUILD_EXAMPLES OFF)
set(GDCM_WRAP_PYTHON OFF)
set(GDCM_WRAP_CSHARP OFF)
set(GDCM_WRAP_JAVA OFF)
set(GDCM_WRAP_PHP OFF)
set(GDCM_USE_VTK OFF)

# set(GDCM_BUILD_APPLICATIONS ON)
# set(GDCM_BUILD_SHARED_LIBS ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/gdcm)
include_directories(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_SOURCE_DIR}/Source/MessageExchangeDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Utilities"
)

SET(GDCM_LIBRARIES 
    gdcmcharls
    gdcmCommon
    gdcmDICT
    gdcmDSED
    gdcmexpat
    # gdcmgetopt
    gdcmIOD
    gdcmjpeg12
    gdcmjpeg16 
    gdcmjpeg8
    gdcmMEXD
    gdcmMSFF
    # gdcmopenjpeg
    # gdcmzlib
    socketxx
    # vtkgdcm
    Rpcrt4) 
# das linken war das eigentlich Problem gewesen. Die libraries waren vorhanden, aber es wurde nicht korrekt eingebunden
target_link_libraries(${CMAKE_PROJECT_NAME} ${GDCM_LIBRARIES})
