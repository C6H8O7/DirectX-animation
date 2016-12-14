#include "stdafx.h"
	
AnimationManager::AnimationManager()
{

}

AnimationManager::AnimationManager(AnimationManager& _cpy)
{

}

AnimationManager::~AnimationManager()
{

}

AnimationManager *AnimationManager::getSingleton()
{
	static AnimationManager instanceUnique;

	return &instanceUnique;
}

bool AnimationManager::loadAnimFromFile(std::string _res, std::string _file)
{
	AnimationModel *anim = new AnimationModel();

	bool ret = anim->loadAnimFromFile(_file);

	if(ret)
		m_AnimationModelMap[_res] = anim;
	else
		delete anim;

	return ret;
}

AnimationModel *AnimationManager::getAnimation(std::string _res)
{
	return m_AnimationModelMap[_res];
}