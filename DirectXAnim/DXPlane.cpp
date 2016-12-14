#include "stdafx.h"

DXPlane::DXPlane(LPDIRECT3DDEVICE9 _Device, FLOAT _x, FLOAT _y, FLOAT _w, FLOAT _h, INT _dW, INT _dH, DWORD _color) : m_pd3dDevice(_Device)
{
	m_iNbStrips = _dH;
	m_iStripsTri = _dW;

	m_iVerticeCount = m_iStripsTri + 2;

	m_ppVB = new LPDIRECT3DVERTEXBUFFER9[m_iNbStrips];

	CUSTOMVERTEX2D *vertices = new CUSTOMVERTEX2D[m_iVerticeCount];
	
	FLOAT w = _w / (FLOAT)_dW * 2.0f;
	FLOAT h = _h / (FLOAT)_dH;

	DWORD color = _color;

	for(INT i=0; i<m_iNbStrips; i++)
	{
		vertices[0].x = _x;
		vertices[0].y = _y + (i+1) * h;
		vertices[0].z = 0.5f;
		vertices[0].rhw = 1.0f;
		vertices[0].color = color;

		vertices[1].x = _x;
		vertices[1].y = _y + i * h;
		vertices[1].z = 0.5f;
		vertices[1].rhw = 1.0f;
		vertices[1].color = color;

		for(INT j=0; j<_dW; j++)
		{
			vertices[2 + j].x = _x + ((j+2) / 2) * w;
			vertices[2 + j].y = _y + i * h + ((j+1) % 2) * h;
			vertices[2 + j].z = 0.5f;
			vertices[2 + j].rhw = 1.0f;
			vertices[2 + j].color = color;
		}

		Game::InitVB(m_pd3dDevice, vertices, m_iVerticeCount, &m_ppVB[i], sizeof(CUSTOMVERTEX2D), D3DFVF_CUSTOMVERTEX2D);
	}

	delete vertices;
}

DXPlane::~DXPlane()
{
	for(INT i=0; i<m_iNbStrips; i++)
		SafeRelease( m_ppVB[i] );

	delete m_ppVB;
}

void DXPlane::Display()
{
	for(INT i=0; i<m_iNbStrips; i++)
	{
		m_pd3dDevice->SetStreamSource( 0, m_ppVB[i], 0, sizeof( CUSTOMVERTEX2D ) );
		m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX2D );
		m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, m_iStripsTri );
	}
}