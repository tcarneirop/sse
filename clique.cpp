/*
 * mqenum.cpp
 *
 *  Created on: 14/04/2014
 *      Author: carneiro
 */





#include <iostream>

#include <immintrin.h>

#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <iomanip>
#include <stdlib.h>


using namespace std;


#define ULLONG 64
#define N 8

#define qtd_vertices 8
#define qtd_palavrasULL 1
//se N > 64, teremos mais uma coluna

struct timeval now;


unsigned long long G[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));

unsigned long long R[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));

unsigned long long c[qtd_palavrasULL]__attribute__ ((aligned (16*(sizeof(unsigned long long)))));



#define R(i,j) R[qtd_palavrasULL*i+j]
#define R_line(i)   R[qtd_palavrasULL*i]

#define G(i,j) G[qtd_palavrasULL*i+j]
#define G_line(i)   G[qtd_palavrasULL*i]


void displayBits(unsigned value){

	const int SHIFT = 8 * sizeof( unsigned ) - 1;
	const unsigned MASK = 1 << SHIFT ;



	//cout<< setw(7) << value << " = ";

	for (unsigned c = 1; c <= SHIFT +1; c++){
		cout << (value & MASK ? '1' : '0');
		value <<= 1;
		if (c % 8 == 0)
			cout << ' ';

	}

	cout << endl;

}

void displayBitsll(unsigned long long value){

	const unsigned long long  SHIFT = 8 * sizeof( unsigned long long ) - 1;
	const unsigned long long MASK = (unsigned long long)1 << SHIFT ;// joga do menos para o mais significativo

	//cout<< setw(7) << value << " = ";

	for (unsigned long long c = 1; c <= SHIFT +1; c++){
		cout << (value & MASK ? '1' : '0');
		value <<= 1;
		if (c % 8 == 0)
			cout << ' ';

	}

	cout << endl;

}


void preencherGrafoll(){

	const unsigned long long  SHIFT = 8 * sizeof( unsigned long long ) - 1;
	const unsigned long long MASK = (unsigned long long)1 << SHIFT ;// joga do menos para o mais significativo


	//G(0,0) = ( unsigned long long) 0;

	for(int i = 0; i<qtd_vertices;++i)
		for(int j = 0; j<qtd_palavrasULL; ++j )
			G(i,j) = MASK + (unsigned long long)8  + (unsigned long long)4096 + (unsigned long long)65536 + (unsigned long long)pow(2,25) + (unsigned long long)pow(2,34) + (unsigned long long)pow(2,42)+ (unsigned long long)pow(2,55);
	//G(i,j) = (unsigned long long)8 + MASK + 4096 + 65536 + 8589934592;
}



int isZero(unsigned long long *R, int i,int *j){

	for(int k = 0; k<qtd_palavrasULL; ++k){
		if(R(i,k)>0){
			*j = __builtin_ffsll(R(i,k)) -1;
			return k;
		}

	}

	return -1;


}

void imprimirLinhall(unsigned long long *R, int i){

	cout<<"\n\nImprimindo Linha "<< i<<" :\n";

	for(int j =0; j<N;++j){
		displayBitsll(R(i,j));

	}
}


void imprimirGrafoll(){

	cout<<"\n\nImprimindo Grafo "<<N<<" x "<<N<<" long long. \n";
	for(int i = 0; i<qtd_vertices; ++i){
		cout<<"\nLinha "<< i<< " : ";
		cout<<"\n";
		for(int j =0; j<qtd_palavrasULL;++j){
			cout<<"\n Coluna "<< j<< " : ";
			displayBitsll(G(i,j));
		}
	}
}

void imprimirGrafoll(unsigned long long *G){

	cout<<"\n\nImprimindo Grafo "<<N<<" x "<<N<<" long long. \n";
	for(int i = 0; i<qtd_vertices; ++i){
		cout<<"\nLinha "<< i<< " : ";
		cout<<"\n";
		for(int j =0; j<qtd_palavrasULL;++j){
			cout<<"\n Coluna "<< j<< " : ";
			displayBitsll(G(i,j));
		}
	}
}



void teste(unsigned long long *R){

	int palavraPrimeiroUm;
	int j;
	for(int i = 0; i<qtd_vertices;++i){

		do{
			palavraPrimeiroUm = isZero(R,i,&j);
			if(palavraPrimeiroUm>-1){
				cout<<"\nVertice "<< i<<". \nPrimeira palavra ULL contendo um: "<<palavraPrimeiroUm<<" . Posiçao: "<<j<<" .\n";
				R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) & ~(1ULL<<j);
			}
		}
		while(palavraPrimeiroUm> -1);
	}


}

void inicializarVetorCll(){

	for(int i = 0; i<qtd_palavrasULL;++i)
		c[i] = 0LL;
}




void cliqueNormal(){

	/*TODO:
	 * Lembrando que isso so' serve se o grafo tiver ate' 63 vertices, algum problema com os ands...
	 * 	-Corrigido o problema do c[]=c[] &~ do fim (OK);
	 * 	-Corrigido o problema do c[] =c[] | verticeCorrente,quando vc > 64;
	 *
	 * 	??E os ands?
	 *
	 * */


	register int i;
	register int j;
	int palavraPrimeiroUm;
	int pilha[qtd_vertices];
	int palavraUtilizada[qtd_vertices];
	int qtd_cliques = 0;
	int palavraRaiz;
	int verticeEmJ;
	int posicaoRaiz;


	for(int verticeCorrente = 0; verticeCorrente<qtd_vertices;++verticeCorrente){

		i=0;

		inicializarVetorCll();

		palavraRaiz  = (int)(verticeCorrente/ULLONG);
		posicaoRaiz = verticeCorrente % ULLONG;

		cout<<"\nVertice corrente: "<<verticeCorrente<<"\n";


		for(j = 0; j<qtd_palavrasULL;++j)
			R(i,j) = G(verticeCorrente,j);


		c[palavraRaiz] = c[palavraRaiz] | (1ULL<<posicaoRaiz);

		while(i>=0){

			palavraPrimeiroUm=isZero(R,i,&j);

			//???? isso tem que ser o tempo todo verificado? creio que nao...


			while(palavraPrimeiroUm>=0){


				//	cout<<"\n\nLoop externo\n";
				cout<<"\n i : "<<i<<"\nPalavra primeiro um: "<< palavraPrimeiroUm<<".\n"<<"Coluna j: "<<j<<". \n";


				palavraUtilizada[i] = palavraPrimeiroUm;

				c[palavraPrimeiroUm] = c[palavraPrimeiroUm] | (1ULL<<j);

				pilha[i] = j;


				//cout<<"\nC: \n";
//				displayBitsll(c[0]);
//				displayBitsll(c[1]);



				/*
				 * eis um erro... coluna j. Se a palavra > 0, j= palavra*64+j
				 * */
				verticeEmJ = palavraPrimeiroUm*64+j;
				/*
				 * Ex: se nao tivermos isso teremos problema na etapa R(i+1) = R(i) & G(j)
				 * ???: que outro erro temos aqui?
				 * Apos o for, mesmo sem realizar o andnot, R(i) torna-se nula.
				 * ?????
				 * */
				/*??????????????????????????????????????????????????????????????
				 * O acima da ok, o abaixo zera todos as posicoes do vetor R
				 * */



//				cout<<"\n\n\nR("<<i<<",0): \n";
//				displayBitsll(R(0,0));
//				cout<<"R("<<i<<",1): \n";
//				displayBitsll(R(0,1));
//
//				cout<<"G("<<verticeEmJ<<",0): \n";
//				displayBitsll(G(verticeEmJ,0));
//				cout<<"G("<<verticeEmJ<<",1): \n";
//				displayBitsll(G(verticeEmJ,1));
//
//				cout<<"R("<<i+1<<",0): \n";
//				displayBitsll(R(0,0)&G(verticeEmJ,0));
//				cout<<"R("<<i+1<<",1): \n";
//				displayBitsll(R(0,1)&G(verticeEmJ,1));


				for(int col = 0; col<qtd_palavrasULL;++col)
					R(i+1,col) = R(i,col) & G(verticeEmJ,col);


				//!!!!Tudo em R foi zerado! õ0


//				imprimirGrafoll(R);
//				exit(1);

				R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) & ~(1ULL<<j); //retirando o um da posicao j


//				cout<<"R("<<i<<"): \n";
//				displayBitsll(R(i,palavraPrimeiroUm));
//
//				cout<<"R("<<i+1<<",0): \n";
//				displayBitsll(R(i+1,0));
//				cout<<"R("<<i+1<<",1): \n";
//				displayBitsll(R(i+1,1));
//

				i++;
				//colunaIteracaoAnterior = palavraPrimeiroUm;
				palavraPrimeiroUm=isZero(R,i,&j);

			}

			i--;
			if(i>=0){
				++qtd_cliques;
				cout<<"\nClique "<<qtd_cliques<<" : \n";
				displayBitsll(c[0]);
				displayBitsll(c[1]);
				c[palavraUtilizada[i]] = c[palavraUtilizada[i]] & ~(1ULL<<pilha[i]);} //algum condicional aqui? estamos mantendo o j antigo...



		}
		//cout<<"\nAo fim: \n";
		//displayBitsll(c[0]);
		c[palavraRaiz] = c[palavraRaiz] & ~(1ULL<<verticeCorrente); //pois todo espaco de solucoes cuja origem eh ''vertice'' foi verificado



		/*@TODO: OK, verificar...
		 *
		 *Creio que também exista um erro aqui. se o vertice for 64, nao iremos mandar andar 64 posicoes. erro...
		 *
		 **/

		for(int k = 0; k<qtd_vertices;++k)
			G(k,palavraRaiz) = G(k,palavraRaiz) & ~(1ULL<<posicaoRaiz);


	}
	cout<<"\n\nQtd_cliques: "<<qtd_cliques<<"\n";
}



void criarGrafoControle(){

	// n = 8, cliques = 19
	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			G(i,j) = (unsigned long long)0;


	G_line(0)= G_line(0) | (1ULL<<1);
	G_line(0)= G_line(0) | (1ULL<<2);
	G_line(0)= G_line(0) | (1ULL<<3);



	G_line(1)= G_line(1) | (1ULL);
	G_line(1)= G_line(1) | (1ULL<<2);
	G_line(1)= G_line(1) | (1ULL<<3);

	G_line(2)= G_line(2) | (1ULL);
	G_line(2)= G_line(2) | (1ULL<<1);
	G_line(2)= G_line(2) | (1ULL<<3);

	G_line(3)= G_line(3) | (1ULL);
	G_line(3)= G_line(3) | (1ULL<<2);
	G_line(3)= G_line(3) | (1ULL<<4);
	G_line(3)= G_line(3) | (1ULL<<5);

	G_line(4)= G_line(4) | (1ULL<<3);
	G_line(4)= G_line(4) | (1ULL<<5);

	G_line(5)= G_line(5) | (1ULL<<3);
	G_line(5)= G_line(5) | (1ULL<<4);
	G_line(5)= G_line(5) | (1ULL<<6);
	G_line(5)= G_line(5) | (1ULL<<7);

	G_line(6)= G_line(6) | (1ULL<<5);
	G_line(6)= G_line(6) | (1ULL<<7);

	G_line(7)= G_line(7) | (1ULL<<5);
	G_line(7)= G_line(7) | (1ULL<<6);



}


void criarGrafoControleDois(){

	// n = 4, cliques = 11

	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			G(i,j) = (unsigned long long)0;


	G_line(0)= G_line(0) | (1ULL<<1);
	G_line(0)= G_line(0) | (1ULL<<2);
	G_line(0)= G_line(0) | (1ULL<<3);


	G_line(1)= G_line(1) | (1ULL);
	G_line(1)= G_line(1) | (1ULL<<2);
	G_line(1)= G_line(1) | (1ULL<<3);

	G_line(2)= G_line(2) | (1ULL);
	G_line(2)= G_line(2) | (1ULL<<1);
	G_line(2)= G_line(2) | (1ULL<<3);

	G_line(3)= G_line(3) | (1ULL);
	G_line(3)= G_line(3) | (1ULL<<1);
	G_line(3)= G_line(3) | (1ULL<<2);

}


void criarGrafoControleTres(){

	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			G(i,j) = (unsigned long long)0;


	G(63,1)= G(63,1) | (1ULL); //63-64
	G(63,1)= G(63,1) | (1ULL<<1); //63-65

	G(64,0)= G(64,0) | (1ULL<<63);
	G(64,1)= G(64,1) | (1ULL<<1); //64-65

	G(65,0)= G(65,0) | (1ULL<<63);
	G(65,1)= G(65,1) | (1ULL); //64-65


}


int main(){

	//preencherGrafoll();
	//criarGrafoControleTres();
	//criarGrafoControleDois();

	cout<<"\n\nQuantidade de vertices: "<<qtd_vertices<<" . Quantidade de palavras ULL: "<<qtd_palavrasULL<<" .\n";
	criarGrafoControle();
	imprimirGrafoll();

	//	cout<<"\nQuantidade de 1(uns) na linha 0 de G: "<< qtdZerosLinhall(0,G,&primeira)<<". \n\t A primeira coluna com uns é a : "<< primeira<<"\n";
	//	cout<<"Quantidade de 1(uns) na linha 1 de G: "<< qtdZerosLinhall(1,G,&primeira)<<". \n\t A primeira coluna com uns é a : "<< primeira<<"\n";
	//
	//	teste(&primeira);
	//	cout<<"\n\nTeste: "<<primeira<<"\n\n";

	//cout<<"\n\nClique"<<endl;

	//teste(G);
	cliqueNormal();

	return 0;
}
