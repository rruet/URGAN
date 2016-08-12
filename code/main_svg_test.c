#include <string.h>
#include "urgan.h"

#define FILES "/var/www/html/files/test6_0408.txt" 

int main(void){
	
	int cpt=NB_CYCLES;
	char line[SIZE];
	char *rssis;
	char *id;
	int first=1;
	float average[N_BALISES];
	float min[N_BALISES];
	float max[N_BALISES]; 
	int closest[4];
	FILE *f=fopen("/dev/ttyUSB0","r+");
	
	if(f == NULL){
		printf("erreur ouverture fichier USB0\n");
		exit(0);
	}

	Marker* dist=malloc(N_BALISES*sizeof(Marker));
	if(dist ==NULL){	
		printf("erreur allocation 1\n");
		exit(0);
	}

	Coordinates *area=malloc(5*sizeof(Coordinates));
	if(area==NULL){
		printf("erreur allocation tableau de coordonnees\n");
		exit(0);
	}


	init_markers(dist);
	print_markers(dist,N_BALISES);
	
	int i;
	for(i=0;i<N_BALISES;i++){
		average[i]=0.0;
		min[i]=0.0;
		max[i]=0.0;
	}
	
	while(cpt){

		FILE* f2=fopen(FILES,"a+");

	        if(f2==NULL){
        	        printf("erreur fichier coordonnees badge a\n");
                	exit(0);
       		 }

			
		fgets(line,SIZE*sizeof(char),f);
		//printf("%s taille : %d\n",line,strlen(line));
		id=strtok(line,";");
		printf("id badge : %s\n",id);
		rssis=strtok(NULL,"\n");
		printf("%s\n",rssis);

		sscanf(rssis,"%d %d %d %d %d %d %d %d\n",&dist[0].rssi,&dist[1].rssi,&dist[2].rssi,&dist[3].rssi,&dist[4].rssi,&dist[5].rssi,&dist[6].rssi,&dist[7].rssi);

		//farther_marker=closest_devices(dist,closest);

		//printf("three closest devices: \n\n");

		print_markers(dist,N_BALISES);
	
		rssi_to_distance(dist);

		if(first){
			for(i=0;i<N_BALISES;i++)
				min[i]=dist[i].dist;
			first=0;
		}

		for(i=0;i<N_BALISES;i++){
			average[i]=average[i]+dist[i].dist;
			if(dist[i].dist>=max[i])
				max[i]=dist[i].dist;
			if(dist[i].dist<= min[i])
				min[i]=dist[i].dist;
		}

		printf("rssi to distance conversion : \n\n");

		print_markers(dist,N_BALISES);
		
		fprintf(f2,"%f,%f,%f,%f,%f,%f,%f,%f\n",dist[0].dist,dist[1].dist,dist[2].dist,dist[3].dist,dist[4].dist,dist[5].dist,dist[6].dist,dist[7].dist);

		fclose(f2);
		
		cpt--;
			
		my_delay(1);	
	}

	for(i=0;i<N_BALISES;i++){
		average[i]=average[i]/NB_CYCLES;
		printf("balise %d => moyenne : %f | min : %f | max : %f\n",i,average[i],min[i],max[i]);  

		FILE * f2=fopen(FILES,"a+");

	        if(f2==NULL){
        	        printf("erreur ouverture fichier fin\n");
                	exit(0);
        	}

		fprintf(f2,"%f,%f,%f,",average[i],min[i],max[i]);

		dist[i].dist=average[i];

		fclose(f2);	
	}
	
	//on modifie dist pour qu'elle comporte les 4 balises les plus proches en première position et pour effectuer la trilateration sur ces dernieres.
	
	for(i=0;i<4;i++){
		devices_sorted(dist,closest,i);
		printf("min[%d] = %d\n",i,closest[i]);
	}
	
	print_markers(dist,N_BALISES);

	trilateration(dist,&area[0],&area[1],&area[2],&area[3],&area[4]);


	printf("\nArea of the badge : (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) \n",area[0].x,area[0].y,area[1].x,area[1].y,area[2].x,area[2].y,area[3].x,area[3].y,area[4].x,area[4].y);

	int n=5;

	for(i=0;i<5;i++){
		if((isfinite(area[i].x) == 0) || (isfinite(area[i].y) == 0) || area[i].x <0 || area[i].y <0){
			area[i].x = 0;
			area[i].y = 0;
			n--;		
		} 	
	}

	printf("n = %d\n", n);

	printf("\nNew area of the badge : (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) \n",area[0].x,area[0].y,area[1].x,area[1].y,area[2].x,area[2].y,area[3].x,area[3].y,area[4].x,area[4].y);


	FILE *f2=fopen(FILES,"a+");
        //fprintf(f2,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,",area[0].x,area[0].y,area[1].x,area[1].y,area[2].x,area[2].y,area[3].x,area[3].y,area[4].x,area[4].y);


	//barycenter of the points

	area[0].x=(area[0].x+area[1].x+area[2].x)/3;
	area[0].y=(area[0].y+area[1].y+area[2].y)/3;

	printf("barycenter : (%f,%f)\n",area[0].x,area[0].y);
	
	fprintf(f2,"%f,%f\n",area[0].x,area[0].y);
	fclose(f2);

	free(dist);
	free(area);
	fclose(f);
		
	return 0;
}
