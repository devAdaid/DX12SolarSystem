#pragma once

#include "Component.h"
#include <string>

using namespace std;

class MeshRendererComponent
{
public:
	string SubMeshName;
	MeshRendererComponent(string subMeshName) : SubMeshName(subMeshName) {}
};