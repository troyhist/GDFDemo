// =======================================================================
// GDF.cpp: implementation of the CGDF class.
// =======================================================================
#include "stdafx.h"
#include "GDFDemo.h"
// ---------------------------------------------------------------
#include <time.h>			// time, srand
#include <math.h>			// cos
#include <stdlib.h>			// srand
// ---------------------------------------------------------------
#include "GDF.h"
// ================================================================
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
// ===============================================================
#define M_PI	(3.1415926535)
// ===============================================================
// Construction/Destruction
// ===============================================================
CGDF::CGDF()
{	
// ---------------------------------------------------------------
Update();
// ---------------------------------------------------------------
m_pDC=NULL;
// ---------------------------------------------------------------
ResetData();
// ---------------------------------------------------------------
// 4. Special settings
// ---------------------------------------------------------------
m_bMirX=0;		// make mirror copy via OX
m_bMirY=0;		// make mirror copy via OY
m_bMirXY=0;		// make mirror copy via XOY
m_nScrCX=0;		// X center of screen
m_nScrCY=0;		// Y center of screen
m_bEnfill=0;		// Enable filling
// ---------------------------------------------------------------
m_pPen=new CPen(m_nLinestyle, m_nThickness, m_nColor);
m_pBrush=new CBrush(m_nFillcolor);
}
// =======================================================================
CGDF::~CGDF()
{
if (m_pPen) delete m_pPen;
if (m_pBrush) delete m_pBrush;
}
// =======================================================================
BOOL CGDF::SetDC(CDC *pDC)
{
if (!pDC) return(false);
m_pDC=pDC;
InitDC();
return(true);
}
// =======================================================================
BOOL CGDF::ResetData()
{
m_nColor=0;
m_nWritemode=0;
m_nLinestyle=PS_SOLID;
m_nUpattern=0;
m_nThickness=1;
m_nFillpattern=HS_SOLID;
m_nFillcolor=15;
return(true);
}
// =======================================================================
BOOL CGDF::InitDC()
{
ResetData();
HDSetColor(0); HDSetFillColor(0);
HDSetFillPattern(HS_SOLID);
HDSetPenStyle(PS_SOLID);
return(true);
}
// =======================================================================
// Hardware depended functions
// =======================================================================
BOOL CGDF::HDEllipseFill(int x1, int y1, int x2, int y2, int nColor,
					 int nFillColor)
{
SetColor(nColor);	SetFillColor(nFillColor);
if (nFillColor!=-1) 
	return(m_pDC->Ellipse(x1, y1, x2, y2));
return(m_pDC->Arc(x1, y1, x2, y2, (x2+x1)/2, y1, (x2+x1)/2, y1));
}
// =======================================================================
BOOL CGDF::HDLineRel (int ndx, int ndy, int nc)
{
// -----------------------------------------------------------------------
// Description: Draws relative line
//   Parametrs: dx, dy	- addictions
//      Return: <none>
// -----------------------------------------------------------------------
SetColor(nc);
POINT p; p.x=ndx; p.y=ndy;
return(true);
}
// =======================================================================
BOOL CGDF::HDLineTo (int nx, int ny, int nc)
{
// -----------------------------------------------------------------------
// Description: Draws line to given coordinates
//   Parametrs: x, y	- coordinates
//      Return: <none>
// -----------------------------------------------------------------------
SetColor(nc);
POINT p; p.x=nx; p.y=ny;
m_pDC->LineTo(p);
return(true);
}
// =======================================================================
BOOL CGDF::HDMoveTo (int nx, int ny)
{
// -----------------------------------------------------------------------
// Description: Moves graphics pointer to given coordinates
//   Parametrs: x, y	- coordinates
//      Return: <none>
// -----------------------------------------------------------------------
POINT p; p.x=nx; p.y=ny;
m_pDC->MoveTo(p);
return(true);
}
// =======================================================================
BOOL CGDF::HDPolyBFill(int nn, POINT *points, int nc, int nfc)
{
SetColor(nc);	SetFillColor(nfc);
if (nfc!=-1) return m_pDC->PolyBezier(points, nn);
return m_pDC->PolyBezier(points, nn);
}
// =======================================================================
BOOL CGDF::HDPolyFill(int nn, POINT* points, int nc, int nfc)
{
// -----------------------------------------------------------------------
// Description: Draws & fills a polygon
//   Parametrs: n	- quantity of points
//				points	- ptr to a sequence of (numpoints x 2) 
//							integers
//				c	- color
//				fc	- fill color (or '-1' to skip filling)
//      Return: <none>
// -----------------------------------------------------------------------
SetColor(nc);	SetFillColor(nfc);
if (nfc!=-1) 
	return m_pDC->Polygon(points, nn);
return m_pDC->Polyline(points, nn);
}
// =======================================================================
BOOL CGDF::HDPutPixel (int nx, int ny, int nc)
{
// -----------------------------------------------------------------------
// Description: Draws unscalable pixel
//   Parametrs: x, y	- coordiantes
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
POINT p; p.x=nx; p.y=ny;
int nColRGB=EGAtoRGB(nc);
m_pDC->SetPixel(p, nColRGB);
return(true);
}
// =======================================================================
BOOL CGDF::HDSetColor (int nc)
{
// -----------------------------------------------------------------------
// Description: Sets output color
//   Parametrs: c	- color
//      Return: <none>
// -----------------------------------------------------------------------
delete m_pPen;
COLORREF nNewColor=EGAtoRGB(nc);
m_pPen=new CPen(m_nLinestyle, m_nThickness, nNewColor);
m_pDC->SelectObject(m_pPen);
return(true);
}
// =======================================================================
BOOL CGDF::HDSetFillColor(int nc)
{
// -----------------------------------------------------------------------
// Description: Sets fill color
//   Parametrs: c	- new fill color
//      Return: <none>
// -----------------------------------------------------------------------
delete m_pBrush;
COLORREF nNewColor=EGAtoRGB(nc);
m_pBrush=new CBrush();
if (m_nFillpattern==HS_SOLID)
	m_pBrush->CreateSolidBrush(nNewColor);
else
	m_pBrush->CreateHatchBrush(m_nFillpattern, nNewColor);
m_pDC->SelectObject(m_pBrush);
return(true);
}
// =======================================================================
BOOL CGDF::HDSetFillPattern (int nStyle)
{
// -----------------------------------------------------------------------
// Description: Sets fill pattern
//   Parametrs: c	- new fill pattern number
//      Return: <none>
// -----------------------------------------------------------------------
delete m_pBrush;
COLORREF nColor=EGAtoRGB(m_nFillcolor);
m_pBrush=new CBrush();
if (nStyle==HS_SOLID)
	m_pBrush->CreateSolidBrush(nColor);
else
	m_pBrush->CreateHatchBrush(nStyle, nColor);
m_pDC->SelectObject(m_pBrush);
return(true);
}
// =======================================================================
BOOL CGDF::HDSetPenSize(int nSize)
{
delete m_pPen;
COLORREF nColor=EGAtoRGB(m_nColor);
m_pPen=new CPen(m_nLinestyle, nSize, nColor);
m_pDC->SelectObject(m_pPen);
return(true);
}
// =======================================================================
BOOL CGDF::HDSetPenStyle(int nStyle)
{
delete m_pPen;
COLORREF nColor=EGAtoRGB(m_nColor);
m_pPen=new CPen(nStyle, m_nThickness, nColor);
m_pDC->SelectObject(m_pPen);
return(true);
}
// =======================================================================
// Basic primitives
// =======================================================================
BOOL CGDF::Arc(int x1, int y1, int x2, int y2, int r, int c)
{
c=x1&x2&y1&y2&r&c;
return(true);
}
// =======================================================================
BOOL CGDF::Circle(int x, int y, int r, int na, double k, int c)
{ return SubCircle(x, y, r, na, k, c, -1);}
// =======================================================================
BOOL CGDF::CircleFill(int x, int y, int r, int na, double k, int c, int fc)
{ return SubCircle(x, y, r, na, k, c, fc); }
// =======================================================================
BOOL CGDF::DrawPoly(int _n_,int *_points_,int _angle_,double _k_,int _c_)
{
// -----------------------------------------------------------------------
// Description: Draws a polygon using the current line style and color.
//   Parametrs: n	- quantity of points
//		points	- ptr to a sequence of (numpoints x 2) integers
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//		c	- color
//      Return: <none>
// -----------------------------------------------------------------------
return (SubPoly(_n_,_points_,_angle_,_k_,_c_,-1)); }
// =======================================================================
BOOL CGDF::Ellipse (int nx1, int ny1, int nx2, int ny2, 
					int nAngle, double fk, int nc)
{ return(SubEllipse(nx1, ny1, nx2, ny2, nAngle, fk, nc, -1)); }
// =======================================================================
BOOL CGDF::EllipseFill(int nx1, int ny1, int nx2, int ny2, 
					int nAngle, double fk, int nc, int nfc)
{ return(SubEllipse(nx1, ny1, nx2, ny2, nAngle, fk, nc, nfc)); }
// =======================================================================
BOOL CGDF::Line (int x1, int y1, int x2, int y2, int angle,
	double k, int nc)
{
// -----------------------------------------------------------------------
// Description: Draws scalable line
//   Parametrs: x1, y1  - coordinates of start of line
//		x2, y2  - coordinates of end of line
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
int cx, cy;
int nx1, ny1, nx2, ny2;
double cs=cos(M_PI*angle/-180), sn=sin(M_PI*angle/-180);
//double cs=_pccos_deg(-angle), sn=_pcsin_deg(-angle);
// -----------------------------------------------------------------------
nx1=(int)(x1*cs-y1*sn); ny1=(int)(y1*cs+x1*sn);
nx2=(int)(x2*cs-y2*sn); ny2=(int)(y2*cs+x2*sn);
// -----------------------------------------------------------------------
cx=m_nScrCX; cy=m_nScrCY;
// -----------------------------------------------------------------------
SubLine((int)(cx+nx1*k), (int)(cy+ny1*k), (int)(cx+nx2*k), 
		(int)(cy+ny2*k), nc);
// -----------------------------------------------------------------------
if (m_bMirX)
	{
	nx1=(int)(x1*cs-(-y1)*sn);	ny1=(int)((-y1)*cs+x1*sn);
	nx2=(int)(x2*cs-(-y2)*sn);	ny2=(int)(-y2*cs+x2*sn);
	SubLine	((int)(cx+nx1*k), (int)(cy+ny1*k), (int)(cx+nx2*k), 
			(int)(cy+ny2*k), nc);}
// -----------------------------------------------------------------------
if (m_bMirY)
	{ 
	nx1=(int)(-x1*cs-y1*sn);	ny1=(int)(y1*cs+(-x1)*sn);
	nx2=(int)(-x2*cs-y2*sn);	ny2=(int)(y2*cs+(-x2)*sn);
	SubLine	((int)(cx+nx1*k), (int)(cy+ny1*k), (int)(cx+nx2*k), 
			(int)(cy+ny2*k), nc);}
// -----------------------------------------------------------------------
if (m_bMirXY)
	{
	nx1=(int)(-x1*cs-(-y1)*sn); ny1=(int)(-y1*cs+(-x1)*sn);
	nx2=(int)(-x2*cs-(-y2)*sn); ny2=(int)(-y2*cs+(-x2)*sn);
	SubLine	((int)(cx+nx1*k), (int)(cy+ny1*k), (int)(cx+nx2*k), 
			(int)(cy+ny2*k), nc);}
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CGDF::LineCurve(int x1, int y1, int x2, int y2, int nxd1, 
					 int nyd1, int nxd2, int nyd2, int nAngle, 
					 double dk, int nc)
{
POINT pP[4];
pP[0]=PixTransform(x1, y1, -nAngle, dk);
pP[1]=PixTransform(nxd1, nyd1, -nAngle, dk);
pP[2]=PixTransform(nxd2, nyd2, -nAngle, dk);
pP[3]=PixTransform(x2, y2, -nAngle, dk);
return HDPolyBFill(4, pP, nc, -1);
}
// =======================================================================
BOOL CGDF::LineTo(int nx, int ny, int nAngle, double fk, int nc)
{
POINT tP=PixTransform(nx, ny, nAngle, fk);
return HDLineTo(tP.x, tP.y, nc);
}
// =======================================================================
BOOL CGDF::LineRel(int ndx, int ndy, int nAngle, double fk, int nc)
{
POINT tP=PixTransform(ndx, ndy, nAngle, fk);
return HDLineRel(tP.x, tP.y, nc);
}
// =======================================================================
BOOL CGDF::MoveTo(int nx, int ny, int nAngle, double fk)
{
POINT tP=PixTransform(nx, ny, nAngle, fk);
return HDMoveTo(tP.x, tP.y);
}
// =======================================================================
BOOL CGDF::PolyBFill(int nn, int *points, int nAngle, double dk, 
					 int nc, int nfc)
{ return SubPolyB(nn, points, nAngle, dk, nc, nfc); }
// =======================================================================
BOOL CGDF::PolyFill(int nn, int* points, int nAngle, double fk,
	int nc, int nfc)
{ return SubPoly(nn, points, nAngle, fk, nc, nfc); }
// =======================================================================
BOOL CGDF::PutPixel(int nx, int ny, int nAngle, double fk, int nc)
{
// -----------------------------------------------------------------------
// Description: Draws scalable pixel
//   Parametrs: x, y	- coordiantes
//              k       - scaling ratio
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
POINT p=PixTransform(nx, ny, -nAngle, fk);
// -----------------------------------------------------------------------
if (fk<1.5)
	HDPutPixel(p.x, p.y, nc);
else if (fk>=1.5 && fk<2.5)
	{
	HDPutPixel(p.x, p.y, nc);
	HDPutPixel(p.x-1, p.y, nc); HDPutPixel(p.x+1, p.y, nc);
	HDPutPixel(p.x,	p.y-1, nc); HDPutPixel(p.x, p.y+1, nc);
	}
else
	{ //HDPutPixel(p.x, p.y, nc);
	SubCircle(nx, ny, 1, nAngle, fk, nc, nc);
	}
return(true);
}
// =======================================================================
BOOL CGDF::Rect(int x1, int y1, int x2, int y2, int angle,double k, int c)
{ return SubRect(x1, y1, x2, y2, angle, k, c, -1); }
// =======================================================================
BOOL CGDF::RectBar (int x1, int y1, int x2, int y2, int angle,
	double k, int c, int fc)
{ return SubRect (x1, y1, x2, y2, angle, k, c, fc); }
// =======================================================================
BOOL CGDF::RectFill(int x1, int y1, int x2, int y2, int angle,
	double k, int c, int fc)
{ return SubRect (x1, y1, x2, y2, angle, k, c, fc); }
// =======================================================================
BOOL CGDF::Sector (int nx, int ny, int nstangle, int nendangle,
	int nxradius, int nyradius, int nc)
{
// -----------------------------------------------------------------------
// Description: Draws and fills unscalable sector
//   Parametrs: x, y	- Center of ellipse
//		xradius	- Horizontal axis
//		yradius	- Vertical axis
//		stangle	- Starting angle
//		endangle - Ending angle
//      Return: <none>
// -----------------------------------------------------------------------
SetColor(nc);
//sector (x, y, stangle, endangle, xradius, yradius);
return(true);
}
// =======================================================================
// Sub functions
// =======================================================================
BOOL CGDF::SubCircle(int x, int y, int r, int nAngle, double fk, 
					 int c, int fc)
{
//*
POINT p;
int nNewR=(int)(r*fk);
p=PixTransform(x, y, -nAngle, fk);
return (HDEllipseFill(p.x-nNewR, p.y-nNewR, p.x+nNewR, p.y+nNewR, 
		c, fc));//*/
//return(SubEllipse(x-r, y-r, x+r, y+r, nAngle, fk, c, fc));
}
// =======================================================================
BOOL CGDF::SubEllipse(int x1, int y1, int x2, int y2, int nAngle,
					  double fk, int c, int fc)
{
POINT tL, tR;
tL=PixTransform(x1, y1, -nAngle, fk);
tR=PixTransform(x2, y2, -nAngle, fk);
return (HDEllipseFill(tL.x, tL.y, tR.x, tR.y, c, fc));
}
// =======================================================================
BOOL CGDF::SubLine (int nx1, int ny1, int nx2, int ny2, int nc)
{
// -----------------------------------------------------------------------
// Description: Draws unscalable HIF line
//   Parametrs: x1, y1  - coordinates of start of line
//		x2, y2  - coordinates of end of line
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
HDMoveTo(nx1, ny1); HDLineTo(nx2, ny2, nc);
return(true);
}
// =======================================================================
BOOL CGDF::SubPoly(int nn, int *points, int nAngle, double fk, 
				   int nc, int nfc)
{
int i;
POINT *ptrpoint;
// -----------------------------------------------------------------------
ptrpoint=new POINT[nn+1];
if (!ptrpoint) return (false);
for (i=0; i<nn; i++)	
	ptrpoint[i]=PixTransform(points[i*2+0], points[i*2+1], 
				-nAngle, fk);	
// -----------------------------------------------------------------------
HDPolyFill(nn, ptrpoint, nc, nfc); delete ptrpoint;
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CGDF::SubPolyB(int nn, int *points, int nAngle, double dk, 
					int nc, int nfc)
{
int i;
POINT *ptrpoint;
// -----------------------------------------------------------------------
ptrpoint=new POINT[nn+1];
if (!ptrpoint) return (false);
for (i=0; i<nn; i++)	
	ptrpoint[i]=PixTransform(points[i*2+0], points[i*2+1], 
				-nAngle, dk);	
// -----------------------------------------------------------------------
HDPolyBFill(nn, ptrpoint, nc, nfc); delete ptrpoint;
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CGDF::SubRect (int x1, int y1, int x2, int y2, int angle,
	double k, int c, int fc)
{
// -----------------------------------------------------------------------
// Description: Draws scalable rectangle
//   Parametrs: x1, y1  - coordinates of lower left corner
//		x2, y2  - coordinates of upper right corner
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//              c       - color flag
//		fc	- fill color
//      Return: <none>
// -----------------------------------------------------------------------
int rect[10];
rect[0]=x1; rect[1]=y1; rect[2]=x2; rect[3]=y1;
rect[4]=x2; rect[5]=y2; rect[6]=x1; rect[7]=y2;
rect[8]=x1; rect[9]=y1;
SubPoly(5, rect, angle, k, c, fc);
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CGDF::SubTri (int x1, int y1, int x2, int y2,
	int x3, int y3, int angle, double k, int c, int fc)
{
// -----------------------------------------------------------------------
// Description: Draws scalable triangle
//   Parametrs: x1,y1,x2,y2,x3,y3	- coordinates of corners
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//              c       - color flag
//		fc	- fill color
//      Return: <none>
// -----------------------------------------------------------------------
int tri[8];
tri[0]=x1; tri[1]=y1; tri[2]=x2; tri[3]=y2;
tri[4]=x3; tri[5]=y3; tri[6]=x1; tri[7]=y1;
return SubPoly(4, tri, angle, k, c, fc);
// -----------------------------------------------------------------------
}
// =======================================================================
// Service functions
// =======================================================================
COLORREF CGDF::EGAtoRGB(int nc)
{
// -----------------------------------------------------------------------
// Description: Converts EGA 16 bit color to RGB format
//   Parametrs: nColor        - color
//      Return: RGB color
// -----------------------------------------------------------------------
BOOL r, g, b, br;
int nr, ng, nb, nbr;
COLORREF nColor;
b=nc&1;		g=(nc>>1)&1;	r=(nc>>2)&1;	br=(nc>>3)&1;
nr=r*155;	ng=g*155;		nb=b*155;		nbr=br*100;
nColor=RGB(nr+nbr, ng+nbr, nb+nbr);
return (nColor);
}
// =======================================================================
BOOL CGDF::Update(void)
{
// -----------------------------------------------------------------------
// Description: Updates graphics parametrs
//   Parametrs: <none>
//      Return: <none>
// -----------------------------------------------------------------------
/*
setcolor(nColor);
setwritemode(m_writemode);
setlinestyle(m_linestyle, m_upattern,
	m_thickness);
setfillstyle(m_fillpattern, m_fillcolor);*/
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
POINT CGDF::PixTransform(int nx, int ny, int nAngle, 
								 double fk)
{
// -----------------------------------------------------------------------
// Description: Scales & rotates pixel coordinates
//   Parametrs: x, y	- pixel coordinates
//		angle	- rotation angle
//		k	- scaling ratio
//      Return: scaled & rotated structure
// -----------------------------------------------------------------------
double cs=cos(M_PI*nAngle/180), sn=sin(M_PI*nAngle/180);
POINT npix;
// -----------------------------------------------------------------------
npix.x=m_nScrCX+(int)(((double)nx*cs-ny*sn)*fk);
npix.y=m_nScrCY+(int)(((double)ny*cs+nx*sn)*fk);
// -----------------------------------------------------------------------
return (npix);
}
// =======================================================================
BOOL CGDF::Tri (int x1, int y1, int x2, int y2,
	int x3, int y3, int angle, double k, int c)
{
// -----------------------------------------------------------------------
// Description: Draws scalable triangle
//   Parametrs: x1,y1,x2,y2,x3,y3	- coordinates of corners
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
return SubTri (x1, y1, x2, y2, x3, y3, angle, k, c, -1);
}
// =======================================================================
BOOL CGDF::TriFill(int x1, int y1, int x2, int y2,
	int x3, int y3, int angle, double k, int c, int fc)
{
// -----------------------------------------------------------------------
// Description: Draws scalable triangle
//   Parametrs: x1,y1,x2,y2,x3,y3	- coordinates of corners
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
return SubTri (x1, y1, x2, y2, x3, y3, angle, k, c, fc);
}
// =======================================================================
// Public functions ... PCGDF
// =======================================================================
BOOL CGDF::Put (int px, int py, int angle, double k, int* obj)
{
// -----------------------------------------------------------------------
BOOL bDrawBezier=false;
int i=0;
int j, n, x, y, x1, y1, x2, y2, x3, y3, x4, y4, r, c, fc;
int* poly;
// -----------------------------------------------------------------------
if (!m_pDC) return(false);
InitDC();
m_nScrCX=px;
m_nScrCY=py;
// -----------------------------------------------------------------------
do
{
// -----------------------------------------------------------------------
switch (obj[i])
	{
	// ---------------------------------------------------------------
	// Main graphics primitives
	// ---------------------------------------------------------------
	case GDF_CC:
		switch(obj[i+1])
			{
			case GDF_CPSZ: SetPenSize(obj[i+2]); i+=2; break;
			case GDF_CPST: SetPenStyle(obj[i+2]); i+=2; break;
			case GDF_CBRST: SetFillStyle(obj[i+2]); i+=2; break;
			default: i++; break;
			};
		i++; break;
	case GDF_PTR:	x=obj[i+1]; y=obj[i+2];
			MoveTo(x, y, angle, k); i+=3; break;
	case GDF_PIX:	x=obj[i+1]; y=obj[i+2]; c=obj[i+3];
			PutPixel(x, y, angle, k, c); i+=4; break;
	case GDF_LNT:	x=obj[i+1]; y=obj[i+2]; c=obj[i+3];
			LineTo(x, y, angle, k, c); i+=4; break;
	case GDF_LNR:	x=obj[i+1]; y=obj[i+2]; c=obj[i+3];
			LineRel(x, y, angle, k, c); i+=4; break;
	// ---------------------------------------------------------------
	case GDF_LN:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4]; c=obj[i+5];
			Line(x1, y1, x2, y2, angle, k, c); i+=6;
			break;
	// ---------------------------------------------------------------
	case GDF_LNC:	x1=obj[i+1]; y1=obj[i+2];
					x2=obj[i+3]; y2=obj[i+4]; 
					x3=obj[i+5]; y3=obj[i+6]; 
					x4=obj[i+7]; y4=obj[i+8]; 
					c=obj[i+9];
			LineCurve(x1, y1, x2, y2, x3, y3, x4, y4, angle, 
				k, c); i+=10; break;
	// ---------------------------------------------------------------
	case GDF_POLYB: bDrawBezier=true;
	case GDF_POLY:	n=obj[i+1]; c=obj[i+2+n*2];
			poly=new int[n*2];
			if (!poly)
				{i=i+3+n*2; break;}
			for (j=0; j<n; j++)
				{ poly[j*2+0]=obj[i+2+j*2+0];
				poly[j*2+1]=obj[i+2+j*2+1]; }
			if (bDrawBezier) PolyBFill(n, poly, angle, k, c, -1);
			else DrawPoly(n, poly, angle, k, c); 
			i=i+3+n*2; bDrawBezier=false;
			delete poly; break;
	// ---------------------------------------------------------------
	case GDF_POLYBFL: bDrawBezier=true;
	case GDF_POLYFL:	n=obj[i+1]; c=obj[i+2+n*2]; fc=obj[i+2+n*2+1];
			poly=new int[n*2];
			if (!poly)
				{i=i+4+n*2; break;}
			for (j=0; j<n; j++)
				{ poly[j*2+0]=obj[i+2+j*2+0];
				poly[j*2+1]=obj[i+2+j*2+1]; }
			if (bDrawBezier) PolyBFill(n, poly, angle, k, c, fc);
			else PolyFill(n, poly, angle, k, c, fc); 
			i=i+4+n*2; bDrawBezier=false;
			delete poly; break;
	// ---------------------------------------------------------------
	case GDF_ELL:	x1=obj[i+1]; y1=obj[i+2]; 
					x2=obj[i+3]; y2=obj[i+4]; c=obj[i+5];
			Ellipse(x1, y1, x2, y2, angle, k, c); i+=6; break;
	// ---------------------------------------------------------------
	case GDF_ELLFL:	x1=obj[i+1]; y1=obj[i+2]; 
					x2=obj[i+3]; y2=obj[i+4]; c=obj[i+5];
					fc=obj[i+6];
			EllipseFill(x1, y1, x2, y2, angle, k, c, fc); i+=7; 
			break;
	// ---------------------------------------------------------------
	// Figures
	// ---------------------------------------------------------------
	case GDF_RECT:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4]; c=obj[i+5];
			Rect(x1, y1, x2, y2, angle, k, c); i+=6;
			break;
	// ---------------------------------------------------------------
	case GDF_RECTFL:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4]; c=obj[i+5]; fc=obj[i+6];
			RectBar(x1, y1, x2, y2, angle, k, c, fc); i+=7;
			break;
	// ---------------------------------------------------------------
	case GDF_TRI:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4];
			x3=obj[i+5]; y3=obj[i+6]; c=obj[i+7];
			Tri(x1, y1, x2, y2, x3, y3,angle, k, c); i+=8;
			break;
	// ---------------------------------------------------------------
	case GDF_TRIFL:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4];
			x3=obj[i+5]; y3=obj[i+6]; c=obj[i+7]; fc=obj[i+8];
			TriFill(x1, y1, x2, y2, x3, y3,angle, k, c, fc);
			i+=9; break;
	// ---------------------------------------------------------------
	case GDF_CIRC:	x=obj[i+1]; y=obj[i+2];
			r=obj[i+3]; c=obj[i+4];
			Circle(x, y, r, angle, k, c); i+=5;
			break;
	// ---------------------------------------------------------------
	case GDF_CIRCFL:	x=obj[i+1]; y=obj[i+2];
			r=obj[i+3]; c=obj[i+4]; fc=obj[i+5];
 			CircleFill(x, y, r, angle, k, c, fc); i+=6;
			break;
	// ---------------------------------------------------------------
	default: break;
	}
// -----------------------------------------------------------------------
} while(obj[i]!=NULL && i<32767);
return(true);
}
// =======================================================================
BOOL CGDF::DrawStars(int npx, int npy, int nwd, int nhg, 
					 int nMaxStars)
{
#define random(_x_)	(rand()%(_x_))
// -----------------------------------------------------------------------
// Description: Draws stars on black sky
//   Parametrs: maxstars        - max quantity of stars
//      Return: <none>
// -----------------------------------------------------------------------
if (!m_pDC) return(false);
srand((unsigned)time(NULL));
for (int i=0; i<nMaxStars; i++)
	{ PutPixel (npx+random(nwd-1), npy+random(nhg-1), 0,
		(double)(random(2)+1), 0+8*random(2));
	PutPixel (npx+random(nwd-1), npy+random(nhg-1), 0,
			(double)(random(2)+1), 7+8*random(2)); 
	//PutPixel (npx+random(nwd-1), npy+random(nhg-1),0, 2, 1+random(16)); 
	}
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CGDF::SetPenStyle(int nStyle)
{
if (m_nLinestyle==nStyle) return(true);
m_nLinestyle=nStyle;
return HDSetPenStyle(m_nLinestyle); 
}
// =======================================================================
BOOL CGDF::SetFillStyle(int nStyle)
{
if (m_nFillpattern==nStyle) return(true);
m_nFillpattern=nStyle;
return HDSetFillPattern(nStyle);
}
// =======================================================================
BOOL CGDF::SetFillColor(int nColor)
{
if (nColor==-1) return(true);
if (nColor==m_nFillcolor) return(true);
m_nFillcolor=nColor;
return HDSetFillColor(nColor); }
// =======================================================================
BOOL CGDF::SetColor(int nColor)
{
if (nColor==-1) return(true);
if (nColor==m_nColor) return(true);
m_nColor=nColor;
return HDSetColor(nColor); 
}
// =======================================================================
BOOL CGDF::SetPenSize(int nSize)
{
if (nSize<1 || nSize>5) return(true);
if (nSize==m_nThickness) return(true);
m_nThickness=nSize;
return HDSetPenSize(nSize);
}
// =======================================================================
