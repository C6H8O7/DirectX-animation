/**************************************************/
/*		@Author	: Marco
/*		@Date	: 13 / 01 / 2015
/*		@Desc	: Header de la classe AnimationModel.
/**************************************************/

#ifndef _ANIMATIONMODEL_H_
#define _ANIMATIONMODEL_H_

class DIRECTXANIMDLL_API AnimationModel
{
	public:

		AnimationModel();
		~AnimationModel();
		
		bool loadAnimFromFile(std::string _file);
		bool loadMeshFromFile(std::string _file);

		Skeleton* getSkeletonPtr();

		void addAnimation(Animation *_animation);

		Animation *findAnimation(std::string _name);

		Mesh* getMeshPtr();

		void setDevice(LPDIRECT3DDEVICE9 _device);

	private:

		LPDIRECT3DDEVICE9		m_pd3dDevice;		// Pointer to device

		Skeleton* m_pSkeleton;

		std::vector<Animation*> m_AnimationVector;

		Mesh* m_pMesh;
};

#endif