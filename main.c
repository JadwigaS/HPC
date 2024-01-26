/*
 *  gcc main.c -o main -lm -O3 -fopenmp -std=c99
 * 
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mct_utils.h"
#include <math.h>
#include <omp.h>
  int **kraj;
  double rozm[2];
   double ag[2];
   int N;
   double **ile;
#define popmax 10000
int main(int argc, char *argv[]){ //N,proc,ag1,ag2,rozm,rozm,kroki, 
	if(argc !=8) return 0;
   N=atoi(argv[1]);
  double proc=strtod(argv[2],NULL);
	printf("Powstało %d symulacji wypelnionych na %lf zielonym \n",N,proc);
  ag[0]=strtod(argv[3],NULL);
  ag[1]=strtod(argv[4],NULL);
   rozm[0]=strtod(argv[5],NULL);
  rozm[1]=strtod(argv[6],NULL);
  int kroki=atoi(argv[7]);
  srand(time(0));
	ile=malloc( 4 * sizeof( int * ) ); 
  ile[0]=malloc((kroki+1)*sizeof(double));
  ile[1]=malloc((kroki+1)*sizeof(double));
   ile[2]=malloc((kroki+1)*sizeof(double));
     ile[3]=malloc((kroki+1)*sizeof(double));
  kraj= malloc( 2 * sizeof( int * ) ); 

  kraj[0]= (int*)malloc( N * sizeof( int ) );

  kraj[1]= (int*)malloc( N * sizeof( int ) );
// printf("alokacja pamięci \n");

	int i=0;
	
	int j=0;
	 
  
	
		
	
		#pragma omp parallel for default(shared) private(j)  schedule(guided) 
        for( j=0;j<=N;j++){
			
            kraj[0][j]=popmax*proc;
            kraj[1][j]=popmax*(1-proc);
		
        }
        
    
     b_t();
	printf("No to zaczynamy \n");
  
    ile[0][0]=0;
	ile[1][0]=0;
	ile[2][0]=0;
		
		int z=0;
		int cz=0;
		#pragma omp parallel for default(shared) private(j)  schedule(guided)  reduction(+:z) reduction(+:cz)
		

		for( j=0;j<N;j++){
			z+=kraj[0][j];
			cz+=kraj[1][j];;
		}
		
		
		ile[0][0]+=z;
		ile[1][0]+=cz;
		ile[0][0]/=(N);
		ile[1][0]/=(N);
		double stdevz=0;
		double stdevc=0;
		#pragma omp parallel for default(shared) private(j)  schedule(guided)  reduction(+:stdevz) reduction(+:stdevc)
		

		for( j=0;j<N;j++){
			stdevz+=(kraj[0][j]-ile[0][0])*(kraj[0][j]-ile[0][0]);
			stdevc+=(kraj[1][j]-ile[1][0])*(kraj[1][j]-ile[1][0]);
		}
		
		
		ile[2][0]=stdevz/((double)(N-1));
		ile[3][0]=stdevc/((double)(N-1));
	for( i=1;i<kroki;i++){
		
			int a;
		#pragma omp parallel for default(shared) private(a)  schedule(guided) 
		for(a=0;a<N;a++){
			
			
			int ka=kraj[0][a];
			int kc=kraj[1][a];	
			double chance=(float)rand()/(float)(RAND_MAX);
			double aga=ag[0];
			double agc=ag[1];
			double szaga=exp(aga*(ka-kc)/(ka+kc)-1);
			double szagc=exp(agc*(kc-ka)/(ka+kc)-1);
			if(chance<szaga&&chance<szagc){
					int kaa=ka;
					ka-=szagc*kc;
					kc-=szaga*kaa;
				
				}
			else if(chance<szagc){			
					ka-=szagc*kc;	
							
				}
			else if(chance<szaga){
					kc-=szaga*ka;
							
				}
					if(ka<0) ka=0;
					if(kc<0) kc=0;
			chance=(float)rand()/(float)(RAND_MAX);
			if(chance<rozm[0]) ka=ka*(1+rozm[0]);
			if(chance<rozm[1]) kc=kc*(1+rozm[1]);	
			if(ka>popmax) ka=popmax;
			if(kc>popmax) kc=popmax;
			kraj[0][a]=ka;
			kraj[1][a]=kc;
			
		}
		
		 ile[0][i]=0;
		ile[1][i]=0;
	
		 z=0;
		 cz=0;
		#pragma omp parallel for default(shared) private(j)  schedule(guided)  reduction(+:z) reduction(+:cz)
		
			
			for( j=0;j<N;j++){
				 z+=kraj[0][j];
				 cz+=kraj[1][j];
			}
		
		
		ile[0][i]+=z;
		ile[1][i]+=cz;
		ile[0][i]/=(N);
		ile[1][i]/=(N);
		 stdevz=0;
		 stdevc=0;
		#pragma omp parallel for default(shared) private(j)  schedule(guided)  reduction(+:stdevz) reduction(+:stdevc)
		

		for( j=0;j<N;j++){
			stdevz+=(kraj[0][j]-ile[0][i])*(kraj[0][j]-ile[0][i]);
			stdevc+=(kraj[1][j]-ile[1][i])*(kraj[1][j]-ile[1][i]);
		}
		
		
		ile[2][i]=stdevz/((double)(N-1));
		ile[3][i]=stdevc/((double)(N-1));
	}
	double tio = e_t(); // stop timing
    printf("# czas liczenia: %f sec\n", tio);
	i=0;
	printf("krok \t zielony \t czerwony \t stdev(z) \t stdev(cz) \n");
	for(i=0;i<kroki;i++){
		printf(" %d \t %0.f \t %0.f \t %0.2f \t %0.2f \n",i,ile[0][i],ile[1][i],sqrt(ile[2][i]),sqrt(ile[3][i]));
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
