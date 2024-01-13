
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

  int **kraj;
  double **rozm;
   double ag[2];
   int N;
   int **ile;
void walka(int i,int j,int k,int l){
//	printf("Zaczela się interakcja \n");
	if(kraj[i][j]!=kraj[k][l]){
	//	 printf("Walka !!\n");
		double chance=(float)rand()/(float)(RAND_MAX);
		if(chance<ag[kraj[i][j]-1]&&chance<ag[kraj[k][l]-1]){
			kraj[i][j]=0;
			kraj[k][l]=0;
	//		printf("Oba nie zyja :o \n");
		}
		else if(chance<ag[kraj[i][j]-1]){
			kraj[k][l]=0;
		//	printf("Wygral %d ! \n",kraj[i][j]);
		}
		else if(chance<ag[kraj[k][l]-1]){
			kraj[i][j]=0;
		//	printf("Wygral %d ! \n",kraj[k][l]);
		}
		else{
			if(rozm[i][j]<1) rozm[i][j]+=0.01;
			if(rozm[k][l]<1) rozm[k][l]+=0.01;
	//		printf("Przyjazna potyczka \n");
		}
	}
	else {
		if(rozm[i][j]<1) rozm[i][j]+=0.01;
		if(rozm[k][l]<1) rozm[k][l]+=0.01;
//		printf("To ci sami ;)");
	}
}
void wiecej(int i,int j,int k,int l){
	double chance=(float)rand()/(float)(RAND_MAX);
	if(chance<rozm[i][j]){
		kraj[k][l]=kraj[i][j];
		rozm[k][l]=0.0;
		rozm[i][j]=0.0;
	//	printf("Powstal nowy %d ! \n",kraj[i][j]);
	}
	else { 
		rozm[i][j]+=0.01;
//		printf("too weak :< \n");
		}
   
}
void srednia(int krok){
	//printf("Liczymy wartosci \n");
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

   N=atoi(argv[1]);
  double proc=strtod(argv[2],NULL);
	printf("Powstała siatka %d na %d wypelniona na %lf zielonym \n",N,N,proc);
  ag[0]=strtod(argv[3],NULL);
  ag[1]=strtod(argv[4],NULL);
  int kroki=atoi(argv[5]);
  srand(time(0));
  ile=malloc( 2 * sizeof( int * ) ); 
  ile[0]=malloc((kroki+1)*sizeof(int));
  ile[1]=malloc((kroki+1)*sizeof(int));
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
        
    }
	printf("No to zaczynamy \n");
    srednia(0);
	for(int i=1;i<kroki;i++){
		for(int j=0;j<N*N;j++){
			int a=(rand()%N);
			int b=(rand()%N);
			int c,d;
		
			if((rand()%2) ==0) c=a-1;
			if(c<0) c=N;
			else c=a+1;
			if(c>N) c=0;
			if((rand()%2)==0) d=b-1;
			else d=b+1;
			if(d<0) d=N;
			if(d>N)d=0;
	//	 printf("a=%d,b=%d,c=%d,d=%d",a,b,c,d);
			if(kraj[a][b]!=0&&kraj[c][d]!=0) walka(a,b,c,d);
			else if(kraj[a][b]!=0) wiecej(a,b,c,d);
			else if(kraj[c][d]!=0) wiecej(c,d,a,b);
		}
		srednia(i);	
	//	printf("zielony to %d \n",ile[0][i]);
	}
	for(int i=0;i<kroki;i++){
		printf("krok %d, zielony %d, czerwony %d \n",i,ile[0][i],ile[1][i]);
	}
	   for (int i=0;i<=N;i++){
		free(kraj[i]);
		free(rozm[i]);
	}
	free(kraj);
	free(rozm);
	free(ile[0]);
	free(ile[1]);
	free(ile);
    return 0;
}
