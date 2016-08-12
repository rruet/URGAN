#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct coo{
	float x;
	float y;
}Coordinates;

typedef struct bal{
	int num;
	Coordinates coor;
	int rssi;
	float dist;
}Marker;

int closest_devices(Marker *dist, Marker* closest);
void rssi_to_distance(Marker *tab);
void distance_to_rssi(Marker* tab);
void init_marker(Marker* bal, int num);
void init_markers(Marker *);
void print_markers(Marker *tab, int size);
float square(float a);
//void trilateration(Marker *markers, Coordinates *b0_1, Coordinates *b1_2, Coordinates *b2_3, Coordinates *b3_0);
void trilateration(Marker *markers, Coordinates *res1,Coordinates *res2, Coordinates *res3, Coordinates *res4);
