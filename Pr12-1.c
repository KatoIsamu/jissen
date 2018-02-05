          #include<stdio.h>
#include<stdlib.h>

        int size[] = {2, 3, 5, 7, 9, 15};

        int value[] = {2, 4, 7, 11, 14, 24};

        #define AS (sizeof(size)/sizeof(size[0]))

        #define MAX_M   200

void DynamicProgramming(int N, int Nsize[], int Nvalue[]){
        int i,j,dispno;

        int total[MAX_M];

        int choice[MAX_M];

        int repack_total;

        for(i=0;i<=N;i++){
                total[i] = 0;
                choice[i] = -1;
        }

        for(i=0;i<AS;i++){
		for(j=0; j<=N; j++){

			if(Nsize[i]<=j){
			     if((total[j-Nsize[i]]+Nvalue[i])>total[j]){
				         total[j]=total[j-Nsize[i]]+Nvalue[i];
				         choice[j]=i;
            }
      }
    }


                printf("i = %d\n",i);
                printf("choice = ");
                for(j=0;j<=N;j++)
                        printf("%2d ",choice[j]);
                printf("\n");
        }

        dispno=N;
        do{
          printf("pack baggage no.%d(value:%d)\n",choice[dispno],value[choice[dispno]]);
          dispno=dispno-size[choice[dispno]];
        }while(dispno>0&&choice[dispno]!=-1);
        printf("total value = %d\n",total[N]);

}

int main(int argc, char *argv[]){
        int m;

        if(argc!=2){
          printf("input size of bag");
          return 0;
        }

        m = atoi(argv[1]);
        printf("Size of knapsack is %d\n",m);

        DynamicProgramming(m,size,value);

        return 0;
}
