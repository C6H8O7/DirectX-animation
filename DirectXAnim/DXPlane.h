/**************************************************/
/*		@Author	: Marco
/*		@Date	: 15 / 01 / 2015
/*		@Desc	: Header de la classe DXPlane.
/**************************************************/

#ifndef _DXPLANE_H_
#define _DXPLANE_H_

class DXPlane
{
	public:

		DXPlane( LPDIRECT3DDEVICE9 _Device, FLOAT _x, FLOAT _y, FLOAT _w, FLOAT _h, INT _dW, INT _dH, DWORD _color );
		~DXPlane();

		void Display();

	private:
	
		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device
		LPDIRECT3DVERTEXBUFFER9	*m_ppVB;			// Buffer to hold Vertices

		INT m_iVerticeCount;
		INT m_iTriCount;

		INT m_iNbStrips;
		INT m_iStripsTri;
};

#endif