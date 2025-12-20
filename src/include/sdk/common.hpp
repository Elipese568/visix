#include <concepts>
#include "sdk/application/Application.hpp"

#define SDK_VERSION "1.0.0"

template<typename AppT>
concept AppTypeConcept = std::derived_from<AppT, visix::application::Application>;

template<AppTypeConcept AppT>
void RunApplication() {
    AppT &app = AppT::current();
    app.run();
}

#define RUN_APPLICATION(AppT) \
    int main(int argc, char **argv) { \
        RunApplication<AppT>(); \
        return 0; \
    }