/**************************************************/
/*		@Author	: Marco
/*		@Date	: 04 / 02 / 2015
/*		@Desc	: Header de la classe Mesh.
/**************************************************/

#ifndef _MESH_H_
#define _MESH_H_

class DIRECTXANIMDLL_API Mesh
{
	public:
		
		Mesh();
		Mesh(Mesh& _cpy);
		~Mesh();

		static HRESULT InitVB(LPDIRECT3DDEVICE9 _device, void *_vertices, INT _nbVertices, LPDIRECT3DVERTEXBUFFER9 *_ppVB, UINT _sizeOfVertex, DWORD _fvf);
		static HRESULT InitIB(LPDIRECT3DDEVICE9 _device, void *_indexes, INT _nbIndexes, LPDIRECT3DINDEXBUFFER9 *_ppIB, UINT _sizeOfIndex, D3DFORMAT _indexFormat);

		static HRESULT CopyVB(void *_vertices, INT _nbVertices, LPDIRECT3DVERTEXBUFFER9 *_ppVB, UINT _sizeOfVertex);
		static HRESULT CopyIB(void *_indexes, INT _nbIndexes, LPDIRECT3DINDEXBUFFER9 *_ppIB, UINT _sizeOfIndex);

		void addSubMesh(SubMesh *_submesh);

		void setDevice(LPDIRECT3DDEVICE9 _device);

		INT getSubMeshCount();

		void resetToOriginal();
		void stickToPose(Pose *_pose);

		void display();

	protected:

		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device

		std::vector<SubMesh*>	m_vecSubMesh;
};

#endif