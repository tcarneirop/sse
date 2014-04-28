
#include <iostream>
//#include <emmintrin.h>
#include <immintrin.h>

#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
//#include <xmmintrin.h>


//#include <avxintrin.h>

using namespace std;




struct timeval now;


//inserindo uma modificacao


#define TIMER(name) Timer timer__(name);
#define N 1024
#define SIZE 8192

int main() {

	cout<<"\n****************************************************\n\tRealizando "<< N <<" testes em "<< SIZE <<" elementos.\n****************************************************\n";
	int rc;

	unsigned int inicio;
	unsigned int fim;
	unsigned int tempo;
	float tempoMedia;
	register int i, j;



	unsigned long long a[SIZE], b[SIZE], c[SIZE];

	for(int i =0; i<SIZE;++i){
		a[i]=b[i]=i;	
	}

	rc = gettimeofday(&now, NULL);
	inicio= now.tv_usec;
	for(j=0;j<N;++j)
		for(i = 0; i<SIZE; i=i+16){

			c[0 + i] = a[0 + i] & b[0 + i];
			c[1 + i] = a[1 + i] & b[1 + i];
			c[2 + i] = a[2 + i] & b[2 + i];
			c[3 + i] = a[3 + i] & b[3 + i];
			c[4 + i] = a[4 + i] & b[4 + i];
			c[5 + i] = a[5 + i] & b[5 + i];
			c[6 + i] = a[6 + i] & b[6 + i];
			c[7 + i] = a[7 + i] & b[7 + i];
			c[8 + i] = a[8 + i] & b[8 + i];
			c[9 + i] = a[9 + i] & b[9 + i];
			c[10 + i] = a[10 + i] & b[10 + i];
			c[11 + i] = a[11 + i] & b[11 + i];
			c[12 + i] = a[12 + i] & b[12 + i];
			c[13 + i] = a[13 + i] & b[13 + i];
			c[14 + i] = a[14 + i] & b[14 + i];
			c[15 + i] = a[15 + i] & b[15 + i];

		}
	rc = gettimeofday(&now, NULL);
	fim=now.tv_usec;

	tempoMedia = ((float)fim - (float)inicio)/N;
	tempo = fim - inicio;

	cout<<"\n\nTempo normal: "<<tempo<<" usec\n";
	cout<<"Tempo medio normal: "<<tempoMedia<<" usec\n\n";


	/*
	 *
	 *
	 * REGIAO CPU Com indice
	 *
	 *
	 *
	 *
	 *
	 *
	 * */

// 	rc = gettimeofday(&now, NULL);
// 	inicio= now.tv_usec;
// #pragma unroll N
// 	for(i = 0; i<N; ++i){
	
// 		for(j =0; j<SIZE; ++j){
// 			c[j] = a[j] & b[j];
// 			//__builtin_prefetch (&a[j+1], 0, 1);
//             //__builtin_prefetch (&b[j+1], 0, 1);
//             //__builtin_prefetch (&c[j+1], 1, 1);
           
// 		}
// 	}

// 	rc = gettimeofday(&now, NULL);
// 	fim=now.tv_usec;

// 	tempoMedia = ((float)fim - (float)inicio)/N;
// 	tempo = fim - inicio;

// 	cout<<"\n\nTempo normal com indice: "<<tempo<<" usec\n";
// 	cout<<"Tempo medio normal com indice: "<<tempoMedia<<" usec\n";

	// for(int i = 0 ; i<SIZE;++i)
	// 	cout<<" "<<c[i];
	// cout<<"\n\n";

	/*
	 *
	 *
	 *
	 *
	 *
	 *
	 * REGIAO SSE
	 *
	 *
	 */
	unsigned long long v1[SIZE] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));
	unsigned long long v2[SIZE] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));
	unsigned long long v3[SIZE] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));

	for(i =0; i<SIZE;++i){
		v1[i]=v2[i]=i;
	}

	__m128i* ptr1 = (__m128i*)v1;
	__m128i* ptr2 = (__m128i*)v2;
	__m128i* ptr3 = (__m128i*)v3;





	/*
	 *
	 *
	 * REGIAO SSE Com indice
	 *
	 *
	 *
	 *
	 *
	 *
	 * */
	rc = gettimeofday(&now, NULL);
	inicio= now.tv_usec;
	for(j=0; j< N;++j){
		for(i=0; i<(SIZE/2);++i){
			//_mm_stream_si128(&ptr3[i],_mm_and_si128(ptr1[i],ptr2[i]));
			ptr3[i]=  _mm_and_si128(ptr1[i],ptr2[i]);
		    //__builtin_prefetch();
			//_mm_store_si128 (ptr3, _mm_and_si128(ptr1[i],ptr2[i]));
			
		}

	}
	rc = gettimeofday(&now, NULL);
	fim=now.tv_usec;


	tempoMedia = ((float)fim - (float)inicio)/N;
	tempo  = fim-inicio;

	cout<<"\n\nTempo SSE com indice: "<<tempo <<" usec;";
	cout<<"\nTempo medio SSE com indice: "<<tempoMedia<<" usec.\n\n";






	rc = gettimeofday(&now, NULL);
	inicio= now.tv_usec;
	for(j=0; j< N;++j){
		for(i=0; i<(SIZE/2);i=i+8){
			ptr3[i + 0]=  _mm_and_si128(ptr1[i + 0],ptr2[i + 0]);
			ptr3[i + 1]=  _mm_and_si128(ptr1[i + 1],ptr2[i + 1]);
			ptr3[i + 2]=  _mm_and_si128(ptr1[i + 2],ptr2[i + 2]);
			ptr3[i + 3]=  _mm_and_si128(ptr1[i + 3],ptr2[i + 3]);	
			ptr3[i + 4]=  _mm_and_si128(ptr1[i + 4],ptr2[i + 4]);
			ptr3[i + 5]=  _mm_and_si128(ptr1[i + 5],ptr2[i + 5]);
			ptr3[i + 6]=  _mm_and_si128(ptr1[i + 6],ptr2[i + 6]);
			ptr3[i + 7]=  _mm_and_si128(ptr1[i + 7],ptr2[i + 7]);
			// ptr3[i + 8]=  _mm_and_si128(ptr1[i + 8],ptr2[i + 8]);
			// ptr3[i + 9]=  _mm_and_si128(ptr1[i + 9],ptr2[i + 9]);
			// ptr3[i + 10]=  _mm_and_si128(ptr1[i + 10],ptr2[i + 10]);
			// ptr3[i + 11]=  _mm_and_si128(ptr1[i + 11],ptr2[i + 11]);	
			// ptr3[i + 12]=  _mm_and_si128(ptr1[i + 12],ptr2[i + 12]);
			// ptr3[i + 13]=  _mm_and_si128(ptr1[i + 13],ptr2[i + 13]);
			// ptr3[i + 14]=  _mm_and_si128(ptr1[i + 14],ptr2[i + 14]);
			// ptr3[i + 15]=  _mm_and_si128(ptr1[i + 15],ptr2[i + 15]);

		}
	}
	rc = gettimeofday(&now, NULL);
	fim=now.tv_usec;


	tempoMedia = ((float)fim - (float)inicio)/N;
	tempo  = fim-inicio;

	cout<<"\n\nTempo SSE: "<<tempo <<" usec\n";
	cout<<"Tempo medio SSE: "<<tempoMedia<<" usec\n\n";



	
	//for(int i = 0 ; i<SIZE;++i)
	//	cout<<" "<<v3[i];
	//cout<<"\n\n";
	return 0;
}
