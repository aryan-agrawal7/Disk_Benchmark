#include "method2.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

void SizeMeasure(int time, char* location) {
    char* command = malloc(1000 * sizeof(char));
    snprintf(command, 100, "timeout %ds cat /dev/zero > %s/random.bin", time, location);
    int status = system(command);
    if (status == -1) {
        perror("system");
        return;
    }
    int size;
    FILE *file = fopen("random.bin", "rb");
    if (file == NULL) {
        perror("fopen");
        return;        
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);
    free(command);
    int size_mb = size / (1024 * 1024);
    printf("Speed = %.2f mb/s\n", (float)size_mb / time);
}
