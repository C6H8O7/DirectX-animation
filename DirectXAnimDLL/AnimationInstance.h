/**************************************************/
/*		@Author	: Marco
/*		@Date	: 13 / 01 / 2015
/*		@Desc	: Header de la classe AnimationInstance.
/**************************************************/

#ifndef _ANIMATIONINSTANCE_H_
#define _ANIMATIONINSTANCE_H_

class DIRECTXANIMDLL_API AnimationInstance
{
	public:

		AnimationInstance(AnimationModel *_pModel, std::string _name, std::string _animName);
		~AnimationInstance();

		Pose *getPosePtr();

		void update(float _timeDelta);

		AnimationModel *getModelPtr();

		AnimationController *getControllerPtr();

	private:

		AnimationModel *m_pModel;

		AnimationController *m_pController;

		Pose *m_pCurrentPose;

		std::string m_strName;

		D3DXVECTOR3 m_Position;
		D3DXQUATERNION m_Rotation;
};

#endif