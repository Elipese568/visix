#include <iostream>
#include <thread>
#include <chrono>

#include "application/Application.hpp"

class AppModelTest : public visix::application::Application {
private:
    std::thread _runningThread;
public:
    AppModelTest() {}
protected:
    void onLaunch() override {
        std::cout << "Launching..." << std::endl;
        std::cout << "Exit on 5 seconds" << std::endl;
        _runningThread = std::thread( [this] {
            std::cout << "Running" << std::endl;
            for(int i = 0; i < 5; i++){
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << i << " seconds" << std::endl;
                
            }
            std::cout << "Exit" << std::endl;
            exit(0);
        });
        _runningThread.detach();
    }

    void onExit() override {
        std::cout << "Exiting..." << std::endl;
    }
};

int main() {
    AppModelTest app{};
    app.run();
    return 0;
}