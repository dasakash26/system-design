# Strategy Design Pattern

The Strategy pattern is a behavioral design pattern that defines a family of algorithms, encapsulates each one, and makes them interchangeable. Strategy lets the algorithm vary independently from the clients that use it. It promotes the core design principle: **Favor Composition over Inheritance**.

---

## Core Architecture

The static class hierarchy decouples algorithm execution from the context that utilizes it. The context class contains a reference to the Strategy interface and delegates the algorithm execution to the concrete strategy object.

| Participant | Responsibility |
| --- | --- |
| **Context** | Maintains a reference to a Strategy object and interfaces with the client. |
| **Strategy** | Declares a common interface for all supported algorithms. |
| **ConcreteStrategy** | Implements the specific algorithm defined by the Strategy interface. |

---

## UML Representation

```mermaid
classDiagram
    direction TB
    class Strategy {
        <<interface>>
        +executeAlgorithm()
    }
    class ConcreteStrategyA {
        +executeAlgorithm()
    }
    class ConcreteStrategyB {
        +executeAlgorithm()
    }
    class Context {
        -strategy Strategy
        +setStrategy(Strategy)
        +performOperation()
    }

    ConcreteStrategyA ..|> Strategy : realizes
    ConcreteStrategyB ..|> Strategy : realizes
    Context o-- Strategy : aggregates
```

---

## The Coupling Problem

* **Problem**: A checkout manager that directly calls payment methods like `processUpiPayment()` or `processCardPayment()` is tightly coupled to concrete execution algorithms.
* **Impact**: Adding a new payment type or changing a provider's API signatures requires modifying the checkout manager, violating the **Open/Closed Principle (OCP)**.
* **Solution**: The checkout processor depends exclusively on a common `Strategy` interface, allowing algorithms to be swapped at runtime or injected via constructor parameters.

---

## C++ Implementation (Payment Processing System)

This implementation demonstrates a thread safe checkout context executing dynamic payment strategies, featuring smart memory management, custom exceptions, and scoped locking.

```cpp
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>

using namespace std;

// Custom System Exception
class PaymentException : public runtime_error {
public:
    explicit PaymentException(const string& msg) : runtime_error(msg) {}
};

// Strategy Interface
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual void collectDetails() = 0;
    virtual void pay(double amount) = 0;
};

// Concrete Strategies
class CardPayment : public PaymentStrategy {
private:
    string cardNumber;
    string cvv;

public:
    CardPayment(string card, string code) : cardNumber(card), cvv(code) {
        if (card.empty() || code.empty()) {
            throw PaymentException("Invalid card details provided");
        }
    }

    void collectDetails() override {
        cout << "Validating Card: " << cardNumber << "\n";
    }

    void pay(double amount) override {
        cout << "Paid " << amount << " using Credit Card.\n";
    }
};

class UpiPayment : public PaymentStrategy {
private:
    string upiId;

public:
    explicit UpiPayment(string id) : upiId(id) {
        if (id.empty()) {
            throw PaymentException("Invalid UPI ID");
        }
    }

    void collectDetails() override {
        cout << "Verifying UPI ID: " << upiId << "\n";
    }

    void pay(double amount) override {
        cout << "Paid " << amount << " using UPI.\n";
    }
};

// Context Class
class CheckoutProcessor {
private:
    shared_ptr<PaymentStrategy> paymentStrategy;
    mutable mutex strategyMutex;

public:
    CheckoutProcessor() : paymentStrategy(nullptr) {}

    void setPaymentStrategy(shared_ptr<PaymentStrategy> strategy) {
        lock_guard<mutex> lock(strategyMutex);
        if (!strategy) {
            throw PaymentException("Cannot set null payment strategy");
        }
        paymentStrategy = strategy;
    }

    void processOrder(double amount) {
        shared_ptr<PaymentStrategy> currentStrategy;
        
        {
            lock_guard<mutex> lock(strategyMutex);
            if (!paymentStrategy) {
                throw PaymentException("Payment strategy not set");
            }
            currentStrategy = paymentStrategy;
        }

        // Execute action outside the critical section to prevent lock contention
        currentStrategy->collectDetails();
        currentStrategy->pay(amount);
    }
};

// Client Driver
int main() {
    try {
        auto checkout = make_unique<CheckoutProcessor>();

        cout << "--- Card Payment Flow ---\n";
        auto card = make_shared<CardPayment>("1234-5678-9012", "999");
        checkout->setPaymentStrategy(card);
        checkout->processOrder(1500.50);

        cout << "\n--- UPI Payment Flow ---\n";
        auto upi = make_shared<UpiPayment>("user@upi");
        checkout->setPaymentStrategy(upi);
        checkout->processOrder(450.00);

    } catch (const PaymentException& ex) {
        cerr << "Payment failure: " << ex.what() << "\n";
    }

    return 0;
}
```

---

## Concurrency & Design Considerations

* **Shared State Protection**: The context class manages the active strategy under a `std::mutex` to protect against simultaneous calls to `setPaymentStrategy` and `processOrder`.
* **Minimizing Lock Contention**: The actual strategy execution (`collectDetails()` and `pay()`) runs **outside the locked critical section**.
* **Local Copy Snapshot**: The context copies the shared pointer locally under lock, releases the mutex, and then runs the payment. This prevents network delays inside the strategy from stalling the entire processor.

---

## Design Tradeoffs

### Advantages & SOLID Alignment
* **OCP Compliance**: You can introduce new payment methods (e.g. `CryptoPayment`) without modifying existing checkout code.
* **SRP Alignment**: Separates checkout orchestration logic from concrete integration details.

### Drawbacks
* **Subclass Proliferation**: Each algorithm requires a new class, increasing the codebase class count.
* **Client Awareness**: The calling client must understand the differences between strategies to instantiate and inject the correct one.
