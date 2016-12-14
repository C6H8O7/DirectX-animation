#include "stdafx.h"

SubMesh::SubMesh()
	: m_iFaceCount(0), m_iVertexCount(0), m_Vertices(nullptr), m_Faces(nullptr), m_pIB(nullptr), m_pVB(nullptr), m_pOriSubMesh(nullptr), m_BoneAttachments(nullptr)
{

}

SubMesh::SubMesh(SubMesh& _cpy)
{
	m_pOriSubMesh = &_cpy;

	m_pd3dDevice = _cpy.m_pd3dDevice;

	m_strMaterial = _cpy.m_strMaterial;

	m_iFaceCount = _cpy.m_iFaceCount;
	m_iVertexCount = _cpy.m_iVertexCount;

	m_Faces = new MESHFACE[m_iFaceCount];
	m_Vertices = new MESHCUSTOMVERTEX[m_iVertexCount];
	m_BoneAttachments = new PBONEATTACHMENT[m_iVertexCount];

	for(int i=0; i<m_iFaceCount; i++)
		m_Faces[i] = _cpy.m_Faces[i];
	
	for(int i=0; i<m_iVertexCount; i++)
	{
		m_Vertices[i] = _cpy.m_Vertices[i];
		m_BoneAttachments[i] = _cpy.m_BoneAttachments[i];
	}

	updateIndexBuffer();
	updateVertexBuffer();
}

SubMesh::~SubMesh()
{
	if(m_Vertices)
		delete m_Vertices;

	if(m_Faces)
		delete m_Faces;

	if(m_BoneAttachments)
		delete m_BoneAttachments;

	if(m_pVB)
		m_pVB->Release();

	if(m_pIB)
		m_pIB->Release();
}

void SubMesh::setVertexCount(INT _count)
{
	m_iVertexCount = _count;
	
	if(m_Vertices)
		delete m_Vertices;

	if(m_BoneAttachments)
		delete m_BoneAttachments;

	m_Vertices = new MESHCUSTOMVERTEX[m_iVertexCount];
	memset(m_Vertices, 0, sizeof(MESHCUSTOMVERTEX) * m_iVertexCount);

	m_BoneAttachments = new PBONEATTACHMENT[m_iVertexCount];
	memset(m_BoneAttachments, 0, sizeof(PBONEATTACHMENT) * m_iVertexCount);
}

MESHCUSTOMVERTEX* SubMesh::getVerticesPtr()
{
	return m_Vertices;
}
		
void SubMesh::setFaceCount(INT _count)
{
	m_iFaceCount = _count;

	if(m_Faces)
		delete m_Faces;

	m_Faces = new MESHFACE[m_iFaceCount];

	memset(m_Faces, 0, sizeof(MESHFACE) * m_iFaceCount);
}

MESHFACE* SubMesh::getFacesPtr()
{
	return m_Faces;
}
		
void SubMesh::updateVertexBuffer()
{
	if(m_pVB && m_Vertices)
		Mesh::CopyVB(m_Vertices, m_iVertexCount, &m_pVB, sizeof(MESHCUSTOMVERTEX));
	else
		Mesh::InitVB(m_pd3dDevice, m_Vertices, m_iVertexCount, &m_pVB, sizeof(MESHCUSTOMVERTEX), D3DFVF_MESHCUSTOMVERTEX);
}

void SubMesh::updateIndexBuffer()
{
	if(m_pIB && m_Faces)
		Mesh::CopyIB(m_Faces, m_iFaceCount * D3DVERTEX_COUNT_BY_FACE, &m_pIB, D3DFMT_INDEX16);
	else
		Mesh::InitIB(m_pd3dDevice, m_Faces, m_iFaceCount * D3DVERTEX_COUNT_BY_FACE, &m_pIB, sizeof(WORD), D3DFMT_INDEX16);
}

void SubMesh::setMaterial(std::string _material)
{
	m_strMaterial = _material;
}

void SubMesh::setDevice(LPDIRECT3DDEVICE9 _device)
{
	m_pd3dDevice = _device;
}

void SubMesh::resetToOriginal()
{
	if(m_pOriSubMesh)
	{
		for(int i=0; i<m_iVertexCount; i++)
			m_Vertices[i] = m_pOriSubMesh->m_Vertices[i];
	}
}

void SubMesh::stickToPose(Pose *_pose)
{
	Bone** bones = (Bone**)_pose->getBoneArray()->data;

	D3DXMATRIX delta;

	D3DXVECTOR4 pos, norm, pos0, norm0;

	for(int i=0; i<m_iVertexCount; i++)
	{
		MESHCUSTOMVERTEX& vertex = m_Vertices[i];

		vertex = m_pOriSubMesh->m_Vertices[i];
		
		D3DXVECTOR4 trans(0.0f, 0.0f, 0.0f, 0.0f);
		D3DXVECTOR4 rot(0.0f, 0.0f, 0.0f, 0.0f);

		PBONEATTACHMENT cur = m_BoneAttachments[i];
			
		pos0.x = vertex.x;
		pos0.y = vertex.y;
		pos0.z = vertex.z;
		pos0.w = 1.0f;

		norm0.x = vertex.normal.x;
		norm0.y = vertex.normal.y;
		norm0.z = vertex.normal.z;
		norm0.w = 1.0f;

		while(cur)
		{
			BONEATTACHMENT& attachment = *cur;
			
			Bone *bone = bones[attachment.boneIndex];
			Bone *oribone = bone->getOriBonePtr();

			FLOAT w = attachment.weight;
			
			D3DXMATRIX& current = bone->getWorldMatrix();
			D3DXMATRIX& restm1 = oribone->getWorldIMatrix();

			// Calcul vertex pos
			D3DXMatrixMultiply(&delta, &restm1, &current);

			pos = w * pos0;
			D3DXVec4Transform(&pos, &pos, &delta);

			trans += pos;

			// Calcul vertex norm
			if(w >= 0.3f)
			{
				delta.m[3][0] = delta.m[3][1] = delta.m[3][2] = 0.0f;
				delta.m[0][3] = delta.m[1][3] = delta.m[2][3] = 0.0f;
				delta.m[3][3] = 1.0f;

				norm = w * norm0;
				D3DXVec4Transform(&norm, &norm, &delta);
			
				rot += norm;
			}

			cur = cur->next;
		}
		
		vertex.x = trans.x;
		vertex.y = trans.y;
		vertex.z = trans.z;
		
		vertex.normal.x = rot.x;
		vertex.normal.y = rot.y;
		vertex.normal.z = rot.z;
	}

	updateVertexBuffer();
}

PBONEATTACHMENT* SubMesh::getBoneAttachments()
{
	return m_BoneAttachments;
}

void SubMesh::display()
{
	m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( MESHCUSTOMVERTEX ) );
	m_pd3dDevice->SetIndices(m_pIB);
	m_pd3dDevice->SetFVF( D3DFVF_MESHCUSTOMVERTEX );

	m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iFaceCount );
}