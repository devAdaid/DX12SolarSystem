#pragma once

#include <vector>
#include <cmath>
#include "Vector3.h"
#include <DirectXMath.h>
#include "Common/MathHelper.h"

using namespace std;
using namespace DirectX;

class Transform
{
public:
	Vector3 LocalPosition() const { return _localPosition; }
	void LocalPosition(Vector3 position) 
	{ 
		_localPosition = std::move(position);
		UpdateChildTransforms();
	}

	Vector3 LocalRotation() const { return _localRotation; }
	void LocalRotation(Vector3 rotation) 
	{
		_localRotation = std::move(rotation);
		UpdateChildTransforms();
	}

	Vector3 LocalScale() const { return _localScale; }
	void LocalScale(Vector3 scale) 
	{ 
		_localScale = std::move(scale);
		UpdateChildTransforms();
	}

	DirectX::XMFLOAT4X4 LocalMatrix() const { return _localMatrix; }

	void AddChild(Transform& child);
	void UpdateChildTransforms();
	void OnParentTransformUpdated();

	Transform(Vector3 position, Vector3 rotation, Vector3 scale, Transform* parent) : _localPosition(position), _localRotation(rotation), _localScale(scale), _parent(parent) 
	{
		_parent->AddChild(*this);
	}

private:
	Vector3 _localPosition;
	Vector3 _localRotation;
	Vector3 _localScale;
	DirectX::XMFLOAT4X4 _localMatrix;

	Transform* _parent;
	vector<Transform*> _childs;

	void UpdateLocalMatrix();
};