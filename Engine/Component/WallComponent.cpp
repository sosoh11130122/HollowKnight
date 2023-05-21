#include "WallComponent.h"
#include "../Component/Tile.h"
#include "../Component/TileMapComponent.h"
#include "../Scene/Scene.h"
#include "../GameObject/GameObject.h"
#include "../Component/Collider.h"
#include "../Component/ColliderBox2D.h"
#include "../Input.h"


CWallComponent::CWallComponent() :
	m_PhysicsSimulate(true),
	m_GravityAccel(10.f),
	m_FallTime(0.f),
	m_FallStartY(0.f),
	m_Jump(false),
	m_JumpVelocity(0.f),
	m_SideWallCheck(false),
	m_JumpCount(0),
	m_Ground(false),
	m_SideWallCollision(false),
	m_MiniJumpOn(false)
{
	m_ComponentType = ComponentType::Object;

	SetTypeID<CWallComponent>();

	m_ComponentTypeName = "Wall";
}

CWallComponent::CWallComponent(const CWallComponent& Obj)
{
}

CWallComponent::~CWallComponent()
{
}

void CWallComponent::SetUpdateComponent(CSceneComponent* Component)
{
	m_UpdateComponent = Component;
}

void CWallComponent::Destroy()
{
}

void CWallComponent::Start()
{
	CObjectComponent::Start();

	if (!m_UpdateComponent)
		m_UpdateComponent = m_Owner->GetRootComponent();

	//if(m_Owner)



	//주체
	//m_Body = (CCollider2D*)m_Owner->FindComponent(OwnerName);

	//if (m_Body)
	//{
	//	m_BodySize = ((CColliderBox2D*)m_Body.Get())->GetBoxSize();
	//	m_BodyInfo = ((CColliderBox2D*)m_Body.Get())->GetInfo();

		//m_Pos = m_Body->GetWorldPos();
		//m_Pos.y = m_Pos.y + (m_BodySize.y * 0.5f); //Center 기준에서 하단 피봇으로 바꿔줌
		//m_PrevPos = m_Pos;
	//}

	////맨 처음 FallStartY 세팅해주기
	//SetFallStartY(m_Pos.y);
}

bool CWallComponent::Init()
{
	CObjectComponent::Init();

	if (!CObjectComponent::Init())
		return false;

	return true;
}

void CWallComponent::Update(float DeltaTime)
{
	CObjectComponent::Update(DeltaTime);

	m_PrevPos = m_Owner->GetWorldPos();

	// 중력 적용
	if (m_UpdateComponent)
	{
		if (!m_Ground && m_PhysicsSimulate)
		{
			m_FallTime += DeltaTime * m_GravityAccel;

			float Velocity = 0.f;

			if (m_Jump)
			{
				Velocity = m_JumpVelocity * m_FallTime;
			}

			// 중력 식
			float Gravity = (Velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime);

			float Y = m_FallStartY + Gravity; // 현재 떨어지는 위치 

			m_UpdateComponent->SetWorldPositionY(Y);
		}
	}
}

void CWallComponent::PostUpdate(float DeltaTime)
{
	CObjectComponent::PostUpdate(DeltaTime);

	//m_Pos = m_Body->GetWorldPos();
	//m_Pivot = m_Body->GetPivot();
	//m_Size = m_Body->GetRelativeScale();

	//m_Pos.y = m_Pos.y;

	m_Pos = m_Owner->GetWorldPos();

	m_Move = m_Pos - m_PrevPos;

	if (m_PhysicsSimulate && m_Move.y <= 0.f)
	{
		CTileMapComponent* m_TileMap = m_Scene->GetTileMap();

		Vector3 Pos = m_Owner->GetRootComponent()->GetWorldPos();
		Vector3 Size = m_Owner->GetRootComponent()->GetWorldScale();
		CColliderBox2D* Collider = (CColliderBox2D*)m_Owner->GetRootComponent();

		Vector2 BoxSize = Collider->GetBoxSize();

		Vector2 Pivot = m_Owner->GetRootComponent()->GetPivot();

		CTile* Tile = m_TileMap->GetTile(Pos);

		if (Tile)

		{	
			Vector3 TilePos = Tile->GetPos();
			float PrevBottom = m_PrevPos.y - (BoxSize.y * 0.5f);
			float CurBottom = Pos.y - (BoxSize.y * 0.5f);

			float PrevLeft = m_PrevPos.x - (BoxSize.x * 0.5f);
			float CurLeft = Pos.x - (BoxSize.x * 0.5f);

			float PrevRight = m_PrevPos.x + (BoxSize.x * 0.5f);
			float CurRight = Pos.x + (BoxSize.x * 0.5f);

			float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
			float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
			float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
			float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;

			Vector2 MousePos = CInput::GetInst()->GetMouseWorldPos();

			int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLeft, Pos.y));
			int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRight, Pos.y));
			int TopIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultTop));
			int BottomIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultBottom));

			LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
			TopIndex = TopIndex < 0 ? 0 : TopIndex;
			RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
			BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;

			if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 &&
				RightIndex >= 0 && BottomIndex >= 0)
			{

				bool Check = false;

				for (int i = TopIndex; i <= BottomIndex; ++i)
				{
					for (int j = LeftIndex; j <= RightIndex; ++j)
					{
						CTile* Tile = m_TileMap->GetTile(j, i);

						if (!Tile)
							continue;

						if (Tile->GetTileOption() == ETileOption::Wall)
						{
							int TileCountX = Tile->GetIndexX();
							int TileCountY = Tile->GetIndexY();

							Check = true;

							m_FallTime = 0.f;

							m_JumpCount = 0; 
							
							Vector3 TilePos = Tile->GetPos();

							float TileTop = TilePos.y + (m_TileMap->GetTileSize().y);

							// 현재 타일의 Top을 이 오브젝트의 Bottom 값으로 지정한다.
							m_Owner->SetWorldPositionY(TileTop + (BoxSize.y * 0.5f + 0.005f));

							m_Ground = true;

							m_Jump = false;

							break;
						}

					}

					if (Check)
						break;
				}

				if (!Check)
				{
					if (m_Ground)
					{
						m_FallTime = 0.f;
						m_FallStartY = m_Owner->GetWorldPos().y;
					}

					m_Ground = false;

				}
			}
		}
	}


	if (m_Move.x != 0.f && m_SideWallCheck)
	{
		// 오른쪽으로 이동할때
		if (m_Move.x > 0.f)
		{
			CheckMoveRight();
		}

		// 왼쪽으로 이동할때
		else
		{
			CheckMoveLeft();
		}
	}

}

void CWallComponent::Render()
{
	CObjectComponent::Render();

}

CWallComponent* CWallComponent::Clone() const
{
	return new CWallComponent(*this);
}

void CWallComponent::Save(FILE* File)
{
	CObjectComponent::Save(File);
}

void CWallComponent::Load(FILE* File)
{
	CObjectComponent::Load(File);
}

void CWallComponent::CheckMoveRight()
{
	//Vector2	LT = m_Pos - m_Pivot * m_Size;
	//Vector2	RB = LT + m_Size;

	//Vector2	PrevLT = m_PrevPos - m_Pivot * m_Size;
	//Vector2	PrevRB = PrevLT + m_Size;

	//CTileMapComponent* m_TileMap = m_Scene->GetTileMap();

	//Vector3 Pos = m_Owner->GetRootComponent()->GetWorldPos();
	//Vector3 Size = m_Owner->GetRootComponent()->GetWorldScale();
	//CColliderBox2D* Collider = (CColliderBox2D*)m_Owner->GetRootComponent();

	//Vector2 BoxSize = Collider->GetBoxSize();

	//Vector2	ResultLT, ResultRB;

	//ResultRB = RB;

	//ResultLT.x = PrevRB.x;
	//ResultLT.y = LT.y > PrevLT.y ? LT.y : PrevLT.y;

	//ResultRB.y = RB.y < PrevRB.y ? RB.y : PrevRB.y;

	//float PrevBottom = m_PrevPos.y - (BoxSize.y * 0.5f);
	//float CurBottom = Pos.y - (BoxSize.y * 0.5f);

	//float PrevLeft = m_PrevPos.x - (BoxSize.x * 0.5f);
	//float CurLeft = Pos.x - (BoxSize.x * 0.5f);

	//float PrevRight = m_PrevPos.x + (BoxSize.x * 0.5f);
	//float CurRight = Pos.x + (BoxSize.x * 0.5f);


	//float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
	//float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
	//float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
	//float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;


	//int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLeft, Pos.y));
	//int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRight, Pos.y));
	//int TopIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultTop));
	//int BottomIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultBottom));

	//LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	//TopIndex = TopIndex < 0 ? 0 : TopIndex;
	//RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
	//BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;

	//if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 &&
	//	RightIndex >= 0 && BottomIndex >= 0)
	//{
	//	bool	SideCollision = false;

	//	// 위에서 아래로 차례로 검사를 해나간다.
	//	// 아래에서부터 하게 되면 위에 벽이 있을 경우 무시하고 처리되버릴 수도 있기 때문이다.
	//	for (int i = TopIndex; i <= BottomIndex; ++i)
	//	{
	//		for (int j = LeftIndex; j <= RightIndex; ++j)
	//		{
	//			CTile* Tile = m_TileMap->GetTile(j, i);

	//			if (Tile->GetTileOption() != ETileOption::Wall)
	//				continue;

	//			Vector2	TilePos = Tile->GetPos();
	//			Vector2	TileSize = Tile->GetSize();

	//			if (TilePos.y - 0.001f <= RB.y && RB.y <= TilePos.y + 0.001f)
	//				continue;

	//			/*if (RB.x - TilePos.x > 8.f)
	//				continue;*/

	//				// 현재 위치의 사각형과 타일을 충돌시켜서 파고들었는지 판단한다.
	//			if (LT.x <= TilePos.x + TileSize.x && LT.y <= TilePos.y + TileSize.y &&
	//				RB.x >= TilePos.x && RB.y >= TilePos.y)
	//			{
	//				SideCollision = true;
	//				m_SideWallCollision = true;

	//				// 얼마나 파고들었는지 구한다.
	//				float MoveX = TilePos.x - RB.x - 0.001f;

	//				m_Pos.x += MoveX;
	//				m_Move.x += MoveX;
	//				break;
	//			}
	//		}

	//		if (SideCollision)
	//			break;
	//	}
	//}



	Vector2	LT = m_Pos - m_Pivot * m_Size;
	Vector2	RB = LT + m_Size;

	Vector2	PrevLT = m_PrevPos - m_Pivot * m_Size;
	Vector2	PrevRB = PrevLT + m_Size;

	CTileMapComponent* m_TileMap = m_Scene->GetTileMap();

	Vector3 Pos = m_Owner->GetRootComponent()->GetWorldPos();
	Vector3 Size = m_Owner->GetRootComponent()->GetWorldScale();
	CColliderBox2D* Collider = (CColliderBox2D*)m_Owner->GetRootComponent();

	Vector2 BoxSize = Collider->GetBoxSize();

	Vector2	ResultLT, ResultRB;

	ResultLT = LT;

	ResultLT.x = PrevLT.x;
	ResultLT.y = LT.y > PrevLT.y ? LT.y : PrevLT.y;
	ResultRB.y = RB.y < PrevRB.y ? RB.y : PrevRB.y;

	float PrevBottom = m_PrevPos.y - (BoxSize.y * 0.5f);
	float CurBottom = Pos.y - (BoxSize.y * 0.5f);

	float PrevLeft = m_PrevPos.x - (BoxSize.x * 0.5f);
	float CurLeft = Pos.x - (BoxSize.x * 0.5f);

	float PrevRight = m_PrevPos.x + (BoxSize.x * 0.5f);
	float CurRight = Pos.x + (BoxSize.x * 0.5f);

	float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
	float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
	float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
	float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;

	int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLeft, Pos.y));
	int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRight, Pos.y));
	int TopIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultTop));
	int BottomIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultBottom));

	LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	TopIndex = TopIndex < 0 ? 0 : TopIndex;
	RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
	BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;

	if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 &&
		RightIndex >= 0 && BottomIndex >= 0)
	{
		bool	SideCollision = false;

		// 위에서 아래로 차례로 검사를 해나간다.
		// 아래에서부터 하게 되면 위에 벽이 있을 경우 무시하고 처리되버릴 수도 있기 때문이다.
		for (int i = TopIndex; i <= BottomIndex; ++i)
		{
			for (int j = RightIndex; j <= LeftIndex; ++j)
			{
				CTile* Tile = m_TileMap->GetTile(j, i);

				if (Tile->GetTileOption() != ETileOption::Wall)
					continue;

				Vector2	TilePos = Tile->GetPos();
				Vector2	TileSize = Tile->GetSize();

				if (TilePos.y - 0.001f <= RB.y && RB.y <= TilePos.y + 0.001f)
					continue;

				/*if (RB.x - TilePos.x > 8.f)
					continue;*/

					// 현재 위치의 사각형과 타일을 충돌시켜서 파고들었는지 판단한다.
				if (LT.x <= TilePos.x + TileSize.x && LT.y <= TilePos.y + TileSize.y &&
					RB.x >= TilePos.x && RB.y >= TilePos.y)
				{
					SideCollision = true;
					m_SideWallCollision = true;

					// 얼마나 파고들었는지 구한다.
					float MoveX = TilePos.x - LT.x - 0.001f;

					m_Pos.x += MoveX;
					m_Move.x += MoveX;

					break;
				}
			}

			if (SideCollision)
				break;
		}
	}


}

void CWallComponent::CheckMoveLeft()
{
	//Vector2	LT = m_Pos - m_Pivot * m_Size;
	//Vector2	RB = LT + m_Size;

	//Vector2	PrevLT = m_PrevPos - m_Pivot * m_Size;
	//Vector2	PrevRB = PrevLT + m_Size;

	//CTileMapComponent* m_TileMap = m_Scene->GetTileMap();

	//Vector3 Pos = m_Owner->GetRootComponent()->GetWorldPos();
	//Vector3 Size = m_Owner->GetRootComponent()->GetWorldScale();
	//CColliderBox2D* Collider = (CColliderBox2D*)m_Owner->GetRootComponent();

	//Vector2 BoxSize = Collider->GetBoxSize();

	//Vector2	ResultLT, ResultRB;

	//ResultLT = LT;

	//ResultLT.x = PrevLT.x;
	//ResultLT.y = LT.y > PrevLT.y ? LT.y : PrevLT.y;
	//ResultRB.y = RB.y < PrevRB.y ? RB.y : PrevRB.y;

	//float PrevBottom = m_PrevPos.y - (BoxSize.y * 0.5f);
	//float CurBottom = Pos.y - (BoxSize.y * 0.5f);

	//float PrevLeft = m_PrevPos.x - (BoxSize.x * 0.5f);
	//float CurLeft = Pos.x - (BoxSize.x * 0.5f);

	//float PrevRight = m_PrevPos.x + (BoxSize.x * 0.5f);
	//float CurRight = Pos.x + (BoxSize.x * 0.5f);

	//float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
	//float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
	//float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
	//float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;

	//int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLeft, Pos.y));
	//int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRight, Pos.y));
	//int TopIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultTop));
	//int BottomIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultBottom));

	//LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	//TopIndex = TopIndex < 0 ? 0 : TopIndex;
	//RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
	//BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;

	//if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 &&
	//	RightIndex >= 0 && BottomIndex >= 0)
	//{
	//	bool	SideCollision = false;

	//	// 위에서 아래로 차례로 검사를 해나간다.
	//	// 아래에서부터 하게 되면 위에 벽이 있을 경우 무시하고 처리되버릴 수도 있기 때문이다.
	//	for (int i = TopIndex; i <= BottomIndex; ++i)
	//	{
	//		for (int j = RightIndex; j <= LeftIndex; ++j)
	//		{
	//			CTile* Tile = m_TileMap->GetTile(j, i);

	//			if (Tile->GetTileOption() != ETileOption::Wall)
	//				continue;

	//			Vector2	TilePos = Tile->GetPos();
	//			Vector2	TileSize = Tile->GetSize();

	//			if (TilePos.y - 0.001f <= RB.y && RB.y <= TilePos.y + 0.001f)
	//				continue;

	//			/*if (RB.x - TilePos.x > 8.f)
	//				continue;*/

	//				// 현재 위치의 사각형과 타일을 충돌시켜서 파고들었는지 판단한다.
	//			if (LT.x <= TilePos.x + TileSize.x && LT.y <= TilePos.y + TileSize.y &&
	//				RB.x >= TilePos.x && RB.y >= TilePos.y)
	//			{
	//				SideCollision = true;

	//				// 얼마나 파고들었는지 구한다.
	//				float MoveX = TilePos.x - LT.x - 0.001f;

	//				m_Pos.x += MoveX;
	//				m_Move.x += MoveX;
	//				break;
	//			}
	//		}

	//		if (SideCollision)
	//			break;
	//	}
	//}




	//==
	Vector2	LT = m_Pos - m_Pivot * m_Size;
	Vector2	RB = LT + m_Size;

	Vector2	PrevLT = m_PrevPos - m_Pivot * m_Size;
	Vector2	PrevRB = PrevLT + m_Size;

	CTileMapComponent* m_TileMap = m_Scene->GetTileMap();

	Vector3 Pos = m_Owner->GetRootComponent()->GetWorldPos();
	Vector3 Size = m_Owner->GetRootComponent()->GetWorldScale();
	CColliderBox2D* Collider = (CColliderBox2D*)m_Owner->GetRootComponent();

	Vector2 BoxSize = Collider->GetBoxSize();

	Vector2	ResultLT, ResultRB;

	ResultRB = RB;

	ResultLT.x = PrevRB.x;
	ResultLT.y = LT.y > PrevLT.y ? LT.y : PrevLT.y;

	ResultRB.y = RB.y < PrevRB.y ? RB.y : PrevRB.y;

	float PrevBottom = m_PrevPos.y - (BoxSize.y * 0.5f);
	float CurBottom = Pos.y - (BoxSize.y * 0.5f);

	float PrevLeft = m_PrevPos.x - (BoxSize.x * 0.5f);
	float CurLeft = Pos.x - (BoxSize.x * 0.5f);

	float PrevRight = m_PrevPos.x + (BoxSize.x * 0.5f);
	float CurRight = Pos.x + (BoxSize.x * 0.5f);


	float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
	float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
	float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
	float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;


	int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLeft, Pos.y));
	int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRight, Pos.y));
	int TopIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultTop));
	int BottomIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultBottom));

	LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	TopIndex = TopIndex < 0 ? 0 : TopIndex;
	RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
	BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;

	if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 &&
		RightIndex >= 0 && BottomIndex >= 0)
	{
		bool	SideCollision = false;

		// 위에서 아래로 차례로 검사를 해나간다.
		// 아래에서부터 하게 되면 위에 벽이 있을 경우 무시하고 처리되버릴 수도 있기 때문이다.
		for (int i = TopIndex; i <= BottomIndex; ++i)
		{
			for (int j = LeftIndex; j <= RightIndex; ++j)
			{
				CTile* Tile = m_TileMap->GetTile(j, i);

				if (Tile->GetTileOption() != ETileOption::Wall)
					continue;

				Vector2	TilePos = Tile->GetPos();
				Vector2	TileSize = Tile->GetSize();

				if (TilePos.y - 0.001f <= RB.y && RB.y <= TilePos.y + 0.001f)
					continue;

				/*if (RB.x - TilePos.x > 8.f)
					continue;*/

					// 현재 위치의 사각형과 타일을 충돌시켜서 파고들었는지 판단한다.
				if (LT.x <= TilePos.x + TileSize.x && LT.y <= TilePos.y + TileSize.y &&
					RB.x >= TilePos.x && RB.y >= TilePos.y)
				{
					SideCollision = true;

					// 얼마나 파고들었는지 구한다.
					float MoveX = TilePos.x - RB.x - 0.001f;

					m_Pos.x += MoveX;
					m_Move.x += MoveX;
					break;
				}
			}

			if (SideCollision)
				break;
		}
	}
}


