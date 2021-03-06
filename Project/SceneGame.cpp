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
m_Gas(),
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
	if (!m_Stage.Load("Data/Stage1.txt")) { return FALSE; }
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//瘴気素材読み込み
	if (!m_Gas.Load()) { return FALSE; }
	//エフェクトの素材読み込み
	if (!m_EffectManager.Load()) { return FALSE; }
	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneGame::Initialize() {
	//共通部
	InitializeBase();
	//ステージの状態初期化
	m_Stage.Initialize(m_EnemyArray, m_ItemArray);
	//プレイヤーの状態初期化
	m_Player.Initialize(m_Stage.GetScroll());
	//瘴気の状態初期化
	m_Gas.Initialize(m_Stage.GetScroll());
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
	//共通部
	UpdateBase();
	//プレイヤーの更新
	m_Player.Update(m_Gas.GetScroll());
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
		m_Gas.CollisionItem(m_ItemArray[i]);
	}
	//瘴気の更新
	m_Gas.Update();
	//ステージの更新
	m_Stage.Update(m_Player);
	//エフェクトの更新
	m_EffectManager.Update();

	//ゲーム終了確認
	if (CGameEndManager::Instance().IsGameEnd())
	{
		SetNextScene(SCENENO_RESULT);
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
		SetNextScene(SCENENO_GAME);
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
	//瘴気の描画
	m_Gas.Render(scroll);
	//共通部
	RenderBase();
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
	//瘴気の解放
	m_Gas.Release();
}