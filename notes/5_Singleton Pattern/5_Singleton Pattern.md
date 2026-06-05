# Singleton Design Pattern

The **Singleton Pattern** is a creational design pattern that ensures a class has **only one instance** and provides a **global point of access** to that instance.

---

## Hello Interview Design Insights

In modern engineering and technical interviews, Singletons are frequently considered an **anti-pattern** and should be used with extreme caution.

### 1. The Singleton Pitfalls
* **Test Pollution**: Singletons carry state across the entire lifetime of an application. If tests run in parallel, they will read and write to the same instance, causing intermittent test failures (flaky tests).
* **SRP Violation**: A Singleton is responsible for both its core business logic AND managing its own lifecycle/instantiation.
* **Tightly Coupled Code**: Using `Singleton::getInstance()` inside a class hardcodes a dependency, making it impossible to mock the singleton during testing.

### 2. The Modern Alternative: Dependency Injection (DI)
Instead of enforcing single-instance creation inside the class:
1. Write a normal class (with a public constructor).
2. Use a Dependency Injection container (like Spring in Java, or simple manual injection in your main entrypoint) to instantiate the class **once**.
3. Pass this single instance to the constructors of any classes that need it.
   - This achieves the same goal (a single shared instance) without hardcoding global access or polluting tests.

---

## Implementation Evolution (C++)

If an interviewer explicitly requests a Singleton (common in systems like C++), implement it with thread safety:

### 1. Meyers' Singleton (Modern C++ Best Practice)
In C++11 and later, static local variables are guaranteed to be initialized in a thread-safe manner by the compiler. This is the cleanest, most efficient way to write singletons in C++.

```cpp
#include <iostream>

class MeyersSingleton {
private:
    MeyersSingleton() {
        std::cout << "MeyersSingleton Instantiated!" << std::endl;
    }

public:
    MeyersSingleton(const MeyersSingleton&) = delete;
    MeyersSingleton& operator=(const MeyersSingleton&) = delete;

    static MeyersSingleton& getInstance() {
        // Thread-safe initialization guaranteed by the C++11 compiler
        static MeyersSingleton instance;
        return instance;
    }
};
```

---

### 2. Thread-Safe Double-Checked Locking (Lazy)
If you need compatibility with older legacy platforms or explicit locking controls:

```cpp
#include <iostream>
#include <mutex>

class DoubleLockingSingleton {
private:
    static DoubleLockingSingleton* instance;
    static std::mutex mtx;

    DoubleLockingSingleton() {
        std::cout << "DoubleLockingSingleton Instantiated!" << std::endl;
    }

public:
    DoubleLockingSingleton(const DoubleLockingSingleton&) = delete;
    DoubleLockingSingleton& operator=(const DoubleLockingSingleton&) = delete;

    static DoubleLockingSingleton* getInstance() {
        if (instance == nullptr) { // First Check (No locking - fast path)
            std::lock_guard<std::mutex> lock(mtx); // Acquire Lock
            if (instance == nullptr) { // Second Check (Confirm no other thread created it)
                instance = new DoubleLockingSingleton();
            }
        }
        return instance;
    }
};

DoubleLockingSingleton* DoubleLockingSingleton::instance = nullptr;
std::mutex DoubleLockingSingleton::mtx;
```

---

## Summary of Singleton Types

| Implementation Style | Thread-Safe? | Lazy Loaded? | Locking Overhead |
| --- | --- | --- | --- |
| **Simple Lazy** | No | Yes | None |
| **Eager Initialization** | Yes | No | None |
| **Double-Checked Locking**| Yes | Yes | Only during first instantiation |
| **Meyers' Singleton** | Yes | Yes | None (compiler-optimized) |