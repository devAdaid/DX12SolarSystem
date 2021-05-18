#include "Transform.h"

using namespace DirectX;

void Transform::AddChild(Transform& child)
{
    //_childs.push_back(child);
}

void Transform::OnParentTransformUpdated()
{
	UpdateLocalMatrix();
}

void Transform::UpdateLocalMatrix()
{
    auto positionMatrix = XMMatrixTranslation(_localPosition.X(), _localPosition.Y(), _localPosition.Z());
    auto rotationMatrix = XMMatrixRotationRollPitchYaw(_localRotation.Z(), _localRotation.X(), _localRotation.Y());
    auto scaleMatrix = XMMatrixScaling(_localScale.X(), _localScale.Y(), _localScale.Z());

    auto localMatrix = XMMatrixMultiply(positionMatrix, XMMatrixMultiply(scaleMatrix, rotationMatrix));
    XMStoreFloat4x4(&_localMatrix, localMatrix);
}