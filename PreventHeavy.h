#include <memory>

#pragma once

class PreventHeavy {
private:
    struct heavyFunc;
    std::unique_ptr<heavyFunc> ptr;

public:
    PreventHeavy();
    ~PreventHeavy();

    PreventHeavy(const PreventHeavy&) = delete;
    PreventHeavy& operator=(const PreventHeavy&) = delete;

    PreventHeavy(PreventHeavy&&) noexcept;
    PreventHeavy& operator=(PreventHeavy&&) noexcept;

    void run();
    int getStatus() const;
};