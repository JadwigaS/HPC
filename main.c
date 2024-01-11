
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
  int **kraj;
  double **rozm;
   double ag[2];
   int N;
   int *ile[2];
void walka(int i,int j,int k,int l){
	
	if(kraj[i][j]!=kraj[k][l]){
		 printf("*");
		double chance=(float)rand()/(float)(RAND_MAX);
		if(chance<ag[kraj[i][j]-1]&&chance<ag[kraj[k][l]-1]){
			kraj[i][j]=0;
			kraj[k][l]=0;
		}
		else if(chance<ag[kraj[i][j]-1]){
			kraj[k][l]=0;
		}
		else if(chance<ag[kraj[k][l]-1]){
			kraj[i][j]=0;
		}
		else{
			if(rozm[i][j]<1) rozm[i][j]+=0.01;
			if(rozm[k][l]<1) rozm[k][l]+=0.01;
		}
	}
	else {
		if(rozm[i][j]<1) rozm[i][j]+=0.01;
		if(rozm[k][l]<1) rozm[k][l]+=0.01;
	}
}
void wiecej(int i,int j,int k,int l){
	double chance=(float)rand()/(float)(RAND_MAX);
	if(chance<rozm[i][j]){
		kraj[k][l]=kraj[i][j];
		rozm[k][l]=0.0;
		rozm[i][j]=0.0;
	}
	else if(rozm[i][j]<1) rozm[i][j]+=0.01;
    //todo dodaj rozmnażanie
}
double srednia(int krok){
	ile[0][krok]=0;
	ile[1][krok]=0;
	for(int i=0;i<=N;i++){
		for(int j=0;j<=N;j++){
			if(kraj[i][j]==1) ile[0][krok]+=1;
			if(kraj[i][j]==2) ile[1][krok]+=1;
		}
	}
}
int main(int argc, char *argv[]){ //N,proc,ag1,ag2,kroki
 
  
   N=(int)argv[0];
  double proc=((double *)argv)[1];

  ag[0]=((double *)argv)[2];
  ag[1]=((double *)argv)[3];
  int kroki=(int)argv[4];
  srand(time(0));
  ile[0]=malloc(kroki*sizeof(int));
  ile[1]=malloc(kroki*sizeof(int));
  kraj=malloc( N * sizeof( int * ) ); 
    rozm=malloc( N * sizeof( double * ) ); 
    for (int i=0;i<=N;i++){
		
		kraj[i]=malloc((N+1)*sizeof(int));
		rozm[i]=malloc((N+1)*sizeof(double));
        for(int j=0;j<=N;j++){
			
            if(((float)rand()/(float)(RAND_MAX))<proc){
				  kraj[i][j]=1;
			  }
            else {
				kraj[i][j]=2;
			}
			rozm[i][j]=0.5;
        }
        printf("%d",i);
    }
	printf("*");
    srednia(0);
	for(int i=1;i<kroki;i++){
		   
		int a=(rand()%N);
		int b=(rand()%N);
		int c,d;
		
		if((rand()%2) ==0) c=a-1;
		else c=a+1;
		if((rand()%2)==0) d=b-1;
		else d=b+1;
		 
		if(kraj[a][b]!=0&&kraj[c][d]!=0) walka(a,b,c,d);
		else if(kraj[a][b]!=0) wiecej(a,b,c,d);
		else if(kraj[c][d]!=0) wiecej(c,d,a,b);
		srednia(i);	
		printf("%d",ile[0][i]);
	}
	free(kraj);
	free(rozm);
	free(ile);
    return 0;
}
