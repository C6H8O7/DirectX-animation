/**************************************************/
/*		@Author	: Marco
/*		@Date	: 13 / 01 / 2015
/*		@Desc	: Header de la classe AnimationController.
/**************************************************/

#ifndef _ANIMATIONCONTROLLER_H_
#define _ANIMATIONCONTROLLER_H_

class DIRECTXANIMDLL_API AnimationInstance;

class DIRECTXANIMDLL_API AnimationController
{
	public:

		AnimationController(AnimationInstance *_instance);
		~AnimationController();

		void setAnimation(Animation *_animation);

		void update(float _timeDelta);

		void setSpeed(float _speed);
		float getSpeed();

	private:

		float m_fTime;
		float m_fSpeed;
		float m_fWeight;
		float m_fMask;

		bool m_bIsLooping;

		AnimationInstance *m_AnimInstance;

		Animation *m_Animation;
};

#endif