# Summary

## Design Patterns

### Foundation

Core object-oriented concepts and the structured workflow for solving low-level design problems in interviews.

| Pattern                                                 | Core Problem Solved                       | Key Participants                                                   | SOLID Alignment                     |
| :------------------------------------------------------ | :---------------------------------------- | :----------------------------------------------------------------- | :---------------------------------- |
| [OOP Concepts](notes/00_OOP_Concepts.md)                     | Managing complexity via objects           | Encapsulation, Abstraction, Inheritance, Polymorphism              | Foundation for all SOLID principles |
| [SOLID Principles](notes/01_Software_Design_Principles.md) | Rigid, coupled, fragile class hierarchies | SRP, OCP, LSP, ISP, DIP                                            | Defines the architectural target    |
| [LLD Delivery Framework](notes/02_Delivery_Framework.md)     | Unstructured LLD interview approach       | Requirements, Entities, Class Design, Implementation, Verification | Process methodology                 |

### Creational

Patterns that abstract object creation mechanisms, enabling loose coupling and controlled instantiation without hardcoding concrete classes.

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [Factory Method](notes/04_Factory_Pattern.md) | Tight coupling to concrete instantiation logic | Product, ConcreteProduct, Creator, ConcreteCreator | OCP, DIP |
| [Builder](notes/16_Builder_Pattern.md) | Telescoping constructors and scattered construction logic | Builder, ConcreteBuilder, Director, Product | SRP, OCP |
| [Singleton](notes/05_Singleton_Pattern.md) | Uncontrolled duplicate instantiation of shared resources | Singleton, Client | Centralized access |

### Structural

Patterns that compose classes and objects into larger structures while keeping those structures flexible and efficient.

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [Decorator](notes/07_Decorator_Pattern.md) | Combinatorial subclass explosion for object variants | Component, ConcreteComponent, Decorator, ConcreteDecorator | OCP, SRP |
| [Adapter](notes/09_Adapter_Pattern.md) | Incompatible interfaces between client and legacy subsystem | Target, Client, Adaptee, Adapter | ISP, DIP |
| [Bridge](notes/15_Bridge_Pattern.md) | Subclass explosion across orthogonal dimensions of variation | Abstraction, RefinedAbstraction, Implementor, ConcreteImplementor | OCP |
| [Facade](notes/10_Facade_Pattern.md) | Deep transitive knowledge of complex subsystems | Facade, Subsystem Classes, Client | Law of Demeter |
| [Composite](notes/11_Composite_Pattern.md) | Inability to treat individual and composite objects uniformly | Component, Leaf, Composite, Client | LSP |
| [Proxy](notes/13_Proxy_Pattern.md) | Eager initialization and lack of access control for heavy resources | Subject, RealSubject, Proxy | Encapsulation |
| [Flyweight](notes/18_Flyweight_Pattern.md) | Excessive memory usage from many similar objects | Flyweight, FlyweightFactory, Context, Client | SRP |

### Behavioral

Patterns that identify common communication patterns between objects and manage complex control flow and responsibility assignment.

| Pattern | Core Problem Solved | Key Participants | SOLID Alignment |
| :--- | :--- | :--- | :--- |
| [Strategy](notes/03_Strategy_Pattern.md) | Rigid algorithm coupling via inheritance/conditionals | Context, Strategy, ConcreteStrategy | OCP, SRP |
| [Observer](notes/06_Observer_Pattern.md) | Tight coupling between state owner and dependents | Subject, Observer, ConcreteSubject, ConcreteObserver | OCP, SRP |
| [Command](notes/08_Command_Pattern.md) | Coupled request emission and execution | Command, ConcreteCommand, Receiver, Invoker | OCP, SRP |
| [Iterator](notes/17_Iterator_Pattern.md) | Traversal logic tied to collection internals | Iterator, ConcreteIterator, Aggregate, ConcreteAggregate | SRP, OCP |
| [Template Method](notes/12_Template_Method_Pattern.md) | Duplicated algorithm orchestration across subclasses | AbstractClass, ConcreteClass | OCP |
| [Chain of Responsibility](notes/14_Chain_of_Responsibility_Pattern.md) | Tight coupling between dispatcher and processing steps | Handler, BaseHandler, ConcreteHandler | OCP, SRP |
| [State](notes/19_State_Pattern.md) | Large conditional branches for lifecycle-dependent behavior | Context, State, ConcreteState | OCP, SRP |

---

## Completed Case Studies

| Project | Description | Source |
| :--- | :--- | :--- |
| [**Notepad**](projects/0_Notepad/0_Notepad.md) | Document editor with mixed content hierarchy and pluggable storage backends | [View](projects/0_Notepad/0_Notepad.md) |
| [**Zomato**](projects/1_Zomato/1_Zomato.md) | Food ordering platform with abstract order factories, payment gateways, and singleton registries | [View](projects/1_Zomato/1_Zomato.md) |
| [**Notification System**](projects/2_Notification/2_Notification.md) | Extensible multi-channel notification dispatcher with dynamic message formatting and subscriber routing | [View](projects/2_Notification/2_Notification.md) |
| [**Elevator**](projects/3_Elevator/3_Elevator.md) | Elevator control system | [View](projects/3_Elevator/3_Elevator.md) |

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
| Separate abstraction from implementation so both can vary independently | **Bridge** |
| Build a complex object step by step | **Builder** |
| Traverse a collection without exposing its representation | **Iterator** |
| Share intrinsic state across many objects | **Flyweight** |
| Change behavior when internal state changes | **State** |
| Decouple an interface from its implementation to allow interoperability | **Adapter** |
| Provide a simplified interface to a complex subsystem | **Facade** |
| Compose objects into tree structures to represent part-whole hierarchies | **Composite** |
| Control access to a resource (lazy init, caching, access control) | **Proxy** |
| Centralize object creation logic and hide concrete class names | **Factory Method** |
| Ensure a class has exactly one instance with global access | **Singleton** |

## Remaining GoF Pattern Gaps

Standalone notes still missing: Abstract Factory, Prototype, Interpreter, Mediator, Memento, and Visitor.
