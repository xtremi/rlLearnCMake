#include <iostream>
#include "useless.h"

int main()
{
    std::cout << "hello world" << std::endl;
    
    int i = useless(1);
    std::cout << "useless(1) = " << i << std::endl;

    return 0;
}