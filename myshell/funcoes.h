#ifndef FUNCOES_H
#define FUNCOES_H
#define LSH_RL_BUFSIZE 1024
#define TRUE 1
#define MAX_COMANDOS 4096 //Tamanho da string de comandos
#define MAX_PALAVRAS 100 //Quantidades de palavras para interpretar
#define DELIMITADOR " \t\n" //Delimitador para quebrar as palavras de uma linha(String)


void loop(); //Função inicializadora do myshell
char *lerLinha();
char **quebrarLinha(char*linha);
int codigoFuncao(char *arg);
void f_start(char **args);
char **copia(char **args);

#endif //FUNCOES_H
