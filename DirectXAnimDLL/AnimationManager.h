/**************************************************/
/*		@Author	: Marco
/*		@Date	: 13 / 01 / 2015
/*		@Desc	: Header de la classe AnimationManager.
/**************************************************/

#ifndef _ANIMATIONMANAGER_H_
#define _ANIMATIONMANAGER_H_

class DIRECTXANIMDLL_API AnimationManager
{
	public:

		static AnimationManager *getSingleton();

		bool loadAnimFromFile(std::string _res, std::string _file);

		AnimationModel *getAnimation(std::string _res);
		
	private:
	
		AnimationManager();
		AnimationManager(AnimationManager& _cpy);
		~AnimationManager();

		std::map<std::string, AnimationModel*> m_AnimationModelMap;
};

#endif