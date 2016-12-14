/**************************************************/
/*		@Author	: Marco
/*		@Date	: 04 / 02 / 2015
/*		@Desc	: Header de la classe SubMesh.
/**************************************************/

#ifndef _SUBMESH_H_
#define _SUBMESH_H_

#define D3DVERTEX_COUNT_BY_FACE 3

#define D3DFVF_MESHCUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// A structure for our custom vertex type
struct MESHCUSTOMVERTEX
{
	FLOAT x, y, z;		// The transformed position for the vertex
	D3DXVECTOR3 normal; // The surface normal for the vertex
	DWORD color;        // The vertex color
	D3DXVECTOR2 uv;		// The texture coordinates
};

struct MESHFACE
{
	WORD index1;
	WORD index2;
	WORD index3;
};

struct BONEATTACHMENT
{
	BONEATTACHMENT *next;
	WORD boneIndex;
	FLOAT weight;
};

typedef BONEATTACHMENT* PBONEATTACHMENT;

class DIRECTXANIMDLL_API SubMesh
{
	public:
		
		SubMesh();
		SubMesh(SubMesh& _cpy);
		~SubMesh();

		void setVertexCount(INT _count);
		MESHCUSTOMVERTEX* getVerticesPtr();

		void setFaceCount(INT _count);
		MESHFACE* getFacesPtr();

		void updateVertexBuffer();
		void updateIndexBuffer();

		void setMaterial(std::string _material);

		void setDevice(LPDIRECT3DDEVICE9 _device);

		void resetToOriginal();
		void stickToPose(Pose *_pose);

		PBONEATTACHMENT* getBoneAttachments();

		void display();

	protected:
	
		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device
		LPDIRECT3DVERTEXBUFFER9	m_pVB;				// Buffer to hold Vertices
		LPDIRECT3DINDEXBUFFER9	m_pIB;				// Buffer to hold Indexes

		INT						m_iFaceCount;
		INT						m_iVertexCount;

		std::string				m_strMaterial;

		MESHCUSTOMVERTEX*		m_Vertices;
		MESHFACE*				m_Faces;

		SubMesh*				m_pOriSubMesh;

		PBONEATTACHMENT*		m_BoneAttachments;
};

#endif