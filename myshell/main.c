#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{


    while(1>0){
        char linha[4096];
        struct comando palavras;
        printf("myshell> ");
        fflush(stdout);
        fgets(linha,4096,stdin);

        palavras = lerLinha(linha);
        int op = codigoFuncao(palavras.comandos);

        switch(op)
        {
            case -2:
            break;
            case -1:
                printf("%s comando desconhecido\n", palavras.comandos);
            break;

            case 1:
                f_start(palavras.palavras);
                break;
            case 2:
                f_wait();
                break;
            case 3:
                f_stop(atoi(palavras.palavras[1]));
//                printf("%d\n", atoi(palavras.palavras[1]));
                break;
            case 4:
                f_continue(atoi(palavras.palavras[1]));
                break;
            case 5:
                f_kill(atoi(palavras.palavras[1]));
                break;
        }
    }

    return 0;
}
