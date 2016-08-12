#include <string.h>
#include "localisation.h"

#define SIZE 55

void my_delay(int i)    /*Pause l'application pour i seconds*/
{
    clock_t start,end;
    start=clock();
    while(((end=clock())-start)<=i*CLOCKS_PER_SEC);
}

int main(void){
	
	char line[SIZE];
	char *rssis;
	float rssi_org[4];
	int farther_marker;
	FILE *f=fopen("/dev/ttyUSB0","r+");
	
	if(f == NULL){
		printf("erreur ouverture fichier USB0\n");
		exit(0);
	}

	Marker* dist=malloc(4*sizeof(Marker));
	if(dist ==NULL){	
		printf("erreur allocation 1\n");
		exit(0);
	}

	Marker *closest=malloc(3*sizeof(Marker));
	if (closest==NULL){
		printf("erreur allocation 2\n");
		exit(0);
	}

	Coordinates *coor=malloc(sizeof(Coordinates));
	if (coor==NULL){
		printf("erreur allocation 3\n");
		exit(0);
	}
	
	init_markers(dist);
	print_markers(dist,4);
	
	while(1){

		FILE* f2=fopen("/var/www/html/coor.txt","a+");
		printf("f2 opened\n");

	        if(f2==NULL){
        	        printf("erreur ouverture fichier de coordonnees\n");
                	exit(0);
       		 }

			
		fgets(line,SIZE*sizeof(char),f);
		printf("fgets\n");
		//printf("%s taille : %d\n",line,strlen(line));
		strtok(line,";");
		rssis=strtok(NULL,"\n");
		printf("strtok\n");
		printf("%s\n",rssis);

		sscanf(rssis,"%f %f %f %f %f %f %f %f\n",&dist[0].rssi,&dist[1].rssi,&dist[2].rssi,&dist[3].rssi,&rssi_org[0],&rssi_org[1],&rssi_org[2],&rssi_org[3]);

		farther_marker=closest_devices(dist,closest);

		printf("three closest devices: \n\n");

		print_markers(closest,3);
	
		rssi_to_distance(closest);

		printf("rssi to distance conversion : \n\n");

		print_markers(closest,3);
		printf("rssi origins : %d %d %d %d\n",rssi_org[0],rssi_org[1],rssi_org[2],rssi_org[3]);

		trilateration(closest,farther_marker,coor);

		printf("\nCoordinates of the badge : (%f,%f)\n",(*coor).x,(*coor).y);
		fprintf(f2,"%f,%f;0.0,0.0;%f,%f,%f,%f,%f,%f,%f,%f\n",(*coor).x,(*coor).y,rssi_org[0],rssi_org[1],rssi_org[2],rssi_org[3],dist[0].rssi,dist[1].rssi,dist[2].rssi,dist[3].rssi);
		
		fclose(f2);
		printf("f2 ferme\n");
		my_delay(1);
		printf("delay\n");	
	}
	free(dist);
	free(closest);
	free(coor);
	fclose(f);
		
	return 0;
}
