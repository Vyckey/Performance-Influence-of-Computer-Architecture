int main(){
    int array[4]={1,2,3,4},result=0;
    for(int i=0;i<0x3fffffff;++i){
        result+=array[0];
        result+=array[1];
        result+=array[2];
        result+=array[3];
    }
    return 0;
}
