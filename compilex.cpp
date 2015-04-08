#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXTARQ 20
#define MAXTA 50

using namespace std;

typedef struct token{
    int id;
    char *name;
    char tipo;
    int linha;
    int coluna;
}Token;

int Quantidade=0;
int linhaAtual=0;
int colunaAtual=0;
int linhaAnter=0;
int colunaAnter=0;

int verificarToken(char *buf,int tamanho);

void gravarTokens(struct token **lista,FILE *arq);

int main()
{ /*  txt com alterações  */
    FILE *arq=NULL;
    FILE *said=NULL;
    Token **lista=NULL;
    cout << "Digite nome do arquivo para leitura: "<< endl;
    lista=new Token[1][1];
    char arquivo[MAXTARQ];
    char um,buf[MAXTA];
    int bufLinha=0,estadoAtual=11,estadoAnter=11;
    cin.getline(arquivo,MAXTARQ-1);
    arq=fopen(arquivo,"r");
    if(!arq){
        cout << "Nao foi possivel abrir o arquivo!";
        return 0;
    };
    said=fopen("tokens.txt","w");
    if(!said){
        cout << "Nao sera possivel gravar o arquivo!\n";
    };
    linhaAtual=1;
    while(feof(arq)==0){
        fread(&um,sizeof(char),1,arq);
        colunaAtual++;
        estadoAnter=estadoAtual;
        if(estadoAnter==0&&um!='\n')
            continue;
        else if(estadoAnter==1&&(um!='*'||um!='/'))
            continue;
        else{
            buf[bufLinha]=um;
            bufLinha++;

            estadoAtual=verificarToken(buf,bufLinha);
        }





    }
    /**
    somente para testar.
    do{
        fread(&um,sizeof(char),1,arq);
        cout << um;
    }while(feof(arq)==0);
    cout << "terminou"<<endl;
    */
    gravarTokens(lista,said);
    fclose(arq);
	fclose(said);
	return 0;
}

int verificarToken(char *buf,int tamanho){
    char um=buf[0];
    switch (um){
        case '#':
            return 0;
            break;
        case '\n':
            linhaAtual++;
            colunaAtual=0;
            return 20;
            break;
        case '"':
            return 9;
            break;
        case '/'||'*'||'+'||'-'||'('||')':
            if(um=='/'){
                if(buf[1]=='/')
                    return 0;
                else if(buf[1]=='*')
                    return 1;
            }
            else if(um=='*'){
                if(buf[1]=='/')
                    return 1;
                else
                    return 2;
            }
            else
                return 2;
            break;
        case '<'||'>'||'!'||'='||'|'||'&':
            return 2;
            break;
        case '['||'{':
            return 4;
            break;
        case '}'||']':
            return 5;
            break;
        case '0'||'1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9'||'.':
            return 3;
            break;
        case 'a'||'b'||'c'||'d'||'e'||'f'||'g'||'h'||'i'||'j'||'k'||'l'||'m'||'n'||'o'||'p'||'q'||'r'||'s'||'t'||'u'||'v'||'w'||'x'||'y'||'z'||'A'||'B'||'C'||'D'||'E'||'F'||'G'||'H'||'I'||'J'||'K'||'L'||'M'||'N'||'O'||'P'||'Q'||'R'||'S'||'T'||'U'||'V'||'W'||'X'||'Y'||'Z'||
            return 8;
            break;
        default:{
            return 11;
            break;
        }
        break;
    };

    return 11;
}
void gravarTokens(Token **lista,FILE *arq){

}
