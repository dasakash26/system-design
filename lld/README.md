# Low Level Design (LLD)

Personal study notes, patterns, and end-to-end implementations for Object-Oriented Design (OOD).

---

## Structure

- [**Notes**](./notes): Core OOP concepts, SOLID principles, and design patterns.
- [**Projects**](./projects): Case studies and system implementations.

---

## Pattern Catalog

| Foundation & Framework | Creational | Structural | Behavioral |
| :--- | :--- | :--- | :--- |
| **[OOP Concepts](0_OOP%20Concepts.md)** <br> <small>Encapsulation, inheritance, polymorphism, vtable mechanics</small> | **[Factory Method](./notes/4_Factory%20Pattern/4_Factory%20Pattern.md)** <br> <small>Decoupling clients from concrete type instantiation</small> | **[Decorator](./notes/7_Decorator%20Pattern/7_Decorator%20Pattern.md)** <br> <small>Replacing combinatorial subclass explosion with composable wrappers</small> | **[Strategy](./notes/3_Strategy%20Pattern/3_Strategy%20Pattern.md)** <br> <small>Eliminating rigid algorithm coupling via runtime composition</small> |
| **[SOLID Principles](1_Software%20Design%20Principles.md)** <br> <small>Recompilation cascades, vtable pollution, interface contracts</small> | **[Singleton](./notes/5_Singleton%20Pattern/5_Singleton%20Pattern.md)** <br> <small>Thread safe single instance access with memory order guarantees</small> | **[Adapter](./notes/9_Adapter%20Pattern/9_Adapter%20Pattern.md)** <br> <small>Bridging incompatible interfaces without modifying either side</small> | **[Observer](./notes/6_Observer%20Pattern/6_Observer%20Pattern.md)** <br> <small>Decoupled one to many state synchronization and event dispatch</small> |
| **[LLD Delivery Framework](./notes/2_Delivery%20Framework/2_Delivery%20Framework.md)** <br> <small>Structured 5-phase approach for 45-minute design interviews</small> | | **[Facade](./notes/10_Facade%20Pattern/10_Facade%20Pattern.md)** <br> <small>Enforcing the Law of Demeter over complex subsystem graphs</small> | **[Command](./notes/8_Command%20Pattern/8_Command%20Pattern.md)** <br> <small>Encapsulating requests as objects for undo/redo and queuing</small> |
| | | **[Composite](./notes/11_Composite%20Pattern/11_Composite%20Pattern.md)** <br> <small>Treating individual and compositions of objects uniformly via recursive trees</small> | **[Template Method](./notes/12_Template%20Method%20Pattern/12_Template%20Method%20Pattern.md)** <br> <small>Defining algorithm skeletons in base classes, deferring steps to subclasses</small> |
| | | **[Proxy](./notes/13_Proxy%20Pattern/13_Proxy%20Pattern.md)** <br> <small>Providing a placeholder or surrogate object to control access to a resource</small> | |





---

## Case Studies

- [**Notepad — Document Editor**](./projects/0_Notepad/0_Notepad.md): Document editor with a mixed content hierarchy and pluggable storage backends (Composite, Strategy, Facade).
- [**Zomato — Food Delivery System**](./projects/1_Zomato/1_Zomato.md): Food ordering platform with abstract order factories, payment gateways, and singleton registries (Factory Method, Strategy, Singleton, Facade).
- [**Notification System**](./projects/2_Notification/2_Notification.md): Extensible multi-channel notification dispatcher with dynamic message formatting and subscriber routing (Decorator, Observer, Strategy, Singleton).

