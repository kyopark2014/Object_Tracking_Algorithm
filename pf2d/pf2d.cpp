// pf2d.cpp: implementation of the pf2d class.
//
//////////////////////////////////////////////////////////////////////

#include "pf2d.h"
#include "math.h"
#include "size.h"
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define randomize() (srand(time(0)))
#define random(x) (rand() %x)

pf2d::pf2d()
{
	int i;

	dt = 1.0;
	ang_error = 0.5/180*pi;

	l0_obj = 20.;
    thetal0_obj = 90./180.*pi;
    r0_obj = 0.5;
    thetar0_obj = 90./180.*pi;
	dr0_obj = 0.1;
	dthetar0_obj = 3./180.*pi; 

/*    l0_obj = 100;
    thetal0_obj = 45./180*pi; 
    r0_obj = 0;
    dr0_obj = 0.; 
    thetar0_obj = 0;
    dthetar0_obj = 0;  */

/*	l0 = l0_obj;
    thetal0 = thetal0_obj;
    r0 = r0_obj;
    thetar0 = thetar0_obj;
	dr0 = dr0_obj;
	dthetar0 = dthetar0_obj; */

	l0 = 100.*random(100000)/(100000.-1.);
	thetal0 = random(100000)/(100000.-1.)*2.*pi;
	r0 = random(100000)/(100000.-1);
//	dr0 =  random(100000)/(100000.-1)*0.1;
	dr0 = 0.1;

	thetar0 = random(100000)/(100000.-1.)*2.*pi;
	dthetar0 = random(100000)/(100000.-1.);  

//	printf("random : %lf\n",random(100000)/(100000.-1.));
//	printf("Obj[%6.2lf %6.2lf] Est[%6.2lf %6.2lf]\n",l0_obj*cos(thetal0_obj),l0_obj*sin(thetal0_obj),l0*cos(thetal0),l0*sin(thetal0));

	double m=0.5,a=0.5;
	double obj=0.001,est=0.005;
	gamma[0] = m*est;
	gamma[1] = a*est;
	gamma[2] = m*est;
	gamma[3] = a*est;
	gamma_obj[0] = m*obj;
	gamma_obj[1] = a*obj;
	gamma_obj[2] = m*obj;
	gamma_obj[3] = a*obj;

	yn = new double [Nt];
	for(i=0;i<Nt;i++) yn[i]=0;
	yn_p = new double [Np];
	for(i=0;i<Np;i++) yn_p[i]=0;
	
	w = new double [Np];
	for(i=0;i<Np;i++) w[i]=0;
	mn = new double [Np];
	for(i=0;i<Np;i++) mn[i]=0;
	r = new double [Np];
	for(i=0;i<Np;i++) r[i]=0;
	thetar = new double [Np];
	for(i=0;i<Np;i++) thetar[i]=0;
	l = new double [Np];
	for(i=0;i<Np;i++) l[i]=0;
	thetal = new double [Np];
	for(i=0;i<Np;i++) thetal[i]=0;
	dr = new double [Np];
	for(i=0;i<Np;i++) dr[i]=0;
	dthetar = new double [Np];
	for(i=0;i<Np;i++) dthetar[i]=0;
	
	r_est = new double [Nt];
	for(i=0;i<Nt;i++) r_est[i]=0;
	thetar_est = new double [Nt];
	for(i=0;i<Nt;i++) thetar_est[i]=0;
	l_est = new double [Nt];
	for(i=0;i<Nt;i++) l_est[i]=0;
	thetal_est = new double [Nt];
	for(i=0;i<Nt;i++) thetal_est[i]=0;
}

pf2d::~pf2d()
{
	delete yn,yn_p,w,r,thetar,l,thetal,mn,dr,dthetar;
	delete l_est,thetal_est,r_est,thetar_est;
}

void pf2d::get_yn(void)
{
	double noise[4];
	double r_obj,thetar_obj,l_obj,thetal_obj;
	int i;
	double mag,ang;

	noise[0] = gamma_obj[0]*gause_noise();
	noise[1] = gamma_obj[1]*gause_noise();
	noise[2] = gamma_obj[2]*gause_noise();
	noise[3] = gamma_obj[3]*gause_noise();

	r_obj = r0_obj + dr0_obj + noise[0];
	thetar_obj = thetar0_obj + dthetar0_obj +  noise[1];
	get_new_pos(l0_obj,thetal0_obj,r_obj,thetar_obj,&mag,&ang);
	l_obj = mag + noise[2];
	thetal_obj = ang + noise[3];

	yn[0] = thetal_obj;

	FILE *fp;
	fp = fopen("object.txt","w");

	fprintf(fp,"%lf %lf\n",l_obj*cos(thetal_obj),l_obj*sin(thetal_obj));

	i=0;
//	printf("yn[%d]=%lf\n",i,yn[i]);

	for(i=1;i<Nt;i++) {
		noise[0] = gamma_obj[0]*gause_noise();
		noise[1] = gamma_obj[1]*gause_noise();
		noise[2] = gamma_obj[2]*gause_noise();
		noise[3] = gamma_obj[3]*gause_noise();

		r_obj += (dr0_obj*dt+noise[0]);
		thetar_obj += ((dthetar0_obj+noise[1])+0.1*gause_noise()) ;
//		thetar_obj += (dthetar0_obj+noise[1]) ;
 
		get_new_pos(l_obj,thetal_obj,r_obj,thetar_obj,&mag,&ang);
		l_obj = mag + noise[2];
		thetal_obj = ang + noise[3];
		
//		if(thetal_obj>2*pi-ang_error || thetal_obj<ang_error) thetal_obj=2*pi;

		yn[i] = thetal_obj;

//		printf("yn[%d]=%lf\n",i,yn[i]);
		fprintf(fp,"%lf %lf\n",l_obj*cos(thetal_obj),l_obj*sin(thetal_obj));
	}

	fclose(fp);
} 

void pf2d::get_new_pos(double l,double thetal,double r,double thetar,double *mag,double *ang)
{
	double x,y;

	x = l*cos(thetal)+r*cos(thetar);
	y = l*sin(thetal)+r*sin(thetar);

	*mag = sqrt(x*x+y*y);

	if(x>0 && y>0)			*ang = atan(y/x);
	else if(x<0 && y>0)		*ang = pi - atan(-y/x);
	else if(x<0 && y<0)		*ang = pi + atan(y/x);
	else if(x>0 && y<0)		*ang = 2*pi-atan(-y/x);
	else if(x==0 && y>0)	*ang = 0.5*pi;
	else if(x==0 && y<0)	*ang = 1.5*pi;
	else if(x>0 && y==0)	*ang = 0;
	else if(x<0 && y==0)	*ang = pi;
	else if(x==0 && y==0)	*ang = 0;
}

/* boxmuller.c           Implements the Polar form of the Box-Muller
                         Transformation

                      (c) Copyright 1994, Everett F. Carter Jr.
                          Permission is granted by the author to use
			  this software for any application provided this
			  copyright notice is preserved.

	http://www.taygeta.com/random/gaussian.html
*/
double pf2d::gause_noise(void)	/* normal random variate generator */
{				        /* mean m, standard deviation s */
	double x1=0,x2=0,w=0;
	double y1=0,y2=0;
	int use_last=0;
	
	if(use_last)		        /* use value from previous call */
	{
		y1 = y2;
		use_last = 0;
	}
	else
	{
		do {
			x1 = 2.0*random(100000)/(100000.-1) - 1.0;
			x2 = 2.0*random(100000)/(100000.-1) - 1.0;
			w = x1*x1 + x2*x2;
		} while (w>=1.0);

		w = sqrt((-2.0*log(w))/w);
		y1 = x1*w;
		y2 = x2*w;
		use_last = 1;
	}

	return y1;
}

void pf2d::estimate_pariticle_2d(void)
{
	double noise[4];
	int i,t;
	double mag,ang;

	FILE *fp_mn;
	fp_mn = fopen("angle.txt","w");	

	FILE *fp_px,*fp_py;
	fp_px = fopen("px.txt","w");
	fp_py = fopen("py.txt","w");

	for(i=0;i<Np;i++) {

//		printf("%lf %lf %lf %lf\n",noise[0],noise[1]*180/pi,noise[2],noise[3]*180/pi);

		noise[0] = gamma[0]*gause_noise();
		noise[1] = gamma[1]*gause_noise();
		noise[2] = gamma[2]*gause_noise();
		noise[3] = gamma[3]*gause_noise();

		r[i] = r0 + dr0*dt + noise[0];
		thetar[i] = thetar0 + dthetar0 + noise[1];

		get_new_pos(l0,thetal0,r[i],thetar[i],&mag,&ang);
		l[i] =  mag + noise[2];
		thetal[i] = ang + noise[3];

//		if(thetal[i]>2*pi-ang_error || thetal[i]<ang_error) thetal[i]=2*pi;
		
		yn_p[i] = thetal[i];
		
		mn[i] = dtheta(yn[0],yn_p[i]);
		dthetar[i] = dthetar0 + mn[i];
		dr[i] = dr0;

		w[i] = exp(-(mn[i]*mn[i]) / (2*(0.005*0.005)));
	}

	for(i=0;i<Np;i++) fprintf(fp_mn,"%7.2lf ",mn[i]/pi*180);
	fprintf(fp_mn,"\n");

	// sampling
	sampling();

	// estimation
	for(i=0;i<Np;i++) {
		r_est[0] += r[i]*w[i];
		thetar_est[0] += thetar[i]*w[i];
		l_est[0] += l[i]*w[i];
		thetal_est[0] += thetal[i]*w[i];
	}

	// Debugging
	for(i=0;i<Np;i++) {
		fprintf(fp_px,"%7.2lf ",l[i]*cos(thetal[i]));
		fprintf(fp_py,"%7.2lf ",l[i]*sin(thetal[i]));
	}
	fprintf(fp_px,"\n");
	fprintf(fp_py,"\n");		


	// From t=1 to t=Nt-1
	for(t=1;t<Nt;t++) {
		for(i=0;i<Np;i++) {
			noise[0] = gamma[0]*gause_noise();
			noise[1] = gamma[1]*gause_noise();
			noise[2] = gamma[2]*gause_noise();
			noise[3] = gamma[3]*gause_noise();

			r[i] += (dr[i]+noise[0]);
			thetar[i] += (dthetar[i]+noise[1]);

			get_new_pos(l[i],thetal[i],r[i],thetar[i],&mag,&ang);
			l[i] =  mag + noise[2];
			thetal[i] = ang + noise[3];

//			if(thetal[i]>2*pi-ang_error || thetal[i]<ang_error) thetal[i]=2*pi;
		
			yn_p[i] = thetal[i];
		
			mn[i] = dtheta(yn[t],yn_p[i]);
			dthetar[i] += mn[i];
//			dr[i] += 0.1*gause_noise();

			w[i] = exp(-(mn[i]*mn[i])/(2.*(0.005*0.005)));			
		}

		for(i=0;i<Np;i++) fprintf(fp_mn,"%7.2lf ",mn[i]/pi*180);
		fprintf(fp_mn,"\n");

		// sampling
		sampling();

		// estimation
		for(i=0;i<Np;i++) {
			r_est[t] += r[i]*w[i];
			thetar_est[t] += thetar[i]*w[i];
			l_est[t] += l[i]*w[i];
			thetal_est[t] += thetal[i]*w[i];
		}

		// for Debugging
		for(i=0;i<Np;i++) {
			fprintf(fp_px,"%7.2lf ",l[i]*cos(thetal[i]));
			fprintf(fp_py,"%7.2lf ",l[i]*sin(thetal[i]));
		}
		fprintf(fp_px,"\n");
		fprintf(fp_py,"\n");

	}	
	fclose(fp_px), fclose(fp_py);


	fclose(fp_mn);

	FILE *fp;
	fp = fopen("estimate.txt","w");
	for(t=0;t<Nt;t++) fprintf(fp,"%lf %lf\n",l_est[t]*cos(thetal_est[t]),l_est[t]*sin(thetal_est[t]));
	fclose(fp);
} 

void pf2d::sampling(void)
{
	int i,j;
	double d=0;

	double *c;
	double *u;

	c = new double [Np];
	for(i=0;i<Np;i++) c[i]=0;
	u = new double [Np];
	for(i=0;i<Np;i++) u[i]=0;

	for(i=0;i<Np;i++) d += w[i];
	if(d==0) {
		for(i=0;i<Np;i++) w[i] = 1./Np;
		d=1;
	}
          
	for(i=0;i<Np;i++)	w[i] = w[i]/d;   // the sum of w is 1.
	
	c[0] = w[0];                         // CDF of w (estimated p)
	for(i=1;i<Np;i++) 
		c[i] = c[i-1] + w[i];        // w(ns)=1
	
	u[0] = random(100000)/(100000.-1)*(1./Np);  // CDF of a basic
	for(j=0;j<Np;j++) u[j] = u[0]+(1./Np)*j;
			
	for(j=0;j<Np;j++) {
		i=0;
		while (u[j]>c[i])            // if c(estimated p) is less than u(basic w)
			i++;                   	        
				
		r[j] = r[i];
		thetar[j] = thetar[i];
		l[j] = l[i];
		thetal[j] = thetal[i];

		w[j] = 1./Np;
	}

	delete u,c;
}

double pf2d::dtheta(double yn,double yn_p)
{
	double mn;

	if(yn_p>yn) {
		if(yn_p-yn<pi)	mn = -(yn_p-yn);
		else			mn = yn + (2*pi - yn_p);
	}
	else {
		if(yn-yn_p<pi)	mn = yn-yn_p;
 		else	 		mn = -(yn_p + (2*pi-yn));
	}

	return mn;
}