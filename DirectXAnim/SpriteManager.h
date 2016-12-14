/**
 * Header SpriteManager
 * 
 * @author  Fabsther
 * @since   09/05/2010
 * @version 1.0
 */

#ifndef SPRITEMANAGER__H
#define SPRITEMANAGER__H

#include <d3dx9.h>
#include "Sprite.h"
#include <vector>
#include <fstream>
#include "Helper.h"

using namespace std;

class SpriteManager
{
	struct SpriteElement
	{
		Sprite* Image;
		//add your parameters here
	};

	protected:
	
		vector<SpriteElement> m_SpriteList;

		SpriteManager();
		IDirect3DDevice9* m_D3DDevice;

	public:

		~SpriteManager();
		static SpriteManager* GetSingleton();
		void Load( IDirect3DDevice9* _Device );
		void Display();

};

#endif //SPRITEMANAGER__H