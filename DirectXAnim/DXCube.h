/**************************************************/
/*		@Author	: Marco
/*		@Date	: 16 / 01 / 2015
/*		@Desc	: Header de la classe DXCube.
/**************************************************/

#ifndef _DXCUBE_H_
#define _DXCUBE_H_

class DXCube
{
	public:
		
		DXCube( LPDIRECT3DDEVICE9 _Device, CUSTOMVERTEX3D *_customvertices );
		~DXCube();

		void Display();

	private:
	
		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device
		LPDIRECT3DVERTEXBUFFER9	m_pVB;				// Buffer to hold Vertices
		LPDIRECT3DINDEXBUFFER9	m_pIB;				// Buffer to hold Indexes

};

#endif