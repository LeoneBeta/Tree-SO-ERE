#ifndef INFODIR_H_INCLUDED
#define INFODIR_H_INCLUDED

//Memoria compartilhada
typedef struct{
    char dirName[20];
    char caminhoDir[100];
    long sizeDir;
    int readDir;
}TInfo;

void removeEnter(char[]);

void* threadSingleDir(void*);
void* threadMultiDir(void*);
int start();
#endif