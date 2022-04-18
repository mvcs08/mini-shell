#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "funcoes.h"

struct comando lerLinha(char *linha){

    struct comando palavras; // struct para guardar as referências das palavras encontradas
    palavras.nPalavras = 0; // Contador de palavras encontradas
    char *palavra;
    //Limpa endereço de memória que o ponteiro aponta
    for(int x = 0; x < 100; x++){
        palavras.palavras[x] = NULL;
    }
    palavra = strtok(linha, " \t\n");

    while(palavra != NULL){
        palavras.palavras[palavras.nPalavras] = palavra;
        palavras.nPalavras++;

        palavra = strtok(NULL, " \t\n");
        if(palavras.nPalavras > 100){
            printf("Comando não processado pois excede o MAX.\n");
//
        }
    }

    palavras.comandos = palavras.palavras[0];

    return palavras;

}


int codigoFuncao(char *arg){
    if(!arg){return -2;}
    if(strcmp(arg,"start")==0){return 1;};
    if(strcmp(arg,"wait")==0){return 2;};
    if(strcmp(arg,"stop")==0){return 3;};
    if(strcmp(arg,"continue")==0){return 4;};
    if(strcmp(arg,"kill")==0){return 5;};


    return -1;
}


void f_start(char **args){

    int retval;
    retval = fork();

    if(retval<0){
        printf("Erro");
    }else{
        if(retval > 0){//processo pai
            //wait(0);//processo pai aguarda o execução do processo filho
        }else{
            printf("[Processo filho: %5d]\n[Processo pai: %5d]\n", getpid(),getppid());
            execvp(args[1], (args+1));
            printf("Errooooooor...\n");//só executa esta linha caso execvp retorne algum erro
        }
    }
}

void f_run(char **args){}

void f_wait(){

    int wstatus;
    wait(&wstatus);
    if(WIFEXITED(wstatus)){
        int statusCode = WEXITSTATUS(wstatus);
        if(statusCode==0){
            printf("PROCESSO FINALIZADO NORMAL COM STATUS 0\n");
        }else{
            printf("PROCESSO  FINALIZADO ANORMAL COM STATUS %d\n",statusCode);
        }
    }else{
            printf("NÃO HÁ PROCESSOS PARA FINALIZAR!\n");
    }

}

void f_stop(int id){

    if(kill(id,SIGSTOP)==0){
        printf("myshell: processo %d parou a execução.\n", id);
    }else{
        printf("myshell: processo no stop\n");
    }

}

void f_continue(int id){
    if(kill(id,SIGCONT)==0){
        printf("myshell: processo %d voltou a execução.\n", id);
    }else{
        printf("myshell: processo no stop\n");
    }
}

void f_kill(int id){
    kill(id,1);
    printf("myshell: processo %d finalizado\n", id);
}
