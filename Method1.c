#include "method1.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

long gettime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec/1000;
}

void method1(int size, char* location) {
    char pathZero[1024];
    char pathRand[1024];

    snprintf(pathZero, sizeof(pathZero), "%s/zero.bin", location);
    snprintf(pathRand, sizeof(pathRand), "%s/rand.bin", location);

    FILE* devzero = fopen("/dev/zero", "r");
    FILE* devrand = fopen("/dev/random", "r");

    if (!devzero || !devrand) {
        printf("Error opening /dev/zero or /dev/random\n");
        return;
    }

    long size_bytes = 1024L * 1024L * 1024L * size;
    
    long size_buffer = 4096; 
    long repetitions = size_bytes / size_buffer;
    
    char* buffer = (char*) malloc(size_buffer);
    if (!buffer) {
        printf("Memory allocation failed\n");
        return;
    }
    // --- Test Zero ---
    long cur_time = gettime(); 
    FILE* fileZero = fopen(pathZero, "wb");
    
    if (fileZero) {
        for(long i = 0; i < repetitions; i++) {
            fread(buffer, 1, size_buffer, devzero);
            fwrite(buffer, 1, size_buffer, fileZero);
        }
        fclose(fileZero);
        long end_time = gettime();
        long timedelta = end_time - cur_time;
        float deltasec = (float)timedelta / 1000;
        float sizemb = (float)size_bytes / (1024 * 1024);
        float speed = sizemb / deltasec;
        printf("Time taken to write %d GB from /dev/zero: %ld ms, speed= %.2f\n", size, end_time - cur_time, speed);
    } else {
        printf("Failed to create file at: %s\n", pathZero);
    }

    // --- Test Random ---
    cur_time = gettime();
    FILE* fileRand = fopen(pathRand, "wb");
    
    if (fileRand) {
        for(long i = 0; i < repetitions; i++) {
            fread(buffer, 1, size_buffer, devrand);
            fwrite(buffer, 1, size_buffer, fileRand);
        }
        fclose(fileRand);
        long end_time = gettime();
        long timedelta = end_time - cur_time;
        float deltasec = (float)timedelta / 1000;
        float sizemb = (float)size_bytes / (1024 * 1024);
        float speed = sizemb / deltasec;
        printf("Time taken to write %d GB from /dev/random: %ld ms, speed= %.2f\n", size, end_time - cur_time, speed);
    } else
    {
        printf("Failed to create file at: %s\n", pathRand);

    }

    fclose(devzero);
    fclose(devrand);
    free(buffer);
}
