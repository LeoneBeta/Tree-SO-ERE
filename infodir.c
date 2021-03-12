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

void removeEnter(char string[]){
	int tamanho = strlen(string) - 1;
	if (string[tamanho] == '\n'){
		string[tamanho] = '\0';
	}else {
		while (getc(stdin) != '\n')
			continue;
	}
}

/*Desenvolvimento das threads após a conclusão do desenvolvimento de busca dos diretórios*/

//Thread base entra em 1 subdiretório e o varre calculando o tamanho dos arquivos dentro dele e retornando
//o tamanho do subdiretório
void* threadSingleDir(void *firstPtr){
    TInfo *ptr;
    ptr = (TInfo*) firstPtr;     //Cast do ponteiro do tipo void para ponteiro do tipo TInfo
    DIR *dir;
    struct dirent *sDirent;
    char nameDir[50];
    int contDir = 0, contSubDir = 0, sizeDir = 0, atualDir = 1;

    struct stat sStat;

    int i = 0;

    //Verificar qual diretório a thread ira abri 


    dir = opendir(ptr->dirName);
    sDirent = readdir(dir);
    if(sDirent->d_type == DT_DIR){
        while(ptr->caminhoDir[i] != '\0')
            i++;
        ptr->caminhoDir[i] = '/';
        i++;
        ptr->caminhoDir[i] = '\0';

        strcat(ptr->caminhoDir,sDirent->d_name);
        threadSingleDir(ptr);   //Chamada recursiva dessa propria função entrando ate o fim dos diretórios
        
    }else{
        i = 0;
        while(ptr->caminhoDir[i] != '\0')
            i++;
        ptr->caminhoDir[i] = '/';
        i++;
        ptr->caminhoDir[i] = '\0';

        strcat(ptr->caminhoDir,sDirent->d_name);

        stat(ptr->caminhoDir,&sStat);
        
        printf("Arquivo: %s",sDirent->d_name);
        printf("\nTamanho do Arquivo Atual: %ld\n",sStat.st_size);

        ptr->sizeDir += sStat.st_size;

        printf("\nTamanho total ja calculado: %ld\n",ptr->sizeDir);

        i = 0;
        while(ptr->caminhoDir[i] != '\0')
            i++;
        while(ptr->caminhoDir[i] != '/'){
            ptr->caminhoDir[i] = '\0';
            i--;
        }
    }
}

//Calcula o resultado dos tamanhos dos diretórios, caso houver mais de 3 diretórios,
//essa thread faz o serviço de percorrer todos os diretórios seguintes
void* threadMultiDir(void *firstPtr){
   TInfo *ptr;
    ptr = (TInfo*) firstPtr;     //Cast do ponteiro do tipo void para ponteiro do tipo TInfo
    DIR *dir;
    struct dirent *sDirent;
    char nameDir[50];
    int contDir = 0, contSubDir = 0, sizeDir = 0, atualDir = 1;

    struct stat sStat;

    int i = 0;

    dir = opendir(ptr->dirName);
    while((sDirent = readdir(dir)) != NULL /*&& contDir > 0*/){
        if(sDirent->d_type == DT_DIR){
            while(ptr->caminhoDir[i] != '\0')
                i++;
            ptr->caminhoDir[i] = '/';
            i++;
            ptr->caminhoDir[i] = '\0';

            strcat(ptr->caminhoDir,sDirent->d_name);
            threadSingleDir(ptr);   //Chamada recursiva dessa propria função entrando ate o fim dos diretórios
            
        }else{
            i = 0;
            while(ptr->caminhoDir[i] != '\0')
                i++;
            ptr->caminhoDir[i] = '/';
            i++;
            ptr->caminhoDir[i] = '\0';

            strcat(ptr->caminhoDir,sDirent->d_name);

            stat(ptr->caminhoDir,&sStat);
            
            printf("Arquivo: %s",sDirent->d_name);
            printf("\nTamanho do Arquivo Atual: %ld\n",sStat.st_size);

            ptr->sizeDir += sStat.st_size;

            printf("\nTamanho total ja calculado: %ld\n",ptr->sizeDir);

            i = 0;
            while(ptr->caminhoDir[i] != '\0')
                i++;
            while(ptr->caminhoDir[i] != '/'){
                ptr->caminhoDir[i] = '\0';
                i--;
            }
        }
    }
}

int start(){
    pthread_t threadSingleDir1_ID,threadSingleDir2_ID,threadSingleDir3_ID,threadMultiDir_ID;                  //ID da Thread
    void *threadSingleDir1_return,*threadSingleDir2_return,*threadSingleDir3_return,*threadMultiDir_return;   //Ponteiro de retorno
    int threadSingleDir1_res,threadSingleDir2_res,threadSingleDir3_res,threadMultiDir_res;                                    //variavel de validação da Thread
    TInfo strDir, *ptrDir;       //struct e ponteiro para a struct de memoria compartilhada
    
    int contThread = 1;

    ptrDir = &strDir;           //passando o endereço da struct para o ponteiro
    
    //Variaveis de Diretório,
    DIR *dir;
    struct dirent *sDirent;
    char nameDir[50];
    int contDir = 0;

    struct stat sStat;

    int i = 0;

    setbuf(stdin,NULL);
    printf("\nNome do diretório: ");
    fgets(nameDir,50,stdin);
    removeEnter(nameDir);
    strcpy(ptrDir->dirName,nameDir);
    strcpy(ptrDir->caminhoDir,nameDir);

    if((dir = opendir(nameDir)) != NULL){    //Abre o diretório fornecido
        while((sDirent = readdir(dir)) != NULL){
            if(sDirent->d_type == DT_DIR)
                contDir++;
        }
        printf("Número de Diretórios: %d\n\n",contDir);
        closedir(dir);

        if(contDir >= 1){   //Se houver 1 ou menos diretórios
            threadSingleDir1_res = pthread_create(&threadSingleDir1_ID,NULL,threadSingleDir,(void*)(ptrDir));
            if(threadSingleDir1_res != 0){
                printf("\nErro ao criar a Thread Calc");
                exit(EXIT_FAILURE);
            }
        pthread_join(threadSingleDir1_ID,threadSingleDir1_return);
        }else 
            if(contDir == 2){   //Se houver 2 diretórios
                threadSingleDir1_res = pthread_create(&threadSingleDir1_ID,NULL,threadSingleDir,(void*)(ptrDir));
                threadSingleDir2_res = pthread_create(&threadSingleDir2_ID,NULL,threadSingleDir,(void*)(ptrDir));
                if(threadSingleDir1_res != 0){
                    printf("\nErro ao criar a Thread 1");
                    exit(EXIT_FAILURE);
                }
                if(threadSingleDir2_res != 0){
                    printf("\nErro ao criar a Thread 2");
                    exit(EXIT_FAILURE);
                }
                pthread_join(threadSingleDir1_ID,threadSingleDir1_return);
                pthread_join(threadSingleDir2_ID,threadSingleDir2_return);
            }else 
                if(contDir == 3){   //Se houver 3 diretórios
                    threadSingleDir1_res = pthread_create(&threadSingleDir1_ID,NULL,threadSingleDir,(void*)(ptrDir));
                    threadSingleDir2_res = pthread_create(&threadSingleDir2_ID,NULL,threadSingleDir,(void*)(ptrDir));
                    threadSingleDir3_res = pthread_create(&threadSingleDir3_ID,NULL,threadSingleDir,(void*)(ptrDir));
                    if(threadSingleDir1_res != 0){
                        printf("\nErro ao criar a Thread 1");
                        exit(EXIT_FAILURE);
                    }
                    if(threadSingleDir2_res != 0){
                        printf("\nErro ao criar a Thread 2");
                        exit(EXIT_FAILURE);
                    }
                    if(threadSingleDir3_res != 0){
                        printf("\nErro ao criar a Thread 3");
                        exit(EXIT_FAILURE);
                    }
                    pthread_join(threadSingleDir1_ID,threadSingleDir1_return);
                    pthread_join(threadSingleDir2_ID,threadSingleDir2_return);
                    pthread_join(threadSingleDir3_ID,threadSingleDir3_return);
                }else
                    if(contDir >= 4){   //Se houver 4 ou mais diretórios
                        threadSingleDir1_res = pthread_create(&threadSingleDir1_ID,NULL,threadSingleDir,(void*)(ptrDir));
                        threadSingleDir2_res = pthread_create(&threadSingleDir2_ID,NULL,threadSingleDir,(void*)(ptrDir));
                        threadSingleDir3_res = pthread_create(&threadSingleDir3_ID,NULL,threadSingleDir,(void*)(ptrDir));
                        threadMultiDir_res = pthread_create(&threadMultiDir_ID,NULL,threadMultiDir,(void*)(ptrDir));
                        if(threadSingleDir1_res != 0){
                            printf("\nErro ao criar a Thread 1");
                            exit(EXIT_FAILURE);
                        }
                        if(threadSingleDir2_res != 0){
                            printf("\nErro ao criar a Thread 2");
                            exit(EXIT_FAILURE);
                        }
                        if(threadSingleDir3_res != 0){
                            printf("\nErro ao criar a Thread 3");
                            exit(EXIT_FAILURE);
                        }
                        if(threadMultiDir_res != 0){
                            printf("\nErro ao criar a Thread 4");
                            exit(EXIT_FAILURE);
                        }
                        pthread_join(threadSingleDir1_ID,threadSingleDir1_return);
                        pthread_join(threadSingleDir2_ID,threadSingleDir2_return);
                        pthread_join(threadSingleDir3_ID,threadSingleDir3_return);
                        pthread_join(threadMultiDir_ID,threadMultiDir_return);
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


    /*  DESENVOLVIMENTO DO PROGRAMA COM THREADS   */
    /*
        
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
    */
