#include <string.h>
#include "localisation2.h"

#define SIZE 60
#define MAX_DEV 6

void my_delay(int i)    /*Pause l'application pour i seconds*/
{
    clock_t start,end;
    start=clock();
    while(((end=clock())-start)<=i*CLOCKS_PER_SEC);
}

int main(void){
	
	char line[SIZE];
	char *rssis;
	char *id;
	int rssi_org[MAX_DEV];
	int farther_marker;
	FILE *f=fopen("/dev/ttyUSB0","r+");
	
	if(f == NULL){
		printf("erreur ouverture fichier USB0\n");
		exit(0);
	}

	Marker* dist=malloc(MAX_DEV*sizeof(Marker));
	if(dist ==NULL){	
		printf("erreur allocation 1\n");
		exit(0);
	}

	Coordinates *coor1=malloc(sizeof(Coordinates));
	if (coor1==NULL){
		printf("erreur allocation 2\n");
		exit(0);
	}

	Coordinates *coor2=malloc(sizeof(Coordinates));
        if (coor2==NULL){
                printf("erreur allocation 3\n");
                exit(0);
        }

	Coordinates *coor3=malloc(sizeof(Coordinates));
        if (coor3==NULL){
                printf("erreur allocation 4\n");
                exit(0);
        }

	Coordinates *coor4=malloc(sizeof(Coordinates));
        if (coor4==NULL){
                printf("erreur allocation 5\n");
                exit(0);
        }


	init_markers(dist);
	print_markers(dist,MAX_DEV);
	
	while(1){

		FILE* f2=fopen("/var/www/html/coor.txt","a+");

	        if(f2==NULL){
        	        printf("erreur fichier coordonnees badge a\n");
                	exit(0);
       		 }

		FILE* f3=fopen("/var/www/html/coorb.txt","a+");

		if(f3==NULL){
			printf("erreur fichier coordonnees badge b\n");
			exit(0);
		}

			
		fgets(line,SIZE*sizeof(char),f);
		//printf("%s taille : %d\n",line,strlen(line));
		id=strtok(line,";");
		printf("id badge : %s\n",id);
		rssis=strtok(NULL,"\n");
		printf("%s\n",rssis);

		sscanf(rssis,"%d %d %d %d %d %d %d %d %d %d %d %d\n",&dist[0].rssi,&dist[1].rssi,&dist[2].rssi,&dist[3].rssi,&dist[4].rssi,&dist[5].rssi,&rssi_org[0],&rssi_org[1],&rssi_org[2],&rssi_org[3],&rssi_org[4],&rssi_org[5]);

		rssi_to_distance(dist);

		printf("rssi to distance conversion : \n\n");

		print_markers(dist,MAX_DEV);
		printf("rssi origins : %d %d %d %d %d %d\n",rssi_org[0],rssi_org[1],rssi_org[2],rssi_org[3], rssi_org[4], rssi_org[5]);

		trilateration(dist,coor1,coor2,coor3,coor4);

		printf("\nArea of the badge : (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f)\n",(*coor1).x,(*coor2).y,(*coor2).x,(*coor2).y,(*coor3).x,(*coor3).y,(*coor4).x,(*coor4).y);
		
		if(strcmp(id,"a")==0){
			fprintf(f2,"%f,%f;%f,%f;%f,%f;%f,%f;%d,%d,%d,%d,%d,%d,%d,%d\n",(*coor1).x,(*coor1).y,(*coor2).x,(*coor2).y,(*coor3).x,(*coor3).y,(*coor4).x,(*coor4).y,rssi_org[0],rssi_org[1],rssi_org[2],rssi_org[3],dist[0].rssi,dist[1].rssi,dist[2].rssi,dist[3].rssi);
		}
		
		if(strcmp(id,"b")==0){
			fprintf(f3,"%f,%f;%f,%f;%f,%f;%f,%f;%d,%d,%d,%d,%d,%d,%d,%d\n",(*coor1).x,(*coor1).y,(*coor2).x,(*coor2).y,(*coor3).x,(*coor3).y,(*coor4).x,(*coor4).y,rssi_org[0],rssi_org[1],rssi_org[2],rssi_org[3],dist[0].rssi,dist[1].rssi,dist[2].rssi,dist[3].rssi);

		}

		fclose(f2);
		fclose(f3);

		my_delay(1);	
	}
	free(dist);
	free(coor1);
	free(coor2);
	free(coor3);
	free(coor4);
	fclose(f);
		
	return 0;
}
