# 42-philosophers
My implementation of the Philosophers project from Ecole 42.

# Installation
Run the 'make' command either in the philo or philo_bonus folder. An output file with the same name will be produced.

# Usage
"philo philo_count time_to_die time_to_eat time_to_sleep [max_eat_count]"

- philo_count: The number of simulated philosophers. More than 200 philosophers may result in undefined behavior.
- time_to_die: A.k.a. the time of starvation. If a philosopher has not started eating within this amount of time since their last meal began, they will die.