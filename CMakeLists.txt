cmake_minimum_required(VERSION 3.22)
project(OpenGLStudy)

set(CMAKE_CXX_STANDARD 11)

#文件头
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/imgui)
include_directories(${PROJECT_SOURCE_DIR}/dep/GLEW/include)
include_directories(${PROJECT_SOURCE_DIR}/dep/GLFW/include)
include_directories(${PROJECT_SOURCE_DIR}/src/base)

link_directories(${PROJECT_SOURCE_DIR}/dep/GLEW/lib)
link_directories(${PROJECT_SOURCE_DIR}/dep/GLFW/lib)
link_directories(${PROJECT_SOURCE_DIR}/lib/assimp/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY out)

add_executable(OpenGLStudy main.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_widgets.cpp lib/imgui/imgui_tables.cpp lib/imgui/imconfig.h lib/imgui/imstb_rectpack.h lib/imgui/imgui.cpp lib/imgui/imgui_impl_glfw.h lib/imgui/imgui_demo.cpp lib/imgui/imgui_internal.h lib/imgui/imstb_truetype.h lib/imgui/imstb_textedit.h lib/imgui/imgui.h lib/imgui/imgui_impl_glfw.cpp lib/imgui/imgui_impl_opengl3.h lib/imgui/imgui_impl_opengl3.cpp src/scene/SceneTriangle.h src/base/ShaderProxy.h)

target_link_libraries(OpenGLStudy opengl32.lib glfw3.lib glew32s.lib assimp.lib)

## copy glsl
#add_custom_command(
#        TARGET ${PROJECT_NAME}
#        PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/glsl/* ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#)

#set(glsl_dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl)
#execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${glsl_dir})
#execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory -f ${PROJECT_SOURCE_DIR}/glsl ${glsl_dir})
