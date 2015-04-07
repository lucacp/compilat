#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXTARQ 20
#define MAXTA 50

using namespace std;

struct token{
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

int adicionaToken(struct token *lista,char *buf,int tamanho);

int verificarToken(char *buf,int tamanho);

int main()
{ /*  txt com alterações  */
    FILE *arq=NULL;
    FILE *said=NULL;
    struct token **lista=NULL;
    cout << "Digite nome do arquivo para leitura: "<< endl;
    char arquivo[MAXTARQ];
    char um,buf[MAXTA],buf2[MAXTA];
    int bufLinha=0,estado=0;
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
        if(um==' ')
            continue;
        else{
            buf[bufLinha]=um;
            bufLinha++;
        };
        if(bufLinha+1==MAXTA){
            estado=adicionaToken(lista[Quantidade]);
            Quantidade++;
            if(estado!=0){

            }
        };



    }
    /**
    somente para testar.
    do{
        fread(&um,sizeof(char),1,arq);
        cout << um;
    }while(feof(arq)==0);
    cout << "terminou"<<endl;
    */
    fclose(arq);
	fclose(said);
	return 0;
}

void adicionaToken(struct token *lista,char *buf,int tamanho){
    Token *Taux=NULL;
    Taux= new Token;
    if (tamanho==0)
        return;
    int aux,dois,atual=0,anter=0,seq[tamanho];
    for(aux=0;aux<tamanho;aux++){
        anter=atual;
        atual=seq[aux]=verificarToken(&buf[aux],tamanho);
        switch (anter){
        case 0:
            if(atual==20){
                for(dois=0;dois<MAXTA;dois++){
                    if(dois>=MAXTA-aux)
                        buf[dois]='\0';
                    else
                        buf[dois]=buf[aux+dois];
                    seq[dois]=0;
                };
            }else
                atual=0;
            break;
        case 9:
            if(atual==9){
                Taux.name=new char[]
            }
        }
    }
    lista=Taux;
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
            if(tamanho==1)
                return 1;
            else if(um=='/'&&(buf[1]=='*'||buf[1]=='/'))
                return 0;
            else
                return 1;
            break;
        case '<'||'>'||'!'||'='||'|'||'&':
            return 2;
            break;
        case '['||']'||'{'||'}':
            return 4;
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
