#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N_BALISES 8
#define SIZE 60
#define NB_CYCLES 10
#define N_BADGE 2
#define BADGE_A "/var/www/html/files/badge_a.txt"
#define BADGE_B "/var/www/html/files/badge_b.txt" 

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

void devices_sorted(Marker *dist,int min[], int i);
void rssi_to_distance(Marker *tab);
void distance_to_rssi(Marker* tab);
void init_marker(Marker* bal, int num);
void init_markers(Marker *);
void print_markers(Marker *tab, int size);
float square(float a);
//void trilateration(Marker *markers, Coordinates *b0_1, Coordinates *b1_2, Coordinates *b2_3, Coordinates *b3_0);
void trilateration(Marker *markers, Coordinates *res1,Coordinates *res2, Coordinates *res3, Coordinates *res4, Coordinates *res5);
void my_delay(int i);
