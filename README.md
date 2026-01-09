# Market Order Book (C++)

A lightweight **limit-order book** implementation written in modern C++ (C++17), built as a learning project to explore market microstructure, matching logic, and practical data-structure trade-offs.

> **Disclaimer:** This is an educational project. It is **not** production trading software and makes no guarantees around latency, determinism, or exchange-grade correctness.

---

## Overview

This project models a financial **order book**:

- Accepts incoming orders (currently focused on limit-style flow).
- Attempts to **match immediately** against the opposite side of the book.
- If an incoming order cannot be fully matched, the remaining quantity is stored in the book as a **FIFO queue** at its price level (price-time priority within a level).

During development I’ve kept notes in-code to capture design decisions and reasoning at the time.

---

## Key Concepts Implemented

- **Price levels** (buckets) holding queued orders.
- **FIFO priority** within each price level (time priority).
- **Fast look-up** for orders and price buckets (iterators + hashing).
- Matching engine behaviour:
  - Execute against best available opposite price levels.
  - Decrease quantities and remove fully-filled orders.

---

## Data Structures & Rationale

### Price Level Storage

Price levels are stored using:

- `std::unordered_map<Price, ...>` for **average O(1)** access to a specific price bucket.
- Each bucket contains a `std::list<Order>` so orders can be removed in **O(1)** when you already have an iterator.

This design supports the common requirement of:
- “Find a price bucket quickly”
- “Cancel/modify a specific resting order quickly”

### Order Lookup via Iterators

When a new order is added to a bucket, an iterator to that order can be stored (e.g. in a separate map keyed by OrderID). This enables:

- **O(1)** removal of an order from the middle of the queue (no search), *provided you have the iterator*.

---

## Using `std::list` for Orders: Pros & Cons

`std::list` is not the fastest container in most performance-critical environments, but it provides properties that are useful for correctness and simplicity early on.

### Pros
- **Stable iterators and references:** inserting/erasing other elements does not invalidate iterators (except the erased element).
- **O(1) erase given an iterator:** ideal for order cancellation if you store iterators per `OrderID`.
- **O(1) splice/move nodes between lists:** can be handy for refactors or re-queuing without copying.
- **Simple FIFO semantics:** `push_back()` / `pop_front()` map cleanly to queue behaviour.

### Cons
- **Poor cache locality:** each node is separately allocated → more cache misses, worse real-world performance.
- **Allocator overhead:** frequent allocations/deallocations can dominate runtime under heavy load.
- **Higher memory footprint:** pointers per node (typically two pointers per element) plus allocator metadata.
- **Slower iteration:** traversing a linked list is slower than a contiguous container due to pointer chasing.
- **Not representative of low-latency designs:** HFT-style books often avoid linked lists and prefer contiguous/pool-allocated structures.

### Likely Future Improvement
A common next step is migrating to:
- `std::deque` for better locality (still supports efficient push/pop at ends), **but** middle erase is not O(1).
- Intrusive lists or pooled node allocation to retain O(1) erase while reducing allocator overhead.
- Custom ring buffers / slab allocators for deterministic performance.

---

## Build & Tooling Notes

### Compiler Setup

- Unit tests use **Apple Clang**, because (in this setup) **GoogleTest does not support Homebrew Clang** cleanly.
- If you cannot build `Debug`, install Homebrew Clang:

```bash
brew install clang
