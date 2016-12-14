#ifndef GAME_H
#define GAME_H

class Game
{
public:

	static Game *getSingleton();

	HRESULT InitD3D( HWND hWnd );
	
	static HRESULT InitVB(LPDIRECT3DDEVICE9 _device, void *_vertices, INT _nbVertices, LPDIRECT3DVERTEXBUFFER9 *_ppVB, UINT _sizeOfVertex, DWORD _fvf);
	static HRESULT InitIB(LPDIRECT3DDEVICE9 _device, void *_indexes, INT _nbIndexes, LPDIRECT3DINDEXBUFFER9 *_ppIB, UINT _sizeOfIndex, D3DFORMAT _indexFormat);

	VOID Init();

	VOID InitViewAndPerspective();

	VOID InitLight();

	VOID Render();

	VOID Cleanup();

	VOID Input();

	static LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

private:

	Game();
	~Game();

	LPDIRECT3D9             m_pD3D;			// Used to create the D3DDevice
	LPDIRECT3DDEVICE9       m_pd3dDevice;	// Our rendering device

	LPDIRECT3DTEXTURE9		m_pTexture;
	Sprite *m_pSprite;

	WNDCLASSEX m_WindowsClassEx;
	HWND m_hWnd;

	DXTerrain *m_pTerrain;

	AnimationInstance *m_Anim;
	Mesh *m_Mesh;
};

#endif