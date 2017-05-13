#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ARRAY_WIDTH 1024
#define ARRAY_SIZE (ARRAY_WIDTH * ARRAY_WIDTH)
#define min(x,y) (((x)<=(y))?(x):(y))

int A[ARRAY_SIZE],B[ARRAY_SIZE],C[ARRAY_SIZE];
void init(){
	for(int i=0;i<ARRAY_SIZE;++i){
		A[i]=1;B[i]=2;C[i]=0;
	}
}
void printMatrix(int *A){
	printf("Sum ->\n");
	for(int i=0;i<ARRAY_WIDTH;++i){
		for(int j=0;j<ARRAY_WIDTH;++j){
			printf("%d ",A[i*ARRAY_WIDTH+j]);
		}
		printf("\n");
	}
}
void MartrixMul(int *A,int *B,int *C,int size){
	for(int i=0;i<size;++i){
		for(int j=0;j<size;++j){
			int sum=0;
			for(int k=0;k<size;++k){
				sum+=(*(A+i*size+k)) * (*(B+k*size+j));
			}
			*(C+i*size+j)=sum;
		}
	}
}
void MatrixMulBlock(int *A,int *B,int *C,int size,int block){
	for(int ii=0;ii<size;ii+=block){
		for(int jj=0;jj<size;jj+=block){
			for(int kk=0;kk<size;kk+=block){
				//min matrix
				int mi=min(ii+block,size),mj=min(jj+block,size),mk=min(kk+block,size);
				for(int i=ii;i<mi;++i){
					for(int j=jj;j<mj;++j){
						int sum=0;
						for(int k=kk;k<mk;++k){
							sum+=(*(A+i*size+k)) * (*(B+k*size+j));
						}
						*(C+i*size+j)+=sum;
					}
				}
			}
		}
	}
}
int main(){
	struct timeval t_begin,t_end;
	printf("Block\tTime\n");
	init();
	gettimeofday(&t_begin,NULL);
	MartrixMul(A,B,C,ARRAY_WIDTH);
	gettimeofday(&t_end,NULL);
	printf("0\t%ld secs/%ld usecs\n",(t_end.tv_sec - t_begin.tv_sec),(t_end.tv_usec-t_begin.tv_usec));
	//printMatrix(C);
	for(int i=2;i<ARRAY_WIDTH;i<<=1){
		init();
		gettimeofday(&t_begin,NULL);
		MatrixMulBlock(A,B,C,ARRAY_WIDTH,16);
		gettimeofday(&t_end,NULL);
		printf("%d\t%ld secs/%ld usecs\n",i,(t_end.tv_sec - t_begin.tv_sec),(t_end.tv_usec-t_begin.tv_usec));
	}
	//printMatrix(C);
    return 0;
}
