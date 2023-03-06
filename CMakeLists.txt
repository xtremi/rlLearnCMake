cmake_minimum_required(VERSION 3.10)
project(rlLearnCMake VERSION 1.0)


configure_file(rlLearnCMakeConfig.h.in rlLearnCMakeConfig.h)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

option(USE_USELESS_LIB "Using the useless lib (default = ON)" ON)

if(USE_USELESS_LIB)
    add_subdirectory(useless)

    list(APPEND EXTRA_LIBS useless)
    list(APPEND EXTRA_LIB_DIRS useless)
    list(APPEND EXTRAN_INCLUDE_DIRS useless)
endif()




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

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/glfw/include    
    PUBLIC ${EXTRA_INCLUDE_DIRS})

#not really needed
#target_link_directories(${PROJECT_NAME}     
#    PRIVATE external/glfw/src
#    PRIVATE ${EXTRA_LIB_DIRS})

target_link_libraries(${PROJECT_NAME}
    glfw
    ${EXTRA_LIBS})
