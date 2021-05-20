#include "Transform.h"

using namespace DirectX;

void Transform::AddChild(Transform* child)
{
    _childs.push_back(child);
}

void Transform::OnParentTransformUpdated()
{
	UpdateMatrix();
    UpdateChildTransforms();
}

void Transform::UpdateMatrix()
{
    auto positionMatrix = XMMatrixTranslation(_localPosition.X(), _localPosition.Y(), _localPosition.Z());
    auto rotationMatrix = XMMatrixRotationRollPitchYaw(_localRotation.Z(), _localRotation.X(), _localRotation.Y());
    auto scaleMatrix = XMMatrixScaling(_localScale.X(), _localScale.Y(), _localScale.Z());

    auto localMatrix = XMMatrixMultiply(positionMatrix, XMMatrixMultiply(scaleMatrix, rotationMatrix));
    XMStoreFloat4x4(&_localMatrix, localMatrix);

    if (_parent != nullptr)
    {
        auto parentWorld = _parent->WorldMatrix();
        auto parentWorldMatrix = XMLoadFloat4x4(&parentWorld);
        auto worldMatrix = XMMatrixMultiply(parentWorldMatrix, localMatrix);
        XMStoreFloat4x4(&_worldMatrix, worldMatrix);
    }
    else
    {
        XMStoreFloat4x4(&_worldMatrix, localMatrix);
    }

    _isDirty = true;
}

void Transform::UpdateChildTransforms()
{
    for (auto& child : _childs)
    {
        child->OnParentTransformUpdated();
    }
}

void Transform::Update()
{
    //MeshRendererComponent->Update();
}