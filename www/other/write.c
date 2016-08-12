#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void my_delay(int i)    /*Pause l'application pour i seconds*/
{
    clock_t start,end;
    start=clock();
    while(((end=clock())-start)<=i*CLOCKS_PER_SEC);
}

int main(void){

	FILE  *f;
	int choix=0;	

	while(1){

		f=fopen("coor.txt","a+");

		if(f==NULL){
			printf("erreur ouverture fichier!\n");
			exit(0);
		}

		switch(choix){
			case 0:
				fputs("2.1,3.2;2.0,4.0\n",f);
				choix=1;
				break;
			case 1:
				fputs("6.0,1.54;3.0,4.0\n",f);
				choix=2;
				break;
			case 2:
				fputs("3.0,2.0;7.0,0.2\n",f);
				choix=0;
				break;	
		}
		my_delay(3);
		

		fclose(f);
	}

	return 0;
}
