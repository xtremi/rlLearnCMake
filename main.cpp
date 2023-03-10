#include <iostream>
#include "rlLearnCMakeConfig.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"


#ifdef USE_USELESS_LIB
    #include "useless.h"
#endif

#define CheckedGLCall(x) (x)

int main(int argc, char* argv[])
{	
    std::cout << argv[0] << " Version: " 
		<< RL_LEARN_CMAKE_VERSION_MAJOR << "."
		<< RL_LEARN_CMAKE_VERSION_MINOR << std::endl;
    
#ifdef USE_USELESS_LIB
    int i = useless(1);
    std::cout << "useless(1) = " << i << std::endl;
#else
    std::cout << "not using useless lib" << std::endl;
#endif    
   
    if(!glfwInit()){
        std::cout << "glfwInit() failed" << std::endl;
        return 1;
    }

    GLFWwindow* w = glfwCreateWindow(300, 300, "Hello world", nullptr, nullptr);
    if(!w){
        std::cout << "glfwCreateWindow() failed" << std::endl;
        return 1;
    }
	glfwMakeContextCurrent(w);

    GLenum err = glewInit();
    if(err != GLEW_OK){
        std::cout << "glewInit() failed" << std::endl;
        return 1;
    }

    char const * VertexShaderSource = R"GLSL(
		#version 150
		in vec2 position;
		void main()
		{
			gl_Position = vec4(position, 0.0, 1.0);
		}
	)GLSL";

	char const * FragmentShaderSource = R"GLSL(
		#version 150
		out vec4 outColor;
		void main()
		{
			outColor = vec4(1.0, 1.0, 1.0, 1.0);
		}
	)GLSL";


	GLfloat const Vertices [] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint const Elements [] = {
		0, 1, 2
	};

	GLuint VAO;
	CheckedGLCall(glGenVertexArrays(1, & VAO));
	CheckedGLCall(glBindVertexArray(VAO));

	GLuint VBO;
	CheckedGLCall(glGenBuffers(1, & VBO));
	CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	CheckedGLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW));
	CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GLuint EBO;
	CheckedGLCall(glGenBuffers(1, & EBO));
	CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	CheckedGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Elements), Elements, GL_STATIC_DRAW));

	GLint Compiled;
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	CheckedGLCall(glShaderSource(VertexShader, 1, & VertexShaderSource, NULL));
	CheckedGLCall(glCompileShader(VertexShader));
	CheckedGLCall(glGetShaderiv(VertexShader, GL_COMPILE_STATUS, & Compiled));
	if (! Compiled)
	{
		std::cout << "Failed to compile vertex shader!" << std::endl;
        return 1;
	}

	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	CheckedGLCall(glShaderSource(FragmentShader, 1, & FragmentShaderSource, NULL));
	CheckedGLCall(glCompileShader(FragmentShader));
	CheckedGLCall(glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, & Compiled));
	if (! Compiled)
	{
		std::cout << "Failed to compile fragment shader!" << std::endl;
		return 1;
	}

	GLuint ShaderProgram = glCreateProgram();
	CheckedGLCall(glAttachShader(ShaderProgram, VertexShader));
	CheckedGLCall(glAttachShader(ShaderProgram, FragmentShader));
	CheckedGLCall(glBindFragDataLocation(ShaderProgram, 0, "outColor"));
	CheckedGLCall(glLinkProgram(ShaderProgram));
	CheckedGLCall(glUseProgram(ShaderProgram));

	GLint PositionAttribute = glGetAttribLocation(ShaderProgram, "position");
	CheckedGLCall(glEnableVertexAttribArray(PositionAttribute));

	CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	CheckedGLCall(glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0));
	CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	while (! glfwWindowShouldClose(w))
	{
		CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		CheckedGLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));

		glfwSwapBuffers(w);
		glfwPollEvents();
	}

	CheckedGLCall(glDeleteProgram(ShaderProgram));
	CheckedGLCall(glDeleteShader(FragmentShader));
	CheckedGLCall(glDeleteShader(VertexShader));

	CheckedGLCall(glDeleteBuffers(1, & EBO));
	CheckedGLCall(glDeleteBuffers(1, & VBO));
	CheckedGLCall(glDeleteVertexArrays(1, & VAO));



    return 0;
}