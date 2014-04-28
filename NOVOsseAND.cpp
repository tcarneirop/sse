
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



#define TIMER(name) Timer timer__(name);
#define N 1024
#define SIZE 4

int main() {

	int rc;

	
	unsigned int inicio;
	unsigned int fim;
	unsigned int tempo;
	register int i;
	float tempoMedia;




	unsigned long long a[SIZE], b[SIZE], c[SIZE];

	for(int i =0; i<SIZE;++i){
		a[i]=b[i]=i;	
	}

	for(int x = 0; x<10;++x){
	
		c[0] = a[0] & b[0];
		c[1] = a[1] & b[1];
		c[2] = a[2] & b[2];
		c[3] = a[3] & b[3];

	}

	rc = gettimeofday(&now, NULL);
	inicio= now.tv_usec;
	for(i = 0; i<N; ++i){
		c[0] = a[0] & b[0];
		c[1] = a[1] & b[1];
		c[2] = a[2] & b[2];
		c[3] = a[3] & b[3];

	}
	rc = gettimeofday(&now, NULL);
	fim=now.tv_usec;

	tempoMedia = ((float)fim - (float)inicio)/N;
	tempo = fim - inicio;

	cout<<"\n\nTempo normal: "<<tempo<<" usec\n\n";
	cout<<"\n\nTempo medio normal: "<<tempoMedia<<" usec\n\n";
	



	/*
		REGIAO SSE
	*/
	unsigned long long v1[4] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));
	unsigned long long v2[4] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));
	unsigned long long v3[4] __attribute__ ((aligned (16*(sizeof(unsigned long long)))));

	for(int i =0; i<SIZE;++i){
		v1[i]=v2[i]=i;
	}

	__m128i* ptr1 = (__m128i*)v1;
	__m128i* ptr2 = (__m128i*)v2;
	__m128i* ptr3 = (__m128i*)v3;

	for(int a=0; a<10;++a){//teste professor

		// _mm_stream_si128(&ptr3[0],  _mm_and_si128(ptr1[0],ptr2[0]));
		// _mm_stream_si128(&ptr3[1],  _mm_and_si128(ptr1[0],ptr2[0]));
		
		ptr3[0]=  _mm_and_si128(ptr1[0],ptr2[0]);
		ptr3[1]=  _mm_and_si128(ptr1[1],ptr2[1]);
	}
	
	rc = gettimeofday(&now, NULL);
	inicio= now.tv_usec;
	for(i=0; i< N;++i){
		// _mm_stream_si128(&ptr3[0],  _mm_and_si128(ptr1[0],ptr2[0]));
		// _mm_stream_si128(&ptr3[1],  _mm_and_si128(ptr1[0],ptr2[0]));
		
		ptr3[0]=  _mm_and_si128(ptr1[0],ptr2[0]);
		ptr3[1]=  _mm_and_si128(ptr1[1],ptr2[1]);
	}
	rc = gettimeofday(&now, NULL);
	fim=now.tv_usec;


	tempoMedia = ((float)fim - (float)inicio)/N;
	tempo  = fim-inicio;

	cout<<"\n\nTempo SSE: "<<tempo <<" usec\n\n";
	cout<<"\n\nTempo medio SSE: "<<tempoMedia<<" usec\n\n";


	/*
		REGIAO AVX
	*/


	//unsigned long long vct1[4] __attribute__ ((aligned (4*(sizeof(unsigned long long)))));
	//unsigned long long vct2[4] __attribute__ ((aligned (4*(sizeof(unsigned long long)))));
	//unsigned long long vct3[4] __attribute__ ((aligned (4*(sizeof(unsigned long long)))));
	
	//int vct1[8]={0,1,2,3,4,5,6,7};
	//int vct2[8]={0,1,2,3,4,5,6,7};
	//int vct3[8]={0,1,2,3,4,5,6,7};

//	__m256i* avx1 = (__m256i*)vct1;
	//__m256i* avx2 = (__m256i*)vct2;
//	__m256i* avx3 = (__m256i*)vct3;

	
//	__m256i va0, va1, va2;             // 256 bit variables

//	va2 = _mm256_and_si256(va0, va1);  // bitwise AND


	//rc = gettimeofday(&now, NULL);
//	inicio= now.tv_usec;
	
	//for(int j=0; j< N;++j){
	//	avx3=  _mm256_and_si256(avx1,avx2);
		
	//}
//	rc = gettimeofday(&now, NULL);
//	fim=now.tv_usec;


//	tempoMedia = ((float)fim - (float)inicio)/1024;
//	tempo  = fim-inicio;

//	cout<<"\n\nTempo AVX 256: "<<tempo <<" usec\n\n";
//	cout<<"\n\nTempo medio AVX 256: "<<tempoMedia<<" usec\n\n";

	return 0;
}
