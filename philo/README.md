*This project has been created as part of the 42 curriculum by ltong.*

# Philosophers

## Description

This project implements the classic dining philosophers problem in C. Each philosopher
is represented by a thread, and each fork is protected by a mutex. The goal is to manage
shared resources without deadlocks or data races while respecting precise timing rules.

The simulation stops when a philosopher dies or, when the optional fifth argument is
provided, when every philosopher has eaten at least the requested number of meals.

## Instructions

Build the mandatory program:

```sh
cd philo
make
```

Run it with:

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
  [number_of_times_each_philosopher_must_eat]
```

Example:

```sh
./philo 5 800 200 200
./philo 5 800 200 200 7
```

Clean build files:

```sh
make clean
make fclean
make re
```

## Resources

- POSIX threads documentation: man pthread_create, man pthread_join, man pthread_mutex_init,
  man pthread_mutex_lock, man pthread_mutex_unlock, man pthread_mutex_destroy, man gettimeofday.
- condequoi.com for threads understanding https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/
- Linux and macOS manual pages for gettimeofday and usleep.
- Classic descriptions of the dining philosophers problem and deadlock prevention.

AI was used to help understand the project subject, the concepts of thread, mutex.
