//
// Created by curo on 03.04.2024.
//

#ifndef BASICSOFPROGRAMMINGCOURSE_FILE_H
#define BASICSOFPROGRAMMINGCOURSE_FILE_H

#include <stdbool.h>

void writeIfNotExist(const char* filename, const char* data);
void writeAnyway(const char* filename, const char* data);
void writeAnywayBin(const char* filename, const void* data, int byte_size);
void readBin(const char* filename, void* data, int byte_size);
long getFileSize(const char* filename);
bool cmpStrF(const char *s, const char *filename);

#endif //BASICSOFPROGRAMMINGCOURSE_FILE_H
