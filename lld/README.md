# Low Level Design (LLD)

Personal study notes, patterns, and end-to-end implementations for Object-Oriented Design (OOD).

---

## Structure

- [**Notes**](./notes): Core OOP concepts, SOLID principles, and design patterns.
- [**Projects**](./projects): Case studies and system implementations.
- [**Lectures**](./lectures): Lecture implementation files.

---

## Pattern Catalog

| # | Pattern | Category | Core Problem Solved |
|---|---------|----------|---------------------|
| 01 | [OOP Concepts](./notes/0_OOP%20Concepts/0_OOP%20Concepts.md) | Foundation | Encapsulation, inheritance, polymorphism, vtable mechanics |
| 02 | [SOLID Principles](./notes/1_Software%20Design%20Principles/1_Software%20Design%20Principles.md) | Foundation | Recompilation cascades, vtable pollution, interface contracts |
| 03 | [LLD Delivery Framework](./notes/2_Delivery%20Framework/2_Delivery%20Framework.md) | Framework | Structured 5-phase approach for 45-minute design interviews |
| 04 | [Strategy](./notes/3_Strategy%20Pattern/3_Strategy%20Pattern.md) | Behavioral | Eliminating rigid algorithm coupling via runtime composition |
| 05 | [Factory Method](./notes/4_Factory%20Pattern/4_Factory%20Pattern.md) | Creational | Decoupling clients from concrete type instantiation |
| 06 | [Singleton](./notes/5_Singleton%20Pattern/5_Singleton%20Pattern.md) | Creational | Thread safe single instance access with memory order guarantees |
| 07 | [Observer](./notes/6_Observer%20Pattern/6_Observer%20Pattern.md) | Behavioral | Decoupled one to many state synchronization and event dispatch |
| 08 | [Decorator](./notes/7_Decorator%20Pattern/7_Decorator%20Pattern.md) | Structural | Replacing combinatorial subclass explosion with composable wrappers |
| 09 | [Command](./notes/8_Command%20Pattern/8_Command%20Pattern.md) | Behavioral | Encapsulating requests as objects for undo/redo and queuing |
| 10 | [Adapter](./notes/9_Adapter%20Pattern/9_Adapter%20Pattern.md) | Structural | Bridging incompatible interfaces without modifying either side |
| 11 | [Facade](./notes/10_Facade%20Pattern/10_Facade%20Pattern.md) | Structural | Enforcing the Law of Demeter over complex subsystem graphs |

---

## Case Studies

- [**Notepad — Document Editor**](./projects/0_Notepad/0_Notepad.md): Document editor with a mixed content hierarchy and pluggable storage backends (Composite, Strategy, Facade).
- [**Zomato — Food Delivery System**](./projects/1_Zomato/1_Zomato.md): Food ordering platform with abstract order factories, payment gateways, and singleton registries (Factory Method, Strategy, Singleton, Facade).
- [**Notification System**](./projects/2_Notification/2_Notification.md): Extensible multi-channel notification dispatcher with dynamic message formatting and subscriber routing (Decorator, Observer, Strategy, Singleton).

