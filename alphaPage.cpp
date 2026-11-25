#include <iostream>
#include <string>
#include <mutex>

int main(int argc, char** argv) {
    std::cout << "Hello World\n";
    return 0;
}

// Copy and Swap
class String {
    char* str;
public:
    // returns manipulate a String (a=b)
    String& operator=(const String& b) {
        String temp(b);
        temp.swap(*this);

        return *this;
    }

    // noexcept prevents leaving callstack layer;
    void swap(String& s) noexcept {
        std::swap(this->str, s.str);
    }
};

// RAII (Resource Acquisition Is Initialization)
std::mutex m;

bool nice = true;

void f() {
    nice = false;
}

bool everything_ok() {
    return nice ? nice : !nice;
}

void bad() {
    m.lock(); // lock manually
    f();
    if(!everything_ok()) { // return early without ever unlocking
        return;
    }
    m.unlock(); // if never reach here then the mutex is never unlocked and your thread is permenantly locked
}

void good() {
    std::lock_guard<std::mutex> lk(m); // lock_guard cleans up once we exit the statement
    f();
    if(!everything_ok()) {
        return; // doesn't matter if exits here
    }
    // or here. lk will be released
}

// ------------------------------------------
// SEE PREVENT HEAVY PROGS FOR PIMPL IDIOM
// ------------------------------------------

// Non Virtual Interface Idiom

class Task {
public:
    virtual ~Task() = default;

    // Public non-virtual interface controls the shared steps
    void execute() {
        std::cout << "Starting task...\n";
        runStep();
        std::cout << "Finished task.\n\n";
    }

private:
    // Private virtual hook customized by derived classes
    // Virtual pretty much allows a method to be changed in the children.
    virtual void runStep() = 0;
};

class DownloadTask : public Task {
public:
    explicit DownloadTask(std::string file) : file_(std::move(file)) {}

private:
    std::string file_;

    void runStep() override {
        std::cout << "Downloading " << file_ << "\n";
    }
};