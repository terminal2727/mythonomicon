#include <display_manager.hpp>
#include <iostream>

GLFWwindow* DisplayManager::main_window = nullptr;
GLFWwindow* DisplayManager::console_window = nullptr;
int DisplayManager::width = 0;
int DisplayManager::height = 0;
int DisplayManager::console_width = 500;
int DisplayManager::console_height = 300;
const char* DisplayManager::title = "Mythonomicon";

bool rendering_display_manager_init(int width, int height, const char* title) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Set DisplayManager properties
    DisplayManager::width = width;
    DisplayManager::height = height;
    DisplayManager::title = title;
    DisplayManager::console_width = 500;
    DisplayManager::console_height = 300;

    // Create a windowed mode window and OpenGL context
    DisplayManager::main_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    
    if (!DisplayManager::main_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Create a console window
    DisplayManager::console_window = glfwCreateWindow(DisplayManager::console_width, DisplayManager::console_height, "Console", nullptr, nullptr);
    
    if (!DisplayManager::console_window) {
        std::cerr << "Failed to create console window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Set the window title
    glfwSetWindowTitle(DisplayManager::main_window, title);
    glfwSetWindowTitle(DisplayManager::console_window, "Mythonomicon Debugger");

    // Make the window's context current
    glfwMakeContextCurrent(DisplayManager::main_window);

    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return false;
    }

    return true;
}

bool rendering_display_manager_should_close() {
    return glfwWindowShouldClose(DisplayManager::main_window);
}

void rendering_display_manager_update_frame() {
    // Swap front and back buffers
    glfwSwapBuffers(DisplayManager::main_window);
    
    // Poll for and process events
    glfwPollEvents();
}

void rendering_display_manager_shutdown() {
    // Clean up and exit
    glfwDestroyWindow(DisplayManager::console_window);
    glfwDestroyWindow(DisplayManager::main_window);

    glfwTerminate();
}