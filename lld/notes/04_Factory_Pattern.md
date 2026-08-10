# Factory Design Pattern

The Factory pattern is a `creational design pattern` that abstracts the instantiation logic of objects. 
Decoupling client code from concrete types is achieved by delegating instantiation to a specialised creator entity.

---
## Core Architecture

Creational factory designs typically manifest in three distinct forms:

| Attribute                   | Simple Factory                                                                     | Factory Method                                                                                                                         | Abstract Factory                                                                                                                              |
| --------------------------- | ---------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| **Core Intent**             | Centralise creation logic in a single class                                        | Delegate instantiation to subclasses                                                                                                   | Create families of related/dependent products                                                                                                 |
| **Instantiation Mechanism** | Static method with conditional branching                                           | Virtual creation methods overridden by derived creators                                                                                | Polymorphic interfaces grouping multiple creation methods                                                                                     |
| **Product Scope**           | Single product hierarchy                                                           | Single product hierarchy                                                                                                               | Multiple interdependent product families                                                                                                      |
| **Fundamental Difference**  | Centralised conditional creator; client requests product by an input token or type | Decentralised creator subclasses supply specific products via polymorphism; client works with appropriate creator or subclass instance | Factory object exposes multiple creation methods to produce a family; client selects factory per family to ensure compatible product variants |
| **Extensibility Model**     | New types require modifying the factory method (breaks Open/Closed)                | New products via new creator subclasses (Open/Closed compliant)                                                                        | New product families via new factory implementations                                                                                          |
| **Code Complexity**         | Low                                                                                | Medium                                                                                                                                 | High                                                                                                                                          |
| **Primary Use Case**        | Stable product sets with infrequent additions                                      | One product family needing runtime variation                                                                                           | Interdependent product suites with shared themes                                                                                              |
| **Small Example**           | SimpleFactory::create(type) — e.g., PizzaFactory::create("Margherita")             | Creator::createProduct() — e.g., OrderDispatcher::createOrder("ORD-1")                                                                 | GUIFactory::createButton()/createCheckbox() — e.g., WindowsFactory                                                                            |

### Factory Method Participants

| Participant | Responsibility |
| --- | --- |
| **Product** | Defines the interface of objects the factory method creates. |
| **ConcreteProduct** | Implements the Product interface. |
| **Creator** | Declares the factory method, which returns an object of type Product. May also define default implementation. |
| **ConcreteCreator** | Overrides the factory method to return an instance of a ConcreteProduct. |

---

## Standard UML Representation

Below is the structure of the **Factory Method** pattern:

```mermaid
classDiagram
    direction TB
    class Product {
        <<interface>>
        +operation()
    }
    class ConcreteProductA {
        +operation()
    }
    class ConcreteProductB {
        +operation()
    }
    class Creator {
        <<abstract>>
        +someOperation()
        +createProduct() Product*
    }
    class ConcreteCreatorA {
        +createProduct() Product*
    }
    class ConcreteCreatorB {
        +createProduct() Product*
    }

    Product <|.. ConcreteProductA : realizes
    Product <|.. ConcreteProductB : realizes
    Creator <|.. ConcreteCreatorA : realizes
    Creator <|.. ConcreteCreatorB : realizes
    ConcreteCreatorA --> ConcreteProductA : instantiates
    ConcreteCreatorB --> ConcreteProductB : instantiates
```

---

## The Coupling Problem

* **Problem**: In a direct instantiation model, client code must import and instantiate concrete classes (e.g. `new InstantOrder()`, `new ScheduledOrder()`) directly.
* **Impact**: Adding a new product type requires modifying the client's routing or creation switch statements, violating the **Open/Closed Principle (OCP)**.
* **Solution**: The client interacts exclusively with the abstract `Order` product and abstract `OrderDispatcher` creator, shielding the client from concrete class modifications.

---


## Example (Scheduled Order Dispatcher)

Below is the UML class diagram for the Scheduled Order Dispatcher scenario:

```mermaid
classDiagram
    direction TB
    class Order {
        <<abstract>>
        #orderId string
        #amount double
        +dispatch() void
    }
    class InstantOrder {
        +dispatch() void
    }
    class ScheduledOrder {
        -deliveryWindow string
        +dispatch() void
    }
    class OrderDispatcher {
        <<abstract>>
        +createOrder(id string, amt double) unique_ptr~Order~*
        +processAndDispatch(id string, amt double) void
    }
    class InstantOrderDispatcher {
        +createOrder(id string, amt double) unique_ptr~Order~
    }
    class ScheduledOrderDispatcher {
        -scheduleTimeWindow string
        +createOrder(id string, amt double) unique_ptr~Order~
    }
    class DispatchRegistry {
        -registry unordered_map~string_shared_ptr~OrderDispatcher~~
        -registryMutex mutex
        +registerDispatcher(type string, dispatcher shared_ptr~OrderDispatcher~) void
        +getDispatcher(type string) shared_ptr~OrderDispatcher~
    }

    Order <|-- InstantOrder : inherits
    Order <|-- ScheduledOrder : inherits
    OrderDispatcher <|-- InstantOrderDispatcher : inherits
    OrderDispatcher <|-- ScheduledOrderDispatcher : inherits
    InstantOrderDispatcher ..> InstantOrder : instantiates
    ScheduledOrderDispatcher ..> ScheduledOrder : instantiates
    OrderDispatcher --o DispatchRegistry : aggregates
```

This implementation demonstrates a thread safe scheduled order dispatch system using the Factory Method pattern. It features robust dynamic allocation, custom exceptions, and registry synchronization.

```cpp
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>

using namespace std;

// Custom System Exception
class DispatchException : public runtime_error {
public:
    explicit DispatchException(const string& msg) : runtime_error(msg) {}
};

// Abstract Product
class Order {
protected:
    string orderId;
    double amount;

public:
    Order(string id, double amt) : orderId(id), amount(amt) {}
    virtual ~Order() = default;
    virtual void dispatch() = 0;
};

// Abstract Creator
class OrderDispatcher {
public:
    virtual ~OrderDispatcher() = default;
    
    // Factory Method
    virtual unique_ptr<Order> createOrder(string id, double amt) = 0;

    // Helper business logic leveraging the Factory Method
    void processAndDispatch(string id, double amt) {
        unique_ptr<Order> order = createOrder(id, amt);
        if (!order) {
            throw DispatchException("Order creation failed");
        }
        order->dispatch();
    }
};

// Concrete Products
class InstantOrder : public Order {
public:
    InstantOrder(string id, double amt) : Order(id, amt) {}
    
    void dispatch() override {
        cout << "Dispatching Instant Order [" << orderId << "] for immediate delivery. Amount: " << amount << "\n";
    }
};

class ScheduledOrder : public Order {
private:
    string deliveryWindow;

public:
    ScheduledOrder(string id, double amt, string window) 
        : Order(id, amt), deliveryWindow(window) {}

    void dispatch() override {
        cout << "Dispatching Scheduled Order [" << orderId << "] for window: " 
             << deliveryWindow << ". Amount: " << amount << "\n";
    }
};

// Concrete Creators
class InstantOrderDispatcher : public OrderDispatcher {
public:
    unique_ptr<Order> createOrder(string id, double amt) override {
        return make_unique<InstantOrder>(id, amt);
    }
};

class ScheduledOrderDispatcher : public OrderDispatcher {
private:
    string scheduleTimeWindow;

public:
    explicit ScheduledOrderDispatcher(string timeWindow) : scheduleTimeWindow(timeWindow) {}

    unique_ptr<Order> createOrder(string id, double amt) override {
        return make_unique<ScheduledOrder>(id, amt, scheduleTimeWindow);
    }
};

// Thread Safe Factory Registry
class DispatchRegistry {
private:
    unordered_map<string, shared_ptr<OrderDispatcher>> registry;
    mutable mutex registryMutex;

public:
    void registerDispatcher(const string& type, shared_ptr<OrderDispatcher> dispatcher) {
        lock_guard<mutex> lock(registryMutex);
        if (!dispatcher) {
            throw DispatchException("Cannot register null dispatcher");
        }
        registry[type] = dispatcher;
    }

    shared_ptr<OrderDispatcher> getDispatcher(const string& type) const {
        lock_guard<mutex> lock(registryMutex);
        auto it = registry.find(type);
        if (it == registry.end()) {
            throw DispatchException("Dispatcher type not registered: " + type);
        }
        return it->second;
    }
};

// Client Driver
int main() {
    try {
        auto registry = make_unique<DispatchRegistry>();

        // Register dispatchers
        registry->registerDispatcher("instant", make_shared<InstantOrderDispatcher>());
        registry->registerDispatcher("scheduled_evening", make_shared<ScheduledOrderDispatcher>("18:00 - 20:00"));

        // Client usage decoupling concrete product types
        cout << "--- Client Processing Instant Order ---\n";
        shared_ptr<OrderDispatcher> instantDispatcher = registry->getDispatcher("instant");
        instantDispatcher->processAndDispatch("ORD-101", 250.75);

        cout << "\n--- Client Processing Scheduled Order ---\n";
        shared_ptr<OrderDispatcher> scheduledDispatcher = registry->getDispatcher("scheduled_evening");
        scheduledDispatcher->processAndDispatch("ORD-102", 1200.00);

    } catch (const DispatchException& ex) {
        cerr << "Dispatch System Failure: " << ex.what() << "\n";
    }

    return 0;
}
```

---
## Concurrency & Design Considerations

* **Thread Safe Registry**: When stored in a global lookup registry (e.g. `DispatchRegistry`), access to the dispatchers map must be protected using standard synchronization primitives (`std::mutex` or `std::shared_mutex`).
* **Eager Initialization**: To avoid lock overhead, the registry can be populated eagerly at startup before spawning worker threads.
* **Factory Caching / Object Pooling**: For expensive products (like database connection adapters or network sockets), the concrete factory can encapsulate a thread safe object pool to recycle instances, minimizing memory churn.

---