# Case Study: Notification System

This case study covers the requirements, class design, and thread safe implementation for an extensible **Notification System**.

---

## Requirements

### Functional Requirements
*   **Dynamic Formatting**: Support dynamically wrapping and modifying base message content before transmission (e.g., automatically prepending timestamps or appending custom signature disclaimers).
*   **Decoupled Observation & Action**: Allow multiple downstream systems (such as a file logger or a delivery engine) to automatically receive updates whenever a new notification is posted, without the posting service needing to know the details of those downstream systems.
*   **Multiple Delivery Channels**: Support delivering notification payloads via different communication channels (e.g., Email, SMS, or Desktop popup notifications) dynamically at runtime.
*   **Centralised Gateway**: Provide a single entry point to trigger notification requests, manage the registration of listening handlers, and access the system's notification logs.

### Non Functional Requirements
*   **Thread Safety**: Ensure safe concurrent execution in multi-threaded environments. Protect the subscription registry, strategy dispatcher list, and notification history log from race conditions.
*   **Memory Management**: Prevent memory leaks by cleaning up nested decorator chains recursively.

### Scope Boundaries
*   **In Scope**: Thread safe event listener registration, dynamic message wrapping and formatting, polymorphism for message delivery channels.
*   **Out of Scope**: Real gateway network transmissions, SMTP/SMS server setup, parsing templates.

---

## Class Design

Below is the conceptual UML diagram showing how the Observer, Decorator, Strategy, and Singleton patterns coordinate:

![Notification Diagram](image.jpg)

---

## Complete Code

Below is the complete, thread safe C++ implementation aligned with **Lecture 14 (NotificationSystemUpdated)**:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <mutex>
#include <memory>

// ==========================================
// 1. DECORATOR PATTERN: NOTIFICATIONS
// ==========================================

// Component Interface
class INotification {
public:
    virtual ~INotification() = default;
    virtual std::string getContent() const = 0;
};

// Concrete Component
class SimpleNotification : public INotification {
private:
    std::string text;
public:
    SimpleNotification(const std::string& msg) : text(msg) {}
    std::string getContent() const override {
        return text;
    }
};

// Abstract Decorator (Recursive delete ensures cleanup of the wrapper chain)
class INotificationDecorator : public INotification {
protected:
    std::unique_ptr<INotification> wrappedNotification;
public:
    INotificationDecorator(INotification* n) : wrappedNotification(n) {}
};

// Concrete Decorator: Timestamp
class TimestampDecorator : public INotificationDecorator {
public:
    TimestampDecorator(INotification* n) : INotificationDecorator(n) {}
    std::string getContent() const override {
        return "[2026-06-05 22:00:00] " + wrappedNotification->getContent();
    }
};

// Concrete Decorator: Signature
class SignatureDecorator : public INotificationDecorator {
private:
    std::string signature;
public:
    SignatureDecorator(INotification* n, const std::string& sig) 
        : INotificationDecorator(n), signature(sig) {}
    std::string getContent() const override {
        return wrappedNotification->getContent() + "\n-- " + signature;
    }
};

// ==========================================
// 2. OBSERVER PATTERN: OBSERVABLE REGISTRY
// ==========================================

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update() = 0;
};

class IObservable {
public:
    virtual ~IObservable() = default;
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

// Thread-Safe Concrete Observable
class NotificationObservable : public IObservable {
private:
    std::vector<IObserver*> observers;
    INotification* currentNotification = nullptr;
    std::mutex registryMutex; // Protects the subscriber list

public:
    void addObserver(IObserver* obs) override {
        std::lock_guard<std::mutex> lock(registryMutex);
        if (std::find(observers.begin(), observers.end(), obs) == observers.end()) {
            observers.push_back(obs);
        }
    }

    void removeObserver(IObserver* obs) override {
        std::lock_guard<std::mutex> lock(registryMutex);
        auto it = std::find(observers.begin(), observers.end(), obs);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyObservers() override {
        std::vector<IObserver*> snapshot;
        {
            std::lock_guard<std::mutex> lock(registryMutex);
            snapshot = observers; // Take a snapshot to prevent deadlocks during callbacks
        }
        for (IObserver* obs : snapshot) {
            obs->update();
        }
    }

    void setNotification(INotification* notification) {
        currentNotification = notification;
        notifyObservers();
    }

    std::string getNotificationContent() const {
        return currentNotification ? currentNotification->getContent() : "";
    }
};

// ==========================================
// 3. SINGLETON PATTERN: CENTRAL COORDINATOR
// ==========================================

class NotificationService {
private:
    NotificationObservable* observable;
    std::vector<std::shared_ptr<INotification>> history;
    std::mutex historyMutex; // Protects the history logs
    static NotificationService* instance;
    static std::mutex instanceMutex;

    NotificationService() {
        observable = new NotificationObservable();
    }

public:
    // Thread-safe Double-Checked Locking Singleton
    static NotificationService* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(instanceMutex);
            if (instance == nullptr) {
                instance = new NotificationService();
            }
        }
        return instance;
    }

    NotificationObservable* getObservable() const {
        return observable;
    }

    void sendNotification(INotification* notification) {
        {
            std::lock_guard<std::mutex> lock(historyMutex);
            history.push_back(std::shared_ptr<INotification>(notification)); // Log history
        }
        observable->setNotification(notification);
    }

    ~NotificationService() {
        delete observable;
    }
};

// Initialize static members
NotificationService* NotificationService::instance = nullptr;
std::mutex NotificationService::instanceMutex;

// ==========================================
// 4. STRATEGY PATTERN: DELIVERY METHODS
// ==========================================

class INotificationStrategy {
public:
    virtual ~INotificationStrategy() = default;
    virtual void sendNotification(const std::string& content) = 0;
};

class EmailStrategy : public INotificationStrategy {
private:
    std::string emailId;
public:
    EmailStrategy(const std::string& email) : emailId(email) {}
    void sendNotification(const std::string& content) override {
        std::cout << "[Email Strategy] Dispatching to " << emailId << ":\n" << content << "\n\n";
    }
};

class SMSStrategy : public INotificationStrategy {
private:
    std::string mobileNumber;
public:
    SMSStrategy(const std::string& phone) : mobileNumber(phone) {}
    void sendNotification(const std::string& content) override {
        std::cout << "[SMS Strategy] Dispatching to " << mobileNumber << ":\n" << content << "\n\n";
    }
};

class PopUpStrategy : public INotificationStrategy {
public:
    void sendNotification(const std::string& content) override {
        std::cout << "[Popup Strategy] Toast alert:\n" << content << "\n\n";
    }
};

// ==========================================
// 5. CONCRETE OBSERVERS
// ==========================================

class Logger : public IObserver {
private:
    NotificationObservable* notificationObservable;
public:
    Logger() {
        notificationObservable = NotificationService::getInstance()->getObservable();
        notificationObservable->addObserver(this);
    }
    void update() override {
        std::cout << "[Logger Observer] New activity logged:\n" 
                  << notificationObservable->getNotificationContent() << "\n\n";
    }
};

class NotificationEngine : public IObserver {
private:
    NotificationObservable* notificationObservable;
    std::vector<std::unique_ptr<INotificationStrategy>> strategies;
    std::mutex engineMutex; // Protects strategies vector

public:
    NotificationEngine() {
        notificationObservable = NotificationService::getInstance()->getObservable();
        notificationObservable->addObserver(this);
    }

    void addNotificationStrategy(INotificationStrategy* ns) {
        std::lock_guard<std::mutex> lock(engineMutex);
        strategies.push_back(std::unique_ptr<INotificationStrategy>(ns));
    }

    void update() override {
        std::string content = notificationObservable->getNotificationContent();
        std::vector<INotificationStrategy*> snapshot;
        {
            std::lock_guard<std::mutex> lock(engineMutex);
            for (auto& s : strategies) {
                snapshot.push_back(s.get());
            }
        }
        for (auto strategy : snapshot) {
            strategy->sendNotification(content);
        }
    }
};

// ==========================================
// 6. CLIENT DRIVER FLOW
// ==========================================

int main() {
    NotificationService* service = NotificationService::getInstance();

    // Auto-registering observers to the centralized service
    std::unique_ptr<Logger> logger = std::make_unique<Logger>();
    std::unique_ptr<NotificationEngine> engine = std::make_unique<NotificationEngine>();

    // Inject strategies
    engine->addNotificationStrategy(new EmailStrategy("developer@company.com"));
    engine->addNotificationStrategy(new SMSStrategy("+91 9999999999"));
    engine->addNotificationStrategy(new PopUpStrategy());

    std::cout << "--- Triggering Notification Flow ---" << std::endl;
    // Create base message, decorate it, and send
    INotification* notification = new SimpleNotification("Deployment Succeeded!");
    notification = new TimestampDecorator(notification);
    notification = new SignatureDecorator(notification, "System Admin");

    service->sendNotification(notification);

    return 0;
}
```

---

## Concurrency & Synchronization

To satisfy production grade expectations, shared resources are locked:
1.  **Observable Subscription**: Adding/removing observers on `NotificationObservable` uses a `std::lock_guard<std::mutex>` on `registryMutex`.
2.  **Notification Dispatches**: Inside `NotificationObservable::notifyObservers()`, a copy snapshot of the observers vector is taken inside the lock boundary. The loop itself executes outside the lock, preventing deadlocks if an observer's `update()` calls subscribe/unsubscribe.
3.  **Singleton Double Checked Locking**: Inside `NotificationService::getInstance()`, double checked locking using `instanceMutex` guarantees thread safety during initialization.
4.  **Notification History Log**: Adding entries to `NotificationService::history` is protected by `historyMutex`.
5.  **Strategies List**: Modifying strategies inside `NotificationEngine` concurrently uses `engineMutex`.

---

## SOLID Trade-offs

### SOLID Principles Satisfied
*   **Open/Closed Principle (OCP)**: We can add new notification decorators (e.g. `EncryptionDecorator`) or new notification channels (e.g. `SlackStrategy`) without modifying any of the engine's core orchestration code.
*   **Single Responsibility Principle (SRP)**: Notification composition (Decorator), routing tracking (Observer), and channel delivery (Strategy) are encapsulated into separate, modular components.

### Design Drawbacks & Tradeoffs
*   **Subclass Explosion of Decorators**: While decorators avoid class explosion of combinations compared to traditional inheritance, adding many small decorators still results in long wrapper chains that can become complex to debug and trace.
*   **Memory Management Overhead**: Since C++ does not feature garbage collection, using raw pointer decorator chains requires precise parent-decorator destructors or smart pointers (`std::unique_ptr`) to avoid memory leaks.
