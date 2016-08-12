#include "localisation.h"

#define A 5 //distance entre balises 0 et 1, 2 et 3
#define B 4 //distance entre balises 1 et 2, 0 et 3
#define N 3.5
#define A_REF 50.0

int closest_devices(Marker *dist, Marker* closest){
	int i;
	int min=0;
	for(i=1;i<4;i++){
		if(dist[i].rssi < dist[min].rssi)
			min=i;
	}
	printf("farther marker : n°%d\n", min);
	switch(min){
		case 0 : 
			closest[0]=dist[1];
			closest[1]=dist[2];
			closest[2]=dist[3];
			break;

		case 1:
			closest[0]=dist[0];
                        closest[1]=dist[2];
                        closest[2]=dist[3];
                        break;

		case 2:
			closest[0]=dist[0];
                        closest[1]=dist[1];
                        closest[2]=dist[3];
                        break;

		case 3:
			closest[0]=dist[0];
                        closest[1]=dist[1];
                        closest[2]=dist[2];
                        break;
	}
	return min;	
}

void rssi_to_distance(Marker* tab){
	int i;
	for(i=0;i<6;i++){
		float expo=(-A_REF - tab[i].rssi)/(N*10);
		tab[i].dist=pow(10.0,expo);
	}
}

void distance_to_rssi(Marker* tab){
	int i;
	for(i=0;i<3;i++)
		tab[i].rssi=(-10.0*N)*log(tab[i].dist)-A_REF;
}

void init_marker(Marker *bal, int num){
	switch(num){
		case 0:
			(*bal).num=num;
			(*bal).coor.x=0;
			(*bal).coor.y=0;
			(*bal).rssi=0;
			(*bal).dist=0.0;
			break;

		case 1:
                        (*bal).num=num;
                        (*bal).coor.x=0;
                        (*bal).coor.y=A;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;

		case 2:
                        (*bal).num=num;
                        (*bal).coor.x=B;
                        (*bal).coor.y=A;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;

		case 3:
                        (*bal).num=num;
                        (*bal).coor.x=B;
                        (*bal).coor.y=0;
                        (*bal).rssi=0;
                        (*bal).dist=0.0;
                        break;
	}
}

void init_markers(Marker *dist){
	int i;
	for(i=0;i<4;i++)
		init_marker(&dist[i],i);
}

void print_markers(Marker *tab, int size){
	int i;
	for(i=0;i<size;i++)
		printf("balise %d, x=%f, y=%f, rssi=%d, dist=%f m\n",tab[i].num,tab[i].coor.x,tab[i].coor.y,tab[i].rssi,tab[i].dist);
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

void trilateration(Marker *markers, Coordinates *res1, Coordinates *res2, Coordinates *res3,Coordinates *res4){
	

	float a01,b01,a02,b02,a13,b13,a03,b03;

	int i;

	a01 = (markers[0].coor.x - markers[1].coor.x)/(markers[1].coor.y - markers[0].coor.y);

	b01 = (square(markers[1].coor.x)+square(markers[1].coor.y)+square(markers[0].dist)-square(markers[1].dist)-square(markers[0].coor.x)-square(markers[0].coor.y))/(2*(markers[1].coor.y - markers[0].coor.y));

	printf("cercle 0 et 1 : y=%f*x+%f\n",a01,b01);

	a02 = (markers[0].coor.x - markers[2].coor.x)/(markers[2].coor.y - markers[0].coor.y);

	b02 = (square(markers[2].coor.x)+square(markers[2].coor.y)+square(markers[0].dist)-square(markers[2].dist)-square(markers[0].coor.x)-square(markers[0].coor.y))/(2*(markers[2].coor.y - markers[0].coor.y));

	printf("cercle 0 et 2 : y=%f*x+%f\n",a02,b02);

	a13 = (markers[1].coor.x - markers[3].coor.x)/(markers[3].coor.y - markers[1].coor.y);

	b13 = (square(markers[3].coor.x)+square(markers[3].coor.y)+square(markers[1].dist)-square(markers[3].dist)-square(markers[1].coor.x)-square(markers[1].coor.y))/(2*(markers[3].coor.y - markers[1].coor.y));

	printf("cercle 1 et 3 : y=%f*x+%f\n",a13,b13);

	b03 = -(square(markers[3].coor.x) + square(markers[3].coor.y)+square(markers[0].dist)-square(markers[3].dist)-square(markers[0].coor.x)-square(markers[0].coor.y))/(2*(markers[0].coor.x - markers[3].coor.x));

	printf("cercle 0 et 3 : x = %f\n",b03);



	//points d'intersection des trois droites précédentes entre elles

	(*res1).x=(b02-b01)/(a01-a02);
	(*res1).y=a01*(*res1).x + b01;

	(*res2).x=(b01-b13)/(a13-a01);
	(*res2).y=a01*(*res2).x + b01;

	(*res3).x=(b02-b13)/(a13-a02);
	(*res3).y=a02*(*res3).x + b02;

	(*res4).x=b03;
	(*res4).y=0.0;
}
