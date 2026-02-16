// Runtime exceptions definitions

#ifndef RUNTIME_EXCEPTIONS_S
#define RUNTIME_EXCEPTIONS_S

// Define your runtime exceptions here, for example:

class RuntimeException {
public:
    virtual const char* what() const noexcept {
        return "Runtime Exception";
    }
};

class IndexOutOfBoundsException : public RuntimeException {
public:
    const char* what() const noexcept override {
        return "Index Out Of Bounds Exception";
    }
};

class NullPointerException : public RuntimeException {
public:
    const char* what() const noexcept override {
        return "Null Pointer Exception";
    }
};

#endif // RUNTIME_EXCEPTIONS_S
