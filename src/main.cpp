#include <mythos_engine.hpp>
#include <iostream>

int main() {
    mythos_engine_init();

    bool should_tick = true;
    while (should_tick) {
        should_tick = mythos_engine_tick();
    }

    return 0;
}