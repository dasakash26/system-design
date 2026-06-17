# System Design & Software Architecture Vault

> A production grade study vault and reference repository containing High Level Design (HLD) systems scalability notes and Low Level Design (LLD) object oriented patterns and implementations.

---

## Repository Structure

The repository is partitioned into two major areas to isolate large scale distributed systems concepts from micro level class design patterns:

```
system-design/
├── HLD/                 ← High Level Design (Scaling & Systems)
│   ├── notes/           # Distributed systems theory and core primitives
│   └── case_studies/    # Architectural designs of real world platforms
├── LLD/                 ← Low Level Design (Object Oriented Patterns)
│   ├── notes/           # Design pattern theory and C++ examples
│   ├── projects/        # End to end low level system implementations
│   └── coder-army-codes/ # Core implementation exercise files
└── Agents.md            # AI coding assistant guidelines and standards
```

---

## Directory Index

| Section | Target Topics | Core Objectives | Reference Link |
| :--- | :--- | :--- | :--- |
| **High Level Design (HLD)** | Caching, load balancers, database sharding, replication, message queues, rate limiting, and consistency models. | Designing scalable, highly available, and fault tolerant distributed systems. | [HLD Directory](file:///Users/akashdas/Developer/0_learn/system-design/hld/) |
| **Low Level Design (LLD)** | OOP principles, SOLID guidelines, design patterns (Strategy, Factory, Observer, Decorator, Command). | Writing clean, modular, extensible, and thread safe compile ready code. | [LLD README](file:///Users/akashdas/Developer/0_learn/system-design/lld/README.md) |

***

## Study Resources & References

*   **Low Level Design Source**: [Coder Army LLD Playlist](https://youtube.com/playlist?list=PLQEaRBV9gAFvzp6XhcNFpk1WdOcyVo9qT&si=Ihevlxfa3nczoXp0)
*   **High Level Design Source**: Hello Interview / System Design Primer
*   **Classic Literature**: Gang of Four — *Design Patterns: Elements of Reusable Object Oriented Software*
