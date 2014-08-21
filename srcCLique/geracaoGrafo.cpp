#include "geracaoGrafo.h"





void criarGrafoControle(){

	// n = 8, cliques = 19
	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			G(i,j) = (unsigned long long)0;

	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			S(i,j) = (unsigned long long)0;

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

	//	G(64,0)= G(64,0) | (1ULL<<63);
	//	G(64,1)= G(64,1) | (1ULL<<1); //64-65
	//
	//	G(65,0)= G(65,0) | (1ULL<<63);
	//	G(65,1)= G(65,1) | (1ULL); //64-65




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

	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			S(i,j) = (unsigned long long)0;

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

void criarGrafoAleatorio(){


	int palavraVerticeJ, posicaoVerticeJ, moeda,palavraVerticeI, posicaoVerticeI;

	srand (time(NULL));

	/*@todo:mudar para memset
	 * */
	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			G(i,j) = (unsigned long long)0;

	for(int i = 0; i<qtd_vertices; ++i)
		for(int j = 0; j<qtd_palavrasULL;++j)
			S(i,j) = (unsigned long long)0;

	for(int i = 0; i<qtd_vertices;++i){
		for(int j = 0; j<qtd_vertices;++j){

			moeda = rand() % 100;

			if(i==j || (moeda < 50))
				continue;
			else{
				palavraVerticeJ  = (int)(j/ULLONG);
				posicaoVerticeJ = j % ULLONG;
				palavraVerticeI  = (int)(i/ULLONG);
				posicaoVerticeI = i % ULLONG;

				G(i,palavraVerticeJ) |= (1ULL << posicaoVerticeJ);
				G(j,palavraVerticeI) |= (1ULL << posicaoVerticeI);
			}
		}
	}


}
