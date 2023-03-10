cmake_minimum_required(VERSION 3.10)
project(rlLearnCMake VERSION 2.0)

#options:
option(USE_USELESS_LIB "Using the useless lib (default = ON)" ON)

#to locate FindXXX for custom find_package functions in /cmake
set(CMAKE_MODULE_PATH cmake)
find_package(MyTest) #only prints a message


if(WIN32)
	message("Setting policy CMP0074 to NEW to allow find_package to locate GLEW based on enviroment variable GLEW_ROOT")
	cmake_policy(SET CMP0074 NEW)
	
	#So that includes do not end up as "system include" (In VS as /external:I <dir> as command line arguments)
	set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
endif()

message("CMAKE_SYSTEM_PROCESSOR   = " ${CMAKE_SYSTEM_PROCESSOR})
message("CMAKE_GENERATOR          = " ${CMAKE_GENERATOR})
message("CMAKE_VS_PLATFORM_NAME   = " ${CMAKE_VS_PLATFORM_NAME})
message("CMAKE_BUILD_TYPE         = " ${CMAKE_BUILD_TYPE})
message("CMAKE_SYSTEM             = " ${CMAKE_SYSTEM})
message("CMAKE_SYSTEM_NAME        = " ${CMAKE_SYSTEM_NAME})
message("UNIX                     = " ${UNIX})
message("WIN32                    = " ${WIN32})
message("MSVC                     = " ${MSVC})

configure_file(rlLearnCMakeConfig.h.in rlLearnCMakeConfig.h)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})


message(STATUS "Locating glew using find_package")
set(GLEW_VERBOSE ON)
find_package(GLEW REQUIRED)
message(STATUS "Glew found")


message(STATUS "Locating OpenGL using find_package")
find_package(OpenGL REQUIRED)
message("OPENGL_INCLUDE_DIR = " ${OPENGL_INCLUDE_DIR})
message("OPENGL_glu_LIBRARY = " ${OPENGL_glu_LIBRARY})
message("OPENGL_gl_LIBRARY  = " ${OPENGL_gl_LIBRARY})
message("OPENGL_LIBRARIES   = " ${OPENGL_LIBRARIES})
message("##################################################")
message(STATUS "OpenGL found")


message("Locating GLFW using git submodules")
#DOWNLOWD GIT SUBMODULES
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

target_link_libraries(${PROJECT_NAME} PUBLIC 
    glfw                    #submodule
    ${OPENGL_LIBRARIES}     #opengl found by find_package
    ${glewlib}              #glewlib found by find_library (windows: path by env var, linux installed apt package)
    ${EXTRA_LIBS}           #integrated lib - optional
	GLEW::GLEW
    )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/rlLearnCMakeConfig.h" DESTINATION include)
if(WIN32)
    install(FILES "$ENV{GLEW_ROOT}/bin/Release/${CMAKE_VS_PLATFORM_NAME}/glew32.dll" DESTINATION bin)
elseif(UNIX)
    #this does not work well - getting dangling symlink on .so file
    #there is .so.1 file that has something to do with that in GLEW_SHARED_LIBRARY directory
    install(FILES ${GLEW_SHARED_LIBRARY} NAMELINK_COMPONENT DESTINATION bin)
endif()
