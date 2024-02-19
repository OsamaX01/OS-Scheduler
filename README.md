# OS Process Scheduler README

## Overview

This C++ program implements a simple process scheduler using a priority-based scheduling algorithm. The program takes input about processes, including their arrival time, processing time, and priority, and simulates the execution of these processes. The scheduler uses a set data structure to maintain the ready state of processes, and the scheduling policy is based on priority, with ties broken by arrival time and index.

## How to Use

1- Compile the code using a C++ compiler.
```txt
g++ -o scheduler scheduler.cpp
```

2- Create an input file named "in.txt" with the following format:
```txt
<number_of_processes>
<process_name_1> <arrival_time_1> <processing_time_1> <priority_1>
<process_name_2> <arrival_time_2> <processing_time_2> <priority_2>
...
<process_name_n> <arrival_time_n> <processing_time_n> <priority_n>
```
Example:
```
5
A 0 3 3
C 4 4 4
B 2 6 6
D 6 5 5
E 8 2 2
```
3- Run the compiled executable and redirect input/output to files:
```
./scheduler
```
make sure to have in.txt, and out.txt file in your directory. 

## Input Format
- The first line of input specifies the number of processes (n).

- The next n lines provide information about each process, including its name, arrival time, processing time, and priority.

## Output Format
- The program outputs the order in which processes are executed and their corresponding statistics.

- The first line shows the order of process execution.

- The following lines provide statistics for each process, including response time, turnaround time, and delay.

Example output:
```
A B D C E
A: (response=0, turnaround=3, delay=0)
B: (response=1, turnaround=7, delay=1)
D: (response=3, turnaround=8, delay=3)
C: (response=10, turnaround=14, delay=10)
E: (response=10, turnaround=12, delay=10)
```

## Code Structure
The code is organized into several functions:

- scheduler(): The main scheduling logic that simulates process execution.

- main(): The entry point of the program that sets up input/output redirection and calls the scheduler function.
  
- The program uses structures (Process and ProcessStatistics) to represent processes and their statistics.
  
- Lambdas are used to encapsulate specific functionalities, such as adding available processes, getting a process from the ready state, adding processes to the history, and executing a process.
  
- The priority queue (readyState) is used to maintain the ready state of processes based on their priority.

## Notes

- The code assumes the input file (in.txt) is available and follows the specified format.

- The output is redirected to an output file (out.txt), which contains the execution order and process statistics.

Feel free to modify the input file, adjust the code, or explore different scheduling algorithms based on your requirements.
