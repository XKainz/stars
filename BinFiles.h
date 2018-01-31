#ifndef BINFILES_H
#define BINFILES_H

#include <iostream>
#include <fstream>
#include <stdlib.h>

void makeBinaryFile(const char* in, char seperator,const char* out);
const float* readBinaryFileVBO(const char* in);
unsigned int readSize( const char* in);
const unsigned int* readBinaryFileEBO(const char* in);
void makeBinaryFileEBO(const char* in, char seperator,const char* out);


#endif // BINFILES_H
