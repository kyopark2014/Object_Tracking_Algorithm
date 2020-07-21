// main.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "pf2d.h"
#include "size.h"

int main(int argc, char* argv[])
{
	int i;

	pf2d pf;

	// get the angle of an object
	pf.get_yn();

	FILE *fp;
	fp = fopen("yn.txt","w"); 
	for(i=0;i<Nt;i++) 
		fprintf(fp,"%f\n",pf.yn[i]*180/pi);
	fclose(fp);

	// trace the object
	pf.estimate_pariticle_2d(); 

	printf("Well Done!\n");

	return 0;
}
