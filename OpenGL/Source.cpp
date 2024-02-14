#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_s.h"
#include "stb_image.h"

using namespace std;

#define MAX_IMAGE_COUNT 5

#pragma region Init_Variables

GLFWwindow* window;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int VBO, VAO, EBO;
unsigned int textureOneID;
unsigned int textureAID, textureBID;

Shader ourShader;

unsigned int currIndex = 1;
unsigned int orientation = 1;

#pragma endregion

#pragma region Geometry_Data

float vertices[] = {
    // positions          // colors           // texture coords
     0.9f,  0.9f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.9f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.9f, -0.9f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.9f,  0.9f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};
unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

#pragma endregion



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int WindowInit()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return 0;
}

int GLLibInit()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    return 0;
}

void CreateGeometry()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void InitTexture()
{
    glGenTextures(1, &textureOneID);
}

const char* imagePaths[MAX_IMAGE_COUNT] = {
	"Images/image1.jpg",
	"Images/image2.jpg",
	"Images/image3.jpg",
	"Images/image4.jpg",
	"Images/image5.jpg"
};

void LoadTextureData(int imageIndex)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureOneID);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(imagePaths[imageIndex - 1], &width, &height, &nrChannels, 0);

    if (data)
    {
        cout << "Loaded texture: " << imagePaths[imageIndex - 1] << "(" << width << "x" << height << ")" << endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }

    stbi_image_free(data);
}

void LoadTextureData_Simultaneous(int texID, int texUnit, int imageIndex)
{
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, texID);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(imagePaths[imageIndex - 1], &width, &height, &nrChannels, 0);

    if (data)
    {
        cout << "Loaded texture: " << imagePaths[imageIndex - 1] << "(" << width << "x" << height << ")" << endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }

    stbi_image_free(data);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        /*currIndex--;
        if (currIndex < 1)
            currIndex = MAX_IMAGE_COUNT;

        LoadTextureData(currIndex);*/

        orientation--;
        if (currIndex < 1)
            currIndex = 4;

        glUniform1i(glGetUniformLocation(ourShader.ID, "orientation"), orientation);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        /*currIndex++;
        if (currIndex > MAX_IMAGE_COUNT)
            currIndex = 1;

        LoadTextureData(currIndex);*/

        orientation++;
        if (currIndex > 4)
            currIndex = 1;

        glUniform1i(glGetUniformLocation(ourShader.ID, "orientation"), orientation);
    }
}

int main()
{
    if (WindowInit() == -1) return -1;

    if (GLLibInit() == -1)  return -1;

    ourShader.ShaderInit("vshader.vs", "fshader.fs");
    
    ourShader.use();

    CreateGeometry();
    //InitTexture();
    //LoadTextureData(currIndex);

    glGenTextures(1, &textureAID);
    LoadTextureData_Simultaneous(textureAID, GL_TEXTURE0, 1);

    glGenTextures(1, &textureBID);
    LoadTextureData_Simultaneous(textureBID, GL_TEXTURE1, 3);

    glUniform1i(glGetUniformLocation(ourShader.ID, "textureA"), 0);
    glUniform1i(glGetUniformLocation(ourShader.ID, "textureB"), 1);
    glUniform1i(glGetUniformLocation(ourShader.ID, "orientation"), orientation);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}