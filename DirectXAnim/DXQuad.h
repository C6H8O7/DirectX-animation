/**************************************************/
/*		@Author	: Marco
/*		@Date	: 15 / 01 / 2015
/*		@Desc	: Header de la classe DXQuad.
/**************************************************/

#ifndef _DXQUAD_H_
#define _DXQUAD_H_

class DXQuad
{
	public:
		
		DXQuad(LPDIRECT3DDEVICE9 _device, CUSTOMVERTEX2D *_customvertices);
		DXQuad(LPDIRECT3DDEVICE9 _device, FLOAT _x, FLOAT _y, FLOAT _w, FLOAT _h, DWORD _color);
		~DXQuad();

		void Display();

	private:
	
		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device
		LPDIRECT3DVERTEXBUFFER9	m_pVB;				// Buffer to hold Vertices
};

#endif