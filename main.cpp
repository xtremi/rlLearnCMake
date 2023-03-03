#include <iostream>
#include "useless.h"
#include "GLFW/glfw3.h"
#include "rlLearnCMakeConfig.h"
int main(int argc, char* argv[])
{	
    std::cout << argv[0] << " Version: " 
		<< RL_LEARN_CMAKE_VERSION_MAJOR << "."
		<< RL_LEARN_CMAKE_VERSION_MINOR << std::endl;
    
    int i = useless(1);
    std::cout << "useless(1) = " << i << std::endl;
    
   
    if(!glfwInit()){
        std::cout << "glfwInit() failed" << std::endl;
        return 1;
    }

    GLFWwindow* w = glfwCreateWindow(300, 300, "Hello world", nullptr, nullptr);
    if(!w){
        std::cout << "glfwCreateWindow() failed" << std::endl;
        return 1;
    }

    while(!glfwWindowShouldClose(w)){
        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}