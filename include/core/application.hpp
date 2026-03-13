#pragma once
#include <memory>
#include <string>

namespace core {

class IModule {
public:
    virtual ~IModule() = default;
    virtual void update(float dt) = 0;
};

class Application {
public:
    explicit Application(std::string name);
    void run();
    void stop();

    void setModule(std::shared_ptr<IModule> module);
private:
    std::string name_;
    bool running_{true};
    std::shared_ptr<IModule> module_;
};

}
