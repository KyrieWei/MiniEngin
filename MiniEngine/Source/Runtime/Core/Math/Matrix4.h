#pragma once
#include "Runtime/Core/Meta/Reflection/Reflection.h"

namespace ME
{
	REFLECTION_TYPE(Matrix4x4_)
	CLASS(Matrix4x4_, Fields)
	{
		REFLECTION_BODY(Matrix4x4_);

	public:
		Matrix4x4_() {};
		float v0{ 1.f };
		float v1{ 0 };
		float v2{ 0 };
		float v3{ 0 };
		float v4{ 0 };
		float v5{ 1.f };
		float v6{ 0 };
		float v7{ 0 };
		float v8{ 0 };
		float v9{ 0 };
		float v10{ 1.f };
		float v11{ 0 };
		float v12{ 0 };
		float v13{ 0 };
		float v14{ 0 };
		float v15{ 1.f };
	};

	class Matrix4x4
	{
	public:
		float m_mat[4][4];

	public:

		Matrix4x4(const Matrix4x4_& mat)
		{
			m_mat[0][0] = mat.v0;
			m_mat[0][1] = mat.v1;
			m_mat[0][2] = mat.v2;
			m_mat[0][3] = mat.v3;
			m_mat[1][0] = mat.v4;
			m_mat[1][1] = mat.v5;
			m_mat[1][2] = mat.v6;
			m_mat[1][3] = mat.v7;
			m_mat[2][0] = mat.v8;
			m_mat[2][1] = mat.v9;
			m_mat[2][2] = mat.v10;
			m_mat[2][3] = mat.v11;
			m_mat[3][0] = mat.v12;
			m_mat[3][1] = mat.v13;
			m_mat[3][2] = mat.v14;
			m_mat[3][3] = mat.v15;
		}

		Matrix4x4(float m00,
			float m01,
			float m02,
			float m03,
			float m10,
			float m11,
			float m12,
			float m13,
			float m20,
			float m21,
			float m22,
			float m23,
			float m30,
			float m31,
			float m32,
			float m33)
		{
			m_mat[0][0] = m00;
			m_mat[0][1] = m01;
			m_mat[0][2] = m02;
			m_mat[0][3] = m03;
			m_mat[1][0] = m10;
			m_mat[1][1] = m11;
			m_mat[1][2] = m12;
			m_mat[1][3] = m13;
			m_mat[2][0] = m20;
			m_mat[2][1] = m21;
			m_mat[2][2] = m22;
			m_mat[2][3] = m23;
			m_mat[3][0] = m30;
			m_mat[3][1] = m31;
			m_mat[3][2] = m32;
			m_mat[3][3] = m33;
		}

		static const Matrix4x4 IDENTITY;
	};
}

