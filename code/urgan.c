#include "urgan.h"

#define N 3.5
#define A_REF 50.0
#define SIZE_M 100

float scale;

void my_delay(int i)    /*Pause l'application pour i seconds*/
{
    clock_t start,end;
    start=clock();
    while(((end=clock())-start)<=i*CLOCKS_PER_SEC);
}


void devices_sorted(Marker *dist, int min[], int cpt){

	int i;
	int mini=cpt;
	Marker aux;

	for(i=cpt+1;i<N_BALISES;i++){
		if(dist[mini].dist >= dist[i].dist){
			mini=i;					
		}
	}
	min[cpt]=mini;
	aux=dist[mini];
	dist[mini]=dist[cpt];
	dist[cpt]=aux;
}

void rssi_to_distance(Marker* tab){
	int i;
	for(i=0;i<N_BALISES;i++){
		float expo=(-A_REF - tab[i].rssi)/(N*10);
		tab[i].dist=pow(10.0,expo)*100;
	}
}

void distance_to_rssi(Marker* tab){
	int i;
	for(i=0;i<N_BALISES;i++)
		tab[i].rssi=(-10.0*N)*log(tab[i].dist)-A_REF;
}

void init_marker(Marker *bal, int num){


	float xb0,yb0,xb1,yb1,xb2,yb2,xb3,yb3,xb4,yb4,xb5,yb5,xb6,yb6,xb7,yb7;
	FILE *config = fopen("/var/www/html/config.txt","r");
	char line[SIZE_M];
	fgets(line,sizeof(line),config);
	sscanf(line,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",&xb0,&yb0,&xb1,&yb1,&xb2,&yb2,&xb3,&yb3,&xb4,&yb4,&xb5,&yb5,&xb6,&yb6,&xb7,&yb7,&scale);

	switch(num){
		case 0:
			(*bal).num=num;
			(*bal).coor.x=xb0;
			(*bal).coor.y=yb0;
			(*bal).rssi=0;
			(*bal).dist=0.0;
			break;

		case 1:
                        (*bal).num=num;
                        (*bal).coor.x=xb1;
                        (*bal).coor.y=yb1;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;

		case 2:
                        (*bal).num=num;
                        (*bal).coor.x=xb2;
                        (*bal).coor.y=yb2;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;

		case 3:
                        (*bal).num=num;
                        (*bal).coor.x=xb3;
                        (*bal).coor.y=yb3;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;

		case 4:
                        (*bal).num=num;
                        (*bal).coor.x=xb4;
                        (*bal).coor.y=yb4;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;

		case 5:
                        (*bal).num=num;
                        (*bal).coor.x=xb5;
                        (*bal).coor.y=yb5;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;

		case 6:
                        (*bal).num=num;
                        (*bal).coor.x=xb6;
                        (*bal).coor.y=yb6;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;
		
		case 7:
                        (*bal).num=num;
                        (*bal).coor.x=xb7;
                        (*bal).coor.y=yb7;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;


	}

	fclose(config);
}

void init_markers(Marker *dist){
	int i;
	for(i=0;i<N_BALISES;i++)
		init_marker(&dist[i],i);
}

void print_markers(Marker *tab, int size){
	int i;
	for(i=0;i<size;i++)
		printf("balise %d, x=%f, y=%f, rssi=%d, dist=%f cm\n",tab[i].num,tab[i].coor.x,tab[i].coor.y,tab[i].rssi,tab[i].dist);
}

float square(float a){
	return a*a;
}

/*void trilateration(Marker *markers, Coordinates *b0_1, Coordinates *b1_2, Coordinates *b2_3, Coordinates *b3_0){
	
	//float x,y;

	switch(farther_marker){
		case 0:
			x=(square(B)-square(markers[2].dist)+square(markers[1].dist))/(2*B);
			y=(square(markers[2].dist)-square(markers[3].dist)-square(A))/(-2*A);
			break;

		case 1:
			x=(square(B)-square(markers[3].dist)+square(markers[0].dist))/(2*B);
			y=(square(markers[2].dist)-square(markers[3].dist)-square(A))/(-2*A);
			break;

		case 2:
			x=(square(B)-square(markers[3].dist)+square(markers[0].dist))/(2*B);
			y=A/2+(square(markers[0].dist)-square(markers[1].dist))/(2*A);
			break;

		case 3:
			x=(square(B)-square(markers[2].dist)+square(markers[1].dist))/(2*B);
			y=A/2+(square(markers[0].dist)-square(markers[1].dist))/(2*A);
			break;
	}
	
	(*res).x=x;
	(*res).y=y;

	(*b0_1).x=(square(B)-square(markers[2].dist)+square(markers[1].dist))/(2*B);
        (*b0_1).y=(square(markers[2].dist)-square(markers[3].dist)-square(A))/(-2*A);
	(*b1_2).x=(square(B)-square(markers[3].dist)+square(markers[0].dist))/(2*B);
        (*b1_2).y=(square(markers[2].dist)-square(markers[3].dist)-square(A))/(-2*A);
	(*b2_3).x=(square(B)-square(markers[3].dist)+square(markers[0].dist))/(2*B);
        (*b2_3).y=A/2+(square(markers[0].dist)-square(markers[1].dist))/(2*A);
	(*b3_0).x=(square(B)-square(markers[2].dist)+square(markers[1].dist))/(2*B);
        (*b3_0).y=A/2+(square(markers[0].dist)-square(markers[1].dist))/(2*A);



}*/

void trilateration(Marker *markers, Coordinates *res1, Coordinates *res2, Coordinates *res3, Coordinates *res4, Coordinates * res5){
	

	float a01,b01,a02,b02,a12,b12,a23,b23,a13,b13,a03,b03;

	a01 = (markers[0].coor.x - markers[1].coor.x)/(markers[1].coor.y - markers[0].coor.y);

	b01 = (square(markers[1].coor.x)+square(markers[1].coor.y)+square(markers[0].dist*scale/100)-square(markers[1].dist*scale/100)-square(markers[0].coor.x)-square(markers[0].coor.y))/(2*(markers[1].coor.y - markers[0].coor.y));

//	printf("cercle %d et %d : y=%f*x+%f\n",markers[0].num,markers[1].num,a01,b01);

	a02 = (markers[0].coor.x - markers[2].coor.x)/(markers[2].coor.y - markers[0].coor.y);

	b02 = (square(markers[2].coor.x)+square(markers[2].coor.y)+square(markers[0].dist*scale/100)-square(markers[2].dist*scale/100)-square(markers[0].coor.x)-square(markers[0].coor.y))/(2*(markers[2].coor.y - markers[0].coor.y));

//	printf("cercle %d et %d : y=%f*x+%f\n",markers[0].num,markers[2].num,a02,b02);

	a13 = (markers[1].coor.x - markers[3].coor.x)/(markers[3].coor.y - markers[1].coor.y);

	b13 = (square(markers[3].coor.x)+square(markers[3].coor.y)+square(markers[1].dist*scale/100)-square(markers[3].dist*scale/100)-square(markers[1].coor.x)-square(markers[1].coor.y))/(2*(markers[3].coor.y - markers[1].coor.y));

//	printf("cercle %d et %d : y=%f*x+%f\n",markers[1].num,markers[3].num,a13,b13);

	a03 = (markers[0].coor.x - markers[3].coor.x)/(markers[3].coor.y - markers[0].coor.y);

	b03 = -(square(markers[3].coor.x) + square(markers[3].coor.y)+square(markers[0].dist*scale/100)-square(markers[3].dist*scale/100)-square(markers[0].coor.x)-square(markers[0].coor.y))/(2*(markers[0].coor.x - markers[3].coor.x));

//	printf("cercle %d et %d : x =%f*x+%f\n",markers[0].num,markers[3].num,a03,b03);

	a12 = (markers[1].coor.x - markers[2].coor.x)/(markers[2].coor.y - markers[1].coor.y);

        b12 = -(square(markers[2].coor.x) + square(markers[2].coor.y)+square(markers[1].dist*scale/100)-square(markers[2].dist*scale/100)-square(markers[1].coor.x)-square(markers[1].coor.y))/(2*(markers[1].coor.x - markers[2].coor.x));

  //      printf("cercle %d et %d : x =%f*x+%f\n",markers[1].num,markers[2].num,a12,b12);
	
	a23 = (markers[2].coor.x - markers[3].coor.x)/(markers[3].coor.y - markers[2].coor.y);

        b23 = -(square(markers[3].coor.x) + square(markers[3].coor.y)+square(markers[2].dist*scale/100)-square(markers[3].dist*scale/100)-square(markers[2].coor.x)-square(markers[2].coor.y))/(2*(markers[2].coor.x - markers[3].coor.x));

//        printf("cercle %d et %d : x =%f*x+%f\n",markers[2].num,markers[3].num,a23,b23);



	//points d'intersection des six droites précédentes entre elles

	(*res1).x=(b02-b01)/(a01-a02);
	(*res1).y=a01*(*res1).x + b01;

	(*res2).x=(b01-b13)/(a13-a01);
	(*res2).y=a01*(*res2).x + b01;

	(*res3).x=(b02-b13)/(a13-a02);
	(*res3).y=a02*(*res3).x + b02;

	(*res4).x=(b02-b23)/(a23-a02);
	(*res4).y=a02*(*res4).x + b02;

	(*res5).x=(b12-b23)/(a23-a12);
	(*res5).y=a12*(*res5).x + b12;

}
