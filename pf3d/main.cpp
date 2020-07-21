// main.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "pf3d.h"
#include "size.h"

int main(int argc, char* argv[])
{
	pf3d pf;

	// get the angle of an object
	pf.get_yn();

	// trace the object
	pf.estimate_pariticle_3d(); 

	printf("Well Done!\n");

	return 0;
}
