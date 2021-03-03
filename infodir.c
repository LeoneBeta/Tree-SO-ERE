#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "infodir.h"

//Memoria compartilhada
typedef struct{
    char dirName[20];
}TDir;

void removeEnter(char string[]){
	int tamanho = strlen(string) - 1;
	if (string[tamanho] == '\n'){
		string[tamanho] = '\0';
	}else {
		while (getc(stdin) != '\n')
			continue;
	}
}

//Função que a thread irá executar
void* funcThread(void *firstPtr){
    TDir *ptr;
    ptr = (TDir*) firstPtr;     //Cast do ponteiro do tipo void para ponteiro do tipo TDir

    
}

int start(){
    pthread_t thread1_ID,thread2_ID,thread3_ID,thread4_ID;                  //ID da Thread
    void *thread1_return,*thread2_return,*thread3_return,*thread4_return;   //Ponteiro de retorno
    int thread1,thread2,thread3,thread4;                                    //variavel de validação da Thread
    TDir strDir, *ptrDir;       //struct e ponteiro para a struct de memoria compartilhada
    ptrDir = &strDir;           //passando o endereço da struct para o ponteiro

    //Variaveis de Diretório,
    DIR *dir;
    struct dirent *ent;
    char caminhoDir[50];

    setbuf(stdin,NULL);
    printf("\nCaminho e nome do diretório: ");
    fgets(caminhoDir,50,stdin);
    removeEnter(caminhoDir);

    if((dir = opendir(caminhoDir)) != NULL){
        while((ent = readdir(dir)) != NULL){
            printf("\n%s: ",ent->d_name);
            

            //Verificar a quantidade de diretorios existentes


             //Função pthread_create passando cmo parametros o endereço do ID da thread, NULL, função que a thread irá
            //executar, parametro para a função passada anteriormente
            thread1 = pthread_create(&thread1_ID,NULL,funcThread,(void*)(ptrDir));
            //Validação da criação da Thread
            if(thread1 != 0){
                printf("\nErro ao iniciar a Thread");
                exit(EXIT_FAILURE);
            }

        }
    }else{
        perror("");
        return EXIT_FAILURE;
    }
    closedir(dir);
    return 0;
}

int main(){
    return start();
}