#include "stdafx.h"

AnimationController::AnimationController(AnimationInstance *_instance)
	: m_AnimInstance(_instance), m_Animation(nullptr), m_fTime(0.0f), m_fSpeed(1.0f), m_bIsLooping(true)
{

}

AnimationController::~AnimationController()
{

}

void AnimationController::setAnimation(Animation *_animation)
{
	m_Animation = _animation;
}

void AnimationController::update(float _timeDelta)
{
	m_fTime += _timeDelta * m_fSpeed;

	if(m_Animation)
	{
		float length = m_Animation->getLength();
		
		if(m_fTime >= length)
		{
			if(m_bIsLooping)
				m_fTime -= length;
			else
				m_fTime = length;
		}

		if(m_fTime < 0.0f)
		{
			if(m_bIsLooping)
				m_fTime += length;
			else
				m_fTime = 0.0f;
		}
		
		Pose *current_pose = m_AnimInstance->getPosePtr();
		
		Array *boneArray = current_pose->getBoneArray();
		Bone** bones = (Bone**)boneArray->data;

		Bone *b;
		Key *k1 = 0, *k2 = 0;
		Track *t;

		for(int i=0; i<boneArray->size; i++)
		{
			b = bones[i];

			t = m_Animation->findTrack(b->getName());

			t->findKeys(&k1, &k2, m_fTime);
			
			float t1 = k1->getTime();
			float t2 = k2->getTime();

			Transform& local = b->getLocalTransform();
			Transform& lerp = b->getLerpTransform();

			local.copyTransform(&b->getOriBonePtr()->getLocalTransform());

			float f = (m_fTime - t1) / (t2 - t1);
			Key::Interpolate(&lerp, k1, k2, f);

			local.applyTransform(&lerp);
		}

		current_pose->getRootBone()->updateWorldTransform(0);
	}
}

void AnimationController::setSpeed(float _speed)
{
	m_fSpeed = _speed;
}

float AnimationController::getSpeed()
{
	return m_fSpeed;
}