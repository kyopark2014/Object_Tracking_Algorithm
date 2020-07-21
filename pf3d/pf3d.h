// ph3d.h: interface for the ph3d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ph3d_H__CD66A280_2C13_4CAD_B63C_9577ED2C7419__INCLUDED_)
#define AFX_ph3d_H__CD66A280_2C13_4CAD_B63C_9577ED2C7419__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class pf3d  
{
public:
	pf3d();
	virtual ~pf3d();

	int N;
	int ns;
	double dt;
	double ang_error;

	double l0_obj,thetal0_obj,phil0_obj,r0_obj,dr0_obj,thetar0_obj,phir0_obj,dthetar0_obj,dphir0_obj;
    double l0,thetal0,phil0,r0,dr0,thetar0,phir0,dthetar0,dphir0;
	
	void get_new_pos(double l,double thetal,double phil,double r,double thetar,double phir,double *mag,double *ang_th,double *ang_ph);
	void get_yn(void);
	double gause_noise(void);
	void estimate_pariticle_3d(void);
	void sampling(void);
	double dtheta(double yn,double yn_p);
	double dphi(double yn,double yn_p);

	double *yn_theta,*yn_theta_p,*yn_phi,*yn_phi_p;
	
	double gamma_obj[6];
	double gamma[6];

	double *w,*w_th,*w_ph,*r,*thetar,*phir,*l,*thetal,*phil,*mn_th,*mn_ph,*dr,*dthetar,*dphir;
	double *r_est,*thetar_est,*phir_est,*l_est,*thetal_est,*phil_est;
};

#endif // !defined(AFX_ph3d_H__CD66A280_2C13_4CAD_B63C_9577ED2C7419__INCLUDED_)
