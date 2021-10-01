/*************************************************************************//*!

					@file	SceneGame.cpp
					@brief	ゲーム画面。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneGame.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneGame::CSceneGame() : 
CSceneBase(),
m_Player(),
m_Stage(),
m_EnemyArray(),
m_ItemArray(),
m_EffectManager() {
}

/// <summary>
/// デストラクタ
/// </summary>
CSceneGame::~CSceneGame() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功：true, 失敗：false</returns>
bool CSceneGame::Load() {
	//プレイヤー素材の読み込み
	if (!m_Player.Load()) { return FALSE; }
	//ステージ素材の読み込み
	if (!m_Stage.Load("Stage1.txt")) { return FALSE; }
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//エフェクトの素材読み込み
	if (!m_EffectManager.Load()) { return FALSE; }
	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneGame::Initialize() {
	Load();
	//ステージの状態初期化
	m_Stage.Initialize(m_EnemyArray, m_ItemArray);
	//プレイヤーの状態初期化
	m_Player.Initialize(m_Stage.GetScroll());
	//エフェクトの状態初期化
	m_EffectManager.Initialize();
	//プレイヤーと敵にエフェクトクラスの設定
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}
}

/// <summary>
/// 更新
/// </summary>
void CSceneGame::Update() {
	//プレイヤーの更新
	m_Player.Update();
	//ステージとプレイヤーの当たり判定
	Vector2 buried = Vector2(0, 0);
	if (m_Stage.Collision(m_Player.GetRect(), buried))
	{
		m_Player.CollisionStage(buried);
	}
	//敵の更新
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update();
		Vector2 buried = Vector2(0, 0);
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), buried))
		{
			m_EnemyArray[i].CollisionStage(buried);
		}
	}
	//アイテムの更新
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		Vector2 buried = Vector2(0, 0);
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), buried))
		{
			m_ItemArray[i].CollisionStage(buried);
		}
	}
	//当たり判定の実行
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_Player.CollisionItem(m_ItemArray[i]);
	}
	//ステージの更新
	m_Stage.Update(m_Player);
	//エフェクトの更新
	m_EffectManager.Update();

	//ゲーム終了確認
	if (CGmeEndManager::Instance().IsGameEnd())
	{
		SetGameEnd(SCENENO_RESULT);
	}

	//デバッグ更新
	if (CDebugManager::Instance().GetDebugFlg())
	{
		UpdateDebug();
	}
}

/// <summary>
/// デバッグ更新
/// </summary>
void CSceneGame::UpdateDebug() {
	//F2キーでゲームシーン初期化
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		SetGameEnd(SCENENO_GAME);
	}
}

/// <summary>
/// 描画
/// </summary>
void CSceneGame::Render() {
	//スクロール量
	Vector2 scroll = m_Stage.GetScroll();
	//ステージの描画
	m_Stage.Render();
	//プレイヤーの描画
	m_Player.Render(scroll);
	//敵の描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(scroll);
	}
	//アイテムの描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(scroll);
	}
	//エフェクトの描画
	m_EffectManager.Render(scroll);
}

/// <summary>
/// デバッグ描画
/// </summary>
void CSceneGame::RenderDebug() {
	//スクロール量
	Vector2 scroll = m_Stage.GetScroll();
	//ステージのデバッグ描画
	m_Stage.RenderDebug();
	//プレイヤーのデバッグ描画
	m_Player.RenderDebug(scroll);
	//敵のデバッグ描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(scroll);
	}
	//アイテムのデバッグ描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(scroll);
	}
	//エフェクトのデバッグ描画
	m_EffectManager.RenderDebug(scroll);
}

/// <summary>
/// 解放
/// </summary>
void CSceneGame::Release() {
	//ステージの解放
	m_Stage.Release();
	//プレイヤーの解放
	m_Player.Release();
	//敵の解放
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//アイテムの解放
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//エフェクトの解放
	m_EffectManager.Release();
}

/// <summary>
/// ゲーム終了を設定する
/// </summary>
/// <param name="sceneNo">次に遷移するシーン番号</param>
void CSceneGame::SetGameEnd(int sceneNo) {
	m_bEnd = true;
	m_bChange = true;
	m_NextScene = sceneNo;
}