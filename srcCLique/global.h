#ifndef GLOBAL_H
#define GLOBAL_H

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
#define N 66
#define qtd_vertices 66
#define qtd_palavrasULL 2
//se N > 64, teremos mais uma coluna


class Timer
{
public:
	Timer(const std::string& name): name_ (name),start_ (clock())
{
}
	~Timer()
	{
		double elapsed = (double(clock() - start_) / double(CLOCKS_PER_SEC));
		cout << name_ << ": " << int(elapsed * 1000) << "ms" << endl;
	}
private:
	string name_;
	clock_t start_;
};

#define TIMER(name) Timer timer__(name);






extern struct timeval now;
extern unsigned long long G[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16)));

extern unsigned long long G_BK[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16)));

extern unsigned long long R[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16))) ;
extern unsigned long long W[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16))) ;
extern unsigned long long V[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16))) ;
extern unsigned long long S[qtd_vertices*qtd_palavrasULL] __attribute__ ((aligned(16))) ;

extern unsigned long long c[qtd_palavrasULL]__attribute__ ((aligned(16)));



#define R(i,j)      R[qtd_palavrasULL*(i)+(j)]
#define R_line(i)   R[qtd_palavrasULL*(i)]

#define W(i,j)      W[qtd_palavrasULL*(i)+(j)]
#define W_line(i)   W[qtd_palavrasULL*(i)]


#define V(i,j)      V[qtd_palavrasULL*(i)+(j)]
#define V_line(i)   V[qtd_palavrasULL*(i)]

#define S(i,j) S[qtd_palavrasULL*(i)+(j)]
#define S_line(i)   S[qtd_palavrasULL*(i)]

#define G(i,j) G[qtd_palavrasULL*(i)+(j)]
#define G_line(i)   G[qtd_palavrasULL*(i)]


#endif //GLOBAL_H

