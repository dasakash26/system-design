# Software Design Principles

Core goal of software design:

```
low coupling
high cohesion
maintainability
extensibility
predictable behavior
```

Two categories:

```
General Design Principles
SOLID (Object Oriented Design Principles)
```

---

# General Software Design Principles

---

# KISS — Keep It Simple, Stupid

## Idea

Prefer the **simplest solution that satisfies the requirement**.

Complex systems fail because:

```
more components
more interactions
more hidden bugs
harder reasoning
```

Simplicity reduces:

```
bug surface
maintenance cost
cognitive load
```

---

## Key Rule

```
If two designs work, choose the simpler one.
```

---

## Example

### Bad

Over-engineered design for simple task.

```
UserService
UserServiceFactory
UserServiceManager
UserValidatorStrategy
UserPersistenceStrategy
```

For simply creating a user.

---

### Good

```
UserService
    createUser()
```

Add abstraction **only when complexity appears**.

---

## Engineering Insight

Complexity often comes from:

```
premature abstraction
unnecessary patterns
trying to predict the future
```

---

# DRY — Don't Repeat Yourself

## Idea

Every **piece of knowledge** should exist **in one place only**.

Duplication creates:

```
inconsistent logic
bug propagation
maintenance difficulty
```

---

## Example

### Bad

```
if(user.age >= 18)
if(customer.age >= 18)
if(member.age >= 18)
```

Business rule repeated.

---

### Good

```
isAdult(age)
```

Centralized rule.

---

## DRY Applies To

```
business rules
algorithms
configuration
database queries
constants
validation logic
```

---

## Important Note

DRY **does not mean removing all duplication blindly**.

Sometimes duplication is safer than premature abstraction.

---

# YAGNI — You Aren't Gonna Need It

## Idea

Do not implement functionality **until it is required**.

Premature development causes:

```
unused code
unnecessary abstraction
system complexity
maintenance burden
```

---

## Example

Bad

```
interface StorageProvider
S3Storage
AzureStorage
LocalStorage
```

When system only uses local storage.

---

Good

```
LocalStorage
```

Add abstraction when second implementation appears.

---

## Philosophy

```
build what is needed now
extend when required
```

---

# Separation of Concerns

## Idea

Each part of a system should handle **one concern**.

Concerns are different aspects of a system:

```
UI
business logic
data access
authentication
validation
network communication
```

---

## Problem Without Separation

```
tightly coupled modules
difficult testing
hard to modify
large classes
```

---

## Bad Design

```
class UserController

    validateInput()
    calculateDiscount()
    saveToDatabase()
    sendEmail()
    renderHTML()
```

Multiple responsibilities.

---

## Good Design

```
Controller
Service
Repository
```

Architecture

```
Controller → handles HTTP request
Service → business logic
Repository → database operations
```

Flow

```
Request
  ↓
Controller
  ↓
Service
  ↓
Repository
  ↓
Database
```

---

## Benefits

```
independent testing
clear responsibilities
easy replacement
maintainable architecture
```

---

# Law of Demeter (Principle of Least Knowledge)

## Idea

Objects should interact **only with their immediate collaborators**.

An object should only call methods of:

```
itself
its own fields
objects passed as parameters
objects it creates
```

---

## Problem: Deep Navigation

Bad code exposes internal structure.

```
order.getCustomer().getAddress().getZipCode()
```

Order now depends on:

```
Customer
Address
Zip structure
```

This creates **tight coupling**.

---

## Better Design

Encapsulate the logic.

```
order.getCustomerZipCode()
```

Internally:

```
return customer.address.zip
```

---

## Why It Matters

Changes inside objects should **not break other classes**.

---

## Train Wreck Code

Bad chain calls.

```
a.getB().getC().getD().doSomething()
```

Signals:

```
poor encapsulation
tight coupling
fragile design
```

---

# Object-Oriented Design Principles (SOLID)

SOLID helps build:

```
maintainable
scalable
extensible
loosely coupled systems
```

---

# SRP — Single Responsibility Principle

## Definition

A class should have **one reason to change**.

This means it should handle **one responsibility**.

---

## Bad Design

```cpp
 class Report {
 public:
   std::string generateContent() { return "content"; }
   void printToPDF() { /* PDF formatting */ }
   void saveToFile() { /* file I/O */ }
 };
```

Responsibilities:

```
business logic
persistence
presentation
```

---

## Good Design

```cpp
 class Report {
 public:
   std::string generateContent() { return "content"; }
 };
 
 class PDFPrinter {
 public:
   void print(const Report& /*report*/) { /* PDF formatting */ }
 };
 
 class FileStorage {
 public:
   void save(const std::string& /*content*/) { /* file I/O */ }
 };
```

Each class focuses on **one responsibility**.

---

## Benefits

```
smaller classes
easier testing
clear ownership
independent changes
```

---

# OCP — Open/Closed Principle

## Definition

Software entities should be:

```
open for extension
closed for modification
```

Meaning:

```
new behavior added without changing existing code
```

---

## Bad Design

```cpp
 class PaymentProcessor {
 public:
   void process(const std::string& type, double amount) {
     if (type == "credit") {
       // credit card logic
     } else if (type == "paypal") {
       // paypal logic
     }
     // Adding crypto means modifying this method
     (void)amount;
   }
 };
```

Adding new payment modifies existing code.

---

## Good Design

Use polymorphism.

```cpp
 class PaymentMethod {
 public:
   virtual ~PaymentMethod() = default;
   virtual void process(double amount) = 0;
 };
 
 class CreditCardPayment : public PaymentMethod {
 public:
   void process(double /*amount*/) override { /* credit card logic */ }
 };
 
 class PayPalPayment : public PaymentMethod {
 public:
   void process(double /*amount*/) override { /* paypal logic */ }
 };
 
 class CryptoPayment : public PaymentMethod {
 public:
   void process(double /*amount*/) override { /* crypto logic */ }
 };
 
 class PaymentProcessor {
 public:
   void process(PaymentMethod& method, double amount) {
     method.process(amount);
   }
 };

```

New payment type → new class. Existing system unchanged.

---

# LSP ( Liskov Substitution Principle )

## Definition

Subtypes must be **substitutable for their base types**.

If `S` is a subtype of `T`:

```
objects of T can be replaced with objects of S
without breaking program behavior
```

## Bad Example

```cpp
 class Bird {
 public:
   virtual ~Bird() = default;
   virtual void fly() { /* flying logic */ }
 };
 
 class Penguin : public Bird {
 public:
   void fly() override {
     throw std::runtime_error("Penguins can't fly");
   }
 };
```

Code expecting Bird may break.

## Correct Design

```cpp
 class Bird {
 public:
   virtual ~Bird() = default;
   virtual void eat() = 0;
 };
 
 class FlyingBird : public Bird {
 public:
   virtual void fly() = 0;
 };
 
 class Sparrow : public FlyingBird {
 public:
   void eat() override { /* eating */ }
   void fly() override { /* flying */ }
 };
 
 class Penguin : public Bird {
 public:
   void eat() override { /* eating */ }
 };
```

Now behaviour matches hierarchy.

## LSP Violation Signals

```
overridden methods throwing exceptions
changing expected behavior
conditional logic checking subtype
```

Example

```
if(bird instanceof Penguin)
```

Indicates broken hierarchy.

## Rules for Correct Substitution

---

### 1. Signature Rules

Method structure must remain compatible.

```
arguments → same or more general
return type → same or more specific
exceptions → should not be broader than parent
```

### 2. Property Rules

Subclass must preserve **state correctness**.

### Invariants

```
conditions that must always hold true
child must not break them
```

Example:

```
balance >= 0 must always remain true
```

### History Constraint

```
object behavior over time must remain consistent
```

Bad:

```
parent: immutable
child: mutable
```

### 3. Method Rules

### a. Do NOT strengthen preconditions

```
child should accept everything parent accepts
```

Bad:

```
parent: withdraw(amount > 0)
child: withdraw(amount > 1000)
```

### b. Do NOT weaken postconditions

```
child must guarantee at least what parent guarantees
```

Bad:

```
parent: returns valid object
child: returns null
```

---

## Mental Model

```
input → more flexible in child
output → more strict / reliable in child
```

---

# ISP — Interface Segregation Principle

## Idea

Clients should not depend on **methods they do not use**.

Large interfaces force unnecessary implementation.

---

## Bad Interface

```
interface Machine
    print()
    scan()
    fax()
```

Printer must implement scan and fax.

---

## Good Interfaces

```
interface Printer
    print()

interface Scanner
    scan()
```

Classes implement only what they need.

---

## Benefits

```
smaller contracts
reduced coupling
clear interfaces
better modularity
```

---

# DIP — Dependency Inversion Principle

## Idea

High-level modules should not depend on low-level modules.

Both depend on **abstractions**.

---

## Bad Design

```cpp
 class EmailSender {
 public:
   void send(const std::string& /*message*/) { /* send email */ }
 };
 
 class NotificationService {
 public:
   void notify(const std::string& message) {
     emailSender.send(message);
   }
 
 private:
   EmailSender emailSender;
 };

```

Direct dependency.

Take a look at this NotificationService that's tightly coupled to a specific email implementation.

---

## Good Design

```cpp
 class MessageSender {
 public:
   virtual ~MessageSender() = default;
   virtual void send(const std::string& message) = 0;
 };
 
 class EmailSender : public MessageSender {
 public:
   void send(const std::string& /*message*/) override { /* send email */ }
 };
 
 class NotificationService {
 public:
   explicit NotificationService(MessageSender& sender) : sender(sender) {}
 
   void notify(const std::string& message) {
     sender.send(message);
   }
 
 private:
   MessageSender& sender;
 };
```

---

## Benefits

```
loose coupling
testability
flexibility
easy swapping of implementations
```

Example

```
pass SMSsender to send sms
```

---

# How These Principles Work Together

Good system architecture usually follows:

```
KISS -> Start simple, add complexity only when needed
```

```
DRY -> Reduce duplication, simplify maintenance
```

```
YAGNI -> Build for today, not hypothetical futures
```

```
Separation of Concerns -> Enable independent testing and changes
```

```
Law of Demeter -> Reduce coupling, hide internal structure
```

```
SOLID -> Maintainable object oriented design

SRP → Keep classes focused on one responsibility
OCP → Support future requirements without modifying existing code
LSP → Prevent brittle hierarchies that break at runtime
ISP → Keep interfaces clean and focused
DIP → Decouple business logic from implementation details
```

---

# Desired System Properties

When principles are applied correctly:

```
high cohesion
low coupling
clear module boundaries
easy testing
predictable code
scalable architecture
```

---

# Practical Mental Model

When designing a system always ask:

```
Does this class have one responsibility?      (SRP)

Will new features require modifying old code? (OCP)

Can subclasses replace base classes safely?   (LSP)

Are interfaces too large?                     (ISP)

Are we depending on abstractions?             (DIP)

Is this solution unnecessarily complex?       (KISS)

Are we repeating logic?                       (DRY)

Are we building unused features?              (YAGNI)

Are responsibilities clearly separated?       (SoC)

Are objects exposing too much internal data?  (Law of Demeter)
```