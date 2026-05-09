# Philosophers

A multithreading and synchronization project written in C as part of the 42 curriculum.

This project explores concurrent programming through the classic Dining Philosophers problem, focusing on thread synchronization, shared resources, mutexes, timing precision, and race condition prevention.

The objective was to understand how concurrent systems behave under resource contention while building reliable and thread-safe execution logic.

---

## 🧠 What I Learned

Working on Philosophers provided practical experience with:

- Multithreading using POSIX threads
- Mutex synchronization
- Race condition prevention
- Deadlock avoidance
- Shared resource management
- Thread-safe programming
- Timing and scheduling precision
- Concurrent system design
- Performance-conscious thinking

---

## ⚙️ Features

### ✅ Core Simulation

- Philosopher thread creation
- Fork/resource management
- Eating, sleeping, and thinking cycles
- Death monitoring system
- Accurate timestamp logging

### ✅ Synchronization

- Mutex-protected shared resources
- Thread-safe printing
- Controlled fork acquisition
- Deadlock prevention strategies
- Proper thread lifecycle management

### ✅ Error Handling

- Argument validation
- Resource cleanup
- Safe thread termination
- Memory management

---

## 🛠 Technologies

- C
- POSIX Threads (`pthread`)
- Mutexes
- Unix/Linux
- Makefile

---

## 🚀 Compilation

```bash
make
```

---

## ▶️ Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

---

## 💻 Example

```bash
./philo 5 800 200 200
```

Example output:

```bash
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

---

## 🧩 Core Concepts

### Threads & Concurrency
- `pthread_create`
- `pthread_join`
- Concurrent execution
- Shared memory

### Synchronization
- Mutex locking/unlocking
- Resource protection
- Atomic state access
- Thread-safe operations

### Problem Solving
- Deadlock prevention
- Starvation prevention
- Precise timing control
- Monitoring concurrent states

---

## 📚 Key Challenges

- Preventing deadlocks between philosophers
- Synchronizing access to shared forks
- Ensuring accurate timing under concurrency
- Avoiding race conditions
- Managing clean thread shutdown
- Designing reliable monitoring logic

---

## 👤 Author

- João Muñoz
