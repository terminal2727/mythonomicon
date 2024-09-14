#include <display_manager.hpp>
#include <type_registry.hpp>
#include <iostream>

struct WindowManager {
    GLFWwindow* window;
    int width, height;
    int type_tag;
    const char* title;

    WindowManager(int width, int height, const char* title) : width(width), height(height), title(title) { 
        
        type_tag = type_registry_get_type_tag<WindowManager>(); 
    }
};

WindowManager* frame_buffer = nullptr;

void* rendering_display_manager_create_window(int width, int height, const char* title) {
    WindowManager* window_manager = new WindowManager(width, height, title);
    window_manager->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    return window_manager;
}

bool rendering_display_manager_successfully_created_window(void* window) {
    WindowManager* window_manager = nullptr;
    if (!is_type_of<WindowManager>(window, &window_manager)) { return false; }
    return window_manager->window != nullptr;
}

void rendering_display_manager_make_context_current(void* window) {
    WindowManager* window_manager = nullptr;
    if (!is_type_of<WindowManager>(window, &window_manager)) { return; }
    glfwMakeContextCurrent(window_manager->window);
}

void rendering_display_manager_set_frame_buffer(void* window) {
    WindowManager* window_manager = nullptr;
    if (!is_type_of<WindowManager>(window, &window_manager)) { return; }
    frame_buffer = window_manager;
}

void rendering_display_manager_render_frame() {
    if (frame_buffer == nullptr) { return; }
    glfwSwapBuffers(frame_buffer->window);
    glfwPollEvents();
}

bool rendering_display_manager_should_close() {
    if (frame_buffer == nullptr) { return true; }
    return glfwWindowShouldClose(frame_buffer->window);
}

void rendering_display_manager_delete_window(void* window) {
    WindowManager* window_manager = nullptr;
    if (!is_type_of<WindowManager>(window, &window_manager)) { return; }
    
    glfwDestroyWindow(window_manager->window);
    delete window_manager;
}