#include "stdafx.h"

Mesh::Mesh()
	: m_pd3dDevice(nullptr)
{

}

Mesh::Mesh(Mesh& _cpy)
	: m_pd3dDevice(_cpy.m_pd3dDevice)
{
	for(int i=0; i<(int)_cpy.m_vecSubMesh.size(); i++)
	{
		SubMesh *submeshcpy = _cpy.m_vecSubMesh[i];

		addSubMesh(new SubMesh(*submeshcpy));
	}
}

Mesh::~Mesh()
{
	for(int i=0; i<(int)m_vecSubMesh.size(); i++)
	{
		SubMesh *submesh = m_vecSubMesh[i];

		delete submesh;
	}

	m_vecSubMesh.clear();
}

HRESULT Mesh::InitVB(LPDIRECT3DDEVICE9 _device, void *_vertices, INT _nbVertices, LPDIRECT3DVERTEXBUFFER9 *_ppVB, UINT _sizeOfVertex, DWORD _fvf)
{
    if( FAILED( _device->CreateVertexBuffer( _nbVertices * _sizeOfVertex, 0, _fvf, D3DPOOL_DEFAULT, _ppVB, NULL ) ) )
        return E_FAIL;

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the Vertices. This mechanism is required because vertex
    // buffers may be in device memory.
    VOID* pVertices;
    if( FAILED( (*_ppVB)->Lock( 0, _nbVertices * _sizeOfVertex, ( void** )&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, _vertices, _nbVertices * _sizeOfVertex );
    (*_ppVB)->Unlock();

    return S_OK;
}

HRESULT Mesh::InitIB(LPDIRECT3DDEVICE9 _device, void *_indexes, INT _nbIndexes, LPDIRECT3DINDEXBUFFER9 *_ppIB, UINT _sizeOfIndex, D3DFORMAT _indexFormat)
{
	if( FAILED( _device->CreateIndexBuffer( _nbIndexes * _sizeOfIndex, 0, _indexFormat, D3DPOOL_DEFAULT, _ppIB, NULL ) ) )
        return E_FAIL;

    // Now we fill the index buffer. To do this, we need to Lock() the IB to
    // gain access to the Indexes. This mechanism is required because indexes
    // buffers may be in device memory.
    VOID* pIndexes;
    if( FAILED( (*_ppIB)->Lock( 0, _nbIndexes * _sizeOfIndex, ( void** )&pIndexes, 0 ) ) )
        return E_FAIL;
    memcpy( pIndexes, _indexes, _nbIndexes * _sizeOfIndex );
    (*_ppIB)->Unlock();

    return S_OK;
}

HRESULT Mesh::CopyVB(void *_vertices, INT _nbVertices, LPDIRECT3DVERTEXBUFFER9 *_ppVB, UINT _sizeOfVertex)
{
    VOID* pVertices;
    if( FAILED( (*_ppVB)->Lock( 0, _nbVertices * _sizeOfVertex, ( void** )&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, _vertices, _nbVertices * _sizeOfVertex );
    (*_ppVB)->Unlock();

    return S_OK;
}

HRESULT Mesh::CopyIB(void *_indexes, INT _nbIndexes, LPDIRECT3DINDEXBUFFER9 *_ppIB, UINT _sizeOfIndex)
{
    VOID* pIndexes;
    if( FAILED( (*_ppIB)->Lock( 0, _nbIndexes * _sizeOfIndex, ( void** )&pIndexes, 0 ) ) )
        return E_FAIL;
    memcpy( pIndexes, _indexes, _nbIndexes * _sizeOfIndex );
    (*_ppIB)->Unlock();

    return S_OK;
}
		
void Mesh::addSubMesh(SubMesh *_submesh)
{
	m_vecSubMesh.push_back(_submesh);
}

void Mesh::setDevice(LPDIRECT3DDEVICE9 _device)
{
	m_pd3dDevice = _device;
}

INT Mesh::getSubMeshCount()
{
	return (INT)m_vecSubMesh.size();
}

void Mesh::resetToOriginal()
{
	for(int i=0; i<(int)m_vecSubMesh.size(); i++)
	{
		SubMesh *submesh = m_vecSubMesh[i];

		submesh->resetToOriginal();

		submesh->updateVertexBuffer();
	}
}

void Mesh::stickToPose(Pose *_pose)
{
	for(int i=0; i<(int)m_vecSubMesh.size(); i++)
		m_vecSubMesh[i]->stickToPose(_pose);
}

void Mesh::display()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	m_pd3dDevice->SetTransform(D3DTS_WORLD, &mat);

	for(int i=0; i<(int)m_vecSubMesh.size(); i++)
		m_vecSubMesh[i]->display();
}