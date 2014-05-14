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
#define N 25

#define qtd_vertices 25

#define qtd_palavrasULL 2
//se N > 64, teremos mais uma coluna

struct timeval now;


unsigned long long G[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16)));

unsigned long long R[qtd_vertices*qtd_palavrasULL]__attribute__ ((aligned(16))) ;

unsigned long long c[qtd_palavrasULL]__attribute__ ((aligned(16)));


#define R(i,j) R[qtd_palavrasULL*(i)+(j)]
#define R_line(i)   R[qtd_palavrasULL*(i)]

#define G(i,j) G[qtd_palavrasULL*(i)+(j)]
#define G_line(i)   G[qtd_palavrasULL*(i)]


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

void displayBitsCliquell(unsigned long long *clique){

	unsigned long long  value;
	const unsigned long long  SHIFT = 8 * sizeof( unsigned long long ) - 1;
	const unsigned long long MASK = (unsigned long long)1 << SHIFT ;// joga do menos para o mais significativo

	//cout<< setw(7) << value << " = ";

	for(int k = 0; k<qtd_palavrasULL;++k){
		value = clique[k];
		for (unsigned long long c = 1; c <= SHIFT +1; c++){
			cout << (value & MASK ? '1' : '0');
			value <<= 1;
			if (c % 8 == 0)
				cout << ' ';

		}
		cout<< endl;
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

int isZero(unsigned long long *vertice, int *j){


	for(int k = 0; k<qtd_palavrasULL; ++k){
		if(vertice[k]>0){
			*j = __builtin_ffsll(vertice[k]) -1;
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
				R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) &  ~(1ULL<<j);
			}
		}
		while(palavraPrimeiroUm> -1);
	}


}


void verticesDaClique(unsigned long long *vertices){

	int palavraPrimeiroUm;
	int j;


	do{
		palavraPrimeiroUm = isZero(vertices,&j);
		if(palavraPrimeiroUm>-1){

			cout<<palavraPrimeiroUm*ULLONG+j;
			cout<<" ";
			vertices[palavraPrimeiroUm] = vertices[palavraPrimeiroUm] &  ~(1ULL<<j);
		}
	}
	while(palavraPrimeiroUm> -1);



}

void inicializarVetorCll(){

	for(int i = 0; i<qtd_palavrasULL;++i)
		c[i] = 0LL;
}




void cliqueNormal(){

	cout<<"\nClique Normal\n";

	/*
	 * Aparentemente ok
	 * @todo:
	 * 	-tirar a modificacao no grafo. Nao entendi como fazer.
	 * */
	register int i;
	register int j;
	int palavraPrimeiroUm;
	int pilha[qtd_vertices];
	int palavraUtilizada[qtd_vertices];
	unsigned long long  qtd_cliques = 0;
	int palavraRaiz;
	int verticeEmJ;
	int posicaoRaiz;
	int tamanhoCliqueCorrente, maiorClique = -1;


	unsigned long long vetorMaiorClique[qtd_palavrasULL];




	inicializarVetorCll();


	for(int verticeCorrente = 0; verticeCorrente<qtd_vertices;++verticeCorrente){

		i=0;

		palavraRaiz  = (int)(verticeCorrente/ULLONG);
		posicaoRaiz = verticeCorrente % ULLONG;

		//cout<<"\nVertice corrente: "<<verticeCorrente<<"\n";


		for(j = 0; j<qtd_palavrasULL;++j)
			R(i,j) = G(verticeCorrente,j);

		c[palavraRaiz] = c[palavraRaiz] | (1ULL<<posicaoRaiz);

		tamanhoCliqueCorrente = 1;

		while(i>=0){

			palavraPrimeiroUm=isZero(R,i,&j);


			while(palavraPrimeiroUm>=0){


				palavraUtilizada[i] = palavraPrimeiroUm;

				c[palavraPrimeiroUm] = c[palavraPrimeiroUm] | (1ULL<<j);
				tamanhoCliqueCorrente++;

				pilha[i] = j;


				R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) & ~(1ULL<<j); //retirando o um da posicao j


				verticeEmJ = palavraPrimeiroUm*ULLONG+j;



				for(int col = 0; col<qtd_palavrasULL;++col){

					R((i+1),col) = R(i,col) & G(verticeEmJ,col);
				}


				i++;

				palavraPrimeiroUm=isZero(R,i,&j);

			}

			if(tamanhoCliqueCorrente>maiorClique){

				maiorClique = tamanhoCliqueCorrente;
				memcpy(vetorMaiorClique,c,sizeof(c));

			}

			i--;

			if(i>=0){

				//				cout<<"\nClique "<<qtd_cliques<<" : \n";
				//				displayBitsll(c[0]);
				//				displayBitsll(c[1]);
				//				displayBitsll(c[2]);

				++qtd_cliques;
				//cout<<"\nClique: \n";
				//displayBitsCliquell(c);
				//cout<<"\n";
				c[palavraUtilizada[i]] = c[palavraUtilizada[i]] & ~(1ULL<<pilha[i]);
				tamanhoCliqueCorrente--;

			}
		}

		c[palavraRaiz] = c[palavraRaiz] & ~(1ULL<<posicaoRaiz);


		/*@TODO: OK, verificar...
		 *
		 *Nao entendi como retirar a etapa abaixo.
		 *
		 **/

		for(int k = 0; k<qtd_vertices;++k)
			G(k,palavraRaiz) = G(k,palavraRaiz) & ~(1ULL<<posicaoRaiz);


	}

	cout<<"\n\nQtd_cliques: "<<qtd_cliques<<endl<<"Tamanho maior clique: "<<maiorClique<<endl;
	verticesDaClique(vetorMaiorClique);


}


void cliqueSSE(){


	cout<<"\nCLIQUE SSE\n";
	/*
	 * Aparentemente ok
	 * @todo:
	 * 	-tirar a modificacao no grafo. Nao entendi como fazer.
	 * */
	register int i;
	register int j;
	int palavraPrimeiroUm;
	int pilha[qtd_vertices];
	int palavraUtilizada[qtd_vertices];
	unsigned long long  qtd_cliques = 0;
	int palavraRaiz;
	int verticeEmJ;
	int posicaoRaiz;
	int tamanhoCliqueCorrente, maiorClique = -1;

	__m128i* R_SSE;
	__m128i* grafoSSE;
	__m128i* R_proximoNivel;

	unsigned long long vetorMaiorClique[qtd_palavrasULL];


	inicializarVetorCll();


	for(int verticeCorrente = 0; verticeCorrente<qtd_vertices;++verticeCorrente){

		i=0;

		palavraRaiz  = (int)(verticeCorrente/ULLONG);
		posicaoRaiz = verticeCorrente % ULLONG;

		//cout<<"\nVertice corrente: "<<verticeCorrente<<"\n";


		R_SSE = (__m128i*)&R_line(i);
		grafoSSE = (__m128i*)&G_line(verticeCorrente);


		for(int col = 0; col<(qtd_palavrasULL/2); col++){
			_mm_store_si128(&R_SSE[col],grafoSSE[col]);
			//R(i,j) = G(verticeCorrente,j);
			//R_SSE[col] = grafoSSE[col];
		}

		c[palavraRaiz] = c[palavraRaiz] | (1ULL<<posicaoRaiz);

		tamanhoCliqueCorrente = 1;

		while(i>=0){

			palavraPrimeiroUm=isZero(R,i,&j);


			while(palavraPrimeiroUm>=0){


				palavraUtilizada[i] = palavraPrimeiroUm;

				c[palavraPrimeiroUm] = c[palavraPrimeiroUm] | (1ULL<<j);
				tamanhoCliqueCorrente++;

				pilha[i] = j;


				R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) & ~(1ULL<<j); //retirando o um da posicao j


				verticeEmJ = palavraPrimeiroUm*ULLONG+j;


				R_SSE = (__m128i*)&R_line(i);
				grafoSSE = (__m128i*)&G_line(verticeEmJ);
				R_proximoNivel = (__m128i*)&R_line((i+1));


				for(int col = 0; col<(qtd_palavrasULL/2);++col){

					//_mm_store_si128(&R_proximoNivel[col],_mm_and_si128(grafoSSE[col],R_SSE[col]));

					R_proximoNivel[col] = _mm_and_si128(grafoSSE[col],R_SSE[col]);
					//_mm_store_si128(&R_proximoNivel[col],_mm_and_si128(grafoSSE[col],R_SSE[col]));
					//R((i+1),col) = R(i,col) & G(verticeEmJ,col);


				}



//
//				for(int col = 0; col<qtd_palavrasULL;++col){
//
//
//					R((i+1),col) = R(i,col) & G(verticeEmJ,col);
//
//				}


				i++;

				palavraPrimeiroUm=isZero(R,i,&j);

			}

			if(tamanhoCliqueCorrente>maiorClique){

				maiorClique = tamanhoCliqueCorrente;
				memcpy(vetorMaiorClique,c,sizeof(c));

			}

			i--;

			if(i>=0){

				//				cout<<"\nClique "<<qtd_cliques<<" : \n";
				//				displayBitsll(c[0]);
				//				displayBitsll(c[1]);
				//				displayBitsll(c[2]);

				++qtd_cliques;
				//cout<<"\nClique: \n";
				//displayBitsCliquell(c);
				//cout<<"\n";
				c[palavraUtilizada[i]] = c[palavraUtilizada[i]] & ~(1ULL<<pilha[i]);
				tamanhoCliqueCorrente--;

			}
		}

		c[palavraRaiz] = c[palavraRaiz] & ~(1ULL<<posicaoRaiz);


		/*@TODO: OK, verificar...
		 *
		 *Nao entendi como retirar a etapa abaixo.
		 *
		 **/

		for(int k = 0; k<qtd_vertices;++k)
			G(k,palavraRaiz) = G(k,palavraRaiz) & ~(1ULL<<posicaoRaiz);


	}

	cout<<"\n\nQtd_cliques: "<<qtd_cliques<<endl<<"Tamanho maior clique: "<<maiorClique<<endl;
	verticesDaClique(vetorMaiorClique);


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

	G(63,1)= G(63,1) | (1ULL); //63-64
	G(63,1)= G(63,1) | (1ULL<<1); //63-65

	G(64,0)= G(64,0) | (1ULL<<63);
	G(64,1)= G(64,1) | (1ULL<<1); //64-65

	G(65,0)= G(65,0) | (1ULL<<63);
	G(65,1)= G(65,1) | (1ULL); //64-65




}


void criarGrafoControleQuatro(){

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

void criarGrafoControleCinco(){

	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			G(i,j) = (unsigned long long)0;


	G_line(0)= G_line(0) | (1ULL<<1);
	G_line(0)= G_line(0) | (1ULL<<2);
	G_line(0)= G_line(0) | (1ULL<<3);

	G(0,2) = G(0,2) | (1ULL); //0-128
	G(0,2) = G(0,2) | (1ULL<<1); //0-129
	G(0,2) = G(0,2) | (1ULL<<2);   //0-130
	G(0,2) = G(0,2) | (1ULL<<3); //0 - 131



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

	G(63,1)= G(63,1) | (1ULL); //63-64
	G(63,1)= G(63,1) | (1ULL<<1); //63-65

	G(64,0)= G(64,0) | (1ULL<<63);
	G(64,1)= G(64,1) | (1ULL<<1); //64-65

	G(65,0)= G(65,0) | (1ULL<<63);
	G(65,1)= G(65,1) | (1ULL); //64-65

	G(128,0) = G(128,0) | (1ULL); //128-0
	G(128,2) = G(128,2) | (1ULL<<1); //128-129
	G(128,2) = G(128,2) | (1ULL<<2);   //128-130
	G(128,2) = G(128,2) | (1ULL<<3); //128 - 131

	G(129,0) = G(129,0) | (1ULL); //129-128
	G(129,2) = G(129,2) | (1ULL); //129-128
	G(129,2) = G(129,2) | (1ULL<<2);   //128-130
	G(129,2) = G(129,2) | (1ULL<<3); //128 - 131

	G(130,0) = G(130,0) | (1ULL); //130-128
	G(130,2) = G(130,2) | (1ULL); //130-128
	G(130,2) = G(130,2) | (1ULL<<1);   //130-129
	G(130,2) = G(130,2) | (1ULL<<3); //128 - 131

	G(131,0) = G(131,0) | (1ULL); //130-128
	G(131,2) = G(131,2) | (1ULL); //130-128
	G(131,2) = G(131,2) | (1ULL<<1);   //130-129
	G(131,2) = G(131,2) | (1ULL<<2); //128 - 131


}



void criarGrafoControleComepleto(){

	int palavraVerticeJ, posicaoVerticeJ;
	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			G(i,j) = (unsigned long long)0;


	for(int i = 0; i<qtd_vertices;++i){
		for(int j = 0; j<qtd_vertices;++j){

			if(i==j)
				continue;
			else{
				palavraVerticeJ  = (int)(j/ULLONG);
				posicaoVerticeJ = j % ULLONG;

				G(i,palavraVerticeJ) = G(i,palavraVerticeJ) | (1ULL << posicaoVerticeJ);
			}
		}
	}


}


int main(){

	//preencherGrafoll();
	//criarGrafoControle();
	//criarGrafoControleQuatro(); //66-4
	//criarGrafoControleDois();

	//criarGrafoControleCinco(); //133-3ull-49cl-5maior

	criarGrafoControleComepleto();
	cout<<"\n\nQuantidade de vertices: "<<qtd_vertices<<" . Quantidade de palavras ULL: "<<qtd_palavrasULL<<" .\n";


	//imprimirGrafoll();

	//cliqueNormal();
	cliqueSSE();


	return 0;
}
