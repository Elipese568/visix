#ifndef VISIX_SDK_APPSTATE_H
#define VISIX_SDK_APPSTATE_H
namespace visix::application{
    enum class AppState{
        Unlaunched,
        Launching,
        Running,
        Suspended,
        Exiting,
        Exited
    };
} // namespace visix::sdk
#endif // VISIX_SDK_APPSTATE_H