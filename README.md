*This project has been created as part of the 42 curriculum by yademirk.*

# Description
The Dining Philosophers problem, created by Edsger Dijkstra in 1965, is an example problem
designed to showcase concurrency and synchronization issues in multithreaded programs.

## Overview

- X number of philosophers sit around a table
- There is a plate of spaghetti in front of everyone
- Each philosopher has a fork to their left and to their right
- There are as many forks as philosophers (e.g. 5 philosophers, 5 forks)
- A philosopher has to eat and think repeatedly without dying
  - The philosophers also sleep for some time after eating in the 42 version
- To eat, a philosopher must use both forks to their left and right
- A fork cannot be used by more than one philosopher
- A philosopher cannot use a fork that is currently in use: They have to wait for their turn
- When a philosopher dies of starvation, the dinner (simulation) ends

The 42 version of the problem incorporates unique challenges such as:
- The philosophers must also sleep after eating
- The simulation can optionally stop once all philosophers have eaten enough times.

## Frequent Issues
The dining philosophers is an example problem, to showcase classic mulithreading and parallelism
problems such as deadlock, livelock, starvation and circular waiting.

- Deadlock: Any situation in which no member of some group of entities (in this case, philosophers)
can proceed because each waits for another member
- Livelock: Similar to deadlock, but all members are active instead of passively waiting. Even though
they are working, no progress occurs. It's very similar to deadlock.
- Starvation: When a process can't access to the resources it needs in time. In this case,
a philosopher may not be able to reach forks and wait indefinitely before it dies because of starvation.

It's the programmer's task to solve these problems and several solutions exist. In this project, I used:

- Fork Ordering to prevent deadlocks
- Fair sleep staggering to prevent starvation
- Waiter solution for bonus (can't order forks in the bonus part)

## Multithreading

Apart from synchronization and concurrency issues, this project is our first introduction to multithreaded
programming. It introduces us to several concepts:

- Threads
- Critical section code
- Mutexes (mutual exclusion)
- Semaphores
- Race conditions
- Data races
- Thread safety

And more.

## Instructions
Run the 'make' command either in the philo or the philo_bonus folder. An output file with the same name will be produced.

## Usage
./philo philo_count time_to_die time_to_eat time_to_sleep [max_eat_count]

- philo_count: The number of simulated philosophers. More than 200 philosophers may result in undefined behavior.
- time_to_die: A.k.a. the time of starvation. If a philosopher has not started eating within this amount of time since their last meal began, they will die.
- time_to_eat: The time it takes for a philosopher to finish their meal.
- time_to_sleep: The time it takes for a philosopher to sleep and wake up.
- max_eat_count: (optional) The minimum number of times each philosopher must eat before the simulation ends. If not provided, the simulation will stop only when a philosopher dies, and will run forever if none of them die.

## Resources
### AI Usage
AI was used to gather and gain knowledge and information about:

- Multithreading, concurrency, parallelism, synchronization
and several other computer concepts
- Brainstorming solutions for the Philosophers problem
- Code quality evaluation
- Grammar and spell checking

### The Dining Philosophers Problem
- Wikipedia: https://en.wikipedia.org/wiki/Dining_philosophers_problem
- ThreadMentor: https://pages.mtu.edu/~shene/NSF-3/e-Book/MUTEX/TM-example-philos-1.html
- Lefty-Right Version: https://pages.mtu.edu/~shene/NSF-3/e-Book/MUTEX/TM-example-left-right.html

### Concurrency
- Concurrency: https://en.wikipedia.org/wiki/Concurrency_(computer_science)
- Concurrent Computing: https://en.wikipedia.org/wiki/Concurrent_computing

### Parallelism
- Parallelism: https://en.wikipedia.org/wiki/Parallel_computing
- Multi-core Processor: https://en.wikipedia.org/wiki/Multi-core_processor
- Bit-level Parallelism: https://en.wikipedia.org/wiki/Bit-level_parallelism
- Instruction-level Parallelism: https://en.wikipedia.org/wiki/Instruction-level_parallelism
- Data Parallelism: https://en.wikipedia.org/wiki/Data_parallelism
- Task Parallelism: https://en.wikipedia.org/wiki/Task_parallelism
- Parallel Algorithm: https://en.wikipedia.org/wiki/Parallel_algorithm
- Sequential Algorithm: https://en.wikipedia.org/wiki/Sequential_algorithm

### Difference between Concurrency and Parallelism
- StackOverflow: https://stackoverflow.com/questions/1050222/what-is-the-difference-between-concurrency-and-parallelism
- Concurrency is not Parallelism: https://bytebytego.com/guides/concurrency-is-not-parallelism/
- Reddit: https://www.reddit.com/r/programming/comments/nfzw29/concurrency_vs_parallelism/

### Threads
- Thread: https://en.wikipedia.org/wiki/Thread_(computing)
- Execution: https://en.wikipedia.org/wiki/Execution_(computing)
- Scheduler: https://en.wikipedia.org/wiki/Scheduling_(computing)

### Multi-Threading
- Multi-threading: https://en.wikipedia.org/wiki/Multithreading_(computer_architecture)
- Oracle's Multithreaded Programming Guide: https://docs.oracle.com/cd/E19455-01/806-5257/index.html
- ThreadMentor: https://pages.mtu.edu/~shene/NSF-3/e-Book/index.html
- Multi-processing: https://en.wikipedia.org/wiki/Multiprocessing
- Synchronization: https://en.wikipedia.org/wiki/Synchronization_(computer_science)
- Context Switch: https://en.wikipedia.org/wiki/Context_switch
- Thread Safety: https://en.wikipedia.org/wiki/Thread_safety

### Threading Problems
- Threading Issues: https://www.geeksforgeeks.org/operating-systems/threading-issues/
- Deadlock: https://en.wikipedia.org/wiki/Deadlock_(computer_science)
- Mutual Exclusion (mutexes): https://en.wikipedia.org/wiki/Mutual_exclusion
- Resource Starvation: https://en.wikipedia.org/wiki/Starvation_(computer_science)
- Resource Contention: https://en.wikipedia.org/wiki/Resource_contention
- Livelock: https://www.geeksforgeeks.org/operating-systems/deadlock-starvation-and-livelock/

### Deadlock Solutions
- Deadlock Prevention: https://www.geeksforgeeks.org/operating-systems/deadlock-prevention/
- Handling Deadlocks: https://www.geeksforgeeks.org/operating-systems/handling-deadlocks/

### Race Condition and Data Races
- Race Condition: https://en.wikipedia.org/wiki/Race_condition#In_software
- Race Condition vs Data Races: https://www.avanderlee.com/swift/race-condition-vs-data-race/
- Race Condition vs Data Races (2): https://stackoverflow.com/questions/11276259/

### Atomicity (Linearizability)
- Wikipedia: https://en.wikipedia.org/wiki/Linearizability
- Atomic Operations in OS: https://www.geeksforgeeks.org/operating-systems/atomic-operations-in-os/

### Multithreading in POSIX (pthreads)
- Pthreads: https://en.wikipedia.org/wiki/Pthreads
- POSIX Threads: https://www.geeksforgeeks.org/operating-systems/posix-threads-in-os/
- UNIX Threads by Dr. Sam Hsu: https://www.cse.fau.edu/~sam/course/netp/lec_note/thread.pdf
- Multithreading in C: https://www.geeksforgeeks.org/c/multithreading-in-c/
- C Multithreading in Reddit: https://www.reddit.com/r/cprogramming/comments/1j86xhz/multithreading_in_c/

### C Mutexes (Mutual Exclusion)
- Lock: https://en.wikipedia.org/wiki/Lock_(computer_science)
- Mutex lock: https://www.geeksforgeeks.org/linux-unix/mutex-lock-for-linux-thread-synchronization/
- Concurrency Control: https://en.wikipedia.org/wiki/Concurrency_control

### Sleeping
- Wikipedia: https://en.wikipedia.org/wiki/Sleep_(system_call)
- usleep() function: https://www.ibm.com/support/pages/example-using-c-api-usleep

### Semaphores
- Wikipedia: https://en.wikipedia.org/wiki/Semaphore_(programming)

## Authors
Yaşam Ensar Demirkıran (yademirk)
