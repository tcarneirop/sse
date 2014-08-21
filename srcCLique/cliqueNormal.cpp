#include "cliqueNormal.h"




void cliqueNormal(){

	cout<<"\n\n<<<<Clique Normal>>>>";

	/*
	 * Aparentemente ok
	 * @todo:
	 * 	-tirar a modificacao no grafo.
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

		//c[palavraRaiz] = c[palavraRaiz] | (1ULL<<posicaoRaiz);
		c[palavraRaiz] |= (1ULL<<posicaoRaiz);

		tamanhoCliqueCorrente = 1;

		while(i>=0){

			palavraPrimeiroUm=isZero(R,i,&j);


			while(palavraPrimeiroUm>=0){


				palavraUtilizada[i] = palavraPrimeiroUm;

				//c[palavraPrimeiroUm] = c[palavraPrimeiroUm] | (1ULL<<j);
				c[palavraPrimeiroUm] |= (1ULL<<j);

				tamanhoCliqueCorrente++;

				pilha[i] = j;


				//R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) & ~(1ULL<<j); //retirando o um da posicao j
				R(i,palavraPrimeiroUm) &=  ~(1ULL<<j);

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



				++qtd_cliques;
				c[palavraUtilizada[i]] &=  ~(1ULL<<pilha[i]);
				tamanhoCliqueCorrente--;

			}
		}

		c[palavraRaiz] &=  ~(1ULL<<posicaoRaiz);


		/*@TODO: OK, verificar...
		 *
		 retirar a etapa abaixo.
		 *
		 **/

		for(int k = 0; k<qtd_vertices;++k)
			G(k,palavraRaiz) &=  ~(1ULL<<posicaoRaiz);


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



void DFSBnBSSE(){

	cout<<"\nDFS-BnB SSE\n";

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
	//int quantidadeDeUns;

	__m128i* R_SSE;
	__m128i* grafoSSE;
	__m128i* R_proximoNivel;

	unsigned long long vetorMaiorClique[qtd_palavrasULL];




	inicializarVetorCll();


	for(int verticeCorrente = 0; verticeCorrente<qtd_vertices;++verticeCorrente){


		i=0;

		palavraRaiz  = (int)(verticeCorrente/ULLONG);
		posicaoRaiz = verticeCorrente % ULLONG;



		/*
		 * Poda inicial
		 * */
		if((qtdUns(G,verticeCorrente)+1) < maiorClique){ //poda ao escolher uma nova raiz

			//	cout<<endl<<verticeCorrente<<" Podado, apenas "<< qtdUns(G,verticeCorrente)<<" uns em seu R\n";

			for(int k = 0; k<qtd_vertices;++k)
				G(k,palavraRaiz) = G(k,palavraRaiz) & ~(1ULL<<posicaoRaiz);
			continue;
		}


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


				R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) & ~(1ULL<<j);


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

				if(qtdUns(R,i+1)>(maiorClique-tamanhoCliqueCorrente)){//tcc = (i+1). tmc = L --> L-i+1
					i++;
					palavraPrimeiroUm=isZero(R,i,&j);
				}//nao podado
				else{
					c[palavraPrimeiroUm] = c[palavraPrimeiroUm] & ~(1ULL<<j);
					tamanhoCliqueCorrente--;
					palavraPrimeiroUm=isZero(R,i,&j);
					//c[palavraPrimeiroUm] = c[palavraPrimeiroUm] & ~(1ULL<<j);

				}//podado


			}//end while, clique maximal feito.

			if(tamanhoCliqueCorrente>maiorClique){

				maiorClique = tamanhoCliqueCorrente;
				memcpy(vetorMaiorClique,c,sizeof(c));

			}

			i--;

			if(i>=0){

				++qtd_cliques;;
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


}//end of dfsbnb

void DFSBnBNormal(){

	cout<<"\nDFS-BnB  normal\n";

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
	//int quantidadeDeUns;

	unsigned long long vetorMaiorClique[qtd_palavrasULL];




	inicializarVetorCll();


	for(int verticeCorrente = 0; verticeCorrente<qtd_vertices;++verticeCorrente){

		/*
		 * Antes de copiar, farei o seguinte:
		 * verificarei, para cada palavra, a quantidade de zeros do vertice em questao.
		 *
		 * * */
		i=0;

		palavraRaiz  = (int)(verticeCorrente/ULLONG);
		posicaoRaiz = verticeCorrente % ULLONG;


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


				R(i,palavraPrimeiroUm) = R(i,palavraPrimeiroUm) & ~(1ULL<<j);


				verticeEmJ = palavraPrimeiroUm*ULLONG+j;



				for(int col = 0; col<qtd_palavrasULL;++col){

					R((i+1),col) = R(i,col) & G(verticeEmJ,col);
				}

				if(qtdUns(R,i+1)>(maiorClique-tamanhoCliqueCorrente)){//tcc = (i+1). tmc = L --> L-i+1
					i++;
					palavraPrimeiroUm=isZero(R,i,&j);
				}//nao podado
				else{
					c[palavraPrimeiroUm] = c[palavraPrimeiroUm] & ~(1ULL<<j);
					tamanhoCliqueCorrente--;
					palavraPrimeiroUm=isZero(R,i,&j);
					//c[palavraPrimeiroUm] = c[palavraPrimeiroUm] & ~(1ULL<<j);

				}//podado


			}//end while, clique maximal feito.

			if(tamanhoCliqueCorrente>maiorClique){

				maiorClique = tamanhoCliqueCorrente;
				memcpy(vetorMaiorClique,c,sizeof(c));

			}

			i--;

			if(i>=0){
				++qtd_cliques;

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



