// pf2d.h: interface for the pf2d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PF2D_H__CD66A280_2C13_4CAD_B63C_9577ED2C7419__INCLUDED_)
#define AFX_PF2D_H__CD66A280_2C13_4CAD_B63C_9577ED2C7419__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class pf2d  
{
public:
	pf2d();
	virtual ~pf2d();

	int N;
	int ns;
	double dt;
	double ang_error;

	double l0_obj,thetal0_obj,r0_obj,dr0_obj,thetar0_obj,dthetar0_obj;
    double l0,thetal0,r0,dr0,thetar0,dthetar0;
	
	void get_new_pos(double l,double thetal,double r,double thetar,double *mag,double *ang);
	void get_yn(void);
	double gause_noise(void);
	void estimate_pariticle_2d(void);
	void sampling(void);
	double dtheta(double yn,double yn_p);

	double *yn,*yn_p;
	
	double gamma_obj[4];
	double gamma[4];

	double *w,*r,*thetar,*l,*thetal,*mn,*dr,*dthetar;
	double *r_est,*thetar_est,*l_est,*thetal_est;
};

#endif // !defined(AFX_PF2D_H__CD66A280_2C13_4CAD_B63C_9577ED2C7419__INCLUDED_)
