#include "sdk/application/Application.hpp"
#include <atomic>

void visix::application::Application::PumpEvents()
{
    // Placeholder for event pumping logic
}

void visix::application::Application::Tick()
{
    // Placeholder for per-frame update logic
}

visix::application::Application &visix::application::Application::current()
{
    static visix::application::Application appInstance;
    return appInstance;
}
void visix::application::Application::run()
{
    this->_state = AppState::Running;
    onLaunch();
    
    this->_state = AppState::Running;

    while (_state == AppState::Running) {
        PumpEvents();   // 现在可以是空实现
        Tick();         // UI / Layout / Render 以后加
    }

    onExit();
    _CRT_UNUSED(4);
    this->_state = AppState::Exited;
}
void visix::application::Application::exit(int code)
{
    this->_state = AppState::Exiting;
}
void visix::application::Application::onLaunch() {}
void visix::application::Application::onExit() {}
void visix::application::Application::onActivated() {}
void visix::application::Application::onSuspending() {}
void visix::application::Application::onResuming() {}