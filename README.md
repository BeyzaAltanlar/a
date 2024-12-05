You are expected to simulate different process scheduling algorithms on the CPU. The program you write in the C programming language will take tasks defined in a file as input. Then, it will simulate the scheduling of these tasks based on the specified scheduling algorithm, displaying the intervals during which the tasks are executed along with the evaluation metrics of the algorithms.

The file tasks.txt contains the defined tasks. Each line of this file represents a task with a name, the time required to complete it (CPU burst), and a priority level. The format for each task is as follows:
[task name] [priority] [CPU burst]

Example:

T1 4 10  
T2 2 5  
T3 3 15  
In the first line, the task is named T1, it has a priority of 4, and it requires 10 units of time to execute.

Your task is to read this file and simulate three different scheduling algorithms:

Shortest Job First (SJF)
Round Robin Scheduling (RR)
Round Robin Scheduling with Priority (RRP)

Assumptions:
All tasks arrive at the system at the same time, at time 0.
Tasks are executed on a single-core processor.
Context switching takes no time.
For the Round Robin Scheduling algorithms, the quantum duration is 5 units of time.
The highest priority has a priority value of 0, and the lowest priority has a priority value of 10.
Evaluation Metrics:
After implementing these algorithms, you must evaluate their performance during the testing phase using the following metrics:

Waiting Time (WT): The average time a task spends waiting before execution.
Response Time (RT): The time from when a task arrives in the system (time 0) to when it is executed for the first time.
While printing these evaluation metrics to the console, they must be displayed as averages.

Example of Input and Output:
The program should be compiled with a Makefile, which creates an executable named schedule.o. The executable should accept the task file and the scheduling algorithm as arguments when run from the command line.

Example Command:

bash
Kodu kopyala
./schedule.o tasks.txt SJF  
Expected Output Format:

Kodu kopyala
<task_name> -> [<interval_1>, <interval_2>, ..., <interval_n>]  
...  
--- Stats ---  
WT : <average_waiting_time>  
RT : <average_response_time>  
Additional Notes:
Prepare a Makefile to compile your program. When the make command is executed, it should produce the schedule.o executable file.
Ensure your program handles inputs robustly and simulates the specified scheduling algorithms correctly.
