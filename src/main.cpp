#include <mythos_engine.hpp>
#include <iostream>

int main() {
    std::cout << "Hello, Mythos!" << std::endl;

    mythos_engine_init();

    bool should_tick = true;
    while (should_tick) {
        should_tick = mythos_engine_tick();
    
        std::cout << "Ticking..." << std::endl;
    
    }

    mythos_engine_shutdown();

    std::cout << "Goodbye, Mythos!" << std::endl;

    return 0;
}