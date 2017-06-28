//************************************************/
//* @file  :Collision.h
//* @brief :�Փ˔��胉�C�u����
//* @date  :2017/06/15
//* @author:S.Katou
//************************************************/
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
namespace ShunLib
{
	/// <summary>
	/// ���̃N���X
	/// </summary>
	class Sphere
	{
	public:
		//���S���W
		DirectX::SimpleMath::Vector3 m_center;

		//���a
		float m_radius;

	public:
		Sphere() :m_radius(1.0f) {}
	};

	/// <summary>
	/// �����N���X
	/// </summary>
	class Segment
	{
	public:
		//�����J�n�_
		DirectX::SimpleMath::Vector3 m_start;

		//�����I���_
		DirectX::SimpleMath::Vector3 m_end;
	};

	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	/// <param name="A">���P</param>
	/// <param name="B">���Q</param>
	/// <returns>true : �������Ă���</returns>
	/// <returns>false: �������Ă��Ȃ�</returns>
	bool CheckSphere2Sphere(const Sphere& A, const Sphere& B);
}
