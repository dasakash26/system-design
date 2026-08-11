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
| **[OOP Concepts](./notes/00_OOP_Concepts.md)** <br> <small>Encapsulation, inheritance, polymorphism, vtable mechanics</small> | **[Factory Method](./notes/04_Factory_Pattern.md)** <br> <small>Decoupling clients from concrete type instantiation</small> | **[Decorator](./notes/07_Decorator_Pattern.md)** <br> <small>Replacing combinatorial subclass explosion with composable wrappers</small> | **[Strategy](./notes/03_Strategy_Pattern.md)** <br> <small>Eliminating rigid algorithm coupling via runtime composition</small> |
| **[SOLID Principles](./notes/01_Software_Design_Principles.md)** <br> <small>Recompilation cascades, vtable pollution, interface contracts</small> | **[Singleton](./notes/05_Singleton_Pattern.md)** <br> <small>Thread-safe single instance access with memory order guarantees</small> | **[Adapter](./notes/09_Adapter_Pattern.md)** <br> <small>Bridging incompatible interfaces without modifying either side</small> | **[Observer](./notes/06_Observer_Pattern.md)** <br> <small>Decoupled one to many state synchronization and event dispatch</small> |
| **[LLD Delivery Framework](./notes/02_Delivery_Framework.md)** <br> <small>Structured 5-phase approach for 45-minute design interviews</small> | **[Builder](./notes/16_Builder_Pattern.md)** <br> <small>Constructing complex objects step by step</small> | **[Facade](./notes/10_Facade_Pattern.md)** <br> <small>Enforcing the Law of Demeter over complex subsystem graphs</small> | **[Command](./notes/08_Command_Pattern.md)** <br> <small>Encapsulating requests as objects for undo/redo and queuing</small> |
| | | **[Composite](./notes/11_Composite_Pattern.md)** <br> <small>Treating individual and compositions of objects uniformly via recursive trees</small> | **[Template Method](./notes/12_Template_Method_Pattern.md)** <br> <small>Defining algorithm skeletons in base classes, deferring steps to subclasses</small> |
| | | **[Proxy](./notes/13_Proxy_Pattern.md)** <br> <small>Providing a placeholder or surrogate object to control access to a resource</small> | **[Chain of Responsibility](./notes/14_Chain_of_Responsibility_Pattern.md)** <br> <small>Passing requests along a linked chain of handlers for decoupled processing</small> |
| | | **[Bridge](./notes/15_Bridge_Pattern.md)** <br> <small>Separating abstraction from implementation so both can vary independently</small> | **[Iterator](./notes/17_Iterator_Pattern.md)** <br> <small>Traversing a collection without exposing its internal structure</small> |
| | | **[Flyweight](./notes/18_Flyweight_Pattern.md)** <br> <small>Sharing intrinsic state across many fine-grained objects</small> | **[State](./notes/19_State_Pattern.md)** <br> <small>Changing behavior when internal lifecycle state changes</small> |

## Remaining GoF Pattern Gaps

These patterns are not yet covered as standalone notes: Abstract Factory, Prototype, Interpreter, Mediator, Memento, and Visitor.

---

## Case Studies

- [**Notepad — Document Editor**](./projects/0_Notepad/0_Notepad.md): Document editor with a mixed content hierarchy and pluggable storage backends (Composite, Strategy, Facade).
- [**Zomato — Food Delivery System**](./projects/1_Zomato/1_Zomato.md): Food ordering platform with abstract order factories, payment gateways, and singleton registries (Factory Method, Strategy, Singleton, Facade).
- [**Notification System**](./projects/2_Notification/2_Notification.md): Extensible multi-channel notification dispatcher with dynamic message formatting and subscriber routing (Decorator, Observer, Strategy, Singleton).
