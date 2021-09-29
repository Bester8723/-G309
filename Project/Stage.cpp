/*************************************************************************//*!

					@file	Stage.cpp
					@brief	ステージ。

															@author	池上　綾香
*//**************************************************************************/
#include "Stage.h"
#include <sys/stat.h>

/// <summary>
/// コンストラクタ
/// </summary>
CStage::CStage() :
m_ChipTexture(),
m_BackTexture(),
m_ChipSize(0),
m_ChipCnt(0,0),
m_pChipData(NULL),
m_Scroll(0,0),
m_EnemyTextureCount(0),
m_pEnemyTexture(NULL),
m_pEnemyData(NULL),
m_EnemyCount(0),
m_ItemTextureCount(0),
m_pItemTexture(NULL),
m_pItemData(NULL),
m_ItemCount(0) {
}

/// <summary>
/// デストラクタ
/// </summary>
CStage::~CStage() {
}

/// <summary>
/// 読み込み
/// 利用するテクスチャとステージファイルを読み込む
/// </summary>
/// <param name="pName">ステージファイルの名前</param>
/// <returns>成功：true, 失敗：false</returns>
bool CStage::Load(char* pName) {
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルをすべてバッファに読み込む
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		return false;
	}

	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr))
	{
		return false;
	}

	//チップサイズ
	m_ChipSize = atof(strtok(NULL, ","));

	//マップのチップ数
	m_ChipCnt.x = atoi(strtok(NULL, ","));
	m_ChipCnt.y = atoi(strtok(NULL, ","));

	//マップチップ用のメモリを確保
	m_pChipData = (char*)malloc(m_ChipCnt.x * m_ChipCnt.y);

	//チップデータの読み込み
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			m_pChipData[y * (int)m_ChipCnt.x + x] = atoi(strtok(NULL, ","));
		}
	}

	//敵のテクスチャの読み込み
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
	for (int i = 0; i < m_EnemyTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pEnemyTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pEnemyData = (char*)malloc(m_ChipCnt.x * m_ChipCnt.y);
	m_EnemyCount = 0;
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			m_pEnemyData[y * (int)m_ChipCnt.x + x] = atoi(strtok(NULL, ","));
			if (m_pEnemyData[y * (int)m_ChipCnt.x + x] > 0)
			{
				m_EnemyCount++;
			}
		}
	}

	//アイテムのテクスチャ読み込み
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pItemData = (char*)malloc(m_ChipCnt.x * m_ChipCnt.y);
	m_ItemCount = 0;
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			pstr = strtok(NULL, ",");
			m_pItemData[y * (int)m_ChipCnt.x + x] = atoi(pstr);
			if (m_pItemData[y * (int)m_ChipCnt.x + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}

	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);

	return true;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pEnemy">敵</param>
/// <param name="pItem">アイテム</param>
void CStage::Initialize(CEnemy* pEnemy, CItem* pItem) {
	m_Scroll = Vector2(10, m_ChipSize * m_ChipCnt.y - g_pGraphics->GetTargetHeight());
	int n = 0;
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			//配置番号
			//番号０は配置しない
			char on = m_pEnemyData[y * (int)m_ChipCnt.x + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on]);
			pEnemy[n++].Initialize(Vector2(x * m_ChipSize, y * m_ChipSize), on);
		}
	}

	n = 0;
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			//配置番号
			//番号０は配置しない
			char on = m_pItemData[y * (int)m_ChipCnt.x + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(Vector2(x * m_ChipSize, y * m_ChipSize), on);
		}
	}
}

/// <summary>
/// 更新
/// </summary>
/// <param name="pl">プレイヤー。スクロールの判定に使用。</param>
void CStage::Update(CPlayer& pl) {
	CRectangle prec = pl.GetRect();											//プレイヤーの矩形
	float sh = CGraphicsUtilities::GetGraphics()->GetTargetHeight();		//スクリーンの高さ
	float stgh = m_ChipSize * m_ChipCnt.y;									//ステージ全体の高さ
	if (prec.Top - m_Scroll.y < STAGESCROLL)
	{
		m_Scroll.y -= STAGESCROLL - (prec.Top - m_Scroll.y);
		if (m_Scroll.y <= 0)
		{
			m_Scroll.y = 0;
		}
	}
	else if (prec.Bottom - m_Scroll.y > sh - STAGESCROLL)
	{
		m_Scroll.y += (prec.Bottom - m_Scroll.y) - (sh - STAGESCROLL);
		if (m_Scroll.y >= stgh - sh)
		{
			m_Scroll.y = stgh - sh;
		}
	}
}

/// <summary>
/// 描画
/// </summary>
void CStage::Render() {
	//遠景の描画
	int sch = g_pGraphics->GetTargetHeight();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_Scroll.y % hn) - hn; y < sch; y += hn)
	{
		m_BackTexture.Render(0, y);
	}

	//テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	//マップチップの描画
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			//描画するチップ番号
			//チップ番号０は描画しない
			char cn = m_pChipData[y * (int)m_ChipCnt.x + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(
				m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx), 
				m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//マップチップの描画
			m_ChipTexture.Render(-m_Scroll.x + x * m_ChipSize, -m_Scroll.y + y * m_ChipSize, cr);
		}
	}
}

/// <summary>
/// デバッグ描画
/// </summary>
void CStage::RenderDebug() {
	CGraphicsUtilities::RenderString(10, 100, "スクロール X : %.0f , Y : %.0f", m_Scroll.x, m_Scroll.y);
}

/// <summary>
/// 解放
/// </summary>
void CStage::Release() {
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	if (m_pEnemyData)
	{
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pEnemyTexture)
	{
		delete[] m_pEnemyTexture;
		m_pEnemyTexture = NULL;
	}
	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pItemTexture)
	{
		delete[] m_pItemTexture;
		m_pItemTexture = NULL;
	}
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="r">判定する矩形</param>
/// <param name="buried">埋まり量</param>
/// <returns>当たっていればtrue, 当たっていなければfalse</returns>
bool CStage::Collision(CRectangle r, Vector2& buried) {
	bool re = false;

	//当たり判定する矩形の左上と右下のチップ位置を求める
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;
	//ステージの範囲外にはならないようにする
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_ChipCnt.x) { rc = m_ChipCnt.x - 1; }
	if (bc >= m_ChipCnt.y) { bc = m_ChipCnt.y - 1; }

	//当たり判定をする矩形の左上から右下の範囲のみ当たり判定をおこなう
	//それ以外の番号は当たることはないので、判定が必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号０は当たり判定しない
			char cn = m_pChipData[y * (int)m_ChipCnt.x + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//当たり判定用のキャラクタ矩形
			//下で範囲を限定した専用の矩形を作成する。
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;		//下の矩形は上側を下と同じ値にする
			brec.Expansion(-6, 0);				//横の範囲を少し狭める
			//下と当たり判定
			if (cr.CollisionRect(brec))
			{
				re = true;
				//チップが傾斜の場合、自分の立ち位置から高さの割合を求める
				if (cn == LEFTSLOPE)
				{
					float sp = (brec.Right - cr.Left) / cr.GetWidth();
					if (sp < 0.0f) { sp = 0.0f; }
					else if (sp > 1.0f) { sp = 1.0f; }
					//斜面の上の位置を求める
					float cTop = cr.Bottom - cr.GetHeight() * sp;
					//求めた上辺より上にある場合は埋まっていない
					if (brec.Bottom < cTop) { continue; }
					//下の埋まりなので、坂上端から矩形の下端の値を引いた値が埋まりの値
					buried.y += cTop - brec.Bottom;
					r.Top += cTop - brec.Bottom;
					r.Bottom += cTop - brec.Bottom;
				}
				else
				{
					//下の埋まりなので、チップ上端から矩形の下端の値を引いた値が埋まりの値
					buried.y += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}
			}
			//チップが斜面の場合、壁・天井としての当たり判定をおこなわない
			if (cn == LEFTSLOPE) { continue; }

			//当たり判定用のキャラクタ矩形
			//左、右それぞれで範囲を限定した専用の矩形を作成する。
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;		//左の矩形は右側を左と同じ値にする
			lrec.Expansion(0, -6);				//縦の範囲を少し狭める
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;		//右の矩形は左側を右と同じ値にする
			rrec.Expansion(0, -6);				//縦の範囲を少し狭める
			//左と当たり判定
			if (cr.CollisionRect(lrec))
			{
				re = true;
				//左の埋まりなので、チップ右端から矩形の左端の値を引いた値が埋まりの値
				buried.x += cr.Right - lrec.Left;
				r.Left += cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//右と当たり判定
			else if (cr.CollisionRect(rrec))
			{
				re = true;
				//右の埋まりなので、チップ左端から矩形の右側の値を引いた値が埋まりの値
				buried.x += cr.Left - rrec.Right;
				r.Left += cr.Left - rrec.Right;
				r.Right += cr.Left - rrec.Right;
			}
			//当たり判定用のキャラクタ矩形
			//上で範囲を限定した専用の矩形を作成する。
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;		//上の矩形は下側を上と同じ値にする
			trec.Expansion(-6, 0);				//横の範囲を少し狭める
			//上と当たり判定
			if (cr.CollisionRect(trec))
			{
				re = true;
				//上の埋まりなので、チップ下端から矩形の上端の値を引いた値が埋まりの値
				buried.y += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
		}
	}

	return re;
}