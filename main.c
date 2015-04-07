#include <stdio.h>
#include <stdlib.h>

int main()
{
    /**Arquivo Fonte que gera a tabela de Tokens
    *
    *
    *
    *   Armazenar ultimo estado valido
    *
    *
    *
    **/
    int i;
    do{
        if(i-1==18){
            if(i==18)
                printf("\ni: %d,",i);
            else
                printf("\nI: %d + %d = %d ",i/2,i/2,(i/2)*2);
        }
        else{
            // これでおわりだ
        }
    }while(i<20);

    return 0;
}
