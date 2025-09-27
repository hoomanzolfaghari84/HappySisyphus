//// cube.cpp
//// Build with: g++ cube.cpp -o cube -lglfw -ldl -lGL    (Linux example)
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <iostream>
//#include <string>
//#include <vector>
//
//// Simple shader helper (compile & link)
//GLuint compileShader(GLenum type, const char* src) {
//    GLuint s = glCreateShader(type);
//    glShaderSource(s, 1, &src, nullptr);
//    glCompileShader(s);
//    GLint ok;
//    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
//    if (!ok) {
//        char buf[1024]; glGetShaderInfoLog(s, 1024, nullptr, buf);
//        std::cerr << "Shader compile error: " << buf << std::endl;
//        return 0;
//    }
//    return s;
//}
//GLuint makeProgram(const char* vsSrc, const char* fsSrc) {
//    GLuint vs = compileShader(GL_VERTEX_SHADER, vsSrc);
//    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSrc);
//    if (!vs || !fs) return 0;
//    GLuint prog = glCreateProgram();
//    glAttachShader(prog, vs);
//    glAttachShader(prog, fs);
//    glLinkProgram(prog);
//    GLint ok; glGetProgramiv(prog, GL_LINK_STATUS, &ok);
//    if (!ok) {
//        char buf[1024]; glGetProgramInfoLog(prog, 1024, nullptr, buf);
//        std::cerr << "Program link error: " << buf << std::endl;
//        return 0;
//    }
//    glDeleteShader(vs);
//    glDeleteShader(fs);
//    return prog;
//}
//
//// Vertex + fragment shaders (GLSL)
//const char* vertexShaderSrc = R"glsl(
//#version 330 core
//layout(location = 0) in vec3 aPos;
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 proj;
//void main() {
//    gl_Position = proj * view * model * vec4(aPos, 1.0);
//}
//)glsl";
//
//const char* fragmentShaderSrc = R"glsl(
//#version 330 core
//out vec4 FragColor;
//uniform vec3 colorIn;
//void main() {
//    FragColor = vec4(colorIn, 1.0);
//}
//)glsl";
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//    glViewport(0, 0, width, height);
//}
//
//int main() {
//    // init GLFW
//    if (!glfwInit()) return -1;
//    // ask for OpenGL 3.3 core
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    GLFWwindow* window = glfwCreateWindow(800, 600, "Cube", nullptr, nullptr);
//    if (!window) { glfwTerminate(); return -1; }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // load OpenGL functions via GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cerr << "Failed to init GLAD\n";
//        return -1;
//    }
//
//    // enable depth testing (very important)
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//
//    // cube data: 8 unique vertices, use indices for 12 triangles (36 indices)
//    float vertices[] = {
//        // positions
//        -0.5f, -0.5f, -0.5f, // 0
//         0.5f, -0.5f, -0.5f, // 1
//         0.5f,  0.5f, -0.5f, // 2
//        -0.5f,  0.5f, -0.5f, // 3
//        -0.5f, -0.5f,  0.5f, // 4
//         0.5f, -0.5f,  0.5f, // 5
//         0.5f,  0.5f,  0.5f, // 6
//        -0.5f,  0.5f,  0.5f  // 7
//    };
//    unsigned int indices[] = {
//        // back face
//        0,1,2, 2,3,0,
//        // front face
//        4,5,6, 6,7,4,
//        // left face
//        4,0,3, 3,7,4,
//        // right face
//        1,5,6, 6,2,1,
//        // bottom face
//        4,5,1, 1,0,4,
//        // top face
//        3,2,6, 6,7,3
//    };
//
//    // VAO VBO EBO
//    GLuint VAO, VBO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glBindVertexArray(0);
//
//    GLuint program = makeProgram(vertexShaderSrc, fragmentShaderSrc);
//    if (!program) {
//        std::cerr << "Shader program failed\n";
//        return -1;
//    }
//
//    // get uniform locations
//    GLint uniModel = glGetUniformLocation(program, "model");
//    GLint uniView = glGetUniformLocation(program, "view");
//    GLint uniProj = glGetUniformLocation(program, "proj");
//    GLint uniColor = glGetUniformLocation(program, "colorIn");
//
//    // camera / projection setup
//    int width = 800, height = 600;
//    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
//    glm::vec3 camPos(2.0f, 2.0f, 2.0f);
//    glm::mat4 view = glm::lookAt(camPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//    // gl state
//    glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
//
//    // render loop
//    while (!glfwWindowShouldClose(window)) {
//        // input
//        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
//
//        // clear color and depth buffers
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // update projection if window resized
//        int w, h;
//        glfwGetFramebufferSize(window, &w, &h);
//        if (w != width || h != height) {
//            width = w; height = h;
//            glViewport(0, 0, width, height);
//            proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
//        }
//
//        // animate model
//        float t = (float)glfwGetTime();
//        glm::mat4 model = glm::rotate(glm::mat4(1.0f), t * glm::radians(30.0f), glm::vec3(0.4f, 1.0f, 0.2f));
//
//        // draw
//        glUseProgram(program);
//        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
//        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
//        glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
//        glUniform3f(uniColor, 0.7f, 0.35f, 0.2f);
//
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//        // swap
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // cleanup
//    glDeleteProgram(program);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    glDeleteVertexArrays(1, &VAO);
//    glfwTerminate();
//    return 0;
//}
