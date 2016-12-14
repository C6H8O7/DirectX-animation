#include "stdafx.h"

DXTerrain::DXTerrain( LPDIRECT3DDEVICE9 _Device, FLOAT _w, FLOAT _h, FLOAT _d, INT _dW, INT _dH ) : m_pd3dDevice(_Device)
{
	m_iNbWDivision = _dW;
	m_iNbHDivision = _dH;

	m_iNbVertices = ((_dW + 1) * (_dH + 1)) * 2;
	m_iNbIndexes = (_dW + 1) * 2 * _dH * 2 + (_dH + 1) * 2 * 2 + (_dW + 1) * 2 * 2;

	m_pVertices = new CUSTOMVERTEX3D[m_iNbVertices];

	FLOAT w = _w / (FLOAT)_dW, h = _h / (FLOAT)_dH;
	FLOAT dw = _w / 2.0f, dh = _h / 2.0f, dd = _d / 2.0f;

	DWORD color = D3DCOLOR_XRGB(255, 0, 0);

	INT currentVertex = 0;

	for(INT k=0; k<2; k++)
	{
		for(INT i=0; i<m_iNbHDivision + 1; i++)
		{
			for(INT j=0; j<m_iNbWDivision + 1; j++)
			{
				m_pVertices[currentVertex].x = -dw + j * w;
				m_pVertices[currentVertex].y = -dd + dd * k;
				m_pVertices[currentVertex].z = -dh + i * h;
				m_pVertices[currentVertex].color = RANDCOLOR;

				currentVertex++;
			}
		}
	}

	m_iNbStrips = m_iNbHDivision * 2 + 1;
	m_iNbIndexesStrips = (m_iNbWDivision + 1) * 2;

	m_pIndexes = new WORD[m_iNbIndexes];

	INT currentIndex = 0;

	for(INT i=0; i<m_iNbHDivision; i++)
	{
		m_pIndexes[currentIndex++] = (m_iNbWDivision + 1) * (i + 1);

		m_pIndexes[currentIndex++] = (m_iNbWDivision + 1) * i;

		for(INT j=0; j<m_iNbWDivision * 2; j++)
		{
			m_pIndexes[currentIndex++] = (j%2 ? 0 : 1) * (m_iNbWDivision + 1) + j/2 + i * (m_iNbWDivision + 1) + 1;
		}
	}

	for(INT i=0; i<m_iNbHDivision; i++)
	{
		m_pIndexes[currentIndex++] = (m_iNbWDivision + 1) * i + m_iNbVertices / 2;

		m_pIndexes[currentIndex++] = (m_iNbWDivision + 1) * (i + 1) + m_iNbVertices / 2;

		for(INT j=0; j<m_iNbWDivision * 2; j++)
		{
			m_pIndexes[currentIndex++] = (j%2) * (m_iNbWDivision + 1) + j/2 + i * (m_iNbWDivision + 1) + 1 + m_iNbVertices / 2;
		}
	}

	for(INT i=0; i<(m_iNbHDivision + 1) * 2; i++)
		m_pIndexes[currentIndex++] = (i%2 ? 0 : 1) * (m_iNbVertices / 2) + (i/2) * (m_iNbWDivision + 1);

	for(INT i=0; i<m_iNbWDivision * 2; i++)
		m_pIndexes[currentIndex++] = (i%2 ? 0 : 1) * (m_iNbVertices / 2) + (i/2) + (m_iNbWDivision + 1) * m_iNbHDivision + 1;

	for(INT i=0; i<m_iNbHDivision * 2; i++)
		m_pIndexes[currentIndex++] = (i%2 ? 0 : 1) * (m_iNbVertices / 2) - (i/2) * (m_iNbWDivision + 1) + (m_iNbVertices / 2) - (m_iNbWDivision + 2);

	for(INT i=0; i<m_iNbWDivision * 2; i++)
		m_pIndexes[currentIndex++] = (i%2 ? 0 : 1) * (m_iNbVertices / 2) - (i/2) + m_iNbWDivision - 1;

	Game::InitVB(m_pd3dDevice, m_pVertices, m_iNbVertices, &m_pVB, sizeof(CUSTOMVERTEX3D), D3DFVF_CUSTOMVERTEX3D);
	Game::InitIB(m_pd3dDevice, m_pIndexes, m_iNbIndexes, &m_pIB, sizeof(WORD), D3DFMT_INDEX16);
}

DXTerrain::~DXTerrain()
{
	SafeRelease( m_pVB );
	SafeRelease( m_pIB );

	SafeDelete( m_pVertices );
	SafeDelete( m_pIndexes );
}

void DXTerrain::Display()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	D3DXMATRIXA16 matRot2;
    FLOAT fAngle = timeGetTime()%10000 * ( 2.0f * D3DX_PI ) / 10000.0f;
    D3DXMatrixRotationY( &matRot2, fAngle );
	matWorld *= matRot2;

	D3DXMATRIXA16 matRot3;
    D3DXMatrixRotationZ( &matRot3, fAngle );
	matWorld *= matRot3;

	 m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	// Render the vertex buffer contents
	m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX3D ) );
	m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3D );
	m_pd3dDevice->SetIndices( m_pIB );

	for(INT i=0; i<m_iNbStrips - 1; i++)
		m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, m_iNbVertices, m_iNbIndexesStrips * i, m_iNbWDivision * 2 );

	m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, m_iNbVertices, m_iNbIndexesStrips * m_iNbHDivision * 2, m_iNbHDivision * 4 + m_iNbWDivision * 4 );
}