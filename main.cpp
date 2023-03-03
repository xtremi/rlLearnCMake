#include <iostream>
#include "useless.h"
#include "GLFW/glfw3.h"

int main()
{
    std::cout << "hello world" << std::endl;
    
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