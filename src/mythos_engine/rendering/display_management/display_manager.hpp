#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void* rendering_display_manager_create_window(int width, int height, const char* title);

bool rendering_display_manager_successfully_created_window(void* window);
bool rendering_display_manager_should_close();

void rendering_display_manager_make_context_current(void* window);
void rendering_display_manager_set_frame_buffer(void* window);
void rendering_display_manager_render_frame();
void rendering_display_manager_delete_window(void* window);

#endif // DISPLAY_MANAGER_HPP