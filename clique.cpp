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



#define N 3

#define qtd_linhas 3
#define qtd_colunas 1
//se N > 64, teremos mais uma coluna

struct timeval now;


unsigned long long G[qtd_linhas*qtd_colunas] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));

unsigned long long R[qtd_linhas*qtd_colunas] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));

unsigned long long c[qtd_colunas]__attribute__ ((aligned (16*(sizeof(unsigned long long)))));


//void inicializarCeR(){
//
//	for(int i = 0; )
//}
//
#define R(i,j) R[qtd_colunas*i+j]
#define R_line(i)   R[qtd_colunas*i]

#define G(i,j) G[qtd_colunas*i+j]
#define G_line(i)   G[qtd_colunas*i]


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

	for(int i = 0; i<qtd_linhas;++i)
		for(int j = 0; j<qtd_colunas; ++j )
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
//	for(int coluna = 0; coluna<qtd_colunas; ++coluna){
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

	for(int k = 0; k<qtd_colunas; ++k){
		if(R(i,k)>0){
			*j = __builtin_ffsll(R(i,k)) -1;
			return k;
		}

	}
	//*j=0;
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
	for(int i = 0; i<qtd_linhas; ++i){
		cout<<"\nLinha "<< i<< " : ";
		cout<<"\n";
		for(int j =0; j<qtd_colunas;++j){
			cout<<"\n Coluna "<< j<< " : ";
			displayBitsll(G(i,j));
		}
	}
}


void teste(unsigned long long *R, int i){

	int colunaPrimeiroUm, j;


	do{

		colunaPrimeiroUm=isZero(R,i,&j);
		displayBitsll(R(i,colunaPrimeiroUm));
		//cout<<"\nColuna primeiro um: "<< colunaPrimeiroUm<<".\n"<<"Coluna j: "<<j<<". \n";
		//cout<<"Imprimindo linha antes do shift: ";
		//imprimirLinhall(R,i);
		R(i,colunaPrimeiroUm) = R(i,colunaPrimeiroUm) & ~((unsigned long long)1<<j); //retirando o um da posicao j
		//cout<<"Imprimindo linha apos o shift: ";
		displayBitsll(R(i,colunaPrimeiroUm));

	}
	while(R(i,colunaPrimeiroUm)>0);

}

void inicializarVetorCll(){

	for(int i = 0; i<qtd_colunas;++i)
		c[i] = 0LL;
}



void cliqueNormal(){

	register int i = 0;
	register int j;
	register int colunaPrimeiroUm, colunaIteracaoAnterior;
	int contador;


	for(j = 0; j<qtd_colunas;++j)
		R(i,j) = G(i,j);

	inicializarVetorCll();


	while(i>=0){


		colunaPrimeiroUm=isZero(R,i,&j); //j ja foi passado para a funcao



		while(colunaPrimeiroUm>=0){

			c[colunaPrimeiroUm] = c[colunaPrimeiroUm] | ((unsigned long long)1<<j);
			
			/*
			 * PROVISORIO!!!!!
			 * @todo:
			 * 	desenrolar este laco.
			 * */
			for(int col = 0; col<qtd_colunas;++col)
				R(i+1,col) = R(i,col) & G(j,col);

			///R(i+1,0) = R(i,0) & G(j,0);
			//R(i+1,1) = R(i,1) & G(j,1);
			//R(i+1,2) = R(i,2) & G(j,2);
			//R(i+1,3) = R(i,3) & G(j,3);


			R(i,colunaPrimeiroUm) = R(i,colunaPrimeiroUm) & ~((unsigned long long)1<<j); //retirando o um da posicao j


			i++; 
			colunaIteracaoAnterior = colunaPrimeiroUm;

			colunaPrimeiroUm=isZero(R,i,&j);
			
		}

		i--;

		/*
		 * PROBLEMA: este passo esta preenchendo C com zeros ou uns...
		 *
		 * Indice do ultimo bit 1 em c??
		 * */
		

		c[colunaIteracaoAnterior] = c[colunaIteracaoAnterior] & ~((unsigned long long)1<<j); //algum condicional aqui? estamos mantendo o j antigo...
	}
	cout<<"\n\nCLique:\n";
	displayBitsll(c[0]);
}



void criarGrafoControle(){

	for(int i = 0; i<qtd_linhas; ++i)
		for(int j = 0; j<qtd_colunas;++j)
			G(i,j) = (unsigned long long)0;

	//G_line(0)= G_line(0) | ((unsigned long long)1<<0);
	G_line(0)= G_line(0) | ((unsigned long long)1<<1);
	G_line(0)= G_line(0) |((unsigned long long)1<<2);

	//G_line(1)= G_line(1) | ((unsigned long long)1<<1);
	G_line(1)= G_line(1) | ((unsigned long long)1<<0);
	G_line(1)= G_line(1) | ((unsigned long long)1<<2);

	G_line(2)= G_line(2) | ((unsigned long long)1<<0);
	G_line(2)= G_line(2) | ((unsigned long long)1<<1);
	//G_line(2)= G_line(2) | ((unsigned long long)1<<2);
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

	cout<<"\n\nClique"<<endl;

	cliqueNormal();
	return 0;
}
