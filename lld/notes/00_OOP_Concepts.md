# Object Oriented Programming (OOP) Concepts

Object oriented Programming (OOP) is a programming paradigm centered around objects rather than functions or logic. It models real world entities, promotes code reuse, and manages complexity in large systems by encapsulating state and behavior within cohesive units.

The core of OOP rests on four fundamental pillars:

| Pillar | Core Objective | Low Level Mechanism / Representation |
| --- | --- | --- |
| **Encapsulation** | Enforce class invariants and restrict direct access to state. | Access specifiers (`private`/`protected`), contiguous memory layouts. |
| **Abstraction** | Hide complex implementation details behind clean interfaces. | Abstract base classes, pure virtual function declarations. |
| **Inheritance** | Establish hierarchy and promote code reuse. | Base class subobjects embedded within derived class memory allocations. |
| **Polymorphism** | Bind method calls dynamically or statically to different behaviors. | Virtual tables (vtables), virtual pointers (vptrs), compiler generated offsets. |

---

## Encapsulation

Encapsulation binds data attributes and behaviors into a single class unit, while restricting direct access to the internal state.

Exposing only controlled public interfaces and hiding internal data representations prevents external components from placing the object into an invalid state, thereby enforcing class invariants.

### Low Level Mechanics
* **Contiguous Memory**: Class data members are laid out contiguously in memory, aligned according to the compiler's padding and packing rules.
* **Compile time enforcement**: Access specifiers (`private` and `protected`) are enforced strictly at compile time. At run time, access boundaries disappear, but invariants remain protected by the compiled interface logic.

### C++ Example

```cpp
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class BankAccount {
private:
    string owner;
    double balance;

public:
    BankAccount(string ownerName, double initialBalance) {
        owner = ownerName;
        if (initialBalance >= 0) {
            balance = initialBalance;
        } else {
            balance = 0;
            throw invalid_argument("Initial balance cannot be negative");
        }
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << ". New balance: " << balance << "\n";
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) return;
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrew: " << amount << ". Remaining balance: " << balance << "\n";
        } else {
            throw invalid_argument("Insufficient funds");
        }
    }
};
```

---

## Abstraction

Abstraction hides complex execution logic and exposes only essential features to the client. This decouples the client from changes in the underlying implementation, allowing developers to change how an operation is performed without affecting the consumer.

### Low Level Mechanics
* **Pure Virtual Declarations**: In C++, abstraction is implemented using abstract base classes containing at least one pure virtual function (indicated by `= 0`).
* **Non Instantiable**: These classes cannot be instantiated directly and serve as formal interface contracts that derived classes must satisfy.

### C++ Example

```cpp
#include <iostream>
#include <string>

using namespace std;

// Abstract interface defining the contract
class Appliance {
public:
    virtual ~Appliance() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

// Concrete implementation hiding physical hardware complexities
class Microwave : public Appliance {
public:
    void turnOn() override {
        // Simulates complex internal procedures: magnetron startup, fan activation, turntable rotation
        cout << "Microwave magnetron active. Heating food...\n";
    }

    void turnOff() override {
        cout << "Microwave magnetron deactivated. Cooling down...\n";
    }
};
```

---

## Inheritance

Inheritance allows a new class (derived class) to inherit member variables and behaviors from an existing class (base class), establishing an IS-A relationship.

### Low Level Mechanics
* **Memory Subobjects**: During compilation, when a derived class is defined, the compiler allocates memory for the base class subobject first.
* **Derived Alignment**: The base subobject is followed immediately by the derived class's member variables in a contiguous memory block.
* **Safe Pointer Casts**: This contiguous layout allows pointers of the base type to point safely to derived class instances.

### C++ Example

```cpp
#include <iostream>
#include <string>

using namespace std;

class Vehicle {
protected:
    string brand;

public:
    explicit Vehicle(string vehicleBrand) : brand(vehicleBrand) {}
    
    void honk() const {
        cout << "Beep beep! " << brand << " is honking.\n";
    }
};

class Car : public Vehicle {
private:
    int doors;

public:
    Car(string carBrand, int carDoors) : Vehicle(carBrand), doors(carDoors) {}

    void showDetails() const {
        cout << "Brand: " << brand << ", Doors: " << doors << "\n";
    }
};
```

---

## Polymorphism

Polymorphism allows one interface to represent multiple forms of behavior. It is split into static (compile time) and dynamic (run time) mechanisms.

| Dimension | Static Polymorphism | Dynamic Polymorphism |
| --- | --- | --- |
| **Resolution Time** | Compile time | Runtime |
| **Mechanism** | Function overloading, templates, operator overloading | Virtual functions, vtables, vptrs |
| **Performance Overhead** | Zero runtime cost (allows compiler inlining) | Pointer indirection lookup, disables inlining optimizations |
| **Flexibility** | Rigid execution paths set during compilation | Highly dynamic, allows uniform processing of polymorphic containers |

### Low Level Mechanics (Vtables & Vptrs)

When a class declares or inherits a virtual function, the compiler automatically sets up two primary components:
* **Virtual Table (vtable)**: A static table generated per class containing pointers to all virtual functions defined or inherited by that class.
* **Virtual Pointer (vptr)**: A hidden pointer added to every instance layout of the class (usually at offset zero). On instantiation, the constructor initializes `vptr` to point to the class's static `vtable`.

When a virtual function is invoked on a base class pointer:
1. **Dereference Pointer**: The CPU dereferences the base pointer to read the object's `vptr`.
2. **Locate Vtable**: It dereferences `vptr` to locate the class's static `vtable`.
3. **Index Vtable**: It indexes into the `vtable` to fetch the concrete function pointer.
4. **Execute Call**: It executes a jump instruction to that address.

This indirection adds a small runtime call cost and prevents compiler inlining, which is the primary trade-off of dynamic polymorphism. 

In multiple inheritance, the compiler must inject offset adjustments (**thunks**) to manipulate the `this` pointer when base classes have distinct memory offsets within the derived object layout.

### C++ Example

#### Static Polymorphism (Function Overloading)

```cpp
#include <iostream>

using namespace std;

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

#### Dynamic Polymorphism (Virtual Function Dispatch)

```cpp
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Animal {
public:
    virtual ~Animal() = default;
    virtual void makeSound() const {
        cout << "Generic animal sound\n";
    }
};

class Dog : public Animal {
public:
    void makeSound() const override {
        cout << "Woof! Woof!\n";
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        cout << "Meow~\n";
    }
};

void playSound(const Animal& animal) {
    animal.makeSound(); // Dispatches dynamically via vptr/vtable lookup
}

int main() {
    unique_ptr<Animal> dog = make_unique<Dog>();
    unique_ptr<Animal> cat = make_unique<Cat>();

    playSound(*dog); // Outputs: Woof! Woof!
    playSound(*cat); // Outputs: Meow~

    return 0;
}
```