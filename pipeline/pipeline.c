#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

int main(int argc,char *argv[]){
	struct timeval t_begin,t_end;
	double used_time=0.0;
    char cmd[128]="./";
    if(argc!=3){
        printf("Error in argment! -> pipeline [file1] [file2]\n");
        return 0;
    }
    strcat(cmd,argv[1]);
	//get begin time
	gettimeofday(&t_begin,NULL);
    system(cmd);
	//get end time
	gettimeofday(&t_end,NULL);
	//calculate used time execute
	used_time=t_end.tv_sec - t_begin.tv_sec + (t_end.tv_usec-t_begin.tv_usec)/1000000.0;
	printf("<1>%s: %f seconds\n",argv[1],used_time);
    
    strcpy(cmd,"./");
    strcat(cmd,argv[2]);
	//get begin time
	gettimeofday(&t_begin,NULL);
    system(cmd);
	//get end time
	gettimeofday(&t_end,NULL);
	//calculate used time execute
	used_time=t_end.tv_sec - t_begin.tv_sec + (t_end.tv_usec-t_begin.tv_usec)/1000000.0;
	printf("<2>%s: %f seconds\n",argv[2],used_time);
	return 0;
}
