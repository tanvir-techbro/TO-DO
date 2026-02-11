#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK 256
#define INCOMPLETE_FILE "incomplete.txt"
#define COMPLETE_FILE   "complete.txt"

// Utility: remove a specific line from a file
void remove_line(const char *filename, int line_num) {
    FILE *file = fopen(filename, "r");
    if (!file) return;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(file);
        return;
    }

    char buffer[MAX_TASK];
    int current = 1;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (current != line_num) {
            fputs(buffer, temp);
        }
        current++;
    }

    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
}

// Add task
void add_task(const char *task) {
    FILE *file = fopen(INCOMPLETE_FILE, "a");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s\n", task);
    fclose(file);
    printf("Task added: %s\n", task);
}

// Mark task as done
void done_task(int num) {
    FILE *file = fopen(INCOMPLETE_FILE, "r");
    FILE *done = fopen(COMPLETE_FILE, "a");
    if (!file || !done) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[MAX_TASK];
    int current = 1;
    while (fgets(buffer, sizeof(buffer), file)) {
        if (current == num) {
            buffer[strcspn(buffer, "\n")] = 0; // strip newline
            fprintf(done, "%s\n", buffer);
            printf("Task marked done: %s\n", buffer);
        }
        current++;
    }

    fclose(file);
    fclose(done);
    remove_line(INCOMPLETE_FILE, num);
}

// Show tasks (both)
void show_all() {
    FILE *file;
    char buffer[MAX_TASK];
    int num = 1;

    printf("\nIncomplete Tasks:\n");
    file = fopen(INCOMPLETE_FILE, "r");
    if (file) {
        while (fgets(buffer, sizeof(buffer), file)) {
            buffer[strcspn(buffer, "\n")] = 0;
            printf("(%d) %s\n", num++, buffer);
        }
        fclose(file);
    } else {
        printf("None.\n");
    }

    printf("\nCompleted Tasks:\n");
    file = fopen(COMPLETE_FILE, "r");
    if (file) {
        while (fgets(buffer, sizeof(buffer), file)) {
            buffer[strcspn(buffer, "\n")] = 0;
            printf("[x] %s\n", buffer);
        }
        fclose(file);
    } else {
        printf("None.\n");
    }
    printf("\n");
}

// Show only incomplete
void show_incomplete() {
    FILE *file = fopen(INCOMPLETE_FILE, "r");
    char buffer[MAX_TASK];
    int num = 1;

    if (!file) {
        printf("No incomplete tasks.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        printf("(%d) %s\n", num++, buffer);
    }
    fclose(file);
}

// Show only complete
void show_complete() {
    FILE *file = fopen(COMPLETE_FILE, "r");
    char buffer[MAX_TASK];

    if (!file) {
        printf("No completed tasks.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        printf("[x] %s\n", buffer);
    }
    fclose(file);
}

// Delete incomplete task
void delete_task(int num) {
    remove_line(INCOMPLETE_FILE, num);
    printf("Deleted incomplete task #%d\n", num);
}

// Clear completed
void clear_done() {
    FILE *file = fopen(COMPLETE_FILE, "w");
    if (file) fclose(file);
    printf("All completed tasks cleared.\n");
}

// Delete all
void delete_all() {
    FILE *file = fopen(INCOMPLETE_FILE, "w");
    if (file) fclose(file);
    file = fopen(COMPLETE_FILE, "w");
    if (file) fclose(file);
    printf("All tasks deleted.\n");
}

int main() {
    char input[300];

    printf("** TO-DO App v1.0 **\nType 'help' for commands.\n");

    while (1) {
        printf("\033[1;34m~# ");
        printf("\033[1;36m");
        printf("\033[0m\n");
        if (!fgets(input, sizeof(input), stdin)) break;

        input[strcspn(input, "\n")] = 0; // strip newline

        if (strncmp(input, "add ", 4) == 0) {
            add_task(input + 4);
        } else if (strncmp(input, "done ", 5) == 0) {
            int n = atoi(input + 5);
            done_task(n);
        } else if (strncmp(input, "delete all", 10) == 0) {
            delete_all();
        } else if (strncmp(input, "delete ", 7) == 0) {
            int n = atoi(input + 7);
            delete_task(n);
        } else if (strcmp(input, "clear") == 0) {
            clear_done();
        } else if (strcmp(input, "show task") == 0) {
            show_all();
        } else if (strcmp(input, "show incomplete") == 0) {
            show_incomplete();
        } else if (strcmp(input, "show done") == 0 || strcmp(input, "show complete") == 0) {
            show_complete();
        } else if (strcmp(input, "help") == 0) {
            FILE *file = fopen("help.txt", "r");
              if (!file) {
                printf("help.txt not found.\n");
              } else {
                char buffer[256];
                while (fgets(buffer, sizeof(buffer), file)) {
                  printf("%s", buffer);
                }
                fclose(file);
              }
        } else if (strcmp(input, "exit") == 0) {
            printf("Exiting... Changes saved.\n");
            break;
        } else if (strlen(input) > 0) {
            printf("Unknown command. Type 'help'.\n");
        }
    }

    return 0;
}

