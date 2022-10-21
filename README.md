
<h1 align="center">
	🍝 Philosophers
</h1>

### 🗝️ Original in [**Russian**](https://github.com/AYglazk0v/philos/blob/main/README.md)

## 💡 About the project:

> _In this project you will learn the basics of organizing threads in a process.
You will see how to create threads and learn about mutexes and semaphores_
	The philosophers (represented by the parts of the program) sit around a table with a
	a large plate of spaghetti. They each have a fork, but they need two forks to eat
	so they must borrow a fork from their neighbor to eat.

	Of course, if they borrow a fork from a neighbor, the neighbor can't use the fork.
	The processes/streams should communicate so that they always know the state of the forks (and other philosophers).
	There should also be a parent process that keeps track of everything.

This project consists of two parts: 
	

 1. Mandatory part:\
	Each philosopher must be a thread.\
	There must be one fork between each philosopher, so if there are several philosophers, each philosopher will have his own fork to the right and left.\
	To avoid a thread race and the problems associated with it, it is necessary to protect the shared resource, the fork, with mutexes.
2. Bonus part:\
	Each philosopher must be a separate process.\
	To protect the shared environment you must use semaphore.
	
More details about the assignment can be found in  [**subject**](https://github.com/MKKurbandibirov/Philosophers/blob/master/Subject.pdf).



## 🛠️ Usage:

### Requirements

The function is written in C and therefore needs the `gcc` compiler and some standard C libraries to execute it.

### Instructions

**1. Build the project**

To build a project, simply clone the repository and run one of the commands in it.
**mandatory part:**
```shell
$ make -C philo/
```
**bonus part:**
```shell
$ make -C philo_bonus/ 
```
**2. Usage the program**

-  Both programs accept the following arguments:
  - **number_of_philosophers**: is the number of philosophers as well as the number of forks.
  - **time_to_die**: иis counted in milliseconds, if the philosopher does not start eating within **'time_to_die'** milliseconds after the start of the last meal or the start of the simulation, he dies.
  - **time_to_eat**:  is expressed in milliseconds and represents the time it takes a philosopher to eat. During this time they will need to hold two forks.
  - **time_to_sleep**: in milliseconds and is the time the philosopher will spend sleeping.
  - **number_of_times_each_philosopher_must_eat**: argument is optional, if all philosophers eat at least 'number_of_times_each_philosopher_must_eat' the simulation will stop. If the argument is not specified, the simulation will only stop when the philosopher dies.

**Example**: Without using **number_of_times_each_philosopher_must_eat**:
 `./philo 4 500 200 200`</br>
**Example**: From use **number_of_times_each_philosopher_must_eat** 
`./philo 7 310 100 100 7`

 ## 🎬 Demonstration(exmaple):
 ![philo](https://github.com/AYglazk0v/philos/blob/main/philo.gif)

 ## 📋 Testing:

To check for a data race, it is necessary to add a flag to the Makefile `-fsanitize=thread`.

You can also use a ready-made checker from [nesvoboda](https://github.com/nesvoboda/socrates).

To visualize the output data you can use [philosophers-visualizer](https://nafuka11.github.io/philosophers-visualizer/)
