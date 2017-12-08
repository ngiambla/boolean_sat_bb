# ms_util #

Boolean SAT solver, using Branch and Bound.



## Introduction ##



To generate the executable required for operation, please navigate to the source directory of this project.

```bash
~$ cd source
```


## Make ##

To generate the executable, open a terminal process, and ensure that the terminal is operating
in the source directory of this folder.

Once there, enter the following commands:

```bash
~$ make clean
~$ make

```


## Execution Instructions ##

To execute this project, please ensure that a terminal process is running and is currently in the source directory of this project. Enter this command:

```bash
~$ ./ms_util -file [filename] -opt [y|n]
```

Where:

`filename` can either be:

```bash
1.cnf
2.cnf
3.cnf
4.cnf
t.cnf
t3.cnf
t4.cnf
t8.cnf
```

And `-opt` defines if this algorithm is to run with an optimization on (`y`) or off (`n`). The optimization performs a heuristic based measured for discovering solving the MAX-SAT problem. 

## Author ##

Nicholas V. Giamblanco, 2017

This project was intended for the course ECE1387, at the University of Toronto.