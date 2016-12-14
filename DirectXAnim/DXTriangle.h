/**************************************************/
/*		@Author	: Marco
/*		@Date	: 15 / 01 / 2015
/*		@Desc	: Header de la classe DXTriangle.
/**************************************************/

#ifndef _DXTRIANGLE_H_
#define _DXTRIANGLE_H_

class DXTriangle
{
	public:

		DXTriangle( LPDIRECT3DDEVICE9 _Device, CUSTOMVERTEX2D *_customvertices );
		~DXTriangle();

		void Display();

	private:
	
		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device
		LPDIRECT3DVERTEXBUFFER9	m_pVB;				// Buffer to hold Vertices
};

#endif