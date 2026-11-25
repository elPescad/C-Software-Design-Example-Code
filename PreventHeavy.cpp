#include <PreventHeavy.h>
#include <iostream>
#include <vector>

struct PreventHeavy::heavyFunc {
    std::vector<int> bigBuffer;
    int status = 0;

    void execute() {
        bigBuffer.assign(10000, 42);
        status = static_cast<int>(bigBuffer.size());
    }
};

// : is a member initializer. It initializes members before the main {} body
PreventHeavy::PreventHeavy() : ptr(std::make_unique<heavyFunc>()) {}

// default tells compiler to clean up all member variables
PreventHeavy::~PreventHeavy() = default;

// looks like ptr(std::move(other.ptr)) under the hood
// moves pointer ownership
// a->ptr = something
// b->ptr = DNE
// PreventHeavy b = std::move(a);
// a->ptr = nullptr
// b->ptr = something
PreventHeavy::PreventHeavy(PreventHeavy&&) noexcept = default;

// same thing as before but this time it's for when it was already created
PreventHeavy& PreventHeavy::operator=(PreventHeavy&&) noexcept = default;

void PreventHeavy::run() {
    ptr->execute();
}

int PreventHeavy::getStatus() const {
    return ptr->status;
}