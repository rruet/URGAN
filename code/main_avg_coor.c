#include <string.h>
#include <stdlib.h>
#include "urgan.h"

int main(void){
	
	char line[SIZE];
	char *rssis;
	const char *id;
	int i; 
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

	//tableaux qui memoriseront pour chaque badge les coordonnees calcules a partir des rssis recus

	float avg_badgex[N_BADGE];
	float avg_badgey[N_BADGE];

	for(i=0;i<N_BADGE;i++){
				avg_badgex[i]=0.0;
				avg_badgey[i]=0.0;
	}

	//tableau qui memorisera l'indice de la derniere distance recuperee pour chaque badge

	int cpt_badge[N_BADGE];


	//tableau qui memorisera si c'est le premier echantillonage du badge. si oui, on prend dix echantillons avant d'effectuer la moyenne,
	//sinon, on applique la fenetre glissante.

	for(i=0;i<N_BADGE;i++){
		cpt_badge[i]=0;
	}
	//initialisation des structures 'marker' correspondants aux balises

	printf("Reading configuration file -----------");

	init_markers(dist);

	printf("---------------> Configuration saved\n");
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

		for(i=0;i<4;i++){
                                devices_sorted(dist,closest,i);
  //                            printf("min[%d] = %d\n",i,closest[i]);
                }


		//printf("rssi to distance conversion : \n\n");
		//print_markers(dist,N_BALISES);


		trilateration(dist,&area[0],&area[1],&area[2],&area[3],&area[4]);


              //printf("\nArea of the badge : (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) \n",area[0].x,area[0].y,area[1].x,area[1].y,area[2].x,area[2].y,area[3].x,area[3].y,area[4].x,area[4].y);

                int n=5;

                //On verifie que les coordonnees ne sont pas negatives, infinies, ou  hors de la page. Sinon on les annule et on calcule le barycentre sur les n-i restantes (i=nb de coordonnees neg ou inf)

                for(i=0;i<5;i++){
                        if((isfinite(area[i].x) == 0) || (isfinite(area[i].y) == 0) || area[i].x <0 || area[i].y <0 || area[i].x>2000 || area[i].y>1000){
                                   area[i].x = 0;
                                   area[i].y = 0;
                                   n--;
                            }
                 }

               //printf("n = %d\n", n);

               //printf("\nNew area of the badge : (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) | (%f,%f) \n",area[0].x,area[0].y,area[1].x,area[1].y,area[2].x,area[2].y,area[3].x,area[3].y,area[4].x,area[4].y);


                 //On calcule le barycentre a partir des coordonnees que la trilateration nous renvoit

                 area[0].x=(area[0].x+area[1].x+area[2].x+area[3].x+area[4].x)/n;
                 area[0].y=(area[0].y+area[1].y+area[2].y+area[3].y+area[4].y)/n;


    //           printf("barycenter : (%f,%f)\n",area[0].x,area[0].y);

		avg_badgex[id[0]-97]+=area[0].x;
		avg_badgey[id[0]-97]+=area[0].y;
		cpt_badge[id[0]-97]++;


		//Une fois qu'on a 10 echantillons, on calcule la distance moyenne de chaque balise avec le badge
		if(cpt_badge[id[0]-97] == NB_CYCLES){
			
			for(i=0;i<N_BADGE;i++){
				area[0].x=avg_badgex[id[0]-97]/NB_CYCLES;
				area[0].y=avg_badgey[id[0]-97]/NB_CYCLES;
			}
	
			//on modifie dist pour qu'elle comporte les 4 balises les plus proches en première position et pour effectuer la trilateration sur ces dernieres.
	
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
			avg_badgex[id[0]-97]=0;
			avg_badgey[id[0]-97]=0;
			printf("badge %s : (%f,%f)\n",id,area[0].x,area[0].y);
		}
	
		my_delay(1);
	
	}
	
		free(dist);
		free(area);
		fclose(f);
		
		return 0;
}
