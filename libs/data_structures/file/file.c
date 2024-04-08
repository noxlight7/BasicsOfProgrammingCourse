//
// Created by curo on 03.04.2024.
//

#include "file.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

void writeIfNotExist(const char* filename, const char* data){
    FILE *f = fopen(filename, "r");
    if (f == NULL){
        f = fopen(filename, "w");
        fprintf(f, "%s" ,data);
    }
    fclose(f);
}

void writeAnyway(const char* filename, const char* data){
    FILE* f = fopen(filename, "w");
    fprintf(f, "%s" ,data);
    fclose(f);
}

void writeAnywayBin(const char* filename, const void* data, int byte_size){
    FILE* f = fopen(filename, "wb");
    fwrite(data, 1, byte_size, f);
    fclose(f);
}

void readBin(const char* filename, void* data, int byte_size){
    FILE* f = fopen(filename, "wr");
    fread(data, 1, byte_size, f);
    fclose(f);
}

long getFileSize(const char* filename) {
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return size;
}

bool cmpStrF(const char *s, const char *filename){
    int size = (int) getFileSize(filename);
    FILE *f = fopen(filename, "rb");
    char buffer[size + 1];
    fread(buffer, size, 1, f);
    buffer[size] = 0;
//    puts(buffer);
    fclose(f);

    return strcmp(s, buffer) == 0;
}