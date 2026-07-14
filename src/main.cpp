#include <cmath>
#include <format>
#include <thirdparty/glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <shader.h>
#include <texture.h>
#include <geometry.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // std::cout << "Resized window to: " << width << " - " << height << std::endl;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Shader shader) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        float newValue = std::clamp(shader.getFloat("mixValue") + .01f, 0.0f, 1.0f);
        shader.setFloat("mixValue", newValue);
    }else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        float newValue = std::clamp(shader.getFloat("mixValue") - .01f, 0.0f, 1.0f);
        shader.setFloat("mixValue", newValue);
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Configure GLFW for OpenGL 4.6 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "MyEngine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int VBO_Points, /*VBO_Col,*/ VAO, EBO;

    // float vertices[180] = cubeVertices;

    unsigned int pIndices[] = {
        0,1,3,
        1,2,3
    };

    Shader myShader = Shader(std::string(SHADER_DIR) + "shader.vert", std::string(SHADER_DIR) + "shader.frag");
    Texture wallTexture = Texture("wall.jpg");
    Texture catTexture = Texture("awesomeface.png");

    glGenBuffers(1, &VBO_Points);
    // glGenBuffers(1, &VBO_Col);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Points);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO_Col);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    wallTexture.bind();
    glActiveTexture(GL_TEXTURE1);
    catTexture.bind();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Points);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO_Col);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pIndices), pIndices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    unsigned int transformLoc = glGetUniformLocation(myShader.getID(), "transf");
    glm::mat4 transf = glm::mat4(1.0f);
    // transf = glm::rotate(transf, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // transf = glm::scale(transf, glm::vec3(0.5f, 0.5f, 0.5f));
    float timeValue = .0f;
    // Main Render Loop
    myShader.use();
    myShader.setInt("texture1", 0);
    myShader.setInt("texture2", 1);

    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

    // View matrix
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Perspective Projection matrix
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        timeValue = static_cast<float>(glfwGetTime());
        float greenValue = (sin(timeValue) + 1.0f) / 2.0f;

        // transf = glm::mat4(1.0f);
        // transf = glm::rotate(transf, (float)glfwGetTime() * .5f, glm::vec3(0.0f, 0.0f, 1.0f));
        // transf = glm::translate(transf, glm::vec3(0.2f, 0.2f, 0.0f));
        //
        // // transf = glm::scale(transf, glm::vec3(0.5f, 0.5f, 0.5f));
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transf));

        int modelLoc = glGetUniformLocation(myShader.getID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(myShader.getID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(myShader.getID(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Clear screen with a nice slate blue color
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // input
        processInput(window, myShader);

        // render
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode
        myShader.setFloat("changingColor", greenValue);

        // wallTexture.bind();
        glBindVertexArray(VAO);

        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if (i%3 == 0) {
                angle = (float)glfwGetTime() * 25.0f;
            }
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        // glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
