#include "Character.h"
#include "../../main.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	m_tex.Load("Asset/Textures/0.png");
}

void Character::Update()
{
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 m_pos = m_mWorld.Translation();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }
	moveVec.Normalize();
	moveVec *= moveSpd;
	m_pos += moveVec;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);

	std::shared_ptr<KdCamera> _camera = Application::Instance().GetCamera().lock();
	if (_camera != nullptr)
	{
		//3D->2D
		_camera->ConvertWorldToScreenDetail(m_mWorld.Translation() + Math::Vector3{ 0,1.5f,0 }, m_circlePos);


		//2D->3D
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			//マウス座標取得
			POINT MousePos;
			GetCursorPos(&MousePos);//座標
			ScreenToClient(Application::Instance().GetWindow().GetWndHandle(), &MousePos);//スクリーン内

			//レイ情報計算
			Math::Vector3 rayPos, rayDir;
			float rayRange;
			_camera->GenerateRayInfoFromClientPos(MousePos, rayPos, rayDir, rayRange);


			///--------------------------------
			///レイ判定
			///--------------------------------

			//レイ判定用変数を作成
			KdCollider::RayInfo ray;

			//レイの発射原点を設定
			ray.m_pos = rayPos;

			//レイの発射方向を設定
			ray.m_dir = rayDir;

			//レイの長さを設定
			ray.m_range = rayRange;

			//当たり判定をしたいタイプを設定
			ray.m_type = KdCollider::TypeGround;

			//レイに当たったオブジェクト情報を格納するリスト
			std::list<KdCollider::CollisionResult> retRayList;

			//レイと当たり判定
			for (auto& obj : Application::Instance().GetGameObjList())
			{
				obj->Intersects(ray, &retRayList);
			}

			//レイに当たったリストから一番近いオブジェクトを検出
			float maxOverLap = 0;	//はみ出たレイの長さ
			Math::Vector3 hitPos;	//レイが遮断された座標
			bool isHit = false;		//当たっていたらtrue
			for (auto& ret : retRayList)
			{
				//レイを遮断し、オーバーした長さが一番長いものを探す
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
					isHit = true;
				}
			}

			if (isHit)
			{
				//地面に当たっている
				m_nextPos = hitPos;
			}
		}
	}

	//線形補間で移動
	Math::Vector3 movedPos = { Lerp(m_pos.x,m_nextPos.x,8 / 60.0f),Lerp(m_pos.y,m_nextPos.y,8 / 60.0f),Lerp(m_pos.z,m_nextPos.z,8 / 60.0f), };
	m_pos = movedPos;
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(m_circlePos.x, m_circlePos.y, 0));
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0);
	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}
