#include <mythos_engine.hpp>
#include <rendering_pipeline.hpp>

bool should_close = false;

void mythos_engine_init() {
    rendering_rendering_pipeline_init();
    Add_On_Should_Close(mythos_engine_shutdown);
}

bool mythos_engine_tick() {
    rendering_rendering_pipeline_render_frame();
    return !should_close;
}

void mythos_engine_shutdown() {
    rendering_rendering_pipeline_shutdown();
    should_close = true;
}