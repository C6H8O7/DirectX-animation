#include "stdafx.h"

AnimationInstance::AnimationInstance(AnimationModel *_pModel, std::string _name, std::string _animName)
	: m_pModel(_pModel), m_strName(_name)
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXQuaternionIdentity(&m_Rotation);

	m_pCurrentPose = new Pose(*_pModel->getSkeletonPtr()->getPosePtr());

	m_pController = new AnimationController(this);

	m_pController->setAnimation(m_pModel->findAnimation(_animName));

	update(0.0f);
}

AnimationInstance::~AnimationInstance()
{

}

Pose* AnimationInstance::getPosePtr()
{
	return m_pCurrentPose;
}

void AnimationInstance::update(float _timeDelta)
{
	m_pController->update(_timeDelta);
}

AnimationModel *AnimationInstance::getModelPtr()
{
	return m_pModel;
}

AnimationController *AnimationInstance::getControllerPtr()
{
	return m_pController;
}