#include <iostream>
#define TAM 8
#include <stdlib.h>
#include <time.h>       /* time */


using namespace std;

struct casa{
    int x;
    int y;
};

struct opcoes{
    casa origem;
    casa destino;
    int pecascom=0;
};

struct posicao{
    bool casaPreta=false;
    int nJogador=0;
};

void iniciarDama(posicao dama[][TAM])
{
    //NAda = 0; Jogador1 = 1, jogador2 = -1;
    int posBrancas = 0;
    for(int i = 0; i<TAM; i++)
    {
        //indica se as posições do branco começarão da coluna 0 ou da coluna 1
        if(i%2==0)
        {
            posBrancas=0;
        }
        else
        {
            posBrancas=1;
        }

        for(int j = 0;j<TAM;j++)
        {
            if(i<3)
            {
                if(posBrancas==j)
                {
                    posBrancas+=2;
                }
                else
                {
                    dama[i][j].casaPreta=true;
                    dama[i][j].nJogador=1;
                }
            }
            else if(i>=5)
            {
                if(posBrancas==j)
                {
                    posBrancas+=2;
                }
                else
                {
                    dama[i][j].casaPreta=true;
                    dama[i][j].nJogador=-1;
                }
            }
            else
            {
                if(posBrancas==j)
                {
                    posBrancas+=2;
                }
                else
                {
                    dama[i][j].casaPreta=true;
                    dama[i][j].nJogador=0;
                }
            }
        }
    }
}

void imprimirDama(posicao dama[][TAM])
{
    //letraColuna e letraLinha se referem a letra/numero que aparecem em cima, embaixo e do lado esquerdo da dama;
    char letraColuna = 'a';
    int numeroLinha = 1;

    //Para as linhas
    for(int i= -1; i<18; i++)
    {
        //Para as colunas
        cout << "    ";
        for(int j = -1; j<TAM; j++)
        {
            //linhas ímpares (com conteudo)
            if(i%2!=0)
            {
                /*Refere-se so primeiro espaço da matriz quando aparece,
                já que a linha das letras não tem um numero relacionado
                tem que substituir por um espaço vazio*/
                if((i==-1||i==17)&&j==-1)
                {
                    cout << "     ";
                }
                else if(i==-1||i==17) //Linhas contendo letras
                {
                   cout << letraColuna << "   ";
                   letraColuna++;
                }
                else if(j==-1)//Primeira coluna de numeros EX: (1   |)
                {
                    cout << numeroLinha << "  |";
                    numeroLinha++;
                }
                else if(dama[i/2][j].casaPreta==false) //Casas brancas
                {
                    cout << "||||";
                }
                else if(dama[i/2][j].nJogador==1) //Casas do jogador 1
                {
                    cout << " x |";
                }
                else if(dama[i/2][j].nJogador==-1) //Casas do jogador 2
                {
                    cout << " o |";
                }
                else // Casas pretas vazias
                {
                    cout << "   |";
                }
            }
            else //Linhas pares (sem conteudo)
            {
                if(j==-1) //Não colocamos o numero da linha nesse tipo de linha
                {
                    cout << "   |";
                }
                else
                {
                    cout << "---|";
                }
            }
        }
        //letraColuna volta para 'a', para que possa ser repetida a sequencia na ultima linha
        letraColuna = 'a';
        cout << endl;
    }
}
/*Função recursiva
1º-dama-Matriz do tabuleiro
2º- linha/coluna -Posição "atual"(que modifica ao longo de cada tentativa de jogada)
3º- linhaf/colunaf -Posição final
4º- jog - Jogador
5º- cam - Mostra o caminho que não deve ser tomado para que o programa não fique indo e voltando
6º- lex/cex - Posição da primeira jogada feita da sequencia
7º- pc - pecas que o movimento irá comer (variavel referenciada)

*/
bool estaLiberado(posicao dama[][TAM], int linha, int linhaf, int coluna, int colunaf, int jog, int cam, int ex, int lex, int cex, int& pc, bool teste)
{
    //Teste necessario para definir posição da primeira jogada da sequencia
    if(ex==1)
    {
        lex=linha;
        cex=coluna;
    }

    //Indica fim da execução, quando a linha e coluna forem iguais as linha e coluna de destino e verifica se pelo menos já foi feita uma jogada
    if(linha==linhaf && coluna==colunaf && ex!=0)
    {
        return true;
    }
    /*cada if testa os quatro extremos do quandrado onde a peça está

    1º-Verifica se a linha e coluna para onde vai a peça comedora existem
    2º-Verifica se há uma peça inimiga no meio para comer
    3º-Verifica se esse caminho não foi de onde ela veio (Para não ficar indo e voltando pelo mesmo caminho)
    4º-Verifica se a casa para onde a peça vai já não tem outra peça ou se tem uma peça do jogador mas coincide com a posição final
    5º-Verifica se a casa para onde vai não é a mesma da jogada inicial (para não andar em circulos)
    6º-Reexecuta a funçao com a nova posição, já que tudo antes era verdadeiro
    */
    else if(linha+2<8&&coluna+2<8&&dama[linha+1][coluna+1].nJogador==jog*-1&&cam!=1&&(dama[linha+2][coluna+2].nJogador==0||(dama[linha+2][coluna+2].nJogador==jog&&linha+2==linhaf&&coluna+2==colunaf))&&(linha+2!=lex||coluna+2!=cex)&&estaLiberado(dama, linha+2, linhaf, coluna+2, colunaf, jog, 4, ex+1, lex, cex, pc, teste))
    {
        //verifica se é só um teste
        if(!teste)
            dama[linha+1][coluna+1].nJogador=0;
        pc++;
    }
    else if(linha+2<8&&coluna-2>=0&&dama[linha+1][coluna-1].nJogador==jog*-1&&cam!=2&&(dama[linha+2][coluna-2].nJogador==0||(dama[linha+2][coluna-2].nJogador==jog&&linha+2==linhaf&&coluna-2==colunaf))&&(linha+2!=lex||coluna-2!=cex)&&estaLiberado(dama, linha+2, linhaf, coluna-2, colunaf, jog, 3, ex+1, lex, cex, pc, teste))
    {
        if(!teste)
            dama[linha+1][coluna-1].nJogador=0;
        pc++;
    }
    else if(linha-2>=0&&coluna-2>=0&&dama[linha-1][coluna-1].nJogador==jog*-1&&cam!=4&&(dama[linha-2][coluna-2].nJogador==0||(dama[linha-2][coluna-2].nJogador==jog&&linha-2==linhaf&&coluna-2==colunaf))&&(linha-2!=lex||coluna-2!=cex)&&estaLiberado(dama, linha-2, linhaf, coluna-2, colunaf, jog, 1, ex+1, lex, cex, pc, teste))
    {
        if(!teste)
            dama[linha-1][coluna-1].nJogador=0;
        pc++;
    }
    else if(linha-2>=0&&coluna+2<8&&dama[linha-1][coluna+1].nJogador==jog*-1&&cam!=3&&(dama[linha-2][coluna+2].nJogador==0||(dama[linha-2][coluna+2].nJogador==jog&&linha-2==linhaf&&coluna+2==colunaf))&&(linha-2!=lex||coluna+2!=cex)&&estaLiberado(dama, linha-2, linhaf, coluna+2, colunaf, jog, 2, ex+1, lex, cex, pc, teste))
    {
        if(!teste)
            dama[linha-1][coluna+1].nJogador=0;
        pc++;
    }
    else
    {
        return false;
    }
}

bool moverPeca(posicao dama[][TAM], int linha, int linhaf, int coluna, int colunaf, int jog, int& pc, bool teste)
{
    //Verificar se a casa de origem está dentro da dama
    if(coluna <= 7 && coluna >= 0 && linha < 8 && linha >= 0)
    {
        //Verificar se a casa de termino está dentro dos limites
        if(colunaf <= 7 && colunaf >= 0 && linhaf < 8 && linhaf >= 0)
        {
            //testa se a casa de destino for preta e se ja for ocupada pelo inimigo
            if(dama[linhaf][colunaf].casaPreta && dama[linhaf][colunaf].nJogador!=jog*-1)
            {
                //se a linha de destino está logo abaixo ou acima (dependendo do jogador) da linha de origeme se ta desocupada
                if(linhaf==linha+jog && (colunaf==coluna+1 || colunaf==coluna-1) && dama[linhaf][colunaf].nJogador==0)
                {
                    //movimento simples e se não for só um movimento teste
                    if(!teste)
                    {
                        dama[linha][coluna].nJogador=0;
                        dama[linhaf][colunaf].nJogador=jog;
                    }
                    return true;
                }
                else
                {
                    //comer pecas
                    if(estaLiberado(dama, linha, linhaf, coluna, colunaf, jog, 0, 0, 0, 0, pc, teste))
                    {
                        if(!teste)
                        {
                            dama[linha][coluna].nJogador=0;
                            dama[linhaf][colunaf].nJogador=jog;
                        }
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void intArtificial(posicao dama[][TAM], int& pc)
{
    //lista de casas por onde as peças do computador podem se mexer
    casa opcdo[12];
    //lista de casas vazias para onde o computador pode ir
    casa opcdd[32];
    //lista das casas de origem e destino possíveis
    opcoes caminho[48];
    //variável aleatória
    srand (time(NULL));
    int cont = 0, cont2 =  0, cont3 = 0, mc;
    //percorre todas as posições da dama
    for(int i=0;i<TAM;i++)
    {
        for(int j=0;j<TAM;j++)
        {
            if(dama[i][j].casaPreta)
            {
                if(dama[i][j].nJogador==1)
                {
                    //Se em qualquer uma das quatros posições, a peça do computador puder se mexer, então ela é adicionada na lista
                    if(i+1<=7&&j+1<=7&&dama[i+1][j+1].nJogador!=1)
                    {
                        opcdo[cont].x=i;
                        opcdo[cont].y=j;
                        cont++;
                    }
                    else if(i+1<=7&&j-1>=0&&dama[i+1][j-1].nJogador!=1)
                    {
                        opcdo[cont].x=i;
                        opcdo[cont].y=j;
                        cont++;
                    }
                    else if(i-1>=0&&j+1<=7&&dama[i-1][j+1].nJogador!=1)
                    {
                        opcdo[cont].x=i;
                        opcdo[cont].y=j;
                        cont++;
                    }
                    else if(i-1>=0&&j-1>=0&&dama[i-1][j-1].nJogador!=1)
                    {
                        opcdo[cont].x=i;
                        opcdo[cont].y=j;
                        cont++;
                    }
                }
                else if(dama[i][j].nJogador==0)
                {
                    //Se hover alguma das quatro posições por onde uma casa vazia poça receber uma peça do computador, então ela é adicionada na lista
                    if(i+1<=7&&j+1<=7&&dama[i+1][j+1].nJogador!=0)
                    {
                        opcdd[cont2].x=i;
                        opcdd[cont2].y=j;
                        cont2++;
                    }
                    else if(i+1<=7&&j-1>=0&&dama[i+1][j-1].nJogador!=0)
                    {
                        opcdd[cont2].x=i;
                        opcdd[cont2].y=j;
                        cont2++;
                    }
                    else if(i-1>=0&&j+1<=7&&dama[i-1][j+1].nJogador!=0)
                    {
                        opcdd[cont2].x=i;
                        opcdd[cont2].y=j;
                        cont2++;
                    }
                    else if(i-1>=0&&j-1>=0&&dama[i-1][j-1].nJogador!=0)
                    {
                        opcdd[cont2].x=i;
                        opcdd[cont2].y=j;
                        cont2++;
                    }
                }
            }
        }
    }
    //percorre o vetor de origens e de destinos, combinando cada possibilidade
    for(int i=0;i<cont;i++)
    {
        for(int j=0;j<cont2;j++)
        {
            //Se o caminho for possível, ele adicionará as posições de origem e destino no vetor 'caminhos'
            if(moverPeca(dama, opcdo[i].x, opcdd[j].x, opcdo[i].y, opcdd[j].y, 1, pc, true))
            {
                caminho[cont3].origem.x=opcdo[i].x;
                caminho[cont3].origem.y=opcdo[i].y;
                caminho[cont3].destino.x=opcdd[j].x;
                caminho[cont3].destino.y=opcdd[j].y;
                caminho[cont3].pecascom=pc;
                pc=0;
                //coloca o caminho que come mais peças em primeiro
                if(caminho[cont3].pecascom>caminho[0].pecascom)
                {
                    opcoes temp = caminho[0];
                    caminho[0]=caminho[cont3];
                    caminho[cont3]=temp;
                }
                cont3++;
            }
        }
    }
    /*Se as peças comidas do primeiro caminho for 0, quer dizer que nenhum caminho come peças,
      tendo em vista o codigo acima, então ele entra no bloco else, onde escolhe um caminho aleatório
      */
    if(caminho[0].pecascom!=0)
    {
        moverPeca(dama, caminho[0].origem.x, caminho[0].destino.x, caminho[0].origem.y, caminho[0].destino.y, 1, pc, false);
    }
    else
    {
        mc = rand() % cont3;
        moverPeca(dama, caminho[mc].origem.x, caminho[mc].destino.x, caminho[mc].origem.y, caminho[mc].destino.y, 1, pc, false);
    }
}

int main()
{
    posicao dama[TAM][TAM];
    int linha, linhaf, jogador=1, pecasj1=12, pecasj2=12, jvj=1, pc=0;
    char coluna, colunaf;
    bool jogadaFinalizada = false, saida = false;


    do //Inicio jogo
    {
        cout<<"Jogo de damas" << endl;
        cout << "Escolha o modo de jogo: (1- Jogador vs Computador, 2- Jogador vs Jogador) ";
        cin >> jvj;
        cout<<"Começando jogo:" << endl << endl;
        iniciarDama(dama);
        do//Jogar até vencer
        {
            do//Jogar até fazer um movimento certo
            {
                if(jogador==-1)
                {
                    if(jvj==2)
                    {
                        cout << "Vez do Jogador 2" << endl;
                    }
                    else
                    {
                        cout << "Vez do jogador" << endl;
                    }
                }
                else
                {
                    if(jvj==2)
                    {
                        cout << "Vez do Jogador 1" << endl;
                    }
                    else
                    {
                        cout << "Vez do Computador" << endl;
                    }
                }
                imprimirDama(dama);

                if((jvj==1&&jogador==-1)||(jvj==2))
                {

                    cout << "Digite a posição da peça que você deseja movimentar (Exemplo: c 2): ";
                    cin >> coluna >> linha;
                    cout << "Digite a posição do destino da peça (Exemplo: b 3): ";
                    cin >> colunaf >> linhaf;
                    if(moverPeca(dama, linha-1, linhaf-1, coluna-'a', colunaf-'a', jogador, pc, false))
                    {
                        if(jogador==-1)
                        {
                            pecasj1-=pc;
                        }
                        else
                        {
                            pecasj2-=pc;
                        }
                        pc=0;
                        jogadaFinalizada=true;
                        jogador*=-1;
                    }
                    else
                    {
                        cout << "Jogada inválida, jogue novamente" << endl;
                    }
                }
                else
                {
                    intArtificial(dama, pc);
                    pecasj2-=pc;
                    pc=0;
                    jogadaFinalizada=true;
                    jogador*=-1;
                }
            }while(!jogadaFinalizada);
        }while(!saida);
    }while(!saida);

}
