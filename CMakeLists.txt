cmake_minimum_required(VERSION 3.10)
project(rlLearnCMake VERSION 2.0)


configure_file(rlLearnCMakeConfig.h.in rlLearnCMakeConfig.h)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

message("CMAKE_SYSTEM_PROCESSOR   = " ${CMAKE_SYSTEM_PROCESSOR})
message("CMAKE_GENERATOR          = " ${CMAKE_GENERATOR})
message("CMAKE_VS_PLATFORM_NAME   = " ${CMAKE_VS_PLATFORM_NAME})
message("CMAKE_BUILD_TYPE         = " ${CMAKE_BUILD_TYPE})
message("CMAKE_SYSTEM             = " ${CMAKE_SYSTEM})
message("CMAKE_SYSTEM_NAME        = " ${CMAKE_SYSTEM_NAME})
message("UNIX                     = " ${UNIX})
message("WIN32                    = " ${WIN32})
message("MSVC                     = " ${MSVC})


message("##################################################")
message("Locating GLEW lib")
message("glew path from environment variable %GLEW%: $ENV{GLEW}")


find_library(glewlib GLEW NAMES 
    glew glew32 glew32s 
    PATHS "$ENV{GLEW}/lib/Release/${CMAKE_VS_PLATFORM_NAME}" #windows
    DOC "glew library" 
    REQUIRED)
    get_filename_component(GLEW_LIB ${glewlib} NAME)
    
get_filename_component(GLEW_LIB_DIR ${glewlib} DIRECTORY)

message("Found GLEW lib: " ${GLEW_LIB} " in " ${GLEW_LIB_DIR})
message("##################################################")

message("##################################################")
message("Locating OpenGL lib")
find_package(OpenGL REQUIRED)
#find_library(gllib GL 
#    NAMES gl opengl openGL
#    DOC "GL library" 
#    REQUIRED)
#get_filename_component(GL_LIB_DIR ${OPENGL_LIBRARIES} DIRECTORY)
#get_filename_component(GL_LIB ${OPENGL_LIBRARIES} NAME)

#message("Found OpenGL lib: " ${GL_LIB} " in " ${GL_LIB_DIR})
message("OPENGL_INCLUDE_DIR = " ${OPENGL_INCLUDE_DIR})
message("OPENGL_glu_LIBRARY = " ${OPENGL_glu_LIBRARY})
message("OPENGL_gl_LIBRARY  = " ${OPENGL_gl_LIBRARY})
message("OPENGL_LIBRARIES   = " ${OPENGL_LIBRARIES})
message("##################################################")

option(USE_USELESS_LIB "Using the useless lib (default = ON)" ON)


#DOWNLOWD GIT SUBMODULES
message("##################################################")
message("Locating GLFW using git submodules")
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}")
        endif()
    endif()

endif()
message("##################################################")


if(USE_USELESS_LIB)
    add_subdirectory(useless)
    list(APPEND EXTRA_LIBS useless)
    list(APPEND EXTRA_LIB_DIRS useless)
    list(APPEND EXTRA_INCLUDE_DIRS useless)
endif()

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/glfw/include    
    PUBLIC ${EXTRA_INCLUDE_DIRS})

if(WIN32)
    target_include_directories(${PROJECT_NAME} 
        PUBLIC "$ENV{GLEW}/include")
endif()

#not really needed
#target_link_directories(${PROJECT_NAME}     
#    PRIVATE external/glfw/src
#    PRIVATE ${EXTRA_LIB_DIRS})

target_link_libraries(${PROJECT_NAME}
    glfw                    #submodule
    ${OPENGL_LIBRARIES}     #opengl found by find_package
    ${glewlib}              #glewlib found by find_library (windows: path by env var, linux installed apt package)
    ${EXTRA_LIBS}           #integrated lib - optional
    )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/rlLearnCMakeConfig.h" DESTINATION include)
if(WIN32)
    install(FILES "$ENV{GLEW}/bin/Release/${CMAKE_VS_PLATFORM_NAME}/glew32.dll" DESTINATION bin)
elseif(UNIX)
    #install(FILES "$ENV{GLEW}/bin/Release/${CMAKE_VS_PLATFORM_NAME}/glew32.dll" DESTINATION bin)
endif()
