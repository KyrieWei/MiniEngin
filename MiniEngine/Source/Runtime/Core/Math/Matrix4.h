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
	};
}

