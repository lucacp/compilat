#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string>
#define MAXTARQ 20
#define MAXTA 30
#define LINECOMMENT 10
#define BLOCKCOMMENT 9
#define ENDLINECOMMENT 20
#define ENDBLOCKCOMMENT 19
#define STARTENDSTR 9
#define NORMAL 11
#define VAZIO 13
#define CARACTER 8
#define OPERADOR 2
#define NUM 256
#define ID 257
#define TRUE 258
#define FALSE 259

std::string to_string(int value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

using namespace std;

int Quantidade=0;

class Token{
    public:
        int id;
        char *name;
        char tipo;
        int linha;
        int coluna;
        class Token *next;
        Token(){
            next=NULL;
            Quantidade++;
        }
        string toString(){
            string id1 = to_string(id);
            string linha1 = to_string(linha);
            string coluna1 = to_string(coluna);
            return "id: "+id1+", Token: "+name[0]+", tipo: "+tipo+", Linha: "+linha1+", Coluna: "+coluna1+"\n";
        };
};


int linhaAtual;
int colunaAtual=0;
int linhaAnter=1;
int colunaAnter=0;

int verificarToken(char *buf,int tamanho);

void gravarTokens(char *buf,int estado);

void gravarTokensTam(char *buf,int estado,int tamanho);

int tratarBuffer(char *buf,int tamanho,int estado);

void identificarNumeros(char *buf,int tamanho);

void identificadorString(char *buf,int tamanho);

int main()
{ /*  txt com alterações  */
    FILE *arq=NULL;
    cout << "Digite nome do arquivo para leitura: "<< endl;
    char arquivo[MAXTARQ];
    char um,*buf;
    buf=new char[MAXTA];
    int bufLinha=1,estado=NORMAL,i=0;
    cin.getline(arquivo,MAXTARQ-1);
    arq=fopen(arquivo,"r");
    if(!arq){
        cout << "Nao foi possivel abrir o arquivo!";
        return 0;
    };
    linhaAtual=1;
    while(feof(arq)==0){
        fread(&um,sizeof(char),1,arq);
        colunaAtual++;
        if(estado==LINECOMMENT){
            cout << " 1.";
            buf[--bufLinha]=um;
            if(verificarToken(&buf[bufLinha],1)==ENDLINECOMMENT);
                estado=NORMAL;
            bufLinha++;
        }
        else if(estado==BLOCKCOMMENT){
            buf[--bufLinha]=um;
            if(verificarToken(&buf[bufLinha],2)==ENDBLOCKCOMMENT)
                estado=NORMAL;
            bufLinha++;
        }
        else{
            if(um==' '||um==';'){
                /*if(um==' '){
                    buf[bufLinha]=um;
                    bufLinha++;
                };*/
                cout << " 3.";
                estado=tratarBuffer(buf,bufLinha,estado);
                cout <<"\nstate: "<< estado<<" ...\n";
                delete[] buf;
                buf=new char[MAXTA];
                bufLinha=1;
            }
            else{
                cout << " 4.";
                buf[bufLinha]=um;
                bufLinha++;
                estado=verificarToken(&buf[bufLinha],bufLinha);
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

    fclose(arq);

	return 0;
}

int verificarToken(char *buf,int tamanho){
    char um=buf[0];
    if(tamanho<=0)
        return VAZIO;
    switch (um){
        case '#':
            cout << " ...;... ";
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
void gravarTokens(char *buf,int estado){
    ///objetivo nessa função é criar e gravar o token no arquivo de saida.
    int i=0;
    ofstream said;
    if(Quantidade==0)
        said.open("tokens.txt",ios::ate|ios::in|ios::trunc);
    else
        said.open("tokens.txt",ios::ate|ios::in);
    if(!said.is_open()){
        cout << "Nao sera possivel abrir o arquivo!2\n";
    };
    class Token *aux=new Token();
    aux->id=Quantidade;
    aux->name=new char;
    aux->name[0]=buf[0];
    switch (estado){
        case NORMAL:
            aux->tipo='N';
            break;
        case CARACTER:
            aux->tipo='C';
            break;
        case NUM:
            aux->tipo='I';
            break;
        case OPERADOR:
            aux->tipo='O';
            break;
        case STARTENDSTR:
            aux->tipo='S';
            break;
        default:
            aux->tipo='E';
            break;
    }
    aux->linha=linhaAnter;
    aux->coluna=colunaAnter;

    cout << aux->toString();

    said << aux->toString();
    said.close();
    delete aux;
    cout << "qt: "<<Quantidade<<endl;
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
    cout << "tratarBuffer: "<<estado<<" \n";
    for(i=2;i<tamanho;i++){
        colunaAnter++;
        if(estado==LINECOMMENT){
            cout << " 1,";
            if(buf[i]=='\n'){
                estado=ENDLINECOMMENT;
                linhaAnter++;
                colunaAnter=0;
            };
        }
        else if(buf[i]=='#'){
            cout << " 2,";
            estado=LINECOMMENT;
        }
        else{
            cout << " 3,";
            if(estado!=BLOCKCOMMENT){
                if(buf[i]=='/'){
                    if(buf[i+1]=='/'){
                        cout << " 4,";
                        estado=LINECOMMENT;
                    }
                    else if(buf[i+1]=='*'){
                        cout << " 5,";
                        estado=BLOCKCOMMENT;
                    }
                    else{
                        cout << " 6,";
                        estado=verificarToken(&buf[i],tamanho-i);
                        gravarTokens(&buf[i],estado);
                    };
                }
                else{
                    cout << " 7,";
                    ///aqui cai todos as outras possibilidades.
                    estado = verificarToken(&buf[i],tamanho-i);
                    switch (estado){
                        case NUM:
                            identificarNumeros(&buf[i],tamanho-i);
                            break;
                        case STARTENDSTR:
                            identificadorString(&buf[i],tamanho-i);
                        case OPERADOR:
                            if(verificarToken(&buf[i+1],tamanho-i-1)==OPERADOR)
                                gravarTokensTam(&buf[i],estado,2);
                            else
                                gravarTokens(&buf[i],estado);
                            break;
                        default:
                            gravarTokens(&buf[i],NORMAL);
                            break;
                    }

                };
            }
            else{
                cout << " 8,";
                verificarToken(&buf[i],tamanho-i);
                if(buf[i]=='*'){
                    if(buf[i+1]=='/'){
                        cout << " 9,";
                        estado=ENDBLOCKCOMMENT;
                    }
                }
            }
        }
    }
    return estado;
}
void identificarNumeros(char *buf,int tamanho){
    int i,stat1=0,stat2=NUM;
    for(i=1;i<tamanho;i++){
        stat1=verificarToken(&buf[i],tamanho);
        if(stat1!=NUM){
            break;
        }
    };
    gravarTokensTam(buf,stat2,i);
}
void identificadorString(char *buf,int tamanho){
    int i,stat1=0,stat2=CARACTER;
    for(i=1;i<tamanho;i++){
        stat1=verificarToken(&buf[i],tamanho);
        if(stat1!=stat2){
            break;
        }
    };
    gravarTokensTam(buf,stat2,i);
};
void gravarTokensTam(char *buf,int estado,int tamanho){
    ///objetivo nessa função é criar e gravar o token no arquivo de saida.
    int i=0;
    ofstream said;
    if(Quantidade==0)
        said.open("tokens.txt",ios::ate|ios::in|ios::trunc);
    else
        said.open("tokens.txt",ios::ate|ios::in);
    if(!said.is_open()){
        cout << "Nao sera possivel abrir o arquivo!2\n";
    };
    class Token *aux=new Token();
    aux->id=Quantidade;
    aux->name=new char[tamanho];
    for(i=0;i<tamanho;i++){
        aux->name[i]=buf[i];
    }
    switch (estado){
        case CARACTER:
            aux->tipo='C';
            break;
        case NUM:
            aux->tipo='I';
            break;
        case OPERADOR:
            aux->tipo='O';
            break;
        case STARTENDSTR:
            aux->tipo='S';
            break;
        default:
            aux->tipo='E';
            break;
    }
    aux->linha=linhaAnter;
    aux->coluna=colunaAnter;

    cout << aux->toString();

    said << aux->toString();
    said.close();
    delete aux;
    cout << "qt: "<<Quantidade<<endl;
}
