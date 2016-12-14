// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclure les en-t�tes Windows rarement utilis�s
// Fichiers d'en-t�te Windows�:
#include <windows.h>
#include <Mmsystem.h>

#pragma warning( disable : 4251 4996 )

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "tinyxml2.h"

#include "DirectXAnimDLL.h"

#include "dyn_list.h"
#include "dyn_array.h"

#include "Clock.h"

#include "Transform.h"

#include "Bone.h"
#include "Pose.h"
#include "Skeleton.h"

#include "SubMesh.h"
#include "Mesh.h"

#include "Key.h"
#include "Track.h"

#include "Animation.h"
#include "AnimationModel.h"
#include "AnimationController.h"
#include "AnimationInstance.h"
#include "AnimationManager.h"

// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme
