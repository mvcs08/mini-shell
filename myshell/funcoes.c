#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "funcoes.h"

void loop(){

    char *linha;
    char **tokens;
    do{

        printf("myshell> ");
        fflush(stdout);
        linha = lerLinha();
        tokens = quebrarLinha(linha);


        f_start(tokens);

    }while(TRUE);



}

char *lerLinha(){
    int tamanho = LSH_RL_BUFSIZE;
    int position = 0;
    char *linha = malloc(sizeof(char)*tamanho); //Retorna um ponteiro que aponta para o bloco consecutivo de memória reservado
    int c;


    if(!linha){
        printf("%s","Erro ao alocar memória...\n");
        exit(EXIT_FAILURE);//Informa ao SO que fechou de maneira excepcional
    }

    while(1){
        c = getchar();

        if(c == EOF || c == '\n'){//EOF infica o final da leitura
            linha[position]='\0';
            return linha;
        }else{
            linha[position] = c;

        }
        position++;

        if(position >= tamanho){
            tamanho+=LSH_RL_BUFSIZE;
            linha = realloc(linha, tamanho);
            if(!linha){
                printf("Error de memória....\n");
            }
        }
    }



}

char **quebrarLinha(char *linha){

    int tamanho = MAX_PALAVRAS;
    char **palavras = malloc(sizeof(char*)*tamanho);
    char *palavra;
    int position = 0;

    if(!palavras){
        printf("Erro de memória...\n");
    }

    palavra = strtok(linha, DELIMITADOR);

    while(palavra != NULL)
    {
        palavras[position] = palavra;
        position++;

       /* if(position>=tamanho){
            tamanho+=MAX_PALAVRAS;
            palavras = realloc(palavras, tamanho * sizeof(char*));
            if(!palavras){
                printf("Erro de memória...\n");
            }
        }*/
        palavra = strtok(NULL, DELIMITADOR);
    }

    palavras[position] = NULL;
//    printf("valor de position %d\n", position);
//    printf("Valor da ultima palavra %s\n", palavras[position]);
    return palavras;

}

int codigoFuncao(char *arg){

    if(strcmp(arg,"start")==0){return 1;};

    return -1;

}

void f_start(char **args){

    int retval;
    retval = fork();

    if(retval<0){
        printf("Erro");
    }else{
        if(retval > 0){//processo pai
            wait(0);//processo pai aguarda o execução do processo filho
        }else{
            printf("[Processo filho:%5d]\n[Processo pai:%5d]\n", getpid(),getppid());
            execvp(args[0], args);
            printf("Errooooooor...\n");//só executa esta linha caso execvp retorne algum erro
        }
    }
}
