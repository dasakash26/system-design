# Decorator Design Pattern

The Decorator pattern is a structural design pattern that allows attaching new behaviors to objects dynamically by placing them inside special wrapper objects that contain these behaviors. It provides a flexible alternative to subclassing for extending functionality.

---

## Core Architecture

The Decorator pattern establishes a wrapper chain through a deliberate dual relationship:

- **IS-A (implements the interface)**: Every decorator conforms to the same `Component` interface as the object it wraps. This is what makes wrapping *transparent*, the client cannot distinguish a decorated object from an undecorated one. It hands a `Component&` to the client regardless of how many wrappers surround the real object.
- **HAS-A (owns a reference to a Component)**: Every decorator aggregates a reference to the next object in the chain. This is what enables *delegation* , a decorator calls the wrapped object's operation, augments the result, and returns it. The chain collapses through recursive delegation until the base `ConcreteComponent` produces the real value.

The pattern exploits both relationships simultaneously: IS-A allows transparent substitution; HAS-A enables chained augmentation. Neither alone produces a decorator — IS-A without HAS-A is plain inheritance; HAS-A without IS-A is a simple wrapper utility.

| Participant | Responsibility |
| --- | --- |
| **Component** | Defines the interface for objects that can have responsibilities added to them dynamically. |
| **ConcreteComponent** | Defines an object to which additional responsibilities can be attached. |
| **Decorator** | Maintains a reference to a Component object and defines an interface that conforms to Component's interface. |
| **ConcreteDecorator** | Adds responsibilities to the component. |

---

## Standard UML Representation

```mermaid
classDiagram
    direction TB
    class Component {
        <<interface>>
        +operation() string
    }
    class ConcreteComponent {
        +operation() string
    }
    class Decorator {
        <<abstract>>
        -component Component
        +operation() string
    }
    class ConcreteDecoratorA {
        +operation() string
        +addedBehavior()
    }
    class ConcreteDecoratorB {
        +operation() string
    }

    Component <|.. ConcreteComponent : realizes
    Component <|.. Decorator : realizes
    Component --o Decorator : wraps
    Decorator <|-- ConcreteDecoratorA : inherits
    Decorator <|-- ConcreteDecoratorB : inherits
```

---

## The Subclass Explosion Problem

* **Problem**: Extending a database client using static inheritance to support various combinations of caching, query logging, and encryption causes a combinatorial class growth:
  - `LoggingSqlDatabase`, `CachingSqlDatabase`, `LoggingCachingSqlDatabase`, etc.
* **Impact**: Rapid subclass explosion and massive code duplication.
* **Solution**: Compose a stack of wrappers dynamically at runtime (e.g. wrapping a `SqlDatabase` in a `CachingDatabase`, which is then wrapped in a `LoggingDatabase`).

---

## Example (Database Client Wrappers)

Below is the UML class diagram for the Database Client Wrappers scenario:

```mermaid
classDiagram
    direction TB
    class Database {
        <<interface>>
        +readData(key string) string
    }
    class SqlDatabase {
        +readData(key string) string
    }
    class DatabaseDecorator {
        <<abstract>>
        #wrappedDatabase unique_ptr~Database~
        +DatabaseDecorator(db unique_ptr~Database~)
        +readData(key string) string
    }
    class CachingDatabase {
        -cache map~string_string~
        +CachingDatabase(db unique_ptr~Database~)
        +readData(key string) string
    }
    class LoggingDatabase {
        +LoggingDatabase(db unique_ptr~Database~)
        +readData(key string) string
    }

    Database <|.. SqlDatabase : realizes
    Database <|.. DatabaseDecorator : realizes
    Database --o DatabaseDecorator : wraps / delegates
    DatabaseDecorator <|-- CachingDatabase : inherits
    DatabaseDecorator <|-- LoggingDatabase : inherits
```

This C++ implementation demonstrates a database query execution pipeline wrapped with caching and logging behaviors using modern memory management.

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>

using namespace std;

// Component Interface
class Database {
public:
    virtual ~Database() = default;
    virtual string readData(const string& key) = 0;
};

// Base Decorator (Is A & Has A)
class DatabaseDecorator : public Database {
protected:
    unique_ptr<Database> wrappedDatabase; // Has A ownership delegation

public:
    explicit DatabaseDecorator(unique_ptr<Database> db) 
        : wrappedDatabase(move(db)) {}
};

// Concrete Component
class SqlDatabase : public Database {
public:
    string readData(const string& key) override {
        cout << "-> Executing raw SQL query to fetch: " << key << "\n";
        return "ValueFor_" + key;
    }
};

// Concrete Decorator - Logging
class LoggingDatabase : public DatabaseDecorator {
public:
    explicit LoggingDatabase(unique_ptr<Database> db) : DatabaseDecorator(move(db)) {}
    
    string readData(const string& key) override {
        cout << "[LOG] Initiating read operation for key: " << key << "\n";
        string result = wrappedDatabase->readData(key);
        cout << "[LOG] Read operation finished.\n";
        return result;
    }
};

// Concrete Decorator - Caching
class CachingDatabase : public DatabaseDecorator {
private:
    unordered_map<string, string> cache;

public:
    explicit CachingDatabase(unique_ptr<Database> db) : DatabaseDecorator(move(db)) {}
    
    string readData(const string& key) override {
        auto it = cache.find(key);
        if (it != cache.end()) {
            cout << "[CACHE] Hit! Returning cached result for key: " << key << "\n";
            return it->second;
        }
        
        cout << "[CACHE] Miss. Delegating downstream...\n";
        string result = wrappedDatabase->readData(key);
        cache[key] = result; // Write to cache
        return result;
    }
};

// Client Flow
int main() {
    // 1. Create base DB client
    unique_ptr<Database> db = make_unique<SqlDatabase>();

    // 2. Add Caching behavior
    db = make_unique<CachingDatabase>(move(db));

    // 3. Add Logging behavior
    db = make_unique<LoggingDatabase>(move(db));

    // First request - Cache Miss -> SQL execution
    cout << "--- First Query ---\n";
    string data1 = db->readData("user_101");
    cout << "Data: " << data1 << "\n";

    // Second request - Cache Hit -> No SQL execution
    cout << "\n--- Second Query (Duplicate) ---\n";
    string data2 = db->readData("user_101");
    cout << "Data: " << data2 << "\n";

    return 0;
}
```

---

## Concurrency & Design Considerations

* **Pipeline Thread Safety**: If the wrapped component or decorators maintain mutable state (such as the cache map in `CachingDatabase`), access must be protected using standard locks (`std::mutex` or `std::shared_mutex`).
* **Stateless Decorators**: If components are entirely stateless behavioral extensions, the pipeline is thread safe by default and needs no synchronization locks.

---

## Design Tradeoffs

| Advantages & SOLID Alignment | Drawbacks & Limitations |
| --- | --- |
| **SRP Alignment**: Segregates individual concerns (caching, logging) into separate wrapper classes. | **Removal Complexity**: Once nested, it is difficult to inspect or remove a specific decorator from deep within a wrapper chain. |
| **Extensibility**: Allows nesting and combining multiple independent behaviors dynamically at runtime. | **Debugging Indirection**: Call tracing and debugging become complex due to deep delegation call stacks passing through multiple wrappers. |

### Decorator vs. Strategy vs. Adapter

All three patterns wrap or delegate to another object. The intent determines the choice:

| Pattern | Interface Change | Behavior Change | Use When |
| --- | --- | --- | --- |
| **Decorator** | None (same interface) | Adds behavior around the original | Layering cross cutting concerns transparently |
| **Strategy** | None (same context) | Replaces the core algorithm | Swapping interchangeable algorithms at runtime |
| **Adapter** | Yes (converts interface) | No new behavior, only translation | Bridging incompatible existing interfaces |
