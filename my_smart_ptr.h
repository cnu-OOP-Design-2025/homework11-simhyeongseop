#pragma once


template<typename T>
class my_shared_ptr {
private:
    T* ptr;
    size_t* refCount;

public:
    explicit my_shared_ptr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}

    my_shared_ptr(const my_shared_ptr& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            ++(*refCount);
        }
    }

    my_shared_ptr& operator=(const my_shared_ptr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                ++(*refCount);
            }
        }
        return *this;
    }

    ~my_shared_ptr() { release(); }

    void release() {
        if (refCount) {
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            ptr = nullptr;
            refCount = nullptr;
        }
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    size_t use_count() const { return *refCount; }

    T* get() const { return ptr; }

    void reset(T* p = nullptr) {
        release();
        ptr = p;
        refCount = new size_t(1);
    }
};


template <typename T>
class my_unique_ptr {
private:
    T* ptr;
public:
    explicit my_unique_ptr(T* p = nullptr) : ptr(p) {}

    ~my_unique_ptr() {
        delete ptr;
    }

    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;

    my_unique_ptr(my_unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    T* get() const { return ptr; }

    T* release() {
        T* rawPtr = ptr;
        ptr = nullptr;
        return rawPtr;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};
