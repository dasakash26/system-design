# Object-Oriented Programming (OOP) Concepts

Object-Oriented Programming (OOP) is a programming paradigm centered around **objects** rather than functions or logic. It is designed to model real-world entities, make code reusable, and manage complexity in large systems.

The core of OOP rests on four fundamental pillars:
1. **Encapsulation**
2. **Abstraction**
3. **Inheritance**
4. **Polymorphism**

---

## 1. Encapsulation

### Concept
Encapsulation is the **binding of data (variables) and behavior (methods) into a single unit (class)**, while restricting direct access to some of the object's components. 

By exposing only safe interfaces (public methods) and hiding internal data states (private variables), encapsulation prevents external code from putting the object into an invalid state.

> [!TIP]
> **Key Rule**: Keep data members `private` and provide public getters and setters *only when necessary* to enforce class invariants.

### Code Example (C++)
```cpp
#include <iostream>
#include <string>
#include <stdexcept>

class BankAccount {
private:
    std::string owner;
    double balance; // Hidden state

public:
    BankAccount(std::string owner, double initialBalance) {
        this->owner = owner;
        if (initialBalance >= 0) {
            this->balance = initialBalance;
        } else {
            this->balance = 0;
            throw std::invalid_argument("Initial balance cannot be negative.");
        }
    }

    // Getter (Read-only access)
    double getBalance() const {
        return balance;
    }

    // Controlled mutation
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited ₹" << amount << ". New balance: ₹" << balance << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) return;
        if (amount <= balance) {
            balance -= amount;
            std::cout << "Withdrew ₹" << amount << ". Remaining balance: ₹" << balance << std::endl;
        } else {
            std::cout << "Insufficient funds!" << std::endl;
        }
    }
};
```

---

## 2. Abstraction

### Concept
Abstraction is the process of **hiding complex implementation details and exposing only the essential features** of an object. 

Clients interact with a simple interface without needing to understand the underlying mechanics.

- **Interface/Abstract Class**: Defines *what* a class does, not *how* it does it.
- In C++, abstraction is achieved using **Abstract Classes** containing at least one **pure virtual function** (`= 0`).

### Code Example (C++)
```cpp
#include <iostream>

// Abstract interface
class Appliance {
public:
    virtual ~Appliance() = default;
    virtual void turnOn() = 0;  // Pure virtual function
    virtual void turnOff() = 0; // Pure virtual function
};

// Concrete implementation
class Microwave : public Appliance {
public:
    void turnOn() override {
        // Complex internal process (heating coils, magnetron start, turntable rotation)
        std::cout << "Microwave is heating food..." << std::endl;
    }

    void turnOff() override {
        std::cout << "Microwave turned off." << std::endl;
    }
};
```

---

## 3. Inheritance

### Concept
Inheritance is the mechanism by which **a new class (derived/child class) inherits the properties and behaviors of an existing class (base/parent class)**. 

It establishes an **IS-A** relationship and promotes code reusability.

- **Base Class (Parent)**: The existing class.
- **Derived Class (Child)**: The new class inheriting from the base class.

### Code Example (C++)
```cpp
#include <iostream>
#include <string>

// Parent Class
class Vehicle {
protected:
    std::string brand;

public:
    Vehicle(std::string brand) : brand(brand) {}
    
    void honk() {
        std::cout << "Beep beep! " << brand << " is honking." << std::endl;
    }
};

// Child Class (inherits from Vehicle)
class Car : public Vehicle {
private:
    int doors;

public:
    Car(std::string brand, int doors) : Vehicle(brand), doors(doors) {}

    void showDetails() {
        std::cout << "Brand: " << brand << ", Doors: " << doors << std::endl;
    }
};
```

---

## 4. Polymorphism

### Concept
Polymorphism literally means **"many forms."** It allows one interface to represent general classes of actions. Polymorphism is split into two types:

1. **Static Polymorphism (Compile-time)**: Resolved during compilation.
   - *Function Overloading*: Same function name, different parameter lists.
   - *Operator Overloading*: Changing operator behaviors for custom types.
2. **Dynamic Polymorphism (Run-time)**: Resolved during execution.
   - *Method Overriding*: Child class overrides a parent class method.
   - Achieved using the `virtual` keyword in C++.

### Code Example (C++)

#### Static Polymorphism (Function Overloading)
```cpp
class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, double b) {
        return a + b;
    }

    int add(int a, int b, int c) {
        return a + b + c;
    }
};
```

#### Dynamic Polymorphism (Method Overriding)
```cpp
#include <iostream>
#include <vector>

class Animal {
public:
    virtual ~Animal() = default;
    virtual void makeSound() const {
        std::cout << "Some generic animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() const override {
        std::cout << "Woof! Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Meow~" << std::endl;
    }
};

// Polymorphic behavior demonstration
void playSound(const Animal* animal) {
    animal->makeSound(); // Calls the specific overridden function at runtime
}

int main() {
    Dog dog;
    Cat cat;

    playSound(&dog); // Outputs: Woof! Woof!
    playSound(&cat); // Outputs: Meow~
}
```