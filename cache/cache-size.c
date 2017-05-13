#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define max_size 18
int main(){
	unsigned int size[max_size];
	struct timeval t_begin,t_end;
	//test different block size
	for(int i=0;i<max_size;++i){
		size[i]=(1<<i)<<10;
	}
	printf("Size(K)\tUsed time(secs)\tSum\t\n");
	for(int i=0;i<max_size;++i){
		unsigned int cur_size=size[i];
		double time_use=0.0;
		char *buffer=(char*)malloc(cur_size*sizeof(char));
		if(buffer==NULL){
			printf("Error in return value of malloc!\n");
			exit(0);
		}
		memset(buffer,1,cur_size);
		int sum=0;
		//get start time
		gettimeofday(&t_begin,NULL);
		for(unsigned int j=0;j<(1<<25);++j){
			sum+=buffer[((long long)63*(j%cur_size))%cur_size];
		}
		//get end time
		gettimeofday(&t_end,NULL);
		//calculate used time
		time_use=t_end.tv_sec - t_begin.tv_sec + (t_end.tv_usec-t_begin.tv_usec)/1000000.0;
		printf("%d\t%f\t%d\n",cur_size>>10,time_use,sum);
		free(buffer);
	}
	return 0;
}
