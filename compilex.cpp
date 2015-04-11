#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <malloc.h>
#define MAXTARQ 20
#define MAXTA 50
#define LINECOMMENT 0
#define BLOCKCOMMENT 1
#define ENDLINECOMMENT 20
#define ENDBLOCKCOMMENT 19
#define STARTENDSTR 9
#define NORMAL 11
#define CARACTER 8
#define OPERADOR 2
#define NUM 256
#define ID 257
#define TRUE 258
#define FALSE 259


using namespace std;

class Token{
    public:

    final int tag;

    Token(int v){
        tag=v;
    };
};
class Num extends Token{
    public:
        final int value;
        Num(int v){
            super(NUM);
            value=v;
        };
};
class Word extends Token{
    public:
        final string lexeme;
        Word(int v,string s){
            super(v);
            lexeme=new string(s);
        };

};
class Lexer{
    private:
        char peek = ' ';
        Hashtable words = new Hashtable();
    public:
        int line=1;
};


int Quantidade=0;
int linhaAtual=0;
int colunaAtual=0;
int linhaAnter=0;
int colunaAnter=0;

int verificarToken(char *buf,int tamanho);

void gravarTokens(class Token *lista,FILE *arq);

int tratarBuffer(char *buf,int tamanho,int estado);

int main()
{ /*  txt com alterações  */
    FILE *arq=NULL;
    FILE *said=NULL;
    Token *lista=new Token();
    cout << "Digite nome do arquivo para leitura: "<< endl;
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
                if(um=='\n'){
                    buf[bufLinha]=um;
                    ++bufLinha;
                };
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
        case '/':
            if(buf[1]=='/'){
                return LINECOMMENT;
            }
            else if(buf[1]=='*'){
                return BLOCKCOMMENT;
            }
            else{
                return OPERADOR;
            };
            break;
        case '*':
            if(buf[1]=='/'){
                return ENDBLOCKCOMMENT;
            }
            else{
                return OPERADOR;
            }
            break;
        case '+':
        case '-':
        case '(':
        case ')':
        case '.':
        case '%':
        case '[':
        case '{':
        case '}':
        case ']':
        case '<':
        case '>':
        case '!':
        case '=':
        case '|':
        case '&':
            return OPERADOR;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return NUM;
            break;
        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y':
        case 'z': case 'A': case 'B': case 'C': case 'D':
        case 'E': case 'F': case 'G': case 'H': case 'I':
        case 'J': case 'K': case 'L': case 'M': case 'N':
        case 'O': case 'P': case 'Q': case 'R': case 'S':
        case 'T': case 'U': case 'V': case 'W': case 'X':
        case 'Y': case 'Z':
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
void gravarTokens(class Token *lista,FILE *arq){
    ///objetivo nessa função é gravar o token que foi criado no tratarBuffer.
}
int tratarBuffer(char *buf,int tamanho,int estado){
    /**
    * se primeiro char é # ignora tudo até '\n'
    * se primeiro char é / e segundo char é / mesma coisa
    * se o segundo char for * então até não aparecer um * e / ignora tudo.
    *                        OK
    * **********************************************************************
    *
    * para os tratar primeiro são os numeros,
    *
    * apos as palavras reservadas
    *
    * identificadores (variaveis)
    *
    * e se mesmo assim não for então é tratado como token.
    *
    *
    *
    */
    int i;
    for(i=0;i<tamanho;i++){
        if(estado==LINECOMMENT){
            if(buf[i]=='\n'){
                estado=ENDLINECOMMENT;
                linhaAtual++;
                colunaAtual=0;
            };
        }
        else if(buf[i]=='#'){
            estado=LINECOMMENT;
        }
        else if(i+1<tamanho){
            if(estado!=BLOCKCOMMENT){
                if(buf[i]=='/'){
                    if(buf[i+1]=='/'){
                        estado=LINECOMMENT;
                    }
                    else if(buf[i+1]=='*'){
                        estado=BLOCKCOMMENT;
                    }
                    else{
                        ///aqui cai quando é: / e mais alguma coisa.
                        estado=verificarToken(&buf[i],tamanho-i);
                    }
                }
                else{
                    ///aqui cai todos as outras possibilidades.
                    estado = verificarToken(&buf[i],tamanho-i);
                }
            }
            else{
                if(buf[i]=='*'){
                    if(buf[i+1]=='/'){
                        estado=ENDBLOCKCOMMENT;
                    }
                }
            }
        }
    }
    return estado;
}
