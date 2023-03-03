#include <iostream>
#include "useless.h"
#include "GLFW/glfw3.h"

int main()
{
    std::cout << "hello world" << std::endl;
    
    int i = useless(1);
    std::cout << "useless(1) = " << i << std::endl;
    
    GLFWwindow* w = nullptr;


    return 0;
}