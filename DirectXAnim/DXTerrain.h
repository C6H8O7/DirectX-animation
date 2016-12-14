/**************************************************/
/*		@Author	: Marco
/*		@Date	: 19 / 01 / 2015
/*		@Desc	: Header de la classe DXTerrain.
/**************************************************/

#ifndef _DXTERRAIN_H_
#define _DXTERRAIN_H_

class DXTerrain
{
	public:

		DXTerrain( LPDIRECT3DDEVICE9 _Device, FLOAT _w, FLOAT _h, FLOAT _d, INT _dW, INT _dH );
		~DXTerrain();

		void Display();

	private:
	
		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device
		LPDIRECT3DVERTEXBUFFER9	m_pVB;				// Buffer to hold Vertices
		LPDIRECT3DINDEXBUFFER9	m_pIB;				// Buffer to hold Indexes
		
		INT						m_iNbWDivision;
		INT						m_iNbHDivision;
		INT						m_iNbVertices;
		INT						m_iNbIndexes;

		CUSTOMVERTEX3D			*m_pVertices;
		WORD					*m_pIndexes;

		INT						m_iNbStrips;
		INT						m_iNbIndexesStrips;
};

#endif