/**************************************************/
/*		@Author	: Marco
/*		@Date	: 16 / 01 / 2015
/*		@Desc	: Header de la classe DXTriangle3D.
/**************************************************/

#ifndef _DXTRIANGLE3D_H_
#define _DXTRIANGLE3D_H_

class DXTriangle3D
{
	public:

		DXTriangle3D( LPDIRECT3DDEVICE9 _Device, CUSTOMVERTEX3D *_customvertices );
		~DXTriangle3D();

		void Display();

	private:
	
		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device
		LPDIRECT3DVERTEXBUFFER9	m_pVB;				// Buffer to hold Vertices
};

#endif