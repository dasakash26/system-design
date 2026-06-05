# Factory Pattern

---

## Core Idea

A factory is a **centralized creator** that returns the correct object so the client doesn’t decide *how or which* object to create.

```
client → asks for type
factory → decides + creates
client → uses abstraction
```

This removes:

```
scattered new calls
tight coupling to concrete classes
duplicate creation logic
```

---

## Problem → Solution Mapping

Without factory:

```
if(type == "email") new Email()
if(type == "sms") new SMS()
(repeated everywhere)
```

With factory:

```
NotificationFactory.create(type)
(single decision point)
```

Result:

```
change happens in one place only
client code remains untouched
```

---

## Simple Factory (What you actually use)

### Structure

```cpp
class Notification {
public:
    virtual void send(string msg) = 0;
};

class EmailNotification : public Notification {
public:
    void send(string msg) override { }
};

class SMSNotification : public Notification {
public:
    void send(string msg) override { }
};

class NotificationFactory {
public:
    static unique_ptr<Notification> create(string type) {
        if (type == "email") return make_unique<EmailNotification>();
        if (type == "sms") return make_unique<SMSNotification>();
        throw invalid_argument("invalid");
    }
};
```

---

### Flow

```
input (type)
→ factory decides
→ object created
→ returned as base type
```

---

## Factory Method (Conceptual Upgrade)

Moves creation into subclasses.

```
no central if/else
each factory knows what to create
```

Structure:

```
Factory (base) → create()
ConcreteFactory → overrides create()
```

---

### When it Helps

```
when creation logic itself varies a lot
when you want polymorphic factories
```

---

## Abstract Factory (Family Creation)

Creates **related objects together**.

```
one factory → multiple products
ensures compatibility
```

Example thinking:

```
DarkFactory → DarkButton + DarkInput
LightFactory → LightButton + LightInput
```

---

## Strategy vs Factory (Clear Separation)

```
Factory → which object to create
Strategy → how object behaves
```

```
Factory = creation time decision
Strategy = runtime behavior switch
```

---

## Where to Use (Pattern Recognition)

```
multiple types based on input/config
"support X, Y, Z types"
avoid new in business logic
```

---

## Design Impact

```
coupling ↓
extensibility ↑
code clarity ↑
testing easier (mock factory / interface)
```

---

## Tradeoffs

```
adds indirection
can be overkill for simple cases
simple factory still violates strict OCP
```

---

## One-Line Summary

```
Factory = isolate object creation so the rest of the system depends only on abstractions
```