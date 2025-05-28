#pragma once
#include "pch.h"
#include "CRandom.h"
//#include "CSlope.h"

namespace Boogi {

	static float Dir;
	static float Limit;
	static bool bForward;

	static void ChangeDir(float delta)
	{
		if (bForward) {
			Dir += delta;
			if (Dir >= Limit) {
				bForward = false; // 반대 방향으로
				Limit = CRandom::GetFloat(0.f, 8.f);
				Dir = Limit;
			}
		}
		else {
			Dir -= delta;
			if (Dir <= -Limit) {
				bForward = true; // 다시 앞으로
				Limit = CRandom::GetFloat(0.f, 8.f);
				Dir = -Limit;
			}
		}
	};

	static float Get_Dir() { return Dir; }
	static float Flip_Dir() { return !bForward; }
	struct tagRectangle {
	private:
		D3DXVECTOR3 m_vCenter = { 0.f, 0.f, 0.f };
		D3DXVECTOR3 m_vScale = { 1.f, 1.f, 1.f };
		D3DXVECTOR3 m_vRotate = { 0.f, 0.f, 0.f };
		D3DXVECTOR3 m_vCorner[4]; // LT, RT, RB, LB

		D3DXMATRIX m_matWorld;
		float offsetLeft = 0.f;
		float offsetRight = 0.f;
		float offsetTop = 0.f;
		float offsetBottom = 0.f;

		D3DXMATRIX* m_pParent = nullptr;
		D3DXVECTOR3 m_vPivot = { 0.f, 0.f, 0.f };
		D3DXVECTOR3 m_vOrbit = { 0.f, 0.f, 0.f };
		POINT WorldPoints[4]; // 폴리곤은 꼭짓점 수만큼만

	public:
		// Getter / Setter
		void Set_Center(const D3DXVECTOR3& v) { m_vCenter = v; }
		void Set_Scale(const D3DXVECTOR3& v) { m_vScale = v; }
		void Set_Rotate(const D3DXVECTOR3& v) { m_vRotate = v; }
		void Set_Pivot(const D3DXVECTOR3& v) { m_vPivot = v; }
		void Set_Orbit(const D3DXVECTOR3& v) { m_vOrbit = v; }
		void Set_Parent(D3DXMATRIX* parent) { m_pParent = parent; }

		void Add_Rotate(float z) { m_vRotate.z += z; }
		void Add_Orbit(float z) { m_vOrbit.z += z; }
		void Add_Center(float x, float y, float z) {
			m_vCenter.x += x;
			m_vCenter.y += y;
			m_vCenter.z += z;
		}
		void Add_Offset(float l, float r, float t, float b) {
			offsetLeft += l;
			offsetRight += r;
			offsetTop += t;
			offsetBottom += b;
			Compute_Corners();
		}

		void Set_Offset(float l, float r, float t, float b) {
			offsetLeft = l;
			offsetRight = r;
			offsetTop = t;
			offsetBottom = b;
			Compute_Corners();
		}

		const D3DXVECTOR3& Get_Center() const { return m_vCenter; }
		const D3DXVECTOR3& Get_Scale() const { return m_vScale; }
		const D3DXVECTOR3& Get_Rotate() const { return m_vRotate; }
		const D3DXVECTOR3& Get_Orbit() const { return m_vOrbit; }
		const D3DXVECTOR3 Get_LT() { return m_vCorner[0]; }
		const D3DXVECTOR3 Get_RT() { return m_vCorner[1]; }
		const D3DXVECTOR3 Get_RB() { return m_vCorner[2]; }
		const D3DXVECTOR3 Get_LB() { return m_vCorner[3]; }
		const POINT Get_WorldLT() { return WorldPoints[0]; }
		const POINT Get_WorldRT() { return WorldPoints[1]; }
		const POINT Get_WorldRB() { return WorldPoints[2]; }
		const POINT Get_WorldLB() { return WorldPoints[3]; }
		const float Get_OffsetL() { return offsetLeft; }
		const float Get_OffsetR() { return offsetRight; }
		const float Get_OffsetB() { return offsetBottom; }
		const float Get_OffsetT() { return offsetTop; }
		D3DXMATRIX* Get_World() { return &m_matWorld; }

		void Compute_Corners() {
			D3DXVECTOR3 local[4] = {
				{ -offsetLeft,   -offsetTop,    0.f }, // LT
				{  offsetRight,  -offsetTop,    0.f }, // RT
				{  offsetRight,  offsetBottom, 0.f }, // RB
				{ -offsetLeft,    offsetBottom, 0.f }  // LB
			};

			// 로컬 좌표 저장
			for (int i = 0; i < 4; ++i)
				m_vCorner[i] = local[i];
		}


		void Update_World() {
			// 행렬 준비
			D3DXMATRIX matScale, matRot, matTrans, matWorld;
			D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
			D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_vRotate.z));
			D3DXMatrixTranslation(&matTrans, m_vCenter.x, m_vCenter.y, m_vCenter.z);
			m_matWorld = matScale * matRot * matTrans;

			D3DXMATRIX matOrbPos, matReOrbPos, matOrbit, matOrbResult;
			D3DXMatrixTranslation(&matOrbPos, m_vPivot.x, m_vPivot.y, m_vPivot.z);
			D3DXMatrixRotationZ(&matOrbit, D3DXToRadian(m_vOrbit.z));
			D3DXMatrixTranslation(&matReOrbPos, -m_vPivot.x, -m_vPivot.y, -m_vPivot.z);

			matOrbResult = matReOrbPos * matOrbit * matOrbPos;

			m_matWorld *= matOrbResult;

			if (m_pParent) {
				m_matWorld *= (*m_pParent);
			}
		}
		void Render(HDC hDC) {


			for (int i = 0; i < 4; ++i) {
				D3DXVECTOR3 worldPt;
				D3DXVec3TransformCoord(&worldPt, &m_vCorner[i], &m_matWorld);
				WorldPoints[i] = { (LONG)worldPt.x, (LONG)worldPt.y };
			}

			Polygon(hDC, WorldPoints, 4); // ✅ 내부가 채워지는 사각형
		}

	};

	struct tagPolygon_EX {
	private:
		std::vector<D3DXVECTOR3> m_vLocalPoints;
		D3DXVECTOR3 m_vScale{ 1.f, 1.f, 1.f };
		D3DXVECTOR3 m_vCenter{ 0.f, 0.f, 0.f };
		D3DXVECTOR3 m_vRotate{ 0.f, 0.f, 0.f };
		D3DXVECTOR3 m_vPivot{ 0.f, 0.f, 0.f };
		D3DXVECTOR3 m_vOrbit{ 0.f, 0.f, 0.f };

		D3DXMATRIX m_matWorld{ };
		D3DXMATRIX* m_pParent = nullptr;

		int m_iPointSize = 3;
		float m_fRadius = 1.f;
	public:
		tagPolygon_EX()
		{
			Set_Size(m_iPointSize);
		}

		void Set_Center(const D3DXVECTOR3& v) { m_vCenter = v; }
		void Set_Scale(const D3DXVECTOR3& v) { m_vScale = v; }
		void Set_Rotate(const D3DXVECTOR3& v) { m_vRotate = v; }
		void Set_Pivot(const D3DXVECTOR3& v) { m_vPivot = v; }
		void Set_Orbit(const D3DXVECTOR3& v) { m_vOrbit = v; }
		void Set_Parent(D3DXMATRIX* p) { m_pParent = p; }

		void Add_Rotate(float z) { m_vRotate.z += z; }
		void Add_Orbit(float z) { m_vOrbit.z += z; }
		void Set_Radius(float r) { m_fRadius = r; }
		int Size() const { return m_iPointSize; }

		void Set_Size(int size)
		{
			m_iPointSize = size;
			m_vLocalPoints.resize(size);
			Generate_LocalPoints();
		}

		void Generate_LocalPoints()
		{
			for (int i = 0; i < m_iPointSize; ++i) {
				float theta = (2.f * D3DX_PI * i) / m_iPointSize;
				m_vLocalPoints[i] = { cosf(theta) * m_fRadius, sinf(theta) * m_fRadius, 0.f };
			}
		}

		void Update_World()
		{
			D3DXMATRIX matScale, matRot, matTrans;
			D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
			D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_vRotate.z));
			D3DXMatrixTranslation(&matTrans, m_vCenter.x, m_vCenter.y, m_vCenter.z);

			m_matWorld = matScale * matRot * matTrans;

			// Orbit (공전)
			D3DXMATRIX matToPivot, matOrbitRot, matFromPivot;
			D3DXMatrixTranslation(&matToPivot, -m_vPivot.x, -m_vPivot.y, -m_vPivot.z);
			D3DXMatrixRotationZ(&matOrbitRot, D3DXToRadian(m_vOrbit.z));
			D3DXMatrixTranslation(&matFromPivot, m_vPivot.x, m_vPivot.y, m_vPivot.z);

			m_matWorld *= matToPivot * matOrbitRot * matFromPivot;

			if (m_pParent)
				m_matWorld *= (*m_pParent);
		}

		void Render(HDC hDC)
		{
			if (m_vLocalPoints.empty()) return;

			std::vector<POINT> pts;
			pts.reserve(m_iPointSize);

			for (const auto& v : m_vLocalPoints) {
				D3DXVECTOR3 worldPt;
				D3DXVec3TransformCoord(&worldPt, &v, &m_matWorld);
				pts.push_back({ LONG(worldPt.x), LONG(worldPt.y) });
			}

			Polygon(hDC, pts.data(), static_cast<int>(pts.size()));
		}
	};

	struct  tagLinePoint {
		D3DXVECTOR3 vStart;
		D3DXVECTOR3 vEnd;
		D3DXMATRIX matWorld;
		D3DXMATRIX matParent;
		float fAngle;
		float momentum = 0.f;

		D3DXVECTOR3 vStartWO;
		D3DXVECTOR3 vEndWO;

		void Update() {
			
			D3DXMATRIX matScale, matRot, matTrans;
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
			D3DXMatrixRotationZ(&matRot, D3DXToRadian(2.f));
			D3DXMatrixTranslation(&matTrans, 0.f, 0.f, 0.f);

			matWorld = matScale * matRot * matTrans * matParent;
			D3DXVec3TransformCoord(&vStartWO, &vStart, &matWorld);
			D3DXVec3TransformCoord(&vEndWO, &vEnd, &matWorld);
		
		}

		void Render(HDC hDC) {
			
			MoveToEx(hDC, vStartWO.x, vStartWO.y, nullptr);
			LineTo(hDC, vEndWO.x, vEndWO.y);
		}

		float Get_Angle() {
			return fAngle;
		}

		bool check_x(const RECT& rc) {
			float minX = min(vStartWO.x, vEndWO.x);
			float maxX = max(vStartWO.x, vEndWO.x);

			// 사각형의 왼쪽과 오른쪽 둘 다 검사
			return (rc.left >= minX && rc.left <= maxX) ||
				(rc.right >= minX && rc.right <= maxX);
		}


		bool check_y(RECT& rc) {
			float thres = (vEndWO.y + vStartWO.y) / 2;
			return fabsf(rc.bottom - thres) < 4.5f;
		}

		bool OutOfScreen() {
			return vEndWO.x < -50;
		}

		void Line_Link(float distance) {
			vEnd.x = vStart.x + distance;
			vEnd.y = vStart.y + Boogi::Dir*0.4f;
		}

		void Set_Angle() {
			D3DXVECTOR3 dir = vEnd - vStart;
			fAngle = atan2f(dir.x, dir.y);
		}
	};

	struct tagSlope {
		list<tagLinePoint> LineContainer;
		D3DXVECTOR3 vPos = { 0.f,0.f,0.f };
		D3DXVECTOR3 vScale = { 1.f,1.f,1.f };

		D3DXMATRIX matWorld;
		float fStartX;
		float fDistanceX;

		void Initialize(float Count, float distance) {
			LineContainer.resize(Count);
			fDistanceX = distance;
			Link_Line();
		}

		void Update()
		{
			D3DXMATRIX matScale, matTrans;
			D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
			D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

			matWorld = matScale * matTrans;

			for (auto iter = LineContainer.begin(); iter != LineContainer.end(); ++iter) {
				iter->matParent = matWorld;
				if (iter->OutOfScreen()) {
					if (iter == LineContainer.begin()) {
						auto last = std::prev(LineContainer.end());
						iter->vStart = last->vEnd;
					}
					else {
						auto prev = std::prev(iter); // 이전 요소
						iter->vStart = prev->vEnd;
					}
					(*iter).Line_Link(fDistanceX);
				}

				(*iter).Update();
				(*iter).Set_Angle();
			}
		}
		void Render(HDC hDC) {
			for (tagLinePoint line : LineContainer) {
				line.Render(hDC);
			}
		}

		void Link_Line() {
			for (auto iter = LineContainer.begin(); iter != LineContainer.end(); ++iter) {
				if (iter == LineContainer.begin()) {
					(*iter).vStart = { 0.f,400.f,0.f };
					(*iter).vEnd = { fDistanceX,401.f,0.f };
				}
				else {
					auto prev = std::prev(iter); // 이전 요소
					iter->vStart = prev->vEnd;
				}
				(*iter).Line_Link(fDistanceX);
				(*iter).Set_Angle();
			}
		}

		bool CheckCollision(RECT rc, float* y, float* fAngleOut) {
			list<tagLinePoint>::iterator iter = std::find_if(LineContainer.begin(), LineContainer.end(),
				[&rc](tagLinePoint& line) {

					if (!line.check_x(rc)) return false;
					//if (!line.check_y(rc)) return false;
					return true;
				}
			); // ✅ 이 세미콜론이 꼭 있어야 함

			if (iter != LineContainer.end()) {
				tagLinePoint& line = *iter;

				// 사각형 중심 x값
				float centerX = (rc.left + rc.right) / 2.f;

				// 직선 방정식으로 y값 계산
				D3DXVECTOR3 dir = line.vEndWO - line.vStartWO;
				float t = (centerX - line.vStartWO.x) / (dir.x == 0 ? 0.0001f : dir.x);
				float calcY = line.vStartWO.y + dir.y * t;

				if (y) *y = calcY;
				if (fAngleOut) *fAngleOut = line.fAngle;
				return true;
			}
			return false;
		}
	};

	

	};
