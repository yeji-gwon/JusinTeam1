#pragma once
#include "pch.h"

//휘어진 곡선 구조체
typedef struct tagLine {
	D3DXVECTOR3 vCenter;
	float fHeight;
	float fWidth;
	vector<D3DXVECTOR3> Points;

	void Set_Height(float _height) { fHeight = _height; }
	void Set_Width(float _width) { fWidth = _width; }
	int Size() { return m_size; }
	void Sync(tagLine& rhs) {
		fHeight = rhs.fHeight;
		fWidth = rhs.fWidth;
		vCenter = rhs.vCenter;
	}
	void Set_Points(int count) {
		if (m_size < count) {
			Points.resize(count, { 0,0,0 });
		}
		m_size = count;
		Distribute();
	}

public:
	void Render(HDC hDC) {
		MoveToEx(hDC, Points[0].x, Points[0].y, nullptr);
		for (int i = 1; i < Size(); ++i) {
			LineTo(hDC, Points[i].x, Points[i].y);
		}
	}

private:
	int m_size;
	void Distribute() {
		float startX = -fWidth / 2.f;
		float stepX = fWidth / (m_size - 1);

		for (int i = 0; i < m_size; ++i)
		{
			float t = (float)i / (m_size - 1);         // 0~1 정규화
			float x = startX + stepX * i;              // 등간격 x
			float yNormalized = -4.f * (t - 0.5f) * (t - 0.5f) + 1.f; // 포물선
			float y = -yNormalized * fHeight; // 실제 y값 (위로 볼록)

			Points[i] = { x, y, 0.f };
		}
	}
};
//사다리꼴 구조체
struct  tagTrapezoid
{
	void Set_Trape(float _height, float _topWidth, float _botWidth) {
		fHeight = _height;
		fTopWidth = _topWidth;
		fBotWidth = _botWidth;
		Set_Corners();
	};
private:
	void Set_Corners() {
		vLT.x = vCenter.x - fTopWidth / 2;
		vRT.x = vCenter.x + fTopWidth / 2;
		vLB.x = vCenter.x - fBotWidth / 2;
		vRB.x = vCenter.x + fBotWidth / 2;

		vLT.y = vCenter.y- fHeight / 2;
		vRT.y = vCenter.y + fTopWidth / 2;
		vLB.y = vCenter.y- fBotWidth / 2;
		vRB.y = vCenter.y + fBotWidth / 2;
	}
private:
	float fHeight = 0.f;
	float fTopWidth = 0.f;
	float fBotWidth = 0.f;
	D3DXVECTOR3 vCenter = { 0.f,0.f,0.f };
	D3DXVECTOR3 vLT = { 0.f,0.f,0.f };
	D3DXVECTOR3 vRT = { 0.f,0.f,0.f };
	D3DXVECTOR3 vLB = { 0.f,0.f,0.f };
	D3DXVECTOR3 vRB = { 0.f,0.f,0.f };
};

//사각형 구조체
struct tagRect {
	D3DXVECTOR3 m_vCorner[4]; // 로컬 좌표 사각형
	D3DXVECTOR3 m_vScale;     // 크기
	D3DXVECTOR3 m_vRotate;    // Z축 회전 (Yaw만 필요함)
	D3DXVECTOR3 m_vPos;       // 위치 (중심)
};