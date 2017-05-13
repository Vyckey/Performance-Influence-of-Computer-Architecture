/* memory_mountain.c - Test and generate memory mountain */
#include <stdlib.h>
#include <stdio.h>
#include "fcyc2.h"
#include "clock.h"

#define MINBYTES (1 << 10)
#define MAXBYTES (1 << 27)  // 1KB to 128 MB
#define MAXSTRIDE 32        // Strides range from 1 to 32
#define STRIDESTRIDE 2      // increment stride by this amount each time
#define MAXELEMS MAXBYTES/sizeof(int) 

int data[MAXELEMS];         // The array we'll be traversing

void init_data(int *data, int n);
void test(int elems, int stride);
double run(int size, int stride, double Mhz);

int main(){
    int size;        // Working set size (in bytes)
    int stride;      // Stride (in array elements)
    double Mhz;      // Clock frequency
    for(int i=0;i<MAXELEMS;++i){
    	data[i]=1;
    }
    Mhz = mhz(0);

    printf("size\\stride");
    printf("\t");
    for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE){
    	printf("s%d\t", stride);
    }
    printf("\n");

    for (size = MAXBYTES; size >= MINBYTES; size >>= 1) {
		if (size > (1 << 20))
		    printf("%dm\t", size >>20);
		else
		    printf("%dk\t", size >> 10);
		for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE) {
		    double tmp = run(size, stride, Mhz);
		    printf("%.0f\t", tmp);
		}
		printf("\n");
    }
    return 0;
}

void test(int elems, int stride){
    int i, result = 0; 
    volatile int sink; 
    for (i = 0; i < elems; i += stride)
		result += data[i];
    sink = result; // compiler doesn't optimize away the loop
}

// Run test(elems, stride) and return read throughput (MB/s)
double run(int size, int stride, double Mhz){
    double cycles;
    int elems = size / sizeof(int); 
    test(elems, stride);                     // warm up the cache
    cycles = fcyc2(test, elems, stride, 0);  // call test(elems,stride)
    return (size / stride) / (cycles / Mhz); // convert cycles to MB/s
}
