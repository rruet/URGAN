#include <string.h>
#include <stdlib.h>
#include "localisation2.h"

int main(void){
	
	int cpt;
	char line[SIZE];
	char *rssis;
	const char *id;
	int i,j,k; 
	float tmp;
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

	//matrice qui memorisera pour chaque badge les distances calculees a partir des rssis recus

	float avg_badge[N_BADGE][N_BALISES];

	for(i=0;i<N_BADGE;i++){
		for(j=0;j<N_BALISES;j++)
				avg_badge[i][j]=0.0;
	}

	//tableau qui memorisera l'indice de la derniere distance recuperee pour chaque badge

	int cpt_badge[N_BADGE];


	//tableau qui memorisera si c'est le premier echantillonage du badge. si oui, on prend dix echantillons avant d'effectuer la moyenne,
	//sinon, on applique la fenetre glissante.

	int first_sampling[N_BADGE];
	
	for(i=0;i<N_BADGE;i++){
		cpt_badge[i]=0;
		first_sampling[i]=1;
	}
	//initialisation des structures 'marker' correspondants aux balises

	printf("Reading configuration file ...\n");

	init_markers(dist);

	printf("-->Configuration saved\n");
//	print_markers(dist,N_BALISES);
	
	
	//On recupere en continu la ligne inscrite par la rfduino sur le port USB0. 
	//On incrementera la somme des rssis, pour le badge concerne, jusqu'a atteindre
 	//10 echantillons, avant d'effectuer la premiere moyenne, puis faire une fenetre glissante ensuite.
	
	printf("calculating positions ...\n");

	while(1){
		fgets(line,SIZE*sizeof(char),f);
		id=strtok(line,";");
//		printf("id badge : %s\n",id);
		
		rssis=strtok(NULL,"\n");
//		printf("%s\n",rssis);
		sscanf(rssis,"%d %d %d %d %d %d %d %d\n",&dist[0].rssi,&dist[1].rssi,&dist[2].rssi,&dist[3].rssi,&dist[4].rssi,&dist[5].rssi,&dist[6].rssi,&dist[7].rssi);
//		print_markers(dist,N_BALISES);
	
		rssi_to_distance(dist);

		//on incremente la valeur totale de rssis recu pour le badge id
		
		avg_badge[id[0]-97][cpt_badge[id[0]-97]]=avg_badge[id[0]-97][cpt_badge[id[0]-97]]+dist[cpt_badge[id[0]-97]].dist;
		cpt_badge[id[0]-97]++;

//		printf("rssi to distance conversion : \n\n");
//		print_markers(dist,N_BALISES);


		//Une fois qu'on a 10 echantillons, on calcule la distance moyenne de chaque balise avec le badge
		if((cpt_badge[id[0]-97] == NB_CYCLES)||(first_sampling[id[0]-97]==0)){
			
			for(i=0;i<N_BALISES;i++){
				avg_badge[id[0]-97][i]=avg_badge[id[0]-97][i]/NB_CYCLES;
//				printf("balise %d => moyenne : %f\n",i,avg_badge[id[0]-97][i]);  
				dist[i].dist=avg_badge[id[0]-97][i];
			}
	
			//on modifie dist pour qu'elle comporte les 4 balises les plus proches en première position et pour effectuer la trilateration sur ces dernieres.
	
			for(i=0;i<4;i++){
				devices_sorted(dist,closest,i);
//				printf("min[%d] = %d\n",i,closest[i]);
			}
	
//			print_markers(dist,N_BALISES);

			trilateration(dist,&area[0],&area[1],&area[2],&area[3],&area[4]);


//			printf("\nArea of the badge : (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) \n",area[0].x,area[0].y,area[1].x,area[1].y,area[2].x,area[2].y,area[3].x,area[3].y,area[4].x,area[4].y);

			int n=5;

			//On verifie que les coordonnees ne sont pas negatives, infinies, ou  hors de la page. Sinon on les annule et on calcule le barycentre sur les n-i restantes (i=nb de coordonnees neg ou inf)

			for(i=0;i<5;i++){
				if((isfinite(area[i].x) == 0) || (isfinite(area[i].y) == 0) || area[i].x <0 || area[i].y <0 || area[i].x>2000 || area[i].y>1000){
					area[i].x = 0;
					area[i].y = 0;
					n--;		
				} 	
			}

//			printf("n = %d\n", n);

//			printf("\nNew area of the badge : (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) \n",area[0].x,area[0].y,area[1].x,area[1].y,area[2].x,area[2].y,area[3].x,area[3].y,area[4].x,area[4].y);


			//On calcule le barycentre a partir des coordonnees que la trilateration nous renvoit

			area[0].x=(area[0].x+area[1].x+area[2].x+area[3].x+area[4].x)/n;
			area[0].y=(area[0].y+area[1].y+area[2].y+area[3].y+area[4].y)/n;

//			printf("barycenter : (%f,%f)\n",area[0].x,area[0].y);
	
			FILE *f2;

			//On test l'id pour savoir dans quel fichier ecrire les coordonnees finales

			if(strcmp(id,"a") == 0){
	                	f2=fopen(BADGE_A,"w");
			}else if(strcmp(id,"b") == 0){
				f2=fopen(BADGE_B,"w");
			}
	
			//....refaire autant de 'else if' qu'il y a de badges en plus
		
			if(f2 == NULL){
				printf("erreur ouverture fichier de badge\n");
				exit(0);			
			}
		
			//On ecrit ensuite les coordonnees finales dans le fichier du badge concerne

			fprintf(f2,"%f,%f\n",area[0].x,area[0].y);
	        	fclose(f2);
			cpt_badge[id[0]-97]=0;
			printf("badge %s : (%f,%f)\n",id,area[0].x,area[0].y);
		}
	
		my_delay(1);
	
	}
	
		free(dist);
		free(area);
		fclose(f);
		
		return 0;
}
