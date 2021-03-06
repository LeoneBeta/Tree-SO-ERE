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

//Thread 1
void* thread_1(void *firstPtr){
    TInfo *ptr;
    ptr = (TInfo*) firstPtr;     //Cast do ponteiro do tipo void para ponteiro do tipo TInfo
}

//Thread 2
void* thread_2(void *firstPtr){
    TInfo *ptr;
    ptr = (TInfo*) firstPtr;     //Cast do ponteiro do tipo void para ponteiro do tipo TInfo
}

//Thread 3
void* thread_3(void *firstPtr){
    TInfo *ptr;
    ptr = (TInfo*) firstPtr;     //Cast do ponteiro do tipo void para ponteiro do tipo TInfo
}

void* calcSize(void *firstPtr){
    TInfo *ptr;
    ptr = (TInfo*) firstPtr;     //Cast do ponteiro do tipo void para ponteiro do tipo TInfo


}

int start(){
    pthread_t thread1_ID,thread2_ID,thread3_ID,threadCalc_ID;                  //ID da Thread
    void *thread1_return,*thread2_return,*thread3_return,*threadCalc_return;   //Ponteiro de retorno
    int thread1,thread2,thread3,threadCalc;                                    //variavel de validação da Thread
    TInfo strDir, *ptrDir;       //struct e ponteiro para a struct de memoria compartilhada
    
    int contThread = 1;

    ptrDir = &strDir;           //passando o endereço da struct para o ponteiro

    //Variaveis de Diretório,
    DIR *dir;
    struct dirent *sDirent;
    char caminhoDir[50];
    int contDir = 0, contSubDir = 0, sizeDir = 0, atualDir = 1;

    setbuf(stdin,NULL);
    printf("\nCaminho e nome do diretório: ");
    fgets(caminhoDir,50,stdin);
    removeEnter(caminhoDir);
    strcpy(ptrDir->dirName,caminhoDir);

    if((dir = opendir(caminhoDir)) != NULL){    //Abre o diretório fornecido
        while((sDirent = readdir(dir)) != NULL){
            if(sDirent->d_type == DT_DIR)
                contDir++;
        }
        printf("Número de Diretórios: %d\n",contDir);
        closedir(dir);

        dir = opendir(caminhoDir);
        while((sDirent = readdir(dir)) != NULL && contDir > 0){
            if(contDir == 0){   //Se não houver nenhum diretório, apenas arquivos
                threadCalc = pthread_create(&threadCalc_ID,NULL,calcSize,(void*)(ptrDir));
                if(threadCalc != 0){
                    printf("\nErro ao criar a Thread Calc");
                    exit(EXIT_FAILURE);
                }
                pthread_join(threadCalc_ID,threadCalc_return);
            }else
                if(contDir == 1){   //Se houver apenas 1 diretório

                }else   
                    if(contDir == 2){   //Se houver 2 diretórios

                    }else 
                        if(contDir == 3){   //Se houver 3 diretórios

                        }else
                            if(contDir >= 4){   //Se houver 4 ou mais diretórios

                            }
                


                
            if(sDirent->d_type == DT_DIR && contThread == 1){
                printf("\nEntrou na thread 1");
            }
            if(sDirent->d_type == DT_DIR && contThread == 2){
                printf("\nEntrou na thread 2");
            }
            if(sDirent->d_type == DT_DIR && contThread == 3){
                printf("\nEntrou na thread 3");
            }
            if(sDirent->d_type == DT_DIR && contThread == 4){
                printf("\nEntrou na thread 4");
            }
            contDir--;
            printf("\nDiretórios restantes: %d",contDir);
            contThread++;       
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