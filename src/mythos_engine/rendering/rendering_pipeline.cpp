#include <display_manager.hpp>
#include <rendering_pipeline.hpp>

#include <iostream>
#include <vector>

// Temporary vertex shader source
const char* vertex_shader_source = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

// Temporary fragment shader source
const char* fragement_shader_source = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

// Temporary vertex data
const float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

std::vector<void (*)() > should_close_callbacks;

GLuint shader_program;
GLuint VAO;

void* main_window;
void* console_window;
    
void rendering_rendering_pipeline_init() {
    // I am displeased that I can't use #region here.
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }
    
    // Creating windows
    main_window = rendering_display_manager_create_window(800, 600, "Mythonomicon");
    console_window = rendering_display_manager_create_window(500, 300, "Debugger");

    // Checking if windows were created successfully
    if (!rendering_display_manager_successfully_created_window(main_window) || !rendering_display_manager_successfully_created_window(console_window)) {
        std::cerr << "Main window creation success: " << rendering_display_manager_successfully_created_window(main_window) << std::endl;
        std::cerr << "Console window creation success: " << rendering_display_manager_successfully_created_window(console_window) << std::endl;
        std::cerr << "Failed to create main window" << std::endl;
        return;
    }

    // Making the main window the current context
    rendering_display_manager_make_context_current(main_window);

    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return;
    }

    // Set frame buffer to main window
    rendering_display_manager_set_frame_buffer(main_window);

    // Compile vertext shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);

    // compile fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragement_shader_source, nullptr);
    glCompileShader(fragment_shader);

    // create shader program
    shader_program = glCreateProgram();

    // attach shaders to program
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // delete shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // create vertex array object
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind vertex array object
    glBindVertexArray(VAO);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Add_On_Should_Close(void (*callback)()) {
    should_close_callbacks.push_back(callback);
}

void On_Should_Close() {
    for (auto callback : should_close_callbacks) {
        callback();
    }
}

void rendering_rendering_pipeline_render_frame() {
    // Clear the color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw triangle
    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap front and back buffers
    rendering_display_manager_render_frame();

    if (rendering_display_manager_should_close()) {
        On_Should_Close();
    }
}

void rendering_rendering_pipeline_shutdown() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shader_program);

    rendering_display_manager_delete_window(main_window);
    rendering_display_manager_delete_window(console_window);
    
    glfwTerminate();
}