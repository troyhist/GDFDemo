// =======================================================================
// Graphics Drawer Files function library ver. 1.0 (CPP)
// Troy computing, Inc.
// Copyright (c) 1994-2002
// -----------------------------------------------------------------------
// GDF Vector graphics support library.
// Used library: UPGL
// -----------------------------------------------------------------------
// File: GDF.h
// -----------------------------------------------------------------------
//     Compiler: Borland C++ 3.1
//  Application: Win32 GUI
// -----------------------------------------------------------------------
// Made date: 07/ IX.2000
// Last edit: 30/ 07.2002
//     Build: 1
// =======================================================================
// GDF.h: interface for the CGDF class.
// =======================================================================
#if !defined(AFX_GDF_H__841CE96B_6D61_47BD_897B_1F91C6E8C343__INCLUDED_)
#define AFX_GDF_H__841CE96B_6D61_47BD_897B_1F91C6E8C343__INCLUDED_
// =======================================================================
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// =======================================================================
// Win MFC include
// =======================================================================
#include "stdafx.h"
// =======================================================================
// GDF commands
// =======================================================================
#define GDF_CSTOP	0
#define GDF_CC		1
// Basics
#define GDF_PTR		2
#define GDF_PIX		3
#define GDF_LNT		4
#define GDF_LNR		5
#define GDF_LN		6
#define GDF_LNC		7
// Polygons & Spilnes
#define GDF_POLY	8
#define GDF_POLYFL	9
#define GDF_POLYB	10
#define GDF_POLYBFL	11
// Figures
#define GDF_ARC		13
#define GDF_ELL		15
#define GDF_ELLFL	16
#define GDF_RECT	17
#define GDF_RECTFL	18
#define GDF_TRI		19
#define GDF_TRIFL	20
#define GDF_CIRC	21
#define GDF_CIRCFL	22
// GDF control code commands
#define HS_SOLID	-1
#define GDF_CPSZ	1
#define GDF_CPST	2
#define GDF_CBRST	3
// =======================================================================
class CGDF  
{
public:
	BOOL DrawStars(int npx, int npy, int nwd, int nhg, int nMaxStars);
	BOOL SetDC(CDC* pDC);
	CGDF();
	virtual ~CGDF();
	BOOL Put (int px, int py, int nAngle, double fk, int* pObj);
// -------------------------------------------------------------------
private:			
	BOOL HDSetPenSize(int nSize);
	BOOL SetPenSize(int nSize);
	BOOL ResetData();
	BOOL SetColor(int nColor);
	BOOL InitDC();
	BOOL SetFillColor(int nColor);
	BOOL HDSetPenStyle(int nStyle);
	BOOL SetFillStyle(int nStyle);
	BOOL SetPenStyle(int nStyle);
	// ---------------------------------------------------------------
	// Pixel 2D
	// ---------------------------------------------------------------	
	// Device context
	// ---------------------------------------------------------------
	CDC* m_pDC;
	CPen* m_pPen;		// pen
	CBrush* m_pBrush;	// brush
	// ---------------------------------------------------------------
	int m_nColor;
	int m_nWritemode;	
	// ---------------------------------------------------------------
	// 2. linesettingstype
	// ---------------------------------------------------------------
	int m_nLinestyle;
	int m_nUpattern;
	int m_nThickness;
	// ---------------------------------------------------------------
	// 3. fillsettingstype
	// ---------------------------------------------------------------
	int m_nFillpattern;	// current fill pattern
	int m_nFillcolor;	// current fill color
	// ---------------------------------------------------------------
	// 4. Special settings
	// ---------------------------------------------------------------
	int m_bMirX;		// make mirror copy via OX
	int m_bMirY;		// make mirror copy via OY
	int m_bMirXY;		// make mirror copy via XOY
	int m_nScrCX;		// X center of screen
	int m_nScrCY;		// Y center of screen
	int m_bEnfill;		// Enable filling
	// ---------------------------------------------------------------	
	// HDF (Hardware depended functions)
	// ---------------------------------------------------------------
	BOOL HDEllipseFill(int x1, int y1, int x2, int y2, int nc, int nfc);
	BOOL HDPolyBFill(int nn, POINT* points, int nc, int nfc);
	BOOL HDPolyFill(int nn, POINT* points, int nc, int nfc);	
	BOOL HDLineRel(int ndx, int ndy, int nc);
	BOOL HDLineTo(int npx, int npy, int nc);
	BOOL HDMoveTo(int npx, int npy);
	BOOL HDPutPixel (int npx, int npy, int nc);
	BOOL HDSetColor (int nc);
	BOOL HDSetFillColor (int nc);
	BOOL HDSetFillPattern (int nc);
	// ---------------------------------------------------------------
	BOOL LineCurve(int x1, int y1, int x2, int y2, int nxd1, int nyd1, int nxd2, int nyd2, int nAngle, double dk, int nc);
	BOOL PolyBFill(int nn, int* points, int nAngle, double dk, int nc, int fc);
	BOOL SubPolyB(int nn, int *points, int nAngle, double dk, int nc, int nfc);
	BOOL SubEllipse(int x1, int y1, int x2, int y2, int nAngle, double fk, int c, int fc);
	BOOL LineRel(int ndx, int ndy, int nAngle, double fk, int nc);
	BOOL LineTo(int nx, int ny, int nAngle, double fk, int nc);
	BOOL MoveTo(int nx, int ny, int nAngle, double fk);
	COLORREF EGAtoRGB(int nColor);
	// ---------------------------------------------------------------
	BOOL Update();
	POINT PixTransform(int npx, int npy, int nAngle, double fK);
	BOOL PolyFill(int nn, int* pPoints, int nAngle, double fk,
		int nc, int fc);
	BOOL Ellipse (int nx1, int ny1, int nx2, int ny2, int nAngle, 
		double fk, int nc);
	BOOL EllipseFill (int nx1, int ny1, int nx2, int ny2, 
		int nAngle, double fk, int nc, int fc);
	BOOL Sector (int nx, int ny, int nstangle, int nendangle,
		int nxradius, int nyradius, int nc);
	BOOL DrawPoly (int nn, int* points, int nangle, double k,
		int nc);	
	BOOL Arc(int x1, int y1, int x2, int y2, int r, int c);
	// ---------------------------------------------------------------
	// Sub functions
	// ---------------------------------------------------------------
	BOOL SubPoly(int nn, int* points, int nAngle, double fk, int nc, int nfc);
	BOOL SubLine(int nx1, int ny1, int nx2, int ny2, int nc);
	BOOL SubRect(int nx1, int ny1, int nx2, int ny2, int nangle,
		double k, int nc, int nfc);
	BOOL SubTri (int nx1, int ny1, int nx2, int ny2,
		int nx3, int ny3, int nangle, double k, int nc, int nfc);
	BOOL SubCircle(int nx, int ny, int nr, int na, double k, int nc, int nfc);
	// ---------------------------------------------------------------
	// HIF (Hardware independed functions)
	// ---------------------------------------------------------------	
	BOOL PutPixel(int nx, int ny, int nAngle, double k, int nc);	
	BOOL Line (int nx1, int ny1, int nx2, int ny2, int nangle,
		double k, int nc);
	BOOL RectFill(int nx1, int ny1, int nx2, int ny2, int nangle,
		double k, int nc, int nfc);
	BOOL RectBar (int nx1, int ny1, int nx2, int ny2, int nangle,
		double k, int nc, int nfc);
	BOOL Rect (int nx1, int ny1, int nx2, int ny2, int nangle,
		double k, int nc);
	BOOL Tri (int nx1, int ny1, int nx2, int ny2,
		int nx3, int ny3, int nangle, double k, int nc);
	BOOL TriFill(int nx1, int ny1, int nx2, int ny2,
		int nx3, int ny3, int nangle, double k, int nc, int nfc);
	BOOL Circle(int nx, int ny, int nr, int nang, double k, int nc);
	BOOL CircleFill(int nx, int ny, int nr, int nang, double k, int nc, int nfc);
};
// =======================================================================
#endif // !defined(AFX_GDF_H__841CE96B_6D61_47BD_897B_1F91C6E8C343__INCLUDED_)
// =======================================================================