# System Design Recap & Mind Map

Consolidated recap of all completed Low Level Design (LLD) study material, including foundational concepts, design principles, creational/structural/behavioral patterns, and end-to-end case studies.

---

## Completed Design Patterns Catalog

### Foundation

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [OOP Concepts](./lld/notes/0_OOP%20Concepts/0_OOP%20Concepts.md) | Managing complexity via objects | Encapsulation, Abstraction, Inheritance, Polymorphism | Foundation for all SOLID principles |
| [SOLID Principles](./lld/notes/1_Software%20Design%20Principles/1_Software%20Design%20Principles.md) | Rigid, coupled, fragile class hierarchies | SRP, OCP, LSP, ISP, DIP | Defines the architectural target |
| [LLD Delivery Framework](./lld/notes/2_Delivery%20Framework/2_Delivery%20Framework.md) | Unstructured LLD interview approach | Requirements, Entities, Class Design, Implementation, Verification | Process methodology |

### Creational

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [Factory Method](./lld/notes/4_Factory%20Pattern/4_Factory%20Pattern.md) | Tight coupling to concrete instantiation logic | Product, ConcreteProduct, Creator, ConcreteCreator | OCP, DIP |
| [Singleton](./lld/notes/5_Singleton%20Pattern/5_Singleton%20Pattern.md) | Uncontrolled duplicate instantiation of shared resources | Singleton, Client | Centralized access |

### Structural

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [Decorator](./lld/notes/7_Decorator%20Pattern/7_Decorator%20Pattern.md) | Combinatorial subclass explosion for object variants | Component, ConcreteComponent, Decorator, ConcreteDecorator | OCP, SRP |
| [Adapter](./lld/notes/9_Adapter%20Pattern/9_Adapter%20Pattern.md) | Incompatible interfaces between client and legacy subsystem | Target, Client, Adaptee, Adapter | ISP, DIP |
| [Facade](./lld/notes/10_Facade%20Pattern/10_Facade%20Pattern.md) | Deep transitive knowledge of complex subsystems | Facade, Subsystem Classes, Client | Law of Demeter |
| [Composite](./lld/notes/11_Composite%20Pattern/11_Composite%20Pattern.md) | Inability to treat individual and composite objects uniformly | Component, Leaf, Composite, Client | LSP |
| [Proxy](./lld/notes/13_Proxy%20Pattern/13_Proxy%20Pattern.md) | Eager initialization and lack of access control for heavy resources | Subject, RealSubject, Proxy | Encapsulation |

### Behavioral

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [Strategy](./lld/notes/3_Strategy%20Pattern/3_Strategy%20Pattern.md) | Rigid algorithm coupling via inheritance/conditionals | Context, Strategy, ConcreteStrategy | OCP, SRP |
| [Observer](./lld/notes/6_Observer%20Pattern/6_Observer%20Pattern.md) | Tight coupling between state owner and dependents | Subject, Observer, ConcreteSubject, ConcreteObserver | OCP, SRP |
| [Command](./lld/notes/8_Command%20Pattern/8_Command%20Pattern.md) | Coupled request emission and execution | Command, ConcreteCommand, Receiver, Invoker | OCP, SRP |
| [Template Method](./lld/notes/12_Template%20Method%20Pattern/12_Template%20Method%20Pattern.md) | Duplicated algorithm orchestration across subclasses | AbstractClass, ConcreteClass | OCP |
| [Chain of Responsibility](./lld/notes/14_Chain%20of%20Responsibility%20Pattern/14_Chain%20of%20Responsibility%20Pattern.md) | Tight coupling between dispatcher and processing steps | Handler, BaseHandler, ConcreteHandler | OCP, SRP |

---

## Completed Case Studies

| Project | Description | Source |
| :--- | :--- | :--- |
| [**Notepad**](./lld/projects/0_Notepad/0_Notepad.md) | Document editor with mixed content hierarchy and pluggable storage backends | [View](./lld/projects/0_Notepad/0_Notepad.md) |
| [**Zomato**](./lld/projects/1_Zomato/1_Zomato.md) | Food ordering platform with abstract order factories, payment gateways, and singleton registries | [View](./lld/projects/1_Zomato/1_Zomato.md) |
| [**Notification System**](./lld/projects/2_Notification/2_Notification.md) | Extensible multi-channel notification dispatcher with dynamic message formatting and subscriber routing | [View](./lld/projects/2_Notification/2_Notification.md) |
| [**Elevator**](./lld/projects/3_Elevator/3_Elevator.md) | Elevator control system | [View](./lld/projects/3_Elevator/3_Elevator.md) |

---

## Design Pattern Decision Matrix

| When you need to... | Apply this pattern |
| :--- | :--- |
| Vary an algorithm independently from the clients that use it | **Strategy** |
| Encapsulate a request as an object for queuing, logging, or undo | **Command** |
| Notify multiple dependents when an object's state changes | **Observer** |
| Attach responsibilities to objects dynamically without subclassing | **Decorator** |
| Define a skeleton algorithm, deferring specific steps to subclasses | **Template Method** |
| Pass a request along a chain of handlers | **Chain of Responsibility** |
| Decouple an interface from its implementation to allow interoperability | **Adapter** |
| Provide a simplified interface to a complex subsystem | **Facade** |
| Compose objects into tree structures to represent part-whole hierarchies | **Composite** |
| Control access to a resource (lazy init, caching, access control) | **Proxy** |
| Centralize object creation logic and hide concrete class names | **Factory Method** |
| Ensure a class has exactly one instance with global access | **Singleton** |
