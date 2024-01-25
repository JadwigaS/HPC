/*
 *  gcc main.c -o main -lm -O3 -fopenmp -std=c99
 * 
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mct_utils.h"

#include <omp.h>
  int **kraj;
  double **rozm;
   double ag[2];
   int N;
   int **ile;
void walka(int a,int b){
//	printf("Zaczela się interakcja \n");
//	if(a!=b){
	//	 printf("Walka !!\n");
		double chance=(float)rand()/(float)(RAND_MAX);
		if(chance<ag[a-1]&&chance<ag[b-1]){
			
			a=0;
			
			b=0;
	//		printf("Oba nie zyja :o \n");
		}
		else if(chance<ag[a-1]){
			
			a=0;
		//	printf("Wygral %d ! \n",kraj[i][j]);
		}
		else if(chance<ag[b-1]){
			
			b=0;
		//	printf("Wygral %d ! \n",kraj[k][l]);
		}
		else{
			//if(rozm[i][j]<1) rozm[i][j]+=0.01;
			//if(rozm[k][l]<1) rozm[k][l]+=0.01;
	//		printf("Przyjazna potyczka \n");
		}
	//}
	//else {
		 
		//if(rozm[i][j]<1) rozm[i][j]+=0.01;
		 
		//if(rozm[k][l]<1) rozm[k][l]+=0.01;
//		printf("To ci sami ;)");
	//}
}
/*void wiecej(int a,int k,int l){
	double chance=(float)rand()/(float)(RAND_MAX);
	if(chance<rozm[i][j]){
		#pragma omp critical 
		kraj[k][l]=kraj[i][j];
		rozm[k][l]=0.0;
		rozm[i][j]=0.0;
	//	printf("Powstal nowy %d ! \n",kraj[i][j]);
	}
	else { 
		#pragma omp critical 
		rozm[i][j]+=0.01;
//		printf("too weak :< \n");
		}
   
}*/
/*void srednia(int krok){
	//printf("Liczymy wartosci \n");
	ile[0][krok]=0;
	ile[1][krok]=0;
	//int i,j;
	for(int i=0;i<=N;i++){
		for(int j=0;j<=N;j++){
			if(kraj[i][j]==1) ile[0][krok]+=1;
			if(kraj[i][j]==2) ile[1][krok]+=1;
		}
	}
}*/
int main(int argc, char *argv[]){ //N,proc,ag1,ag2,kroki
	if(argc !=6) return 0;
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
    
	//cppmallocl(ile[0],kroki,int);
	//cppmallocl(ile[1],kroki,int); 
	
	int i=0;
	int j=0;
    for (i=0;i<N;i++){
		
		kraj[i]=malloc((N)*sizeof(int));
		rozm[i]=malloc((N)*sizeof(double));
		#pragma omp parallel for default(shared) private(j)  schedule(guided) 
        for( j=0;j<=N;j++){
			
            if(((float)rand()/(float)(RAND_MAX))<proc){
				  kraj[i][j]=1;
			  }
            else {
				kraj[i][j]=2;
			}
			rozm[i][j]=0.5;
        }
        
    }
     b_t();
	printf("No to zaczynamy \n");
  
    ile[0][0]=0;
	ile[1][0]=0;
	
		int k;
		int z=0;
		int cz=0;
		#pragma omp parallel for default(shared) private(j,k)  schedule(guided) collapse(2) reduction(+:z) reduction(+:cz)
		for(k=0;k<N;k++){

			for( j=0;j<N;j++){
				if(kraj[k][j]==1) z+=1;
				if(kraj[k][j]==2) cz+=1;
		}
		
		}
		ile[0][0]+=z;
		ile[1][0]+=cz;
	
	
	for( i=1;i<kroki;i++){
		//printf("aa");
		//#pragma omp parallel for default(shared) private(j)  schedule(dynamic)
		//for(j=0;j<N*N;j++){
			//int a=(rand()%N);
			//int b=(rand()%N);
			int a,b,jj,aa,bb;
			int ch=rand()%4;
			if(ch ==0){
				j=1;
				jj=2;
				aa=0;
				bb=0;
			}
			else if(ch==1){
				j=1;
				jj=2;
				aa=0;
				bb=1;
			}
			else if(ch==2){
				j=2;
				jj=1;
				aa=0;
				bb=0;
			}
			else if(ch==3){
				j=2;
				jj=1;
				aa=1;
				bb=0;
			}
		#pragma omp parallel for default(shared) private(a,b)  schedule(guided) collapse(2)
		for(a=aa;a<N;a=a+j){
			for(b=bb;b<N;b=b+jj){
			//if((rand()%2) ==0) c=a-1;
			//if(c<0) c=N-1;
			//else c=a+1;
			//if(c>=N) c=0;
			//if((rand()%2)==0) d=b-1;
			//else d=b+1;
			//if(d<0) d=N-1;
			//if(d>=N)d=0;
		// printf("a=%d,b=%d,c=%d,d=%d",a,b,c,d);
		int c,d;
			if(ch==0 || ch==1){
				c=a;
				d=b+1;
				if(d>=N)d=0;
			}
			else{
				c=a+1;
				d=b;
				if(c>=N)c=0;
			}
			int ka=kraj[a][b];
			int kc = kraj[c][d];
			
			double roza= rozm[a][b];
			double rozc= rozm[c][d];
			if(ka!=0&&kc!=0){
				if(ka!=kc){ 
					//walka(ka,kc);
					double chance=(float)rand()/(float)(RAND_MAX);
					double aga=ag[ka-1];
					double agc=ag[kc-1];
					aga=aga-roza+0.5; //im mniejszy roza, tym wiecej agresywnych zachowań
					agc=agc-rozc+0.5;
					if(chance<aga&&chance<agc){
						ka=0;
						kc=0;
					}
					else if(chance<agc){			
						ka=0;	
						if(rozc>0) rozc-=0.01;	
					}
					else if(chance<aga){
						kc=0;
						if(roza>0) roza-=0.01;	
					}
					else{
						if(roza<1) roza+=0.01;
		 
						if(rozc<1) rozc+=0.01;
					}
				}
				else{
					roza=(roza+rozc)/2;
					rozc=roza;
					if(roza<1) roza+=0.02;
		 
					if(rozc<1) rozc+=0.02;
				}
			}
			else if(ka!=0){
					double chance=(float)rand()/(float)(RAND_MAX);
					if(chance<=roza){
						kc=ka;
						rozc/=2;
						roza/=2;
					}
					else if(roza<1) roza+=0.01;
				} 
			else if(kc!=0){
				double chance=(float)rand()/(float)(RAND_MAX);
				if(chance<=rozc){
					ka=kc;
					rozc/=2;
					roza/=2;
				}
				else if(rozc<1) rozc+=0.01;
					
			}
			kraj[a][b]=ka;
			kraj[c][d]=kc;
			rozm[a][b]=roza;
			rozm[c][d]=rozc;
		}}
		//srednia(i);	
		 ile[0][i]=0;
		ile[1][i]=0;
		//int k;
		int z=0;
		int cz=0;
		#pragma omp parallel for default(shared) private(j,k)  schedule(guided) collapse(2) reduction(+:z) reduction(+:cz)
		for(k=0;k<N;k++){
			
			for( j=0;j<N;j++){
				if(kraj[k][j]==1) z+=1;
				if(kraj[k][j]==2) cz+=1;
			}
		
		}
		ile[0][i]+=z;
		ile[1][i]+=cz;
	}
	double tio = e_t(); // stop timing
    printf("# czas liczenia: %f sec\n", tio);
	i=0;
	printf("krok \t zielony \t czerwony \n");
	for(i=0;i<kroki;i++){
		printf(" %d \t %d \t %d \n",i,ile[0][i],ile[1][i]);
	}

	/*for (i=0;i<=N;i++){
		free(kraj[i]);
		free(rozm[i]);
	}
	free(kraj);
	free(rozm);
	free(ile[0]);
	free(ile[1]);
	free(ile);*/
    return 0;
}
