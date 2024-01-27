/*
 *  gcc main.c -o main -lm -O3 -fopenmp -std=c99
 * 	 mpicc mainmpi.c -o main -lm -O3 -Wall
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "mct_utils.h"
#include <math.h>
#include <omp.h>
#include <mpi.h>
  int **kraj;
  double rozm[2];
   double ag[2];
   int N;
   double **ile;
#define popmax 10000
/**
 * Function for uniform distribution of array elemnts
 * @param ip index of MPI process
 * @param np number of MPI processes 
 * @param N number of array elements
 * @return chunk size
 * */
long int getNip( int ip , int np , long int N ) 
{
  long int Nip;
  Nip  = N / np ;
  if ( ip < (N % np) ) Nip++ ;
  return Nip;
}

/**
 * Function for uniform distribution of array elemnts
 * @param ip index of MPI process
 * @param np number of MPI processes 
 * @param N number of array elements
 * @return index of first elemten in global array. 
 * */
long int get_i0( int ip , int np , long int N ) 
{
  long int Nip;
  long int i0=0; 
  int i;
  for(i=0; i<ip; i++)
  {
    Nip  = N / np ;
    if ( i < (N % np) ) Nip++ ;
    i0+=Nip;
  }
  return i0;
}



int main(int argc, char *argv[]){ //N,proc,ag1,ag2,rozm,rozm,kroki, 
	
	if(argc !=8) return 0;
   N=atoi(argv[1]);
  double proc=strtod(argv[2],NULL);
	
  ag[0]=strtod(argv[3],NULL);
  ag[1]=strtod(argv[4],NULL);
   rozm[0]=strtod(argv[5],NULL);
  rozm[1]=strtod(argv[6],NULL);
  int kroki=atoi(argv[7]);
  srand(time(0));
  ile=malloc( 4 * sizeof( double* ) ); 
	 ile[0]=malloc((kroki+1)*sizeof(double));
  ile[1]=malloc((kroki+1)*sizeof(double));
   ile[2]=malloc((kroki+1)*sizeof(double));
     ile[3]=malloc((kroki+1)*sizeof(double));
	
	  // Initilize MPI 
    int ip, np; // basic MPI indicators
    MPI_Init( &argc , &argv ) ; /* set up the parallel WORLD */
    MPI_Comm_size( MPI_COMM_WORLD , &np ) ; /* total number of processes */
    MPI_Comm_rank( MPI_COMM_WORLD , &ip ) ; /* id of process st 0 <= ip < np */   
     long int Nip = getNip(ip , np , N);
    long int i0 = get_i0(ip , np , N);
    //size_t sized = sizeof(double)*Nip;
    size_t sizei=sizeof(int)*Nip;
    
 
	kraj= malloc( 2 * sizeof( int * ) ); 

	kraj[0]= (int*)malloc( sizei );

	kraj[1]= (int*)malloc( sizei );
  
	int i;
	
	int j=0;
	 
  
	
		
	
		
        for( j=0;j<=Nip;j++){
			
            kraj[0][j]=popmax*proc;
            kraj[1][j]=popmax*(1-proc);
		
        }
        
    
     b_t();
	 if(ip == 0){printf("Powstało %d symulacji wypelnionych na %lf zielonym, z ag zielonych = %f, czerwonych =%f, i wspł. rozmnażania ziel= %f i czerw =%f \n",N,proc,ag[0],ag[1],rozm[0],rozm[1]);}
  
    ile[0][0]=0;
	ile[1][0]=0;
	ile[2][0]=0;
		
		double z=0;
		double cz=0;

		
		
		for( j=0;j<Nip;j++){
			
			z+=kraj[0][j];
			cz+=kraj[1][j];
			
		}
		 MPI_Allreduce(&z,&ile[0][0],1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		 MPI_Allreduce(&cz,&ile[1][0],1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
	//	 printf("%f \t",ile[0][0]);
	//	ile[0][0]+=z;
	//	ile[1][0]+=cz;
		ile[0][0]/=(N);
		ile[1][0]/=(N);
		double stdevz=0;
		double stdevc=0;
		
		

		for( j=0;j<Nip;j++){
			stdevz+=(kraj[0][j]-ile[0][0])*(kraj[0][j]-ile[0][0]);
			stdevc+=(kraj[1][j]-ile[1][0])*(kraj[1][j]-ile[1][0]);
		}
		
		 MPI_Allreduce(&stdevz,&ile[2][0],1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		 MPI_Allreduce(&stdevc,&ile[3][0],1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		ile[2][0]=stdevz/((double)(N-1));
		ile[3][0]=stdevc/((double)(N-1));
		double tio = e_t(); // stop timing
   if(ip==0){ printf("# czas liczenia pozycji początkowych: %f sec\n", tio);}
    MPI_Barrier(MPI_COMM_WORLD);
    b_t();
	for( i=1;i<kroki;i++){
		
			int a;
			
		
		for(a=0;a<Nip;a++){
		//	b_t();
			
			int ka=kraj[0][a];
			int kc=kraj[1][a];	
			double chance=(float)rand()/(float)(RAND_MAX);
			double aga=ag[0];
			double agc=ag[1];
			double szaga=aga*((double)(ka-kc))/((double)(ka+kc));
			double szagc=agc*((double)(kc-ka))/((double)(ka+kc));
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
			
			 ka=ka*(1+rozm[0]);
			 kc=kc*(1+rozm[1]);	
			if(ka>popmax) ka=popmax;
			if(kc>popmax) kc=popmax;
			kraj[0][a]=ka;
			kraj[1][a]=kc;
			//double tio = e_t(); // stop timing
			//printf("# czas liczenia wewnatrz kroku %d: %f sec\n", a,tio);
		}
		
		 ile[0][i]=0;
		ile[1][i]=0;
	
		 z=0;
		 cz=0;
		
		
			MPI_Barrier(MPI_COMM_WORLD);
			for( j=0;j<Nip;j++){
				 z+=kraj[0][j];
				 cz+=kraj[1][j];
			}
		 MPI_Allreduce(&z,&ile[0][i],1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		 MPI_Allreduce(&cz,&ile[1][i],1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		
		//ile[0][i]+=z;
	//	ile[1][i]+=cz;
		ile[0][i]/=(N);
		ile[1][i]/=(N);
		 stdevz=0;
		 stdevc=0;
	
		

		for( j=0;j<Nip;j++){
			stdevz+=(kraj[0][j]-ile[0][i])*(kraj[0][j]-ile[0][i]);
			stdevc+=(kraj[1][j]-ile[1][i])*(kraj[1][j]-ile[1][i]);
		}
		 MPI_Allreduce(&stdevz,&ile[2][i],1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		 MPI_Allreduce(&stdevc,&ile[3][i],1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		
		ile[2][i]/=((double)(N-1));
		ile[3][i]/=((double)(N-1));
		
	}
	 tio = e_t(); // stop timing
	 if(ip == 0){
    printf("# czas liczenia: %f sec\n", tio);
	i=0;
	
		printf("krok \t zielony \t czerwony \t stdev(z) \t stdev(cz) \n");
	
		for(i=0;i<kroki;i++){
			printf(" %d \t %0.f \t %0.f \t %0.2f \t %0.2f \n",i,ile[0][i],ile[1][i],sqrt(ile[2][i]),sqrt(ile[3][i]));
		}
	}
	MPI_Finalize();
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
