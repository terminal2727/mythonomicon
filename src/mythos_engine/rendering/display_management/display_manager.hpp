#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct DisplayManager {
    static GLFWwindow* main_window;
    static GLFWwindow* console_window;
    static int width, height;
    static int console_width, console_height;
    static const char* title;
};

bool rendering_display_manager_init(int width, int height, const char* title);
bool rendering_display_manager_should_close();
void rendering_display_manager_update_frame();
void rendering_display_manager_shutdown();

#endif // DISPLAY_MANAGER_HPP