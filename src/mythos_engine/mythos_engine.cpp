#include <mythos_engine.hpp>
#include <display_manager.hpp>

// This won't depend on display_manager.hpp eventually, it's just for testing
// how I'll get the shutdown command from the window to the engine? that's for future me to figure out

// This is the entry point for the engine
// This function is called once at the beginning of the program
void mythos_engine_init() {
    if (!rendering_display_manager_init(800, 600, "Mythonomicon")) {
        return;
    }
}

// will eventually take in a delta time parameter
bool mythos_engine_tick() {
    rendering_display_manager_update_frame();
    return !rendering_display_manager_should_close();
}

void mythos_engine_shutdown() {
    rendering_display_manager_shutdown();
}