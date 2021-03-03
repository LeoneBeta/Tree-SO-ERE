/*o programa infodir pode criar até 4 funções, sendo elas, 3 para os 3 primeiros diretórios, e o quarto 
verificando todos os diretorios e arquivos restantes, caso so tenha arquivos na pasta pesquisada, criar um 
processo filho para calcular o tamanho dos arquivos*/

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
    int sizeDir;
}TInfo;

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
    TInfo *ptr;
    ptr = (TInfo*) firstPtr;     //Cast do ponteiro do tipo void para ponteiro do tipo TDir
}

int start(){
    pthread_t thread1_ID,thread2_ID,thread3_ID,thread4_ID;                  //ID da Thread
    void *thread1_return,*thread2_return,*thread3_return,*thread4_return;   //Ponteiro de retorno
    int thread1,thread2,thread3,thread4;                                    //variavel de validação da Thread
    TInfo strDir, *ptrDir;       //struct e ponteiro para a struct de memoria compartilhada
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
            printf("%d\n ",ent->d_reclen);
            
/*
            //Verificar a quantidade de diretorios existentes e criar 3 threads para percorrer esses diretórios
            //e uma thread para armazenando e somanod o tamanho dos diretórios pesquisados


             //Função pthread_create passando cmo parametros o endereço do ID da thread, NULL, função que a thread irá
            //executar, parametro para a função passada anteriormente
            thread1 = pthread_create(&thread1_ID,NULL,funcThread,(void*)(ptrDir));
            //Validação da criação da Thread
            if(thread1 != 0){
                printf("\nErro ao iniciar a Thread");
                exit(EXIT_FAILURE);
            }
*/
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