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



	cout<< setw(7) << value << " = ";

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

	cout<< setw(7) << value << " = ";

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


//inline int qtdZerosLinhall(int linha, unsigned long long *GRAFO, int *primeiraColuna){
//
//	int qtd = 0;
//	int retorno;
//
//	bool primeiraVez = true;
//
//	for(int coluna = 0; coluna<qtd_palavrasULL; ++coluna){
//		retorno = __builtin_popcountll(GRAFO[linha*N+coluna]);
//		if(primeiraVez == true && (retorno > 0)){
//			cout<<"\n\tcoluna "<< coluna;
//			cout<<"\nRerotno "<<retorno<<"\n";
//			*primeiraColuna = coluna;
//			primeiraVez = false;
//			cout<<"\n\tPrimeira coluna com 1(uns): "<<*primeiraColuna<<" \n";
//
//		}
//		qtd += retorno;
//	}
//	return qtd;
//
//}


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


void teste(unsigned long long *R, int i){

	int palavraPrimeiroUm, j;


	do{

		palavraPrimeiroUm=isZero(R,i,&j);
		displayBitsll(R(i,palavraPrimeiroUm));
		//cout<<"\nColuna primeiro um: "<< palavraPrimeiroUm<<".\n"<<"Coluna j: "<<j<<". \n";
		//cout<<"Imprimindo linha antes do shift: ";
		//imprimirLinhall(R,i);
		R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) & ~((unsigned long long)1<<j); //retirando o um da posicao j
		//cout<<"Imprimindo linha apos o shift: ";
		displayBitsll(R(i,palavraPrimeiroUm));

	}
	while(R(i,palavraPrimeiroUm)>0);

}

void inicializarVetorCll(){

	for(int i = 0; i<qtd_palavrasULL;++i)
		c[i] = 0LL;
}



void cliqueNormal(){

	/*@TODO ok
	 * -setar a raiz do espaco de solucoes na clique. Nao fazia sentido nao ter isso;
	 * -substituor qtd_palavrasULL por qtd_palavrasULL
	 * -substituir palavraPrimeiroUm por palavraPrimeiroUm;
	 * -mostrar a clique e o size da clique ao sair do loop mais interno;
	 * -Obs: ao sair do laco mais interno eu obtenho uma clique. Faco c[]=c[]&~(1<<pilha[i]);--i.
	 * -colocar um for para realizar a busca para todo no'.
	 *
	 * */


	register int i;
	register int j;
	int palavraPrimeiroUm;
	int pilha[qtd_vertices];
	int palavraUtilizada[qtd_vertices];
	int verticeCorrente = 0;
	int qtd_cliques = 0;


	for(int verticeCorrente = 0; verticeCorrente<qtd_vertices;++verticeCorrente){


		cout<<"\nVertice corrente: "<<verticeCorrente<<"\n";
		i=0;
		for(j = 0; j<qtd_palavrasULL;++j)
			R(i,j) = G(verticeCorrente,j);



		inicializarVetorCll();



		while(i>=0){

			palavraPrimeiroUm=isZero(R,i,&j);

			c[palavraPrimeiroUm] = c[palavraPrimeiroUm] | (1ULL<<verticeCorrente); //???? isso tem que ser o tempo todo verificado? creio que nao...

			//	cout<<"\n\nLoop externo\n";
			//	cout<<"\n i : "<<i<<"\nColuna primeiro um: "<< palavraPrimeiroUm<<".\n"<<"Coluna j: "<<j<<". \n";
			//	cout<<"R("<<i<<"): \n";
			//	displayBitsll(R(i,palavraPrimeiroUm));


			while(palavraPrimeiroUm>=0){

				palavraUtilizada[i] = palavraPrimeiroUm;

				c[palavraPrimeiroUm] = c[palavraPrimeiroUm] | (1ULL<<j);
				pilha[i] = j;

				//cout<<"\nC: \n";
				//displayBitsll(c[0]);


				for(int col = 0; col<qtd_palavrasULL;++col)
					R(i+1,col) = R(i,col) & G(j,col);

				///R(i+1,0) = R(i,0) & G(j,0);
				//R(i+1,1) = R(i,1) & G(j,1);
				//R(i+1,2) = R(i,2) & G(j,2);
				//R(i+1,3) = R(i,3) & G(j,3);


				R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) & ~(1ULL<<j); //retirando o um da posicao j


				//cout<<"R("<<i<<"): \n";
				//displayBitsll(R(i,palavraPrimeiroUm));
				//cout<<"R("<<i+1<<"): \n";
				//displayBitsll(R(i+1,palavraPrimeiroUm));

				i++;
				//colunaIteracaoAnterior = palavraPrimeiroUm;
				palavraPrimeiroUm=isZero(R,i,&j);

			}

			i--;
			if(i>=0){
				++qtd_cliques;
				cout<<"\nClique "<<qtd_cliques<<" : \n";
				displayBitsll(c[0]);
				c[palavraUtilizada[i]] = c[palavraUtilizada[i]] & ~(1ULL<<pilha[i]);} //algum condicional aqui? estamos mantendo o j antigo...



		}
		//cout<<"\nAo fim: \n";
		//displayBitsll(c[0]);
		c[0] = c[0] & ~(1ULL<<verticeCorrente); //pois todo espaco de solucoes cuja origem eh ''vertice'' foi verificado




		for(int k = 0; k<qtd_vertices;++k)
			G(k,verticeCorrente) = G(k,verticeCorrente) & ~(1ULL<<verticeCorrente);


	}
	cout<<"\n\nQtd_cliques: "<<qtd_cliques<<"\n";
}

/*
 * Lembrando que isso so' serve se o grafo tiver ate' 63 vertices
 * */

void criarGrafoControle(){

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

	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			G(i,j) = (unsigned long long)0;


	G_line(0)= G_line(0) | (1ULL<<1);
	G_line(0)= G_line(0) | (1ULL<<3);


	G_line(1)= G_line(1) | (1ULL);
	G_line(1)= G_line(1) | (1ULL<<3);

	G_line(2)= G_line(2) | (1ULL);
	G_line(2)= G_line(2) | (1ULL<<3);

	G_line(3)= G_line(3) | (1ULL);
	G_line(3)= G_line(3) | (1ULL<<1);
	G_line(3)= G_line(3) | (1ULL<<2);

}

int main(){

	cout<<"\n"<<sizeof(int)<<"\n"<<sizeof(unsigned long long)<<"\n";

	//preencherGrafoll();
	criarGrafoControle();
	imprimirGrafoll();

	//	cout<<"\nQuantidade de 1(uns) na linha 0 de G: "<< qtdZerosLinhall(0,G,&primeira)<<". \n\t A primeira coluna com uns é a : "<< primeira<<"\n";
	//	cout<<"Quantidade de 1(uns) na linha 1 de G: "<< qtdZerosLinhall(1,G,&primeira)<<". \n\t A primeira coluna com uns é a : "<< primeira<<"\n";
	//
	//	teste(&primeira);
	//	cout<<"\n\nTeste: "<<primeira<<"\n\n";

	//cout<<"\n\nClique"<<endl;

	cliqueNormal();
	return 0;
}
