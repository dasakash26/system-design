# Software Design Principles

The core objective of software design is to manage complexity. A well designed system exhibits low coupling, high cohesion, easy maintainability, and structural extensibility. Software design principles are split into two primary categories: General Design Principles and SOLID Object Oriented Design Principles.

---

## General Design Principles

General design principles guide the macro architecture of a system, focusing on simplicity, reuse, and clean boundary separation.

| Principle | Core Intent | Architectural Target | Low Level Consequence of Violation |
| --- | --- | --- | --- |
| **KISS** | Keep it simple | Minimize architectural overhead | Excessive branching, poor CPU branch prediction, code bloat. |
| **DRY** | Do not repeat knowledge | Centralize authoritative logic | Disjoint state mutations, duplicate binary size, cache performance degradation. |
| **YAGNI** | Avoid premature features | Avoid hypothetical future proofing | Dead code path execution, unnecessary compile time overhead, bloated layouts. |
| **Separation of Concerns** | Isolate system responsibilities | Modular boundary isolation | Recompilation cascades, hard to optimize critical hot paths. |
| **Law of Demeter** | Minimize immediate collaborators | Strict encapsulation boundaries | Train wreck traversal calls, pointer chaining, fragile layout dependencies. |

### Separation of Concerns

Partition the system into distinct features with minimal overlap, typically implemented using a layered architecture:
1. **Controller Layer**: Handles incoming transport details (HTTP/gRPC) and request routing.
2. **Service Layer**: Implements core business rules, completely isolated from storage or transport logic.
3. **Repository Layer**: Coordinates database access and mapping.

### Law of Demeter

Objects must interact only with their immediate neighbors. Avoid nested object graph traversal (train wrecks) which leak layout details:
* **Violation**: `order.getCustomer().getAddress().getZipCode()`
* **Solution**: `order.getCustomerZipCode()`


---

## SOLID Design Principles

SOLID principles guide class hierarchy design, helping developers build codebases that are robust under changing requirements.

| Principle | Core Objective | Low Level Impact |
| --- | --- | --- |
| **Single Responsibility (SRP)** | One reason to change | Flat, cohesive source files; minimal recompilation domains. |
| **Open/Closed (OCP)** | Open for extension, closed for modification | Dynamic dispatch via stable vtable slots, preventing recompilation cascades. |
| **Liskov Substitution (LSP)** | Safe subtype substitution | Correct inheritance hierarchy, predictable virtual method behavior. |
| **Interface Segregation (ISP)** | Client specific narrow contracts | Reduced vtable sizes, minimal dependency pollution in headers. |
| **Dependency Inversion (DIP)** | Depend on abstractions | Decoupling of compile time dependencies, interface libraries. |

### Single Responsibility Principle (SRP)

A class must have exactly one reason to change, meaning it should encapsulate a single responsibility. Mixing business logic, persistence, and rendering in one class makes it fragile and difficult to test.

#### C++ Example

```cpp
#include <iostream>
#include <string>

using namespace std;

// Encapsulates content generation only
class Report {
public:
    string generateContent() const {
        return "Cohesive report content";
    }
};

// Encapsulates formatting/output concerns
class PDFPrinter {
public:
    void print(const Report& report) const {
        cout << "Rendering PDF: " << report.generateContent() << "\n";
    }
};

// Encapsulates I/O concerns
class FileStorage {
public:
    void save(const string& content) const {
        cout << "Saving content to storage...\n";
    }
};
```

---

### Open/Closed Principle (OCP)

Software entities must be open for extension but closed for modification. You should be able to introduce new behaviors without modifying existing source code.

This is achieved using dynamic polymorphism. Instead of hardcoding conditional branching on types, the client depends on an interface, and new types are introduced as new classes implementing that interface.

#### Low Level Impact: Recompilation Cascades
Without OCP, adding a new type requires modifying a central switch statement in a shared header file. This forces the compiler to recompile every source file that includes that header. Under OCP, a new subclass is placed in its own translation unit, avoiding recompilation of existing modules and minimizing build times.

#### C++ Example

```cpp
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual void process(double amount) = 0;
};

class CreditCardPayment : public PaymentMethod {
public:
    void process(double amount) override {
        cout << "Processing card payment: " << amount << "\n";
    }
};

class UpiPayment : public PaymentMethod {
public:
    void process(double amount) override {
        cout << "Processing UPI payment: " << amount << "\n";
    }
};

// Open for extension (can pass any PaymentMethod), closed for modification
class PaymentProcessor {
public:
    void execute(PaymentMethod& method, double amount) {
        method.process(amount);
    }
};
```

---

### Liskov Substitution Principle (LSP)

Subclasses must be substitutable for their base classes without altering the correctness of the program.

LSP ensures that the assumptions a client makes about a base class hold true when a derived class is substituted. The rules of LSP are categorized as follows:

| Rule Category | Specific Rule | Architectural Meaning / Impact |
| --- | --- | --- |
| **Signature Rules** | Covariant return types | Derived return types must be equal to or more specific than base return types. |
| **Signature Rules** | Contravariant arguments | Derived method arguments must be equal to or more general than base arguments. |
| **Signature Rules** | Exception constraints | Derived methods must not throw broader checked exceptions than base methods. |
| **Property Rules** | Class Invariants | Derived classes must preserve all conditions that hold true in the base class. |
| **Property Rules** | History Constraint | Derived classes must not allow mutations of state that are immutable in the base class. |
| **Method Rules** | Preconditions | Subclass methods must not require more restrictive inputs than base methods. |
| **Method Rules** | Postconditions | Subclass methods must guarantee at least what the base class methods guarantee. |

#### C++ Violation Example

A classic violation: `Bird` declares `fly()`, and `Penguin` inherits it but throws an exception. Any code calling `bird->fly()` on a `Penguin` pointer breaks at runtime — the substitution fails.

```cpp
// VIOLATION: Penguin cannot fulfil the fly() postcondition
class Bird {
public:
    virtual void fly() { cout << "Flying...\n"; }
};

class Penguin : public Bird {
public:
    void fly() override {
        throw runtime_error("Penguins cannot fly"); // Breaks caller assumptions
    }
};

void makeFly(Bird& b) { b.fly(); } // Crashes when passed a Penguin
```

#### C++ Correct Example

```cpp
#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

// Base class defining a broad category
class Bird {
public:
    virtual ~Bird() = default;
    virtual void eat() {
        cout << "Eating seeds...\n";
    }
};

// Intermediate class for birds that can fly
class FlyingBird : public Bird {
public:
    virtual void fly() {
        cout << "Flying high...\n";
    }
};

class Sparrow : public FlyingBird {
public:
    void eat() override {
        cout << "Sparrow eating...\n";
    }
    void fly() override {
        cout << "Sparrow flying...\n";
    }
};

// Penguin is a Bird, but cannot fly. It does not inherit from FlyingBird, preserving LSP.
class Penguin : public Bird {
public:
    void eat() override {
        cout << "Penguin eating fish...\n";
    }
};

void feedBird(Bird& bird) {
    bird.eat(); // Safe for all Bird subtypes
}
```

---

### Interface Segregation Principle (ISP)

Clients should not be forced to depend on methods they do not use. This principle promotes creating small, cohesive interfaces rather than large, multipurpose ones.

#### Low Level Impact: Vtable Pollution
When a class implements a large interface with unused methods, it must override those methods, polluting its `vtable` with empty functions or exception throwing stubs. Additionally, any change to the signature of an unused method in the large interface forces recompilation and relinking of all implementing classes.

#### C++ Example

```cpp
#include <iostream>

using namespace std;

// Segregated, single purpose interfaces
class Printer {
public:
    virtual ~Printer() = default;
    virtual void print() = 0;
};

class Scanner {
public:
    virtual ~Scanner() = default;
    virtual void scan() = 0;
};

// Concrete printer only implements what it uses
class SimplePrinter : public Printer {
public:
    void print() override {
        cout << "Printing document...\n";
    }
};

// Multi function device implements both interfaces
class MultiFunctionMachine : public Printer, public Scanner {
public:
    void print() override {
        cout << "Printing document...\n";
    }
    void scan() override {
        cout << "Scanning document...\n";
    }
};
```

---

### Dependency Inversion Principle (DIP)

High level modules must not depend on low level modules. Both must depend on abstractions. Furthermore, abstractions must not depend on details; details must depend on abstractions.

#### Architectural Meaning
DIP swaps compile time dependencies. Instead of the high level business logic importing concrete implementation headers, the business logic defines an abstract interface. The low level implementation modules import the interface header and implement it, reversing the dependency graph.

#### C++ Example

```cpp
#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Abstraction owned by the high level module domain
class MessageSender {
public:
    virtual ~MessageSender() = default;
    virtual void send(const string& message) = 0;
};

// Low level implementation detail
class EmailSender : public MessageSender {
public:
    void send(const string& message) override {
        cout << "Email dispatched: " << message << "\n";
    }
};

// High level module depending solely on the abstraction
class NotificationService {
private:
    shared_ptr<MessageSender> sender;

public:
    explicit NotificationService(shared_ptr<MessageSender> s) : sender(s) {}

    void notify(const string& message) {
        sender->send(message);
    }
};

int main() {
    auto emailService = make_shared<EmailSender>();
    NotificationService service(emailService);
    service.notify("System alert: CPU threshold exceeded");
    return 0;
}
```

> **DIP vs. Dependency Injection**: DIP is a design *principle* — high level modules must not depend on low level modules; both depend on abstractions. Dependency Injection (DI) is one *mechanism* to satisfy it: the abstraction is passed in (via constructor, setter, or factory) rather than instantiated internally. DIP can also be satisfied through template parameters (compile time injection) or service locators. Conflating DI with DIP is a common mistake — DI is the technique, DIP is the goal.

---

## SOLID Interactions

The five principles are not independent. They reinforce and sometimes tension each other:

| Interaction | Description |
| --- | --- |
| **OCP depends on LSP** | You can extend freely only if subtypes behave correctly. A broken substitution means every extension risks breaking existing clients. |
| **ISP enables DIP** | Narrow, focused interfaces are easier to invert. A fat interface forces high level modules to import more low level details than they need. |
| **OCP and SRP can conflict** | Each new extension class adds a responsibility axis. Keeping classes small (SRP) while making the system open to extension (OCP) requires deliberate interface design. |
| **SRP scopes LSP** | When each class has one responsibility, its contract is narrow and easy to honour in subclasses. Mixed responsibility classes produce wide contracts that subtypes struggle to fully satisfy. |
| **DIP is the mechanism OCP uses** | OCP says "closed for modification"; DIP is how you achieve that — the existing code depends on an abstraction, so new implementations extend without touching it. |