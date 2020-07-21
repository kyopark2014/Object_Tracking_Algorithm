// pf3d.cpp: implementation of the pf3d class.
//
//////////////////////////////////////////////////////////////////////

#include "pf3d.h"
#include "math.h"
#include "size.h"
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define randomize() (srand(time(0)))
#define random(x) (rand() %x)

pf3d::pf3d()
{
	int i;

	dt = 1.0;
	ang_error = 1.5/180*pi;

	l0_obj = 20.;
    thetal0_obj = 90./180.*pi;
	phil0_obj = 90./180.*pi;
    r0_obj = 0.5;
    thetar0_obj = 90./180.*pi;
	phir0_obj = 90./180.*pi;
	dr0_obj = 0.1;
	dthetar0_obj = 3./180.*pi;
	dphir0_obj = 3./180.*pi;

/*	l0 = l0_obj;
	thetal0 = thetal0_obj;
	phil0 = phil0;
	r0 = r0_obj;
	dr0 = dr0_obj;
	thetar0 = thetar0_obj;
	dthetar0 = dthetar0_obj;  
	phir0 = phir0_obj;
	dphir0 = dphir0_obj;  */

	l0 = 100.*random(100000)/(100000.-1.);
	thetal0 = random(100000)/(100000.-1.)*2.*pi;
	phil0 = random(100000)/(100000.-1.)*2.*pi;
	r0 = random(100000)/(100000.-1);
	dr0 = 0.1;
	thetar0 = random(100000)/(100000.-1.)*2.*pi;
	dthetar0 = random(100000)/(100000.-1.);  
	phir0 = random(100000)/(100000.-1.)*2.*pi;
	dphir0 = random(100000)/(100000.-1.); 

//	printf("random : %lf\n",random(100000)/(100000.-1.));
//	printf("Obj[%6.2lf %6.2lf] Est[%6.2lf %6.2lf]\n",l0_obj*cos(thetal0_obj),l0_obj*sin(thetal0_obj),l0*cos(thetal0),l0*sin(thetal0));

	double m=0.5,a=0.5;
	double obj=0.001,est=0.005;
	gamma[0] = m*est;
	gamma[1] = a*est;
	gamma[2] = a*est;
	gamma[3] = m*est;
	gamma[4] = a*est;
	gamma[5] = a*est;
	gamma_obj[0] = m*obj;
	gamma_obj[1] = a*obj;
	gamma_obj[2] = a*obj;
	gamma_obj[3] = m*obj;
	gamma_obj[4] = a*obj;
	gamma_obj[5] = a*obj;

	yn_theta = new double [Nt];
	for(i=0;i<Nt;i++) yn_theta[i]=0;
	yn_theta_p = new double [Np];
	for(i=0;i<Np;i++) yn_theta_p[i]=0;
	yn_phi = new double [Nt];
	for(i=0;i<Nt;i++) yn_phi[i]=0;
	yn_phi_p = new double [Np];
	for(i=0;i<Np;i++) yn_phi_p[i]=0;
	
	w = new double [Np];
	for(i=0;i<Np;i++) w[i]=0;
	w_th = new double [Np];
	for(i=0;i<Np;i++) w_th[i]=0;
	w_ph = new double [Np];
	for(i=0;i<Np;i++) w_ph[i]=0;
	mn_th = new double [Np];
	for(i=0;i<Np;i++) mn_th[i]=0;
	mn_ph = new double [Np];
	for(i=0;i<Np;i++) mn_ph[i]=0;
	r = new double [Np];
	for(i=0;i<Np;i++) r[i]=0;
	thetar = new double [Np];
	for(i=0;i<Np;i++) thetar[i]=0;
	phir = new double [Np];
	for(i=0;i<Np;i++) phir[i]=0;
	l = new double [Np];
	for(i=0;i<Np;i++) l[i]=0;
	thetal = new double [Np];
	for(i=0;i<Np;i++) thetal[i]=0;
	phil = new double [Np];
	for(i=0;i<Np;i++) phil[i]=0;
	dr = new double [Np];
	for(i=0;i<Np;i++) dr[i]=0;
	dthetar = new double [Np];
	for(i=0;i<Np;i++) dthetar[i]=0;
	dphir = new double [Np];
	for(i=0;i<Np;i++) dphir[i]=0;
	
	r_est = new double [Nt];
	for(i=0;i<Nt;i++) r_est[i]=0;
	thetar_est = new double [Nt];
	for(i=0;i<Nt;i++) thetar_est[i]=0;
	phir_est = new double [Nt];
	for(i=0;i<Nt;i++) phir_est[i]=0;
	l_est = new double [Nt];
	for(i=0;i<Nt;i++) l_est[i]=0;
	thetal_est = new double [Nt];
	for(i=0;i<Nt;i++) thetal_est[i]=0;
	phil_est = new double [Nt];
	for(i=0;i<Nt;i++) phil_est[i]=0;
}

pf3d::~pf3d()
{
	delete yn_theta,yn_phi,yn_theta_p,yn_phi_p,w,w_th,w_ph,r,thetar,phir,l,thetal,phil,mn_th,mn_ph,dr,dthetar,dphir;
	delete l_est,thetal_est,phil_est,r_est,thetar_est,phir_est;
}

void pf3d::get_yn(void)
{
	double noise[6];
	double r_obj,thetar_obj,phir_obj,l_obj,thetal_obj,phil_obj;
	int i;
	double mag,ang_th,ang_ph;

	noise[0] = gamma_obj[0]*gause_noise();
	noise[1] = gamma_obj[1]*gause_noise();
	noise[2] = gamma_obj[2]*gause_noise();
	noise[3] = gamma_obj[3]*gause_noise();
	noise[4] = gamma_obj[4]*gause_noise();
	noise[5] = gamma_obj[5]*gause_noise();

	r_obj = r0_obj + dr0_obj + noise[0];
	thetar_obj = thetar0_obj + dthetar0_obj +  noise[1];
	phir_obj = phir0_obj + dphir0_obj +  noise[2];
	get_new_pos(l0_obj,thetal0_obj,phil0_obj,r_obj,thetar_obj,phir_obj,&mag,&ang_th,&ang_ph);
	l_obj = mag + noise[3];
	thetal_obj = ang_th + noise[4];
	phil_obj = ang_ph + noise[5];

	yn_theta[0] = thetal_obj;
	yn_phi[0] = phil_obj;

	FILE *fp;
	fp = fopen("object.txt","w");

	double x,y,z;
	x = l_obj*sin(thetal_obj)*cos(phil_obj);
	y = l_obj*sin(thetal_obj)*sin(phil_obj);
	z = l_obj*cos(thetal_obj);
	fprintf(fp,"%lf %lf %lf\n",x,y,z);

	i=0;
//	printf("yn_theta[%d]=%lf\n",i,yn_theta[i]);

	for(i=1;i<Nt;i++) {
		noise[0] = gamma_obj[0]*gause_noise();
		noise[1] = gamma_obj[1]*gause_noise();
		noise[2] = gamma_obj[2]*gause_noise();
		noise[3] = gamma_obj[3]*gause_noise();
		noise[4] = gamma_obj[4]*gause_noise();
		noise[5] = gamma_obj[5]*gause_noise();

		r_obj += (dr0_obj*dt+noise[0]);
		thetar_obj += (dthetar0_obj+noise[1]);
		phir_obj += (dphir0_obj+noise[2]);
 
		get_new_pos(l_obj,thetal_obj,phil_obj,r_obj,thetar_obj,phir_obj,&mag,&ang_th,&ang_ph);
		l_obj = mag + noise[3];
		thetal_obj = ang_th + noise[4];
		phil_obj = ang_ph + noise[5];
		
		if(thetal_obj>2*pi-ang_error || thetal_obj<ang_error) thetal_obj=2*pi;
		if(phil_obj>2*pi-ang_error || phil_obj<ang_error) phil_obj=2*pi;

		yn_theta[i] = thetal_obj;
		yn_phi[i] = phil_obj;

//		printf("yn_theta[%d]=%lf\n",i,yn_theta[i]);	
		x = l_obj*sin(thetal_obj)*cos(phil_obj);
		y = l_obj*sin(thetal_obj)*sin(phil_obj);
		z = l_obj*cos(thetal_obj);
		fprintf(fp,"%lf %lf %lf\n",x,y,z);
	} 

	fclose(fp);
} 

void pf3d::get_new_pos(double l,double thetal,double phil,double r,double thetar,double phir,double *mag,double *ang_th,double *ang_ph)
{
	double x,y,z;
	double tx,ty;

	x = l0*sin(thetal0)*cos(phil0) + r*sin(thetar)*cos(phir);
	y = l0*sin(thetal0)*sin(phil0) + r*sin(thetar)*sin(phir);
	z = l0*cos(thetal0) + r*cos(thetar);

	*mag = sqrt(x*x + y*y + z*z);

	ty = sqrt(x*x + y*y);
	tx = z;

	if(tx>0 && ty>0)
		*ang_th = atan(ty/tx);
	else if(tx<0 && ty>0)
		*ang_th = pi - atan(-ty/tx);
	else if(tx==0 && ty>0)
		*ang_th = 0.5*pi;
	else if(tx>0 && ty==0)
		*ang_th = 0;
	else if(tx<0 && ty==0)
		*ang_th = pi;
	else if(tx==0 && ty==0)
		*ang_th = 0;

	ty = y;
	tx = x;

	if(tx>0 && ty>0)
		*ang_ph = atan(ty/tx);
	else if(tx<0 && ty>0)
		*ang_ph = pi - atan(-ty/tx);
	else if(tx<0 && ty<0)
		*ang_ph = pi + atan(ty/tx);
	else if(tx>0 && ty<0)
		*ang_ph = 2*pi-atan(-ty/tx);
	else if(tx==0 && ty>0)
		*ang_ph = 0.5*pi;
	else if(tx==0 && ty<0)
		*ang_ph = 1.5*pi;
	else if(tx>0 && ty==0)
		*ang_ph = 0;
	else if(tx<0 && ty==0)
		*ang_ph = pi;
	else if(tx==0 && ty==0)
		*ang_ph = 0;
}

/* boxmuller.c           Implements the Polar form of the Box-Muller
                         Transformation

                      (c) Copyright 1994, Everett F. Carter Jr.
                          Permission is granted by the author to use
			  this software for any application provided this
			  copyright notice is preserved.

	http://www.taygeta.com/random/gaussian.html
*/
double pf3d::gause_noise(void)	/* normal random variate generator */
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

void pf3d::estimate_pariticle_3d(void)
{
	double noise[6];
	int i,t;
	double mag,ang_th,ang_ph;

	FILE *fp_mn_th,*fp_mn_ph;
	fp_mn_th = fopen("mn_th.txt","w");	
	fp_mn_ph = fopen("mn_ph.txt","w");	

	FILE *fp_px,*fp_py,*fp_pz;
	fp_px = fopen("px.txt","w");
	fp_py = fopen("py.txt","w");
	fp_pz = fopen("pz.txt","w");

	for(i=0;i<Np;i++) {

//		printf("%lf %lf %lf %lf\n",noise[0],noise[1]*180/pi,noise[2],noise[3]*180/pi);

		noise[0] = gamma[0]*gause_noise();
		noise[1] = gamma[1]*gause_noise();
		noise[2] = gamma[2]*gause_noise();
		noise[3] = gamma[3]*gause_noise();
		noise[4] = gamma[4]*gause_noise();
		noise[5] = gamma[5]*gause_noise();

		r[i] = r0 + dr0 + noise[0];
		thetar[i] = thetar0 + dthetar0 + noise[1];
		phir[i] = phir0 + dphir0 + noise[2];

		get_new_pos(l0,thetal0,phil0,r[i],thetar[i],phir[i],&mag,&ang_th,&ang_ph);
		l[i] =  mag + noise[3];
		thetal[i] = ang_th + noise[4];
		phil[i] = ang_ph + noise[5];

		if(thetal[i]>2*pi-ang_error || thetal[i]<ang_error) thetal[i]=2*pi;
		if(phil[i]>2*pi-ang_error || phil[i]<ang_error) phil[i]=2*pi;
		
		yn_theta_p[i] = thetal[i];
		yn_phi_p[i] = phil[i];
		
		mn_th[i] = dtheta(yn_theta[0],yn_theta_p[i]);
		mn_ph[i] = dphi(yn_phi[0],yn_phi_p[i]);
		dthetar[i] = dthetar0 + mn_th[i];
		dphir[i] = dphir0 + mn_ph[i];
//		dthetar[i] = dthetar0;
//		dphir[i] = dphir0;
		dr[i] = dr0;
	
		w_th[i] = exp(-(mn_th[i]*mn_th[i]) / (2*(0.005*0.005)));
		w_ph[i] = exp(-(mn_ph[i]*mn_ph[i]) / (2*(0.005*0.005)));

		w[i] = w_th[i]+w_ph[i];
	}

	for(i=0;i<Np;i++) fprintf(fp_mn_th,"%7.2lf ",mn_th[i]/pi*180.);
	fprintf(fp_mn_th,"\n");
	for(i=0;i<Np;i++) fprintf(fp_mn_ph,"%7.2lf ",mn_ph[i]/pi*180.);
	fprintf(fp_mn_ph,"\n");

	// sampling
	sampling();

	// estimation
	for(i=0;i<Np;i++) {
		r_est[0] += r[i]*w[i];
		thetar_est[0] += thetar[i]*w[i];
		phir_est[0] += phir[i]*w[i];
		l_est[0] += l[i]*w[i];
		thetal_est[0] += thetal[i]*w[i];
		phil_est[0] += phil[i]*w[i];
	}

	// Debugging
	for(i=0;i<Np;i++) {
		fprintf(fp_px,"%7.2lf ",l[i]*sin(thetal[i])*cos(phil[i]));
		fprintf(fp_py,"%7.2lf ",l[i]*sin(thetal[i])*sin(phil[i]));
		fprintf(fp_pz,"%7.2lf ",l[i]*cos(thetal[i]));
	}
	fprintf(fp_px,"\n");
	fprintf(fp_py,"\n");		
	fprintf(fp_pz,"\n");		


	// From t=1 to t=Nt-1
	for(t=1;t<Nt;t++) {
		for(i=0;i<Np;i++) {
			noise[0] = gamma[0]*gause_noise();
			noise[1] = gamma[1]*gause_noise();
			noise[2] = gamma[2]*gause_noise();
			noise[3] = gamma[3]*gause_noise();
			noise[4] = gamma[4]*gause_noise();
			noise[5] = gamma[5]*gause_noise();

			r[i] += (dr[i]+noise[0]);
//			printf("r[%d]=%lf dr[%d]=%lf noise=%lf\n",i,r[i],i,dr[i],noise[0]);
			thetar[i] += (dthetar[i]+noise[1]);
			phir[i] += (dphir[i]+noise[2]);

			get_new_pos(l[i],thetal[i],phil[i],r[i],thetar[i],phir[i],&mag,&ang_th,&ang_ph);
			l[i] =  mag + noise[3];
			thetal[i] = ang_th + noise[4];
			phil[i] = ang_ph + noise[5];

//			printf("l[%d]=%lf thetal[%d]=%lf\n",i,l[i],i,thetal[i]);
			if(thetal[i]>2*pi-ang_error || thetal[i]<ang_error) thetal[i]=2*pi;
			if(phil[i]>2*pi-ang_error || phil[i]<ang_error) phil[i]=2*pi;
		
			yn_theta_p[i] = thetal[i];
			yn_phi_p[i] = phil[i];
		
			mn_th[i] = dtheta(yn_theta[t],yn_theta_p[i]);
			mn_ph[i] = dphi(yn_phi[t],yn_phi_p[i]);
//			dthetar[i] += mn_th[i];
//			dphir[i] += mn_ph[i];
//			dr[i] += 0.1*gause_noise();

			w_th[i] = exp(-(mn_th[i]*mn_th[i])/(2.*(0.005*0.005)));			
			w_ph[i] = exp(-(mn_ph[i]*mn_ph[i])/(2.*(0.005*0.005)));			
			w[i] = w_th[i]+w_ph[i];
		}

		for(i=0;i<Np;i++) fprintf(fp_mn_th,"%7.2lf ",mn_th[i]/pi*180.);
		fprintf(fp_mn_th,"\n");
		for(i=0;i<Np;i++) fprintf(fp_mn_ph,"%7.2lf ",mn_ph[i]/pi*180.);
		fprintf(fp_mn_ph,"\n");

		// sampling
		sampling();

		// estimation
		for(i=0;i<Np;i++) {
			r_est[t] += r[i]*w[i];
			thetar_est[t] += thetar[i]*w[i];
			phir_est[t] += phir[i]*w[i];
			l_est[t] += l[i]*w[i];
			thetal_est[t] += thetal[i]*w[i];
			phil_est[t] += phil[i]*w[i];
		}

		// for Debugging
		for(i=0;i<Np;i++) {
			fprintf(fp_px,"%7.2lf ",l[i]*sin(thetal[i])*cos(phil[i]));
			fprintf(fp_py,"%7.2lf ",l[i]*sin(thetal[i])*sin(phil[i]));
			fprintf(fp_pz,"%7.2lf ",l[i]*cos(thetal[i]));
		}
		fprintf(fp_px,"\n");
		fprintf(fp_py,"\n");		
		fprintf(fp_pz,"\n");
	}	
	fclose(fp_px), fclose(fp_py);


	fclose(fp_mn_th),fclose(fp_mn_ph);

	FILE *fp;
	fp = fopen("estimate.txt","w");
	double x,y,z;
	for(t=0;t<Nt;t++) {
		x = l_est[t]*sin(thetal_est[t])*cos(phil_est[t]);
		y = l_est[t]*sin(thetal_est[t])*sin(phil_est[t]);
		z = l_est[t]*cos(thetal_est[t]);

		fprintf(fp,"%lf %lf %lf\n",x,y,z);
	}

	fclose(fp);
} 

void pf3d::sampling(void)
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

//	for(i=0;i<5;i++)
//		printf("d=%lf w[%d]=%2.4lf ",d, i,w[i]);
//	printf("\n");
          
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
				
//		r[j] = r[i];
//		thetar[j] = thetar[i];
//		phir[j] = phir[i];
		l[j] = l[i];
		thetal[j] = thetal[i];
		phil[j] = phil[i];

		w[j] = 1./Np;
		w_th[j] = 1./Np;
		w_ph[j] = 1./Np;
	}

	delete u,c;
}

double pf3d::dtheta(double yn,double yn_p)
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

double pf3d::dphi(double yn,double yn_p)
{
	double mn;

	mn = yn-yn_p;

	return mn;
}