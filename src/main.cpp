#include <glad/glad.h> // make sure glad is included before glfw
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// 
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
// 

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    // make window resizable
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Text", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
   
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //start of triangle lecture -->
    //start our rendering pipeline
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // third val is 0 because we are doing 2D triangle right now
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    // Create our buffer
    unsigned int VBO;
    // printf("%d\n", VBO); // before buffer creation --> 0
    glGenBuffers(1, &VBO); // 1 means how many "vertex buffer objects" are we creating
    // printf("%d\n", VBO); // after buffer creation --> 1
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    // Create our "Attribute Buffer"
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);



    // Send data to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // we send vertices once so use gl_static_draw


    // Create our vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader); // compile shader

    // Create our fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Attach our shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Tell OpenGL to use it
    glUseProgram(shaderProgram);

    // Cleanup time
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    // Specify our vertex attributes
    //aka how to interpret our vertices from before
    //first line is like laying out the ingredients and the second line is actually "cooking" or "enabling"

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // first param: location of vertex attribute
    // second param: size of vertex attributes
    // 3 * sizeof(float): the stride
    glEnableVertexAttribArray(0); // we need to enable slot 0



    // we need a infinite lloop to keep the window open
    while (!glfwWindowShouldClose(window)){
        
        // clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // makes the window slightly green
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3); // ***

        glfwSwapBuffers(window);
        glfwPollEvents();
    }




    glfwTerminate();
    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}