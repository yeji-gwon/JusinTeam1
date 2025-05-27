#pragma once
#include "CObj.h"
typedef struct tagLine {
	D3DXVECTOR3 vCenter;
	float fHeight;
	float fWidth;
	vector<D3DXVECTOR3> Points;

	void Set_Height(float _height) { fHeight = _height; }
	void Set_Width(float _width) { fWidth = _width; }
	int Size() { return m_size; }

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
		float startX = vCenter.x - fWidth / 2.f;
		float stepX = fWidth / (m_size - 1);

		for (int i = 0; i < m_size; ++i)
		{
			float t = (float)i / (m_size - 1);         // 0~1 정규화
			float x = startX + fWidth / 2 + stepX * i; // 등간격 x
			float yNormalized = (float)(-4 * (t - 0.5f) * (t - 0.5f) + 1);
			float y = vCenter.y - yNormalized * fHeight; // 실제 y값 (위로 볼록)

			Points[i] = { x, y, 0 };
		}

	}

};

class CRoad :
	public CObj
{
public:
	CRoad();
	~CRoad();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void RenderHorizon();
private:
	//중앙선
	tagLine m_Horizon;
	//지평선
	//도로
};

