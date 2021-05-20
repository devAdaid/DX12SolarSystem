#pragma once

#include <vector>
#include <cmath>
#include "Vector3.h"
#include "MeshRendererComponent.h"
#include <DirectXMath.h>
#include "Common/MathHelper.h"

using namespace std;
using namespace DirectX;

class Transform
{
public:
	MeshRendererComponent* MeshRendererComponent = nullptr;

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

	vector<Transform*> Childs()const { return _childs; }

	DirectX::XMFLOAT4X4 LocalMatrix() const { return _localMatrix; }
	DirectX::XMFLOAT4X4 WorldMatrix() const { return _worldMatrix; }

	bool IsDirty() const { return _isDirty; }
	void IsDirty(bool isDirty)
	{
		_isDirty = isDirty;
	}

	void AddChild(Transform* child);
	void UpdateChildTransforms();
	void OnParentTransformUpdated();
	void Update();

	Transform(Transform* parent) : _localPosition(Vector3(0, 0, 0)), _localRotation(Vector3(0, 0, 0)), _localScale(Vector3(1, 1, 1)), _parent(parent)
	{
		if (_parent != nullptr)
		{
			_parent->AddChild(this);
		}

		UpdateMatrix();
	}

	Transform(Vector3 position, Vector3 rotation, Vector3 scale, Transform* parent) : _localPosition(position), _localRotation(rotation), _localScale(scale), _parent(parent) 
	{
		if (_parent != nullptr)
		{
			_parent->AddChild(this);
		}

		UpdateMatrix();
	}

private:
	Vector3 _localPosition;
	Vector3 _localRotation;
	Vector3 _localScale;
	DirectX::XMFLOAT4X4 _localMatrix;
	DirectX::XMFLOAT4X4 _worldMatrix;
	bool _isDirty;

	Transform* _parent;
	vector<Transform*> _childs;

	void UpdateMatrix();
};