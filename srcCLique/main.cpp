
#include "global.h"
#include "geracaoGrafo.h"
#include "cliqueNormal.h"
#include "russianDoll.h"



/*
*V 210814, 0237
* @todo:
*  -colocar estrategias de podas na boneca russa.
*
*/
struct timeval now;
unsigned long long G[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16)));

unsigned long long G_BK[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16)));

unsigned long long R[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16))) ;
unsigned long long W[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16))) ;
unsigned long long V[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16))) ;
unsigned long long S[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16))) ;

unsigned long long c[qtd_palavrasULL]__attribute__ ((aligned(16)));

int main(){

	/*@todo:
	 * posix_memalign((void**)&a, 16,  N * sizeof(float)); e criar matrizes dinamicas na heap
	 * explicitas alinhadas. Lembrar que podemos ter certa perda de performance.
	 *
	 * */

	criarGrafoAleatorio();
	memcpy(G_BK,G,sizeof(G));
	{
		TIMER("\nNormal");
		cliqueNormal();
	}
	

	memcpy(G,G_BK,sizeof(G_BK));
	{
		TIMER("\n Russian DOll");
		MWNonRecursiveRussianDoll();
	}

	

	return 0;
}
