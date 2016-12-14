/**************************************************/
/*		@Author	: Marco
/*		@Date	: 13 / 01 / 2015
/*		@Desc	: Header de la classe Bone.
/**************************************************/

#ifndef _BONE_H_
#define _BONE_H_

class DIRECTXANIMDLL_API Bone
{
	public:

		Bone();
		Bone(Bone& _cpy);
		~Bone();

		Transform& getWorldTransform();
		Transform& getLocalTransform();
		Transform& getLerpTransform();
		
		void setParentPtr	(Bone *_parent);
		void setParentName	(std::string& _name);
		void setID			(int _id);
		void setName		(std::string _name);

		void addChildPtr	(Bone *_child);

		Bone*				getParentPtr();
		std::string			getParentName();
		int					getID();
		std::string			getName();

		void				updateWorldTransform(Bone *_parent);
		
		D3DXMATRIXA16&		getWorldMatrix();
		D3DXMATRIXA16&		getWorldIMatrix();

		Bone*				getOriBonePtr();

	private:

		int					m_iID;
		std::string			m_strName;

		Transform			m_TWorld;
		Transform			m_TLocal;

		D3DXMATRIXA16		m_MWorld;
		D3DXMATRIXA16		m_MWorldI;

		Bone*				m_pParent;
		std::string			m_strParentName;
		Array*				m_aChilds;

		Bone*				m_pOriBone;

		Transform			m_TLerp;
};

#endif