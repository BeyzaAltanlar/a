#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define QUANTUM 5

typedef struct {
    char name[10];
    int priority;
    int cpu_burst;
    int remaining_time;
    int arrival_time;
    int completion_time;
    int start_time;
    int first_response;
    int waiting_time;
    int turnaround_time;
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;

void read_tasks(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    while (fscanf(file, "%s %d %d", tasks[task_count].name, &tasks[task_count].priority, &tasks[task_count].cpu_burst) != EOF) {
        tasks[task_count].remaining_time = tasks[task_count].cpu_burst;
        tasks[task_count].first_response = -1; // İlk respnse (henuz yok)
        task_count++;
    }
    fclose(file);
}

// Shortest Job First (SJF)
void sjf() {
    int current_time = 0, completed_tasks = 0;

    while (completed_tasks < task_count) {
        int shortest_job = -1;

        for (int i = 0; i < task_count; i++) {
            if (tasks[i].remaining_time > 0 &&
                (shortest_job == -1 || tasks[i].cpu_burst < tasks[shortest_job].cpu_burst)) {
                shortest_job = i;
            }
        }

        if (shortest_job != -1) {
            tasks[shortest_job].start_time = current_time;
            if (tasks[shortest_job].first_response == -1) {
                tasks[shortest_job].first_response = current_time;
            }

            printf("%s -> [%d-%d]\n", tasks[shortest_job].name, current_time,
                   current_time + tasks[shortest_job].cpu_burst);
            current_time += tasks[shortest_job].cpu_burst;

            tasks[shortest_job].completion_time = current_time;
            tasks[shortest_job].waiting_time = current_time - tasks[shortest_job].cpu_burst;
            tasks[shortest_job].remaining_time = 0;
            completed_tasks++;
        }
    }
}

// Round Robin (RR)
void rr() {
    int current_time = 0, remaining_tasks = task_count;

    while (remaining_tasks > 0) {
        for (int i = 0; i < task_count; i++) {
            if (tasks[i].remaining_time > 0) {
                if (tasks[i].first_response == -1) {
                    tasks[i].first_response = current_time;
                }

                int time_slice = (tasks[i].remaining_time > QUANTUM) ? QUANTUM : tasks[i].remaining_time;
                printf("%s -> [%d-%d]\n", tasks[i].name, current_time, current_time + time_slice);

                current_time += time_slice;
                tasks[i].remaining_time -= time_slice;

                if (tasks[i].remaining_time == 0) {
                    tasks[i].completion_time = current_time;
                    remaining_tasks--;
                }
            }
        }
    }
}

// Round Robin with Priority (RRP) 
void rrp() {
    int current_time = 0, remaining_tasks = task_count;
    int completed_tasks = 0;

    // Priority e gore processleri siralama 
    while (remaining_tasks > 0) {
        int highest_priority_task = -1;

        // onceligi en yuksek olan processi bul
        for (int i = 0; i < task_count; i++) {
            if (tasks[i].remaining_time > 0 && (highest_priority_task == -1 || tasks[i].priority < tasks[highest_priority_task].priority)) {
                highest_priority_task = i;
            }
        }

        if (highest_priority_task != -1) {
            // ilk response
            if (tasks[highest_priority_task].first_response == -1) {
                tasks[highest_priority_task].first_response = current_time;
            }

            // Quantum kadar zaman dilimi ayarla
            int time_slice = (tasks[highest_priority_task].remaining_time > QUANTUM) ? QUANTUM : tasks[highest_priority_task].remaining_time;
            printf("%s -> [%d-%d]\n", tasks[highest_priority_task].name, current_time, current_time + time_slice);

            current_time += time_slice;
            tasks[highest_priority_task].remaining_time -= time_slice;

            if (tasks[highest_priority_task].remaining_time == 0) {
                tasks[highest_priority_task].completion_time = current_time;
                remaining_tasks--;
            }
        }
    }
}

// Performans metriklerini hesapla
void calculate_stats() {
    float total_waiting_time = 0, total_response_time = 0;

    for (int i = 0; i < task_count; i++) {
        total_waiting_time += tasks[i].completion_time - tasks[i].cpu_burst;
        total_response_time += tasks[i].first_response;
    }

    printf("--- Stats ---\n");
    printf("WT : %.2f\n", total_waiting_time / task_count);
    printf("RT : %.2f\n", total_response_time / task_count);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Kullanim: ./schedule.o <dosya_adı> <algoritma>\n");
        return 1;
    }

    read_tasks(argv[1]);

    if (strcmp(argv[2], "SJF") == 0) {
        sjf();
    } else if (strcmp(argv[2], "RR") == 0) {
        rr();
    } else if (strcmp(argv[2], "RRP") == 0) {
        rrp();
    } else {
        printf("Gecersiz: %s\n", argv[2]);
        return 1;
    }

    calculate_stats();
    return 0;
}

