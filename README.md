# Low Level Design

> A production-grade reference for Object Oriented Design, Design Patterns, and System Architecture, written with the depth and vocabulary of an advanced system design textbook.

---

## Overview

Personal study notes for mastering **Low Level Design (LLD)** and **Object Oriented Design (OOD)**. Every note covers low level memory mechanics, thread safety primitives, pattern interaction analysis, and compile ready C++ implementations.

---

## Structure

```
lld/
├── notes/               ← Design pattern theory, UML, C++ examples
│   ├── 0_OOP Concepts
│   ├── 1_Software Design Principles
│   ├── 2_Delivery Framework
│   ├── 3_Strategy Pattern
│   ├── 4_Factory Pattern
│   ├── 5_Singleton Pattern
│   ├── 6_Observer Pattern
│   ├── 7_Decorator Pattern
│   ├── 8_Command Pattern
│   ├── 9_Adapter Pattern
│   └── 10_Facade Pattern
├── projects/            ← Full system case studies (end to end)
│   ├── 0_Notepad
│   ├── 1_Zomato
│   └── 2_Notification
└── course/              ← Raw lecture implementation files
```

---

## Pattern Catalog

| # | Pattern | Category | Core Problem Solved |
|---|---------|----------|---------------------|
| 01 | [OOP Concepts](notes/0_OOP%20Concepts/0_OOP%20Concepts.md) | Foundation | Encapsulation, inheritance, polymorphism, vtable mechanics |
| 02 | [SOLID Principles](notes/1_Software%20Design%20Principles/1_Software%20Design%20Principles.md) | Foundation | Recompilation cascades, vtable pollution, interface contracts |
| 03 | [LLD Delivery Framework](notes/2_Delivery%20Framework/2_Delivery%20Framework.md) | Framework | Structured 5-phase approach for 45-minute design interviews |
| 04 | [Strategy](notes/3_Strategy%20Pattern/3_Strategy%20Pattern.md) | Behavioral | Eliminating rigid algorithm coupling via runtime composition |
| 05 | [Factory Method](notes/4_Factory%20Pattern/4_Factory%20Pattern.md) | Creational | Decoupling clients from concrete type instantiation |
| 06 | [Singleton](notes/5_Singleton%20Pattern/5_Singleton%20Pattern.md) | Creational | Thread safe single instance access with memory order guarantees |
| 07 | [Observer](notes/6_Observer%20Pattern/6_Observer%20Pattern.md) | Behavioral | Decoupled one to many state synchronization and event dispatch |
| 08 | [Decorator](notes/7_Decorator%20Pattern/7_Decorator%20Pattern.md) | Structural | Replacing combinatorial subclass explosion with composable wrappers |
| 09 | [Command](notes/8_Command%20Pattern/8_Command%20Pattern.md) | Behavioral | Encapsulating requests as objects for undo/redo and queuing |
| 10 | [Adapter](notes/9_Adapter%20Pattern/9_Adapter%20Pattern.md) | Structural | Bridging incompatible interfaces without modifying either side |
| 11 | [Facade](notes/10_Facade%20Pattern/10_Facade%20Pattern.md) | Structural | Enforcing the Law of Demeter over complex subsystem graphs |

---

## Case Studies

Full end-to-end low level designs covering requirements, class diagrams,  C++ implementation, code analysis, and SOLID tradeoffs.

---

### [Notepad — Document Editor](projects/0_Notepad/0_Notepad.md)

>Document editor with a mixed content hierarchy and pluggable storage backends.

| Pattern | Role in System |
|---------|----------------|
| **Composite** | Uniform treatment of text, images, newlines, and tab spaces as document nodes |
| **Strategy** | Swappable persistence backends (file system, database) without altering the editor |
| **Facade** | `DocumentEditor` as a single orchestration surface hiding composition internals |

---

### [Zomato — Food Delivery System](projects/1_Zomato/1_Zomato.md)

> Food ordering platform with abstract order factories, payment gateways, and singleton manager registries.

| Pattern | Role in System |
|---------|----------------|
| **Factory Method** | Instant and scheduled order creation with distinct dispatch logic |
| **Strategy** | Pluggable payment gateways (UPI, card) resolved at checkout time |
| **Singleton** | Thread safe global registries for restaurants and order history |
| **Facade** | `TomatoApp` as the unified client entry point |

---

### [Notification System](projects/2_Notification/2_Notification.md)

> Extensible multi-channel notification dispatcher with dynamic message formatting and subscriber routing.

| Pattern | Role in System |
|---------|----------------|
| **Decorator** | Dynamic message wrapping — timestamps and signatures layered at runtime |
| **Observer** | Logger and delivery engine auto-triggered on new notification events |
| **Strategy** | Modular delivery channels — Email, SMS, Desktop popup |
| **Singleton** | Centralized `NotificationService` coordinating history and dispatch |

---

## Sources

- [Coder Army LLD Playlist](https://youtube.com/playlist?list=PLQEaRBV9gAFvzp6XhcNFpk1WdOcyVo9qT&si=Ihevlxfa3nczoXp0)
- Hello Interview
- Gang of Four — *Design Patterns: Elements of Reusable Object Oriented Software*
