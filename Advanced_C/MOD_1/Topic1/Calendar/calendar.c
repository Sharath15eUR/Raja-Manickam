#include <stdio.h>
#include <string.h>

struct Day {
    char task[3][100];       // max 3 tasks per day, max 100 chars each
    char dayName[15];        
    int taskCount;           
};

void inputTasks(struct Day week[], int totalDays) {
    for (int i = 0; i < totalDays; i++) {
        printf("Enter day name (e.g., Monday): ");
        scanf("%s", week[i].dayName);
        printf("Enter number of tasks for %s (Max 3): ", week[i].dayName);
        scanf("%d", &week[i].taskCount);
        getchar(); 

        if (week[i].taskCount > 3) {
            week[i].taskCount = 3;
        }

        for (int j = 0; j < week[i].taskCount; j++) {
            printf("Enter task %d: ", j + 1);
            fgets(week[i].task[j], 100, stdin);
            week[i].task[j][strcspn(week[i].task[j], "\n")] = '\0'; // remove newline
        }
    }
}

void displayTasks(struct Day week[], int totalDays) {
    printf("\nWeekly Tasks:\n");
    for (int i = 0; i < totalDays; i++) {
        printf("%s:\n", week[i].dayName);
        for (int j = 0; j < week[i].taskCount; j++) {
            printf("  - %s\n", week[i].task[j]);
        }
    }
}

int main() {
    struct Day week[7];    // Max 7 days in a week
    int totalDays;

    printf("Enter number of days to input tasks for (Max 7): ");
    scanf("%d", &totalDays);
    if (totalDays > 7) {
        totalDays = 7;
    }

    inputTasks(week, totalDays);
    displayTasks(week, totalDays);

    return 0;
}
