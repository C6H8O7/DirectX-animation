#include "stdafx.h"

AnimationModel::AnimationModel()
	: m_pd3dDevice(nullptr)
{
	m_pSkeleton = new Skeleton();

	m_pMesh = new Mesh();
}

AnimationModel::~AnimationModel()
{
	if(m_pSkeleton)
		delete m_pSkeleton;

	if(m_pMesh)
		delete m_pMesh;
}

bool AnimationModel::loadAnimFromFile(std::string _file)
{
	Pose* pose = m_pSkeleton->getPosePtr();

	tinyxml2::XMLDocument doc;
	doc.LoadFile(_file.c_str());

	tinyxml2::XMLElement* skeleton = doc.FirstChildElement("skeleton");

	for(tinyxml2::XMLElement* bone = skeleton->FirstChildElement("bones")->FirstChildElement(); bone; bone = bone->NextSiblingElement())
	{
		Bone *b = new Bone();
		
		b->setID(bone->IntAttribute("id"));
		b->setName(bone->Attribute("name"));
		
		tinyxml2::XMLElement* bone_position = bone->FirstChildElement("position");
		tinyxml2::XMLElement* bone_rotation = bone->FirstChildElement("rotation");
		tinyxml2::XMLElement* bone_rotation_axis = bone_rotation->FirstChildElement("axis");

		b->getLocalTransform().setTranslation(D3DXVECTOR3(bone_position->FloatAttribute("x"), bone_position->FloatAttribute("y"), bone_position->FloatAttribute("z")));

		D3DXQUATERNION quat;

		FLOAT angle = bone_rotation->FloatAttribute("angle");

		D3DXVECTOR3 axis;
		axis.x = bone_rotation_axis->FloatAttribute("x");
		axis.y = bone_rotation_axis->FloatAttribute("y");
		axis.z = bone_rotation_axis->FloatAttribute("z");

		D3DXQuaternionRotationAxis(&quat, &axis, angle);

		b->getLocalTransform().setRotation(quat);

		pose->addBone(b);
	}

	for(tinyxml2::XMLElement* boneparent = skeleton->FirstChildElement("bonehierarchy")->FirstChildElement(); boneparent; boneparent = boneparent->NextSiblingElement())
	{
		Bone *b = pose->findBone(boneparent->Attribute("bone"));

		if(b)
		{
			const char *parent_name = boneparent->Attribute("parent");

			b->setParentName(std::string(parent_name));
			b->setParentPtr(pose->findBone(parent_name));
		}
	}

	for(tinyxml2::XMLElement* animation = skeleton->FirstChildElement("animations")->FirstChildElement(); animation; animation = animation->NextSiblingElement())
	{
		Animation *anim = new Animation(animation->Attribute("name"), animation->FloatAttribute("length"));
		addAnimation(anim);

		for(tinyxml2::XMLElement* track = animation->FirstChildElement("tracks")->FirstChildElement(); track; track = track->NextSiblingElement())
		{
			Track *t = new Track(track->Attribute("bone"));
			anim->addTrack(t);

			for(tinyxml2::XMLElement* key = track->FirstChildElement("keyframes")->FirstChildElement(); key; key = key->NextSiblingElement())
			{
				Key *k = new Key(key->FloatAttribute("time"));
				t->addKey(k);
				
				tinyxml2::XMLElement* key_translation = key->FirstChildElement("translate");
				tinyxml2::XMLElement* key_rotation = key->FirstChildElement("rotate");
				tinyxml2::XMLElement* key_rotation_axis = key_rotation->FirstChildElement("axis");
				tinyxml2::XMLElement* key_scale = key->FirstChildElement("scale");

				D3DXVECTOR3 translation, scale, axis;
				D3DXQUATERNION rotation;
				
				translation.x = key_translation->FloatAttribute("x");
				translation.y = key_translation->FloatAttribute("y");
				translation.z = key_translation->FloatAttribute("z");
				
				scale.x = key_scale->FloatAttribute("x");
				scale.y = key_scale->FloatAttribute("y");
				scale.z = key_scale->FloatAttribute("z");

				axis.x = key_rotation_axis->FloatAttribute("x");
				axis.y = key_rotation_axis->FloatAttribute("y");
				axis.z = key_rotation_axis->FloatAttribute("z");

				D3DXQuaternionRotationAxis(&rotation, &axis, key_rotation->FloatAttribute("angle"));

				k->setTranslation(translation);
				k->setScale(scale);
				k->setRotation(rotation);

				//printf("%f %f %f\n%f %f %f\n______\n", translation.x, translation.y, translation.z, axis.x, axis.y, axis.z);
			}
		}
	}

	pose->getRootBone()->updateWorldTransform(0);

	pose->calculateWorldInv();

	return true;
}

bool AnimationModel::loadMeshFromFile(std::string _file)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(_file.c_str());

	tinyxml2::XMLElement* submeshes = doc.FirstChildElement("mesh")->FirstChildElement("submeshes");

	m_pMesh = new Mesh();
	m_pMesh->setDevice(m_pd3dDevice);

	for(tinyxml2::XMLElement* submesh = submeshes->FirstChildElement(); submesh; submesh = submesh->NextSiblingElement())
	{
		SubMesh *sm = new SubMesh();
		m_pMesh->addSubMesh(sm);
		sm->setDevice(m_pd3dDevice);
		
		tinyxml2::XMLElement* faces = submesh->FirstChildElement("faces");
		tinyxml2::XMLElement* geometry = submesh->FirstChildElement("geometry");
		tinyxml2::XMLElement* vertexbuffer = geometry->FirstChildElement("vertexbuffer");
		tinyxml2::XMLElement* boneassignments = submesh->FirstChildElement("boneassignments");
		
		INT nbFaces = faces->IntAttribute("count");
		INT nbVertices = geometry->IntAttribute("vertexcount");
		
		sm->setFaceCount(nbFaces);
		sm->setVertexCount(nbVertices);

		sm->setMaterial(submesh->Attribute("material"));
		
		MESHCUSTOMVERTEX *vertices = sm->getVerticesPtr();
		MESHFACE *meshfaces = sm->getFacesPtr();
		PBONEATTACHMENT *attachments = sm->getBoneAttachments();

		int i = 0;
		
		for(tinyxml2::XMLElement* face = faces->FirstChildElement(); face; face = face->NextSiblingElement())
		{
			meshfaces[i].index1 = face->IntAttribute("v1");
			meshfaces[i].index2 = face->IntAttribute("v2");
			meshfaces[i].index3 = face->IntAttribute("v3");

			i++;
		}

		i = 0;

		for(tinyxml2::XMLElement* vertex = vertexbuffer->FirstChildElement(); vertex; vertex = vertex->NextSiblingElement())
		{
			tinyxml2::XMLElement* position = vertex->FirstChildElement("position");
			tinyxml2::XMLElement* normal = vertex->FirstChildElement("normal");
			
			vertices[i].x = position->FloatAttribute("x");
			vertices[i].y = position->FloatAttribute("y");
			vertices[i].z = position->FloatAttribute("z");

			vertices[i].normal.x = normal->FloatAttribute("x");
			vertices[i].normal.y = normal->FloatAttribute("y");
			vertices[i].normal.z = normal->FloatAttribute("z");

			vertices[i].color = D3DCOLOR_XRGB(255, 0, 0);

			i++;
		}
		
		for(tinyxml2::XMLElement* boneassignment = boneassignments->FirstChildElement(); boneassignment; boneassignment = boneassignment->NextSiblingElement())
		{
			BONEATTACHMENT attachment;
			
			WORD vertexIndex = boneassignment->IntAttribute("vertexindex");
			WORD boneIndex = boneassignment->IntAttribute("boneindex");
			FLOAT weight = boneassignment->FloatAttribute("weight");
			
			attachment.boneIndex = boneIndex;
			attachment.weight = weight;

			BONEATTACHMENT *na = new BONEATTACHMENT;
			*na = attachment;

			dyn_addObjectToListBACK(na, sizeof(BONEATTACHMENT), (void**)&attachments[vertexIndex]);
		}
		
		sm->updateIndexBuffer();
		sm->updateVertexBuffer();
	}

	return true;
}

Skeleton* AnimationModel::getSkeletonPtr()
{
	return m_pSkeleton;
}

void AnimationModel::addAnimation(Animation *_animation)
{
	m_AnimationVector.push_back(_animation);
}

Animation *AnimationModel::findAnimation(std::string _name)
{
	for(std::vector<Animation*>::iterator it = m_AnimationVector.begin();
		it != m_AnimationVector.end();
		++it)
	{
		Animation *anim = (*it);

		if(anim->getName() == _name)
			return anim;
	}

	return 0;
}

Mesh* AnimationModel::getMeshPtr()
{
	return m_pMesh;
}

void AnimationModel::setDevice(LPDIRECT3DDEVICE9 _device)
{
	m_pd3dDevice = _device;
}