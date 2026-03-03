<div align="center">

```
                                   |====================>
                                   |
                                   |====================>
                                   |
(==================================|
                                   |
                                   |====================>
                                   |
                                   |====================>
```

# dining_philosophers

*I'm watching my carbs — and my shared resources*

</div>

---

## The Problem

The **Dining Philosophers** problem, formulated by Edsger W. Dijkstra in 1965, is a classic illustration of synchronisation challenges in concurrent programming.

*N* philosophers sit at a circular table. A single fork lies between each adjacent pair. To eat, a philosopher must pick up **both** the fork to their left and the fork to their right. Since forks are shared, a naive implementation leads to:

- **Deadlock** — every philosopher holds one fork and waits forever for the other
- **Starvation** — a philosopher is perpetually denied the resources they need

The challenge is to design a solution using threads and mutex locks that is free of both failure modes.

---

## Overview

<div align="center">

| Field | Details |
|:------|:--------|
| Language | C (C11) |
| Compiler | `cc` |
| Flags | `-Wall` `-Wextra` `-Werror` |
| Commits | 20 |
| Status | In Development |
| Unit Tests | Pending |

</div>

---

## Arguments

<div align="center">

| # | Name | Type | Required | Description |
|:-:|:----:|:----:|:--------:|:------------|
| 1 | `N` | `int` | Yes | Number of philosophers (and forks) at the table |
| 2 | `td` | `int` (ms) | Yes | Time to die — a philosopher dies if they have not begun eating within `td` ms of their last meal, or of the simulation start |
| 3 | `te` | `int` (ms) | Yes | Time to eat — duration of a single meal |
| 4 | `ts` | `int` (ms) | Yes | Time to sleep — duration spent sleeping between meals |
| 5 | `Nm` | `int` | No | Number of meals — simulation stops once all philosophers have eaten at least `Nm` times |

</div>

---

## Constraints

- All time values are in **milliseconds**
- All argument values must be **positive integers**
- `N >= 1` — a single philosopher has only one fork; they cannot eat and will die
- `Nm`, if provided, must be `>= 1`

---

## Usage

### Build

```bash
make          # Compile the executable
make re       # Clean and rebuild from scratch
make clean    # Remove object and dependency files
make fclean   # Remove object files and the executable
```

### Run

```bash
./phil N td te ts [Nm]
```

---

## Example

Five philosophers, 800 ms to die, 200 ms to eat, 200 ms to sleep — no meal limit:

```bash
$ ./phil 5 800 200 200
0 1 has taken a fork
0 1 is eating
0 2 has taken a fork
0 2 is eating
200 1 is sleeping
200 2 is sleeping
400 1 is thinking
...
800 3 died
```

Stop the simulation once every philosopher has eaten three times:

```bash
$ ./phil 5 800 200 200 3
```

---

## Project Structure

```
dining_philosophers/
├── include/
│   └── philo.h           # Shared data structures and function declarations
├── src/
│   ├── main.c            # Entry point: argument validation, thread lifecycle
│   ├── init.c            # Resource initialisation: mutexes, philosopher structs
│   ├── thread_logic.c    # Per-philosopher thread routine: eat / sleep / think
│   └── timing.c          # Time utility functions
└── Makefile
```

