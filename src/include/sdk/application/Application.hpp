#include "sdk/application/AppState.hpp"

#ifndef VISIX_SDK_APPLICATION_H
#define VISIX_SDK_APPLICATION_H
namespace visix::application
{
    class Application
    {
    private:
        AppState _state;

        void PumpEvents();
        void Tick();

    public:
        static Application &current();

        void run();
        void exit(int code = 0);

    protected:
        virtual void onLaunch();
        virtual void onExit();

        virtual void onActivated();
        virtual void onSuspending();
        virtual void onResuming();
    };
} // namespace visix::sdk
#endif // VISIX_SDK_APPLICATION_H