//************************************************/
//* @file  :Collision.h
//* @brief :�Փ˔��胉�C�u����
//* @date  :2017/06/15
//* @author:S.Katou
//************************************************/
#include "Collision.h"
using namespace ShunLib;

/// <summary>
/// ���Ƌ��̓����蔻��
/// </summary>
/// <param name="A">���P</param>
/// <param name="B">���Q</param>
/// <returns>true : �������Ă���</returns>
/// <returns>false: �������Ă��Ȃ�</returns>
bool ShunLib::CheckSphere2Sphere(const Sphere& A, const Sphere& B)
{
	//���S���W�Ԃ̍�
	auto sub = B.m_center - A.m_center;

	//���S���W�Ԃ̋���
	float distance = sub.x*sub.x + sub.y*sub.y + sub.z*sub.z;

	//���������a�̘a���傫����΁A�������Ă��Ȃ�
	float radius = A.m_radius + B.m_radius;
	radius = radius*radius;

	if (distance > radius)
	{
		return false;
	}
	return true;
}

