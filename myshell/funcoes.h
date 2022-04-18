#ifndef FUNCOES_H
#define FUNCOES_H

struct comando{
    char *palavras[100];
    char *comandos;
    int nPalavras;
};

struct comando lerLinha(char *linha);
int codigoFuncao(char* arg);
void f_start(char **args);
void f_run(char **agrs);
void f_wait();
void f_stop(int id);
void f_continue(int id);
void f_kill(int id);
void f_quit();




#endif // FUNCOES_H
