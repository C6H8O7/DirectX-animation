/**************************************************/
/*		@Author	: Marco
/*		@Date	: 16 / 01 / 2015
/*		@Desc	: Header de la classe DXCuboid.
/**************************************************/

#ifndef _DXCUBOID_H_
#define _DXCUBOID_H_

class DXCuboid
{
	public:

		DXCuboid( LPDIRECT3DDEVICE9 _Device, FLOAT _w, FLOAT _h, FLOAT _d );
		~DXCuboid();

		void Display();

		void SetPosition(FLOAT _x, FLOAT _y, FLOAT _z);
		void SetRotation(D3DXQUATERNION _q);

		void SetMaterial(D3DMATERIAL9 _mat);

		void SetTransform(D3DXMATRIXA16 *_mat);

private:
	
		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device
		LPDIRECT3DVERTEXBUFFER9	m_pVB;				// Buffer to hold Vertices
		LPDIRECT3DINDEXBUFFER9	m_pIB;				// Buffer to hold Indexes

		D3DXVECTOR3				m_Position;
		LPD3DXQUATERNION		m_Rotation;

		D3DMATERIAL9			*m_Material;

		D3DXMATRIXA16			*m_Transform;
};

#endif