# Summary

## Design Patterns

### Foundation

Core object-oriented concepts and the structured workflow for solving low-level design problems in interviews.

| Pattern                                                 | Core Problem Solved                       | Key Participants                                                   | SOLID Alignment                     |
| :------------------------------------------------------ | :---------------------------------------- | :----------------------------------------------------------------- | :---------------------------------- |
| [OOP Concepts](0_OOP%20Concepts.md)                     | Managing complexity via objects           | Encapsulation, Abstraction, Inheritance, Polymorphism              | Foundation for all SOLID principles |
| [SOLID Principles](1_Software%20Design%20Principles.md) | Rigid, coupled, fragile class hierarchies | SRP, OCP, LSP, ISP, DIP                                            | Defines the architectural target    |
| [LLD Delivery Framework](2_Delivery%20Framework.md)     | Unstructured LLD interview approach       | Requirements, Entities, Class Design, Implementation, Verification | Process methodology                 |

### Creational

Patterns that abstract object creation mechanisms, enabling loose coupling and controlled instantiation without hardcoding concrete classes.

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [Factory Method](4_Factory%20Pattern.md) | Tight coupling to concrete instantiation logic | Product, ConcreteProduct, Creator, ConcreteCreator | OCP, DIP |
| [Singleton](5_Singleton%20Pattern.md) | Uncontrolled duplicate instantiation of shared resources | Singleton, Client | Centralized access |

### Structural

Patterns that compose classes and objects into larger structures while keeping those structures flexible and efficient.

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [Decorator](7_Decorator%20Pattern.md) | Combinatorial subclass explosion for object variants | Component, ConcreteComponent, Decorator, ConcreteDecorator | OCP, SRP |
| [Adapter](9_Adapter%20Pattern.md) | Incompatible interfaces between client and legacy subsystem | Target, Client, Adaptee, Adapter | ISP, DIP |
| [Facade](10_Facade%20Pattern.md) | Deep transitive knowledge of complex subsystems | Facade, Subsystem Classes, Client | Law of Demeter |
| [Composite](11_Composite%20Pattern.md) | Inability to treat individual and composite objects uniformly | Component, Leaf, Composite, Client | LSP |
| [Proxy](13_Proxy%20Pattern.md) | Eager initialization and lack of access control for heavy resources | Subject, RealSubject, Proxy | Encapsulation |

### Behavioral

Patterns that identify common communication patterns between objects and manage complex control flow and responsibility assignment.

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [Strategy](3_Strategy%20Pattern.md) | Rigid algorithm coupling via inheritance/conditionals | Context, Strategy, ConcreteStrategy | OCP, SRP |
| [Observer](6_Observer%20Pattern.md) | Tight coupling between state owner and dependents | Subject, Observer, ConcreteSubject, ConcreteObserver | OCP, SRP |
| [Command](8_Command%20Pattern.md) | Coupled request emission and execution | Command, ConcreteCommand, Receiver, Invoker | OCP, SRP |
| [Template Method](12_Template%20Method%20Pattern.md) | Duplicated algorithm orchestration across subclasses | AbstractClass, ConcreteClass | OCP |
| [Chain of Responsibility](14_Chain%20of%20Responsibility%20Pattern.md) | Tight coupling between dispatcher and processing steps | Handler, BaseHandler, ConcreteHandler | OCP, SRP |

---

## Completed Case Studies

| Project | Description | Source |
| :--- | :--- | :--- |
| [**Notepad**](0_Notepad.md) | Document editor with mixed content hierarchy and pluggable storage backends | [View](0_Notepad.md) |
| [**Zomato**](1_Zomato.md) | Food ordering platform with abstract order factories, payment gateways, and singleton registries | [View](1_Zomato.md) |
| [**Notification System**](2_Notification.md) | Extensible multi-channel notification dispatcher with dynamic message formatting and subscriber routing | [View](2_Notification.md) |
| [**Elevator**](3_Elevator.md) | Elevator control system | [View](3_Elevator.md) |

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
