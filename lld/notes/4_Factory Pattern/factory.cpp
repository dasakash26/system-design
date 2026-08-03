#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>

using namespace std;

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
