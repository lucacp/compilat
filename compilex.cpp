#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXTARQ 20
#define MAXTA 50
#define LINECOMMENT 0
#define BLOCKCOMMENT 1
#define ENDLINECOMMENT 20
#define ENDBLOCKCOMMENT 19
#define STARTENDSTR 9
#define NORMAL 11
#define NUMERO 3
#define CARACTER 8
#define OPERADOR 2

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

int tratarBuffer(char *buf,int tamanho,int estado);

int main()
{ /*  txt com alterações  */
    FILE *arq=NULL;
    FILE *said=NULL;
    Token **lista=NULL;
    cout << "Digite nome do arquivo para leitura: "<< endl;
    lista=new Token[1][1];
    char arquivo[MAXTARQ];
    char um,buf[MAXTA];
    int bufLinha=0,estado=NORMAL,i=0;
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
        if(estado==LINECOMMENT&&um!='\n')
            continue;
        else if(estado==BLOCKCOMMENT&&(um!='/'&&um!='*'))
            continue;
        else{
            if(um==' '||um==';'||um=='\t'||um=='\n'){
                estado=tratarBuffer(buf,bufLinha,estado);
                for(i=0;i<bufLinha;i++){
                    buf[i]=' ';
                }
                bufLinha=0;
            }
            else{
                buf[bufLinha]=um;
                bufLinha++;
            };
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
    //gravarTokens(lista,said);
    fclose(arq);
	fclose(said);
	return 0;
}

int verificarToken(char *buf,int tamanho){
    char um=buf[0];
    switch (um){
        case '#':
            return LINECOMMENT;
            break;
        case '\n':
            linhaAtual++;
            colunaAtual=0;
            return ENDLINECOMMENT;
            break;
        case '"':
            return STARTENDSTR;
            break;
        case '/'||'*':
            if(um=='/'){
                if(buf[1]=='/')
                    return LINECOMMENT;
                else if(buf[1]=='*')
                    return BLOCKCOMMENT;
            }
            else if(um=='*'){
                if(buf[1]=='/')
                    return ENDBLOCKCOMMENT;
                else
                    return OPERADOR;
            }
            else
                return OPERADOR;
            break;
        case '<'||'>'||'!'||'='||'|'||'&'||'+'||'-'||'('||')'||'.':
            return OPERADOR;
            break;
        case '['||'{':
            return 4;
            break;
        case '}'||']':
            return 5;
            break;
        case '0'||'1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9':
            return NUMERO;
            break;
        case 'a'||'b'||'c'||'d'||'e'||'f'||'g'||'h'||'i'||'j'||'k'||'l'||'m'||'n'||'o'||'p'||'q'||'r'||'s'||'t'||'u'||'v'||'w'||'x'||'y'||'z'||'A'||'B'||'C'||'D'||'E'||'F'||'G'||'H'||'I'||'J'||'K'||'L'||'M'||'N'||'O'||'P'||'Q'||'R'||'S'||'T'||'U'||'V'||'W'||'X'||'Y'||'Z'||
            return CARACTER;
            break;
        default:{
            return NORMAL;
            break;
        }
        break;
    };

    return 11;
}
void gravarTokens(Token **lista,FILE *arq){

}
int tratarBuffer(char *buf,int tamanho,int estado){
    /**
    * se primeiro char é # ignora tudo até '\n'
    * se primeiro char é / e segundo char é / mesma coisa
    * se o segundo char for * então até não aparecer um * e / ignora tudo.
    * **********************************************************************
    * para os tokens primeiro são os numeros, apos as palavras reservadas e identificadores,
    * se mesmo assim não for então é tratado como token.
    *
    *
    *
    */
    int i;
    for(i=0;i<tamanho;i++){
        if(estado==LINECOMMENT)
            if(buf[i]=='\n'){
                estado=ENDLINECOMMENT;
                linhaAtual++;
                colunaAtual=0;
            };
        else if(buf[i]=='#')
            estado=LINECOMMENT;
        else if(i+1<tamanho){
            if(estado!=BLOCKCOMMENT){
                if(buf[i]=='/'){
                    if(buf[i+1]=='/')
                        estado=LINECOMMENT;
                    else if(buf[i+1]=='*')
                        estado=BLOCKCOMMENT;
                    else{
                        ///aqui cai quando é: / e mais alguma coisa.
                    }
                }
                else{

                }
            }
            else{
                if(buf[i]=='*'){
                    if(buf[i+1]=='/')
                        estado=ENDBLOCKCOMMENT;
                };
            };
        }
    }
}
