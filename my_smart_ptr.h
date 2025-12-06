#pragma once


template<typename T>
class my_shared_ptr {
private:
    T* ptr;
    size_t* refCount;

public:
    // 생성자
    explicit my_shared_ptr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}

    // 복사 생성자
    my_shared_ptr(const my_shared_ptr& other) : ptr(other.ptr), refCount(other.refCount) {
        /* TODO */
        if (refCount) {
            ++(*refCount);
        }
    }

    // 대입 연산자
    my_shared_ptr& operator=(const my_shared_ptr& other) {
        if (this != &other) {
            release();
            /* TODO */
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                ++(*refCount);
            }
        }
        return *this;
    }

    // 소멸자
    ~my_shared_ptr() { release(); }

    // 참조 해제
    void release() {
        /* TODO */
        if (refCount) {
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            ptr = nullptr;
            refCount = nullptr;
        }
    }

    // 접근 연산자
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // 참조 카운트 확인
    size_t use_count() const { return *refCount; }

    // get() 기능: raw 포인터 리턴
    T* get() const { return ptr; }

    // reset() 기능: 새로운 포인터로 교체
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
    // 생성자
    explicit my_unique_ptr(T* p = nullptr) : ptr(p) {}

    // 소멸자
    ~my_unique_ptr() {
        delete ptr;
    }

    // 복사 금지
    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;

    // 이동 생성자: other가 관리하는 자원의 소유권을 가져옴 
    my_unique_ptr(my_unique_ptr&& other) noexcept: ptr(other.ptr) {
        /* TODO */
        other.ptr = nullptr;
    }

    // 이동 대입 연산자: 기존 unique_ptr이 관리하던 자원을 해제하고, 다른 unique_ptr가 관리하는 자원의 소유권을 가져옴 
    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        if (this != &other) {
            /* TODO */
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // 포인터 접근
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // get() 메서드
    T* get() const { return ptr; }

    // release() 메서드: 내부 포인터를 반환하고, ptr은 nullptr로 초기화
    T* release() {
        /* TODO */
        T* rawPtr = ptr;
        ptr = nullptr;
        return rawPtr;
    }

    // reset() 메서드
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};
