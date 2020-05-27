/**
* @file enemy.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "ball.h"
#include "meetstrike.h"
#include "effect.h"
#include "score.h"
#include "select.h"
#include "enemy.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief ポリゴン頂点生成関数 MakeVertexEnemy
* @param[in] int EnemyNum エネミー添え字, int EnemyType エネミータイプ
* @return HRESULT
*/
HRESULT MakeVertexEnemy(int EnemyNum, int EnemyType);

/**
* @brief テクスチャ設定関数 SetTextureEnemy
* @param[in] int cntPattern アニメパターン, int EnemyNum エネミー添え字, int EnemyType エネミータイプ
*/
void SetTextureEnemy(int cntPattern, int EnemyNum, int EnemyType);

/**
* @brief ポリゴン頂点設定関数 SetVertexEnemy
* @param[in] int EnemyNum エネミー添え字, int EnemyType エネミータイプ
*/
void SetVertexEnemy(int EnemyNum, int EnemyType);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int catmax;												  //!< ネコの合計
CAT g_cat[CAT_GOUKEI];									  //!< ネコ構造体変数
SURAIMU g_suraimu[SURAIMU_GOUKEI];						  //!< スライム構造体変数
HINOTAMA g_hinotama[HINOTAMA_GOUKEI];					  //!< 火の玉構造体変数
UFO g_ufo[UFO_GOUKEI];									  //!< UFO構造体変数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int EnemyType = 0; EnemyType < ENEMY_TYPE; EnemyType++)
	{
		switch (EnemyType)
		{
		case TYPE_CAT:
		{
			for (int CatNum = 0; CatNum < CAT_GOUKEI; CatNum++)
			{
				g_cat[CatNum].pos = D3DXVECTOR3(150.0f + Random(X), 150.0f + Random(Y), 0.0f);
				g_cat[CatNum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].point = 0;
				g_cat[CatNum].nPatternAnim = 0;
				g_cat[CatNum].nCountAnim = 0;
				g_cat[CatNum].colori = 255;
				g_cat[CatNum].motion = false;										//真アニメしている 偽アニメしていない
				g_cat[CatNum].color = false;										//真透明色A値が最大　偽最大でない
				g_cat[CatNum].effect = false;										//真エフェクトしている　偽していない
				g_cat[CatNum].chengeval = 0;										//テクスチャサイズを座標位置で変化させる
				g_cat[CatNum].oldchengeval = 0;										//進入禁止座標に行くとこれ以上サイズが変化しない
				g_cat[CatNum].use = true;											//真使用している(表示描画する) 偽使用していない

				// テクスチャの読み込み  
				if (type == 0)													// 初回のみ読み込む
				{
					D3DXCreateTextureFromFile(pDevice,							// デバイスのポインタ
						TEXTURE_GAME_CAT,										// ファイルの名前
						&g_cat[CatNum].pD3DTexture);								// 読み込むメモリのポインタ
				}
				// 頂点情報の作成
				MakeVertexEnemy(EnemyType, CatNum);
			}
			break;
		}
		case TYPE_SURAIMU:
		{
			for (int SuraimuNum = 0; SuraimuNum < SURAIMU_GOUKEI; SuraimuNum++)
			{
				g_suraimu[SuraimuNum].pos = D3DXVECTOR3(200.0f+Random(X), 160.0f + Random(Y), 0.0f);
				g_suraimu[SuraimuNum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].colori = 255;
				g_suraimu[SuraimuNum].nCountAnim = 0;
				g_suraimu[SuraimuNum].nPatternAnim = 0;
				g_suraimu[SuraimuNum].point = 0;
				g_suraimu[SuraimuNum].motion = false;									
				g_suraimu[SuraimuNum].color = false;
				g_suraimu[SuraimuNum].use = true;		
				g_suraimu[SuraimuNum].effect = false;
				g_suraimu[SuraimuNum].chengeval = 0;
				g_suraimu[SuraimuNum].oldchengeval = 0;
				if (type == 0)
				{
					D3DXCreateTextureFromFile(pDevice,
						TEXTURE_GAME_SURAIMU,
						&g_suraimu[SuraimuNum].pD3DTexture);
				}
				MakeVertexEnemy(SuraimuNum, EnemyType);
			}
			break;
		}
		case TYPE_HINOTAMA:
		{
			for (int HinotamaNum = 0; HinotamaNum < HINOTAMA_GOUKEI; HinotamaNum++)
			{
				g_hinotama[HinotamaNum].pos = D3DXVECTOR3(200.0f+Random(X), 155.0f + Random(Y), 0.0f);
				g_hinotama[HinotamaNum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].colori = 255;
				g_hinotama[HinotamaNum].nCountAnim = 0;
				g_hinotama[HinotamaNum].nPatternAnim = 0;
				g_hinotama[HinotamaNum].point = 0;
				g_hinotama[HinotamaNum].motion = false;
				g_hinotama[HinotamaNum].color = false;
				g_hinotama[HinotamaNum].use = true;		
				g_hinotama[HinotamaNum].effect = false;
				g_hinotama[HinotamaNum].chengeval = 0;
				g_hinotama[HinotamaNum].oldchengeval = 0;
				if (type == 0)
				{
					D3DXCreateTextureFromFile(pDevice,
							TEXTURE_GAME_HINOTAMA,
							&g_hinotama[HinotamaNum].pD3DTexture);
				}
				MakeVertexEnemy(HinotamaNum, EnemyType);
			}
			break;
		}
		case TYPE_UFO:
		{
			for (int UFONum = 0; UFONum < UFO_GOUKEI; UFONum++)
			{
				g_ufo[UFONum].pos = D3DXVECTOR3(250.0f+Random(X), 100.0f + Random(Y), 0.0f);
				g_ufo[UFONum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].colori = 255;
				g_ufo[UFONum].nCountAnim = 0;
				g_ufo[UFONum].point = 0;
				g_ufo[UFONum].nPatternAnim = 0;
				g_ufo[UFONum].motion = false;
				g_ufo[UFONum].color = false;
				g_ufo[UFONum].use = true;		
				g_ufo[UFONum].effect = false;
				D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_UFO_SIZE_X, TEXTURE_UFO_SIZE_Y);
				g_ufo[UFONum].rad = D3DXVec2Length(&temp);
				g_ufo[UFONum].angle = atan2f(TEXTURE_UFO_SIZE_Y, TEXTURE_UFO_SIZE_X);
				g_ufo[UFONum].movecount = BALL_MOTION_SPEED_FAST;
				if (type == 0)
				{
					D3DXCreateTextureFromFile(pDevice,
						TEXTURE_GAME_UFO,
						&g_ufo[UFONum].pD3DTexture);
				}
				MakeVertexEnemy(UFONum, EnemyType);
			}
			break;
		}
		default:
			break;
		}
	}
	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitEnemy(void)
{
	for (int EnemyType = 0; EnemyType < ENEMY_TYPE; EnemyType++)
	{
		switch (EnemyType)
		{
		case TYPE_CAT:
		{
			for (int CatNum = 0; CatNum < CAT_GOUKEI; CatNum++)
			{
				g_cat[CatNum].pos = D3DXVECTOR3(150.0f + Random(X), 150.0f + Random(Y), 0.0f);
				g_cat[CatNum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[CatNum].point = 0;
				g_cat[CatNum].nPatternAnim = 0;
				g_cat[CatNum].nCountAnim = 0;
				g_cat[CatNum].colori = 255;
				g_cat[CatNum].motion = false;										//真アニメしている 偽アニメしていない
				g_cat[CatNum].color = false;											//真透明色A値が最大　偽最大でない
				g_cat[CatNum].effect = false;										//真エフェクトしている　偽していない
				g_cat[CatNum].chengeval = 0;											//テクスチャサイズを座標位置で変化させる
				g_cat[CatNum].oldchengeval = 0;										//進入禁止座標に行くとこれ以上サイズが変化しない
				MakeVertexEnemy(CatNum, EnemyType);
				SetTextureEnemy(g_cat[CatNum].nPatternAnim, CatNum, TYPE_CAT);
			}

			SCORE * score = GetScore();
			CAT *catmax = GetCat(0);
			int cat = GetSpos();
			if (cat == L)
			{
				for (int k = 0; k < CAT_GOUKEI; k++, catmax++)
				{
					if (k < CAT_L_LEVEL) catmax->use = true;
					else catmax->use = false;
				}
				score->level = CAT_L_LEVEL;
			}
			else if (cat == M)
			{
				for (int k = 0; k < CAT_GOUKEI; k++, catmax++)
				{
					if (k < CAT_M_LEVEL) catmax->use = true;
					else catmax->use = false;
				}
				score->level = CAT_M_LEVEL;
			}
			else if (cat == H)
			{
				for (int k = 0; k < CAT_GOUKEI; k++, catmax++)
				{
					if (k < CAT_H_LEVEL) catmax->use = true;
					else catmax->use = false;
				}
				score->level = CAT_H_LEVEL;
			}
			break;
		}
		case TYPE_SURAIMU:
		{
			for (int SuraimuNum = 0; SuraimuNum < SURAIMU_GOUKEI; SuraimuNum++)
			{
				g_suraimu[SuraimuNum].pos = D3DXVECTOR3(200.0f + Random(X), 160.0f + Random(Y), 0.0f);
				g_suraimu[SuraimuNum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[SuraimuNum].colori = 255;
				g_suraimu[SuraimuNum].nCountAnim = 0;
				g_suraimu[SuraimuNum].nPatternAnim = 0;
				g_suraimu[SuraimuNum].point = 0;
				g_suraimu[SuraimuNum].motion = false;
				g_suraimu[SuraimuNum].color = false;
				g_suraimu[SuraimuNum].use = true;
				g_suraimu[SuraimuNum].effect = false;
				g_suraimu[SuraimuNum].chengeval = 0;
				g_suraimu[SuraimuNum].oldchengeval = 0;
				MakeVertexEnemy(SuraimuNum, EnemyType);
				SetTextureEnemy(g_suraimu[SuraimuNum].nPatternAnim, SuraimuNum, TYPE_SURAIMU);
			}
			break;
		}
		case TYPE_HINOTAMA:
		{
			for (int HinotamaNum = 0; HinotamaNum < HINOTAMA_GOUKEI; HinotamaNum++)
			{
				g_hinotama[HinotamaNum].pos = D3DXVECTOR3(200.0f + Random(X), 155.0f + Random(Y), 0.0f);
				g_hinotama[HinotamaNum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[HinotamaNum].colori = 255;
				g_hinotama[HinotamaNum].nCountAnim = 0;
				g_hinotama[HinotamaNum].nPatternAnim = 0;
				g_hinotama[HinotamaNum].point = 0;
				g_hinotama[HinotamaNum].motion = false;
				g_hinotama[HinotamaNum].color = false;
				g_hinotama[HinotamaNum].use = true;
				g_hinotama[HinotamaNum].effect = false;
				g_hinotama[HinotamaNum].chengeval = 0;
				g_hinotama[HinotamaNum].oldchengeval = 0;
				MakeVertexEnemy(HinotamaNum, EnemyType);
				SetTextureEnemy(g_hinotama[HinotamaNum].nPatternAnim, HinotamaNum, TYPE_HINOTAMA);
			}
			break;
		}
		case TYPE_UFO:
		{
			for (int UFONum = 0; UFONum < UFO_GOUKEI; UFONum++)
			{
				g_ufo[UFONum].pos = D3DXVECTOR3(250.0f + Random(X), 100.0f + Random(Y), 0.0f);
				g_ufo[UFONum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[UFONum].colori = 255;
				g_ufo[UFONum].nCountAnim = 0;
				g_ufo[UFONum].point = 0;
				g_ufo[UFONum].nPatternAnim = 0;
				g_ufo[UFONum].motion = false;
				g_ufo[UFONum].color = false;
				g_ufo[UFONum].use = true;
				g_ufo[UFONum].effect = false;
				D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_UFO_SIZE_X, TEXTURE_UFO_SIZE_Y);
				g_ufo[UFONum].rad = D3DXVec2Length(&temp);
				g_ufo[UFONum].angle = atan2f(TEXTURE_UFO_SIZE_Y, TEXTURE_UFO_SIZE_X);
				g_ufo[UFONum].movecount = BALL_MOTION_SPEED_FAST;
				MakeVertexEnemy(UFONum, EnemyType);
				SetTextureEnemy(g_ufo[UFONum].nPatternAnim, UFONum, TYPE_UFO);
			}
			break;
		}
		default:
			break;
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < CAT_GOUKEI; i++)
	{
		if (g_cat[i].pD3DTexture != NULL)	// 画像が読み込まれていたらテクスチャを破棄している
		{
			g_cat[i].pD3DTexture->Release();
			g_cat[i].pD3DTexture = NULL;
		}
	}
	for (int i = 0; i < SURAIMU_GOUKEI; i++)
	{
		if (g_suraimu[i].pD3DTexture != NULL)
		{
			g_suraimu[i].pD3DTexture->Release();
			g_suraimu[i].pD3DTexture = NULL;
		}
	}
	for (int i = 0; i < HINOTAMA_GOUKEI; i++)
	{
		if (g_hinotama[i].pD3DTexture != NULL)
		{
			g_hinotama[i].pD3DTexture->Release();
			g_hinotama[i].pD3DTexture = NULL;
		}
	}
	for (int i = 0; i < UFO_GOUKEI; i++)
	{
		if (g_ufo[i].pD3DTexture != NULL)	
		{
			g_ufo[i].pD3DTexture->Release();
			g_ufo[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	for (int i = 0; i < CAT_GOUKEI; i++)
	{
		if (g_cat[i].effect == false&& g_cat[i].use == true)
		{
			//動きをランダムで処理。移動方向に合わせてテクスチャパターンを変更。指定範囲外に行くと戻す
			g_cat[i].movecount++;
			if (g_cat[i].movecount > 100) g_cat[i].movecount = 0;
			if (g_cat[i].chengeval > 20.0f) g_cat[i].chengeval = g_cat[i].oldchengeval;
			if (g_cat[i].chengeval < -20.0f) g_cat[i].chengeval = g_cat[i].oldchengeval;
			if (g_cat[i].nCountAnim > 100) g_cat[i].nCountAnim = 0;
			if (g_cat[i].movecount % TIME_CAT_MOVECOUNT_MID == 0)
			{
				switch (rand() % 6)
				{
				case DIRECTION_LEFT:
					g_cat[i].direction = DIRECTION_LEFT;
					break;
				case DIRECTION_RIGHT:
					g_cat[i].direction = DIRECTION_RIGHT;
					break;
				case DIRECTION_UP:
					g_cat[i].direction = DIRECTION_UP;
					break;
				case DIRECTION_DOWN:
					g_cat[i].direction = DIRECTION_DOWN;
					break;
				default:
					g_cat[i].direction = 100;//移動しない
					break;
				}
			}
			//左向き
			if (g_cat[i].direction == DIRECTION_LEFT)
			{
				g_cat[i].nCountAnim++;
				g_cat[i].oldpos = g_cat[i].pos;
				g_cat[i].pos.x -= MOTION_SPEED_MID;
				if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0)
				{
					if (g_cat[i].nPatternAnim != ENEMY_PATTERN3 && g_cat[i].nPatternAnim != ENEMY_PATTERN4 && g_cat[i].nPatternAnim != ENEMY_PATTERN5) g_cat[i].nPatternAnim = ENEMY_PATTERN3;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN3) g_cat[i].nPatternAnim = ENEMY_PATTERN4;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN4) g_cat[i].nPatternAnim = ENEMY_PATTERN5;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN5) g_cat[i].nPatternAnim = ENEMY_PATTERN3;

				}
			}
			//右向き
			else if (g_cat[i].direction == DIRECTION_RIGHT)
			{
				g_cat[i].nCountAnim++;
				g_cat[i].oldpos = g_cat[i].pos;
				g_cat[i].pos.x += MOTION_SPEED_MID;
				if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0)
				{
					if (g_cat[i].nPatternAnim != ENEMY_PATTERN6 && g_cat[i].nPatternAnim != ENEMY_PATTERN7 && g_cat[i].nPatternAnim != ENEMY_PATTERN8) g_cat[i].nPatternAnim = ENEMY_PATTERN6;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN6) g_cat[i].nPatternAnim = ENEMY_PATTERN7;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN7) g_cat[i].nPatternAnim = ENEMY_PATTERN8;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN8) g_cat[i].nPatternAnim = ENEMY_PATTERN6;
				}
			}
			//上向き
			else if (g_cat[i].direction == DIRECTION_UP)
			{
				g_cat[i].oldchengeval = g_cat[i].chengeval;
				g_cat[i].chengeval -= ENEMY_CHENGEVAL_SIZE;
				g_cat[i].nCountAnim++;
				g_cat[i].oldpos = g_cat[i].pos;
				g_cat[i].pos.y -= MOTION_SPEED_MID;
				if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0)
				{
					if (g_cat[i].nPatternAnim != ENEMY_PATTERN9 && g_cat[i].nPatternAnim != ENEMY_PATTERN10 && g_cat[i].nPatternAnim != ENEMY_PATTERN11) g_cat[i].nPatternAnim = ENEMY_PATTERN9;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN9) g_cat[i].nPatternAnim = ENEMY_PATTERN10;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN10)g_cat[i].nPatternAnim = ENEMY_PATTERN11;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN11)g_cat[i].nPatternAnim = ENEMY_PATTERN9;

				}
			}
			//下向き
			else if (g_cat[i].direction == DIRECTION_DOWN)
			{
				g_cat[i].oldchengeval = g_cat[i].chengeval;
				g_cat[i].chengeval += ENEMY_CHENGEVAL_SIZE;
				g_cat[i].nCountAnim++;
				g_cat[i].oldpos = g_cat[i].pos;
				g_cat[i].pos.y += MOTION_SPEED_MID;
				if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0)
				{

					if (g_cat[i].nPatternAnim != ENEMY_PATTERN0 && g_cat[i].nPatternAnim != ENEMY_PATTERN1 && g_cat[i].nPatternAnim != ENEMY_PATTERN2) g_cat[i].nPatternAnim = ENEMY_PATTERN0;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN0) g_cat[i].nPatternAnim = ENEMY_PATTERN1;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN1) g_cat[i].nPatternAnim = ENEMY_PATTERN2;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN2) g_cat[i].nPatternAnim = ENEMY_PATTERN0;
				}
			}
			//動いてなくてもアニメはする
			else
			{
				g_cat[i].nCountAnim++;
			if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0) g_cat[i].nPatternAnim++;
			}
			//画面外に行ったとき処理
			if (g_cat[i].pos.y < BG_SIZE_H_TTOP) g_cat[i].pos.y = g_cat[i].oldpos.y;
			if (g_cat[i].pos.x <= TEXTURE_CAT_SIZE_X || g_cat[i].pos.x >= SCREEN_W- TEXTURE_CAT_SIZE_X)	g_cat[i].pos.x = g_cat[i].oldpos.x;
			else if (g_cat[i].pos.y >= BG_SIZE_H_TOP && g_cat[i].pos.x <= BG_SIZE_W_TOP) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_MID && g_cat[i].pos.x <= BG_SIZE_W_MID) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_UNDER && g_cat[i].pos.x <= BG_SIZE_W_UNDER) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_TOP && g_cat[i].pos.x >= SCREEN_W - BG_SIZE_W_TOP) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_MID && g_cat[i].pos.x >= SCREEN_W - BG_SIZE_W_MID) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_UNDER && g_cat[i].pos.x >= SCREEN_W - BG_SIZE_W_UNDER) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_UUNDER) g_cat[i].pos = g_cat[i].oldpos;
		}
		//死んだらエフェクトかける
		else if (g_cat[i].effect == true) DeadEffect(i,TYPE_CAT);
		SetVertexEnemy(i, TYPE_CAT);
		SetTextureEnemy(g_cat[i].nPatternAnim, i, TYPE_CAT);
	}
	for (int i = 0; i < SURAIMU_GOUKEI; i++)
	{
		if (g_suraimu[i].effect == false && g_suraimu[i].use == true)
		{
			//動きをランダムで処理。移動方向に合わせてテクスチャパターンを変更。指定範囲外に行くと戻す
			g_suraimu[i].movecount++;
			if (g_suraimu[i].movecount > 100) g_suraimu[i].movecount = 0;
			if (g_suraimu[i].chengeval > 20.0f) g_suraimu[i].chengeval = g_suraimu[i].oldchengeval;
			if (g_suraimu[i].chengeval < -20.0f) g_suraimu[i].chengeval = g_suraimu[i].oldchengeval;
			if (g_suraimu[i].nCountAnim > 100) g_suraimu[i].nCountAnim = 0;
			if (g_suraimu[i].movecount % TIME_SURAIMU_MOVECOUNT_MID == 0)
			{
				switch (rand() % 6)
				{
				case DIRECTION_LEFT:
					g_suraimu[i].direction = DIRECTION_LEFT;
					break;
				case DIRECTION_RIGHT:
					g_suraimu[i].direction = DIRECTION_RIGHT;
					break;
				case DIRECTION_UP:
					g_suraimu[i].direction = DIRECTION_UP;
					break;
				case DIRECTION_DOWN:
					g_suraimu[i].direction = DIRECTION_DOWN;
					break;
				default:
					g_suraimu[i].direction = 100;//移動しない
					break;
				}
			}
			//左向き
			if (g_suraimu[i].direction == DIRECTION_LEFT)
			{
				g_suraimu[i].nCountAnim++;
				g_suraimu[i].oldpos = g_suraimu[i].pos;
				g_suraimu[i].pos.x -= MOTION_SPEED_MID;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0)
				{
					if (g_suraimu[i].nPatternAnim != ENEMY_PATTERN3 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN4 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN5) g_suraimu[i].nPatternAnim = ENEMY_PATTERN3;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN3) g_suraimu[i].nPatternAnim = ENEMY_PATTERN4;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN4) g_suraimu[i].nPatternAnim = ENEMY_PATTERN5;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN5) g_suraimu[i].nPatternAnim = ENEMY_PATTERN3;

				}
			}
			//右向き
			else if (g_suraimu[i].direction == DIRECTION_RIGHT)
			{
				g_suraimu[i].nCountAnim++;
				g_suraimu[i].oldpos = g_suraimu[i].pos;
				g_suraimu[i].pos.x += MOTION_SPEED_MID;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0)
				{
					if (g_suraimu[i].nPatternAnim != ENEMY_PATTERN6 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN7 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN8) g_suraimu[i].nPatternAnim = ENEMY_PATTERN6;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN6) g_suraimu[i].nPatternAnim = ENEMY_PATTERN7;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN7) g_suraimu[i].nPatternAnim = ENEMY_PATTERN8;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN8) g_suraimu[i].nPatternAnim = ENEMY_PATTERN6;
				}
			}
			//上向き
			else if (g_suraimu[i].direction == DIRECTION_UP)
			{
				g_suraimu[i].oldchengeval = g_suraimu[i].chengeval;
				g_suraimu[i].chengeval -= ENEMY_CHENGEVAL_SIZE;
				g_suraimu[i].nCountAnim++;
				g_suraimu[i].oldpos = g_suraimu[i].pos;
				g_suraimu[i].pos.y -= MOTION_SPEED_MID;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0)
				{
					if (g_suraimu[i].nPatternAnim != ENEMY_PATTERN9 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN10 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN11) g_suraimu[i].nPatternAnim = ENEMY_PATTERN9;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN9) g_suraimu[i].nPatternAnim = ENEMY_PATTERN10;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN10)g_suraimu[i].nPatternAnim = ENEMY_PATTERN11;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN11)g_suraimu[i].nPatternAnim = ENEMY_PATTERN9;

				}
			}
			//下向き
			else if (g_suraimu[i].direction == DIRECTION_DOWN)
			{
				g_suraimu[i].oldchengeval = g_suraimu[i].chengeval;
				g_suraimu[i].chengeval += ENEMY_CHENGEVAL_SIZE;
				g_suraimu[i].nCountAnim++;
				g_suraimu[i].oldpos = g_suraimu[i].pos;
				g_suraimu[i].pos.y += MOTION_SPEED_MID;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0)
				{

					if (g_suraimu[i].nPatternAnim != ENEMY_PATTERN0 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN1 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN2) g_suraimu[i].nPatternAnim = ENEMY_PATTERN0;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN0) g_suraimu[i].nPatternAnim = ENEMY_PATTERN1;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN1) g_suraimu[i].nPatternAnim = ENEMY_PATTERN2;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN2) g_suraimu[i].nPatternAnim = ENEMY_PATTERN0;
				}
			}
			//動いてなくてもアニメはする
			else
			{
				g_suraimu[i].nCountAnim++;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0) g_suraimu[i].nPatternAnim++;
			}
			//画面外に行ったとき処理
			if (g_suraimu[i].pos.y < BG_SIZE_H_TTOP)
			{
				g_suraimu[i].pos.y = g_suraimu[i].oldpos.y;
			}
			if (g_suraimu[i].pos.x <= TEXTURE_CAT_SIZE_X || g_suraimu[i].pos.x >= SCREEN_W - TEXTURE_CAT_SIZE_X)
			{
				g_suraimu[i].pos.x = g_suraimu[i].oldpos.x;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_TOP && g_suraimu[i].pos.x <= BG_SIZE_W_TOP)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_MID && g_suraimu[i].pos.x <= BG_SIZE_W_MID)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_UNDER && g_suraimu[i].pos.x <= BG_SIZE_W_UNDER)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_TOP && g_suraimu[i].pos.x >= SCREEN_W - BG_SIZE_W_TOP)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_MID && g_suraimu[i].pos.x >= SCREEN_W - BG_SIZE_W_MID)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_UNDER && g_suraimu[i].pos.x >= SCREEN_W - BG_SIZE_W_UNDER)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_UUNDER)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
		}
			//死んだらエフェクトかける
		else if (g_suraimu[i].effect == true ) DeadEffect(i, TYPE_SURAIMU);
		SetVertexEnemy(i, TYPE_SURAIMU);
		SetTextureEnemy(g_suraimu[i].nPatternAnim, i, TYPE_SURAIMU);
	}
	for (int i = 0; i < HINOTAMA_GOUKEI; i++)
	{
		if (g_hinotama[i].effect == false && g_hinotama[i].use == true)
		{
			//動きをランダムで処理。移動方向に合わせてテクスチャパターンを変更。指定範囲外に行くと戻す
			g_hinotama[i].movecount++;
			if (g_hinotama[i].chengeval > 20.0f) g_hinotama[i].chengeval = g_hinotama[i].oldchengeval;
			if (g_hinotama[i].chengeval < -20.0f) g_hinotama[i].chengeval = g_hinotama[i].oldchengeval;
			if (g_hinotama[i].movecount > 100) g_hinotama[i].movecount = 0;
			if (g_hinotama[i].nCountAnim > 100) g_hinotama[i].nCountAnim = 0;
			if (g_hinotama[i].movecount % TIME_HINOTAMA_MOVECOUNT_MID == 0)
			{
				switch (rand() % 6)
				{
				case DIRECTION_LEFT:
					g_hinotama[i].direction = DIRECTION_LEFT;
					break;
				case DIRECTION_RIGHT:
					g_hinotama[i].direction = DIRECTION_RIGHT;
					break;
				case DIRECTION_UP:
					g_hinotama[i].direction = DIRECTION_UP;
					break;
				case DIRECTION_DOWN:
					g_hinotama[i].direction = DIRECTION_DOWN;
					break;
				default:
					g_hinotama[i].direction = 100;//移動しない
					break;
				}
			}
			//左向き
			if (g_hinotama[i].direction == DIRECTION_LEFT)
			{
				g_hinotama[i].nCountAnim++;
				g_hinotama[i].oldpos = g_hinotama[i].pos;
				g_hinotama[i].pos.x -= MOTION_SPEED_MID;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0)
				{
					if (g_hinotama[i].nPatternAnim != ENEMY_PATTERN3 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN4 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN5) g_hinotama[i].nPatternAnim = ENEMY_PATTERN3;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN3) g_hinotama[i].nPatternAnim = ENEMY_PATTERN4;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN4) g_hinotama[i].nPatternAnim = ENEMY_PATTERN5;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN5) g_hinotama[i].nPatternAnim = ENEMY_PATTERN3;

				}
			}
			//右向き
			else if (g_hinotama[i].direction == DIRECTION_RIGHT)
			{
				g_hinotama[i].nCountAnim++;
				g_hinotama[i].oldpos = g_hinotama[i].pos;
				g_hinotama[i].pos.x += MOTION_SPEED_MID;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0)
				{
					if (g_hinotama[i].nPatternAnim != ENEMY_PATTERN6 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN7 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN8) g_hinotama[i].nPatternAnim = ENEMY_PATTERN6;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN6) g_hinotama[i].nPatternAnim = ENEMY_PATTERN7;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN7) g_hinotama[i].nPatternAnim = ENEMY_PATTERN8;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN8) g_hinotama[i].nPatternAnim = ENEMY_PATTERN6;
				}
			}
			//上向き
			else if (g_hinotama[i].direction == DIRECTION_UP)
			{
				g_hinotama[i].oldchengeval = g_hinotama[i].chengeval;
				g_hinotama[i].chengeval -= ENEMY_CHENGEVAL_SIZE;
				g_hinotama[i].nCountAnim++;
				g_hinotama[i].oldpos = g_hinotama[i].pos;
				g_hinotama[i].pos.y -= MOTION_SPEED_MID;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0)
				{
					if (g_hinotama[i].nPatternAnim != ENEMY_PATTERN9 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN10 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN11) g_hinotama[i].nPatternAnim = ENEMY_PATTERN9;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN9) g_hinotama[i].nPatternAnim = ENEMY_PATTERN10;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN10)g_hinotama[i].nPatternAnim = ENEMY_PATTERN11;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN11)g_hinotama[i].nPatternAnim = ENEMY_PATTERN9;

				}
			}
			//下向き
			else if (g_hinotama[i].direction == DIRECTION_DOWN)
			{
				g_hinotama[i].oldchengeval = g_hinotama[i].chengeval;
				g_hinotama[i].chengeval += ENEMY_CHENGEVAL_SIZE;
				g_hinotama[i].nCountAnim++;
				g_hinotama[i].oldpos = g_hinotama[i].pos;
				g_hinotama[i].pos.y += MOTION_SPEED_MID;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0)
				{

					if (g_hinotama[i].nPatternAnim != ENEMY_PATTERN0 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN1 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN2) g_hinotama[i].nPatternAnim = ENEMY_PATTERN0;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN0) g_hinotama[i].nPatternAnim = ENEMY_PATTERN1;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN1) g_hinotama[i].nPatternAnim = ENEMY_PATTERN2;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN2) g_hinotama[i].nPatternAnim = ENEMY_PATTERN0;
				}
			}
			//動いてなくてもアニメはする
			else
			{
				g_hinotama[i].nCountAnim++;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0) g_hinotama[i].nPatternAnim++;
			}
			//画面外に行ったとき処理
			if (g_hinotama[i].pos.y < BG_SIZE_H_TTOP)
			{
				g_hinotama[i].pos.y = g_hinotama[i].oldpos.y;
			}
			if (g_hinotama[i].pos.x <= TEXTURE_CAT_SIZE_X || g_hinotama[i].pos.x >= SCREEN_W - TEXTURE_CAT_SIZE_X)
			{
				g_hinotama[i].pos.x = g_hinotama[i].oldpos.x;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_TOP && g_hinotama[i].pos.x <= BG_SIZE_W_TOP)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_MID && g_hinotama[i].pos.x <= BG_SIZE_W_MID)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_UNDER && g_hinotama[i].pos.x <= BG_SIZE_W_UNDER)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_TOP && g_hinotama[i].pos.x >= SCREEN_W - BG_SIZE_W_TOP)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_MID && g_hinotama[i].pos.x >= SCREEN_W- BG_SIZE_W_MID)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_UNDER && g_hinotama[i].pos.x >= SCREEN_W - BG_SIZE_W_UNDER)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_UUNDER)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
		}
		//死んだらエフェクトかける
		else if (g_hinotama[i].effect == true) DeadEffect(i, TYPE_HINOTAMA);
		SetVertexEnemy(i, TYPE_HINOTAMA);
		SetTextureEnemy(g_hinotama[i].nPatternAnim, i, TYPE_HINOTAMA);
	}
	for (int i = 0; i < UFO_GOUKEI; i++)
	{
		if (g_ufo[i].use == true && g_ufo[i].effect == false)
		{
			if (i & 1) g_ufo[i].rot.z += 0.1f;
			else
			{
				D3DXVECTOR3 pos = GetStrike()->s.pos - g_ufo[i].pos;
				g_ufo[i].rot.z = atan2f(pos.y, pos.x) - D3DX_PI / 2;
			}
			g_ufo[i].pos.x += g_ufo[i].movecount;
			if ((g_ufo[i].pos.x < TEXTURE_UFO_SIZE_X) || (g_ufo[i].pos.x > SCREEN_W - TEXTURE_UFO_SIZE_X)) g_ufo[i].movecount *= -1;
		}
		else if (g_ufo[i].effect == true) DeadEffect(i, TYPE_UFO);
		SetVertexEnemy(i, TYPE_UFO);
		SetTextureEnemy(g_ufo[i].nPatternAnim, i, TYPE_UFO);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < CAT_GOUKEI; i++)
	{
		if (g_cat[i].use == true)
		{
				// 頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_2D);
				// テクスチャの設定  
				pDevice->SetTexture(0, g_cat[i].pD3DTexture);
				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_cat[i].vertexWk[0], sizeof(VERTEX_2D));
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_cat[i].vertexWk[4], sizeof(VERTEX_2D));
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_cat[i].vertexWk[8], sizeof(VERTEX_2D));
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_cat[i].vertexWk[12], sizeof(VERTEX_2D));
		}
	}
	for (int i = 0; i < SURAIMU_GOUKEI; i++)
	{
		if (g_suraimu[i].use == true)
		{
			pDevice->SetFVF(FVF_VERTEX_2D);
			pDevice->SetTexture(0, g_suraimu[i].pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_suraimu[i].vertexWk[0], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_suraimu[i].vertexWk[4], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_suraimu[i].vertexWk[8], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_suraimu[i].vertexWk[12], sizeof(VERTEX_2D));
		}
	}
	for (int i = 0; i < HINOTAMA_GOUKEI; i++)
	{
		if (g_hinotama[i].use == true)
		{
			pDevice->SetFVF(FVF_VERTEX_2D);
			pDevice->SetTexture(0, g_hinotama[i].pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_hinotama[i].vertexWk[0], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_hinotama[i].vertexWk[4], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_hinotama[i].vertexWk[8], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_hinotama[i].vertexWk[12], sizeof(VERTEX_2D));
		}
	}
	for (int i = 0; i < UFO_GOUKEI; i++)
	{
		if (g_ufo[i].use == true)
		{
			pDevice->SetFVF(FVF_VERTEX_2D);
			pDevice->SetTexture(0, g_ufo[i].pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_ufo[i].vertexWk[0], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_ufo[i].vertexWk[4], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_ufo[i].vertexWk[8], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_ufo[i].vertexWk[12], sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy(int EnemyNum, int EnemyType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	switch (EnemyType)
	{
	case TYPE_CAT:
	{
		// rhwの設定　頂点が重なった時の描画順番
		g_cat[EnemyNum].vertexWk[0].rhw =
			g_cat[EnemyNum].vertexWk[1].rhw =
			g_cat[EnemyNum].vertexWk[2].rhw =
			g_cat[EnemyNum].vertexWk[3].rhw =
			g_cat[EnemyNum].vertexWk[4].rhw =
			g_cat[EnemyNum].vertexWk[5].rhw =
			g_cat[EnemyNum].vertexWk[6].rhw =
			g_cat[EnemyNum].vertexWk[7].rhw =
			g_cat[EnemyNum].vertexWk[8].rhw =
			g_cat[EnemyNum].vertexWk[9].rhw =
			g_cat[EnemyNum].vertexWk[10].rhw =
			g_cat[EnemyNum].vertexWk[11].rhw =
			g_cat[EnemyNum].vertexWk[12].rhw =
			g_cat[EnemyNum].vertexWk[13].rhw =
			g_cat[EnemyNum].vertexWk[14].rhw =
			g_cat[EnemyNum].vertexWk[15].rhw = 1.0f;
		// 反射光の設定  頂点カラー指定した色とテクスチャの色が混ざってカラーリングされる
		// フェードインは始めに表示したテクスチャの上に透明なテクスチャを表示。RGBAのAを徐々に不透明にしていく
		g_cat[EnemyNum].vertexWk[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[4].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[5].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[6].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[7].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[8].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[9].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[10].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[11].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[EnemyNum].vertexWk[12].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cat[EnemyNum].vertexWk[13].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cat[EnemyNum].vertexWk[14].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cat[EnemyNum].vertexWk[15].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		// テクスチャ座標の設定  
		g_cat[EnemyNum].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_cat[EnemyNum].vertexWk[1].tex = D3DXVECTOR2(0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.0f);
		g_cat[EnemyNum].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		g_cat[EnemyNum].vertexWk[3].tex = D3DXVECTOR2(0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y);

		g_cat[EnemyNum].vertexWk[4].tex = D3DXVECTOR2(0.5f, 0.0f);
		g_cat[EnemyNum].vertexWk[5].tex = D3DXVECTOR2(1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.0f);
		g_cat[EnemyNum].vertexWk[6].tex = D3DXVECTOR2(0.5f, 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		g_cat[EnemyNum].vertexWk[7].tex = D3DXVECTOR2(1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y);

		g_cat[EnemyNum].vertexWk[8].tex = D3DXVECTOR2(0.0f, 0.5f);
		g_cat[EnemyNum].vertexWk[9].tex = D3DXVECTOR2(0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.5f);
		g_cat[EnemyNum].vertexWk[10].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		g_cat[EnemyNum].vertexWk[11].tex = D3DXVECTOR2(0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X, 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y);

		g_cat[EnemyNum].vertexWk[12].tex = D3DXVECTOR2(0.5f, 0.5f);
		g_cat[EnemyNum].vertexWk[13].tex = D3DXVECTOR2(1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.5f);
		g_cat[EnemyNum].vertexWk[14].tex = D3DXVECTOR2(0.5f, 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		g_cat[EnemyNum].vertexWk[15].tex = D3DXVECTOR2(1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X, 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		// 頂点座標の設定
		SetVertexEnemy(EnemyNum, EnemyType);
		break;
	}
	case TYPE_SURAIMU:
	{
		g_suraimu[EnemyNum].vertexWk[0].rhw =
			g_suraimu[EnemyNum].vertexWk[1].rhw =
			g_suraimu[EnemyNum].vertexWk[2].rhw =
			g_suraimu[EnemyNum].vertexWk[3].rhw =
			g_suraimu[EnemyNum].vertexWk[4].rhw =
			g_suraimu[EnemyNum].vertexWk[5].rhw =
			g_suraimu[EnemyNum].vertexWk[6].rhw =
			g_suraimu[EnemyNum].vertexWk[7].rhw =
			g_suraimu[EnemyNum].vertexWk[8].rhw =
			g_suraimu[EnemyNum].vertexWk[9].rhw =
			g_suraimu[EnemyNum].vertexWk[10].rhw =
			g_suraimu[EnemyNum].vertexWk[11].rhw =
			g_suraimu[EnemyNum].vertexWk[12].rhw =
			g_suraimu[EnemyNum].vertexWk[13].rhw =
			g_suraimu[EnemyNum].vertexWk[14].rhw =
			g_suraimu[EnemyNum].vertexWk[15].rhw = 1.0f;
		g_suraimu[EnemyNum].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[4].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[5].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[6].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[7].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[8].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[9].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[10].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[11].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[12].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[13].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[14].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[15].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[EnemyNum].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_suraimu[EnemyNum].vertexWk[1].tex = D3DXVECTOR2(0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.0f);
		g_suraimu[EnemyNum].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[EnemyNum].vertexWk[3].tex = D3DXVECTOR2(0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[EnemyNum].vertexWk[4].tex = D3DXVECTOR2(0.5f, 0.0f);
		g_suraimu[EnemyNum].vertexWk[5].tex = D3DXVECTOR2(1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.0f);
		g_suraimu[EnemyNum].vertexWk[6].tex = D3DXVECTOR2(0.5f, 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[EnemyNum].vertexWk[7].tex = D3DXVECTOR2(1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[EnemyNum].vertexWk[8].tex = D3DXVECTOR2(0.0f, 0.5f);
		g_suraimu[EnemyNum].vertexWk[9].tex = D3DXVECTOR2(0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.5f);
		g_suraimu[EnemyNum].vertexWk[10].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[EnemyNum].vertexWk[11].tex = D3DXVECTOR2(0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[EnemyNum].vertexWk[12].tex = D3DXVECTOR2(0.5f, 0.5f);
		g_suraimu[EnemyNum].vertexWk[13].tex = D3DXVECTOR2(1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.5f);
		g_suraimu[EnemyNum].vertexWk[14].tex = D3DXVECTOR2(0.5f, 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[EnemyNum].vertexWk[15].tex = D3DXVECTOR2(1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		SetVertexEnemy(EnemyNum, EnemyType);
		break;
	}
	case TYPE_HINOTAMA:
	{
		g_hinotama[EnemyNum].vertexWk[0].rhw =
			g_hinotama[EnemyNum].vertexWk[1].rhw =
			g_hinotama[EnemyNum].vertexWk[2].rhw =
			g_hinotama[EnemyNum].vertexWk[3].rhw =
			g_hinotama[EnemyNum].vertexWk[4].rhw =
			g_hinotama[EnemyNum].vertexWk[5].rhw =
			g_hinotama[EnemyNum].vertexWk[6].rhw =
			g_hinotama[EnemyNum].vertexWk[7].rhw =
			g_hinotama[EnemyNum].vertexWk[8].rhw =
			g_hinotama[EnemyNum].vertexWk[9].rhw =
			g_hinotama[EnemyNum].vertexWk[10].rhw =
			g_hinotama[EnemyNum].vertexWk[11].rhw =
			g_hinotama[EnemyNum].vertexWk[12].rhw =
			g_hinotama[EnemyNum].vertexWk[13].rhw =
			g_hinotama[EnemyNum].vertexWk[14].rhw =
			g_hinotama[EnemyNum].vertexWk[15].rhw = 1.0f;
		g_hinotama[EnemyNum].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[4].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[5].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[6].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[7].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[8].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[9].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[10].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[11].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[12].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[13].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[14].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[15].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[EnemyNum].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_hinotama[EnemyNum].vertexWk[1].tex = D3DXVECTOR2(0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.0f);
		g_hinotama[EnemyNum].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[EnemyNum].vertexWk[3].tex = D3DXVECTOR2(0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[EnemyNum].vertexWk[4].tex = D3DXVECTOR2(0.5f, 0.0f);
		g_hinotama[EnemyNum].vertexWk[5].tex = D3DXVECTOR2(1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.0f);
		g_hinotama[EnemyNum].vertexWk[6].tex = D3DXVECTOR2(0.5f, 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[EnemyNum].vertexWk[7].tex = D3DXVECTOR2(1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[EnemyNum].vertexWk[8].tex = D3DXVECTOR2(0.0f, 0.5f);
		g_hinotama[EnemyNum].vertexWk[9].tex = D3DXVECTOR2(0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.5f);
		g_hinotama[EnemyNum].vertexWk[10].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[EnemyNum].vertexWk[11].tex = D3DXVECTOR2(0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[EnemyNum].vertexWk[12].tex = D3DXVECTOR2(0.5f, 0.5f);
		g_hinotama[EnemyNum].vertexWk[13].tex = D3DXVECTOR2(1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.5f);
		g_hinotama[EnemyNum].vertexWk[14].tex = D3DXVECTOR2(0.5f, 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[EnemyNum].vertexWk[15].tex = D3DXVECTOR2(1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		SetVertexEnemy(EnemyNum, EnemyType);
		break;
	}
	case TYPE_UFO:
	{
		g_ufo[EnemyNum].vertexWk[0].rhw =
			g_ufo[EnemyNum].vertexWk[1].rhw =
			g_ufo[EnemyNum].vertexWk[2].rhw =
			g_ufo[EnemyNum].vertexWk[3].rhw =
			g_ufo[EnemyNum].vertexWk[4].rhw =
			g_ufo[EnemyNum].vertexWk[5].rhw =
			g_ufo[EnemyNum].vertexWk[6].rhw =
			g_ufo[EnemyNum].vertexWk[7].rhw =
			g_ufo[EnemyNum].vertexWk[8].rhw =
			g_ufo[EnemyNum].vertexWk[9].rhw =
			g_ufo[EnemyNum].vertexWk[10].rhw =
			g_ufo[EnemyNum].vertexWk[11].rhw =
			g_ufo[EnemyNum].vertexWk[12].rhw =
			g_ufo[EnemyNum].vertexWk[13].rhw =
			g_ufo[EnemyNum].vertexWk[14].rhw =
			g_ufo[EnemyNum].vertexWk[15].rhw = 1.0f;
		g_ufo[EnemyNum].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[4].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[5].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[6].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[7].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[8].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[9].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[10].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[11].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[12].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[13].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[14].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[15].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[EnemyNum].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ufo[EnemyNum].vertexWk[1].tex = D3DXVECTOR2(0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.0f);
		g_ufo[EnemyNum].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[EnemyNum].vertexWk[3].tex = D3DXVECTOR2(0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[EnemyNum].vertexWk[4].tex = D3DXVECTOR2(0.5f, 0.0f);
		g_ufo[EnemyNum].vertexWk[5].tex = D3DXVECTOR2(1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.0f);
		g_ufo[EnemyNum].vertexWk[6].tex = D3DXVECTOR2(0.5f, 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[EnemyNum].vertexWk[7].tex = D3DXVECTOR2(1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[EnemyNum].vertexWk[8].tex = D3DXVECTOR2(0.0f, 0.5f);
		g_ufo[EnemyNum].vertexWk[9].tex = D3DXVECTOR2(0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.5f);
		g_ufo[EnemyNum].vertexWk[10].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[EnemyNum].vertexWk[11].tex = D3DXVECTOR2(0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X, 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[EnemyNum].vertexWk[12].tex = D3DXVECTOR2(0.5f, 0.5f);
		g_ufo[EnemyNum].vertexWk[13].tex = D3DXVECTOR2(1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.5f);
		g_ufo[EnemyNum].vertexWk[14].tex = D3DXVECTOR2(0.5f, 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[EnemyNum].vertexWk[15].tex = D3DXVECTOR2(1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X, 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		SetVertexEnemy(EnemyNum, EnemyType);
		break;
	}
	default:
		break;
	}
	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy(int cntPattern, int EnemyNum, int EnemyType)
{
	switch (EnemyType)
	{
	case TYPE_CAT:
	{
		// テクスチャ座標の設定000,122,241,360,482,,,,000,122,244,360,482,5104,,,,,051,13,25
		int x = cntPattern % TEXTURE_CAT_PATTERN_DIVIDE_X;	//x軸のアニメパターン数をxとする								xパターン数3
		int y = cntPattern / TEXTURE_CAT_PATTERN_DIVIDE_X;	//y軸のアニメパターン数をyとする								yパターン数4
		float sizeX = 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X;		//x軸のアニメパターン数に応じてsizeXづつx軸がずれる				x1パターンずれる
		float sizeY = 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y;		//y軸のアニメパターン数に応じてsizeYづつy軸がずれる
		float sizeXofs = 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X;		//x軸のアニメパターン数に応じてsizeXづつx軸がずれる				x1パターンずれる
		float sizeYofs = 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y;		//y軸のアニメパターン数に応じてsizeYづつy軸がずれる
		/*

		                     1                                    3                                  5                  
		0.0,0.0              0.16             0.3              0.5,0.0            0.66              0.83              1.0,0.0
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll     p1         ll                l
			l       p1       ll       p2       ll                ll      p2        ll                ll     p2         l
			l                ll                ll         p1     ll      2         ll     3          ll                l
			l       1        ll       1        ll       2        ll                ll                ll    3           l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
0.125		l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l       p3       ll     p4         ll        p3      ll      p4        ll                ll      p4        l
			l       1        ll       1        ll                ll                ll        p3      ll                l
			l                ll                ll        2       ll                ll                ll                l
			l                ll                ll                ll       2        ll                ll    3           l
			l                ll                ll                ll                ll      3         ll                l
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l                ll     4          ll      5         ll                ll                ll                l
			l       4        ll                ll                ll                ll           6    ll        6       l
			l                ll                ll                ll  5             ll                ll                l
			l                ll                ll                ll                ll                ll                l
0.375		l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l         4      ll                ll                ll                ll                ll        6       l
			l                ll        4       ll        5       ll     5          ll         6      ll                l
			l                ll                ll                ll                ll                ll                l
 0.0,0.5	l                ll                ll                ll                ll                ll                l  1.0,0.5
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll 7              ll                ll                ll                ll                l
			l        7       ll                ll                ll                ll   9            ll       9        l
			l                ll                ll                ll         8      ll                ll                l
			l                ll                ll   8            ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
0.625		l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l                ll      7         ll                ll                ll        9       ll                l
			l        7       ll                ll       8        ll       8        ll                ll       9        l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll 10             ll                ll                ll                ll                l
			l        10      ll                ll                ll                ll   12           ll       12       l
			l                ll                ll                ll         11     ll                ll                l
			l                ll                ll  11            ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
0.875		l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l                ll      10        ll                ll                ll       12       ll                l
			l       10       ll                ll       11       ll      11        ll                ll       12       l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l

		0.0,1.0													0.5,1.0													1.0,1.0




		*/



		g_cat[EnemyNum].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);												//0.0,0.0
		g_cat[EnemyNum].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);									//0.5,0.0
		g_cat[EnemyNum].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);									//0.0,0.5
		g_cat[EnemyNum].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);							//0.5,0.5
																															
		g_cat[EnemyNum].vertexWk[4].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);									//0.5,0.0
		g_cat[EnemyNum].vertexWk[5].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY);							//1.0,0.0
		g_cat[EnemyNum].vertexWk[6].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);							//0.5,0.5
		g_cat[EnemyNum].vertexWk[7].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);				//1.0,0.5
																															
		g_cat[EnemyNum].vertexWk[8].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);									//0.0,0.5
		g_cat[EnemyNum].vertexWk[9].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);							//0.5,0.5
		g_cat[EnemyNum].vertexWk[10].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs + sizeYofs);						//0.0,1.0
		g_cat[EnemyNum].vertexWk[11].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);				//0.5,1.0
																															
		g_cat[EnemyNum].vertexWk[12].tex = D3DXVECTOR2((float)(x)* sizeX+ sizeXofs, (float)(y)* sizeY + sizeYofs);							//0.5,0.5
		g_cat[EnemyNum].vertexWk[13].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);				//1.0,0.5
		g_cat[EnemyNum].vertexWk[14].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);				//0.5,1.0
		g_cat[EnemyNum].vertexWk[15].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);	//1.0,1.0
		break;
	}
	case TYPE_SURAIMU:
	{
		int x = cntPattern % TEXTURE_SURAIMU_PATTERN_DIVIDE_X;
		int y = cntPattern / TEXTURE_SURAIMU_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y;
		float sizeXofs = 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X;
		float sizeYofs = 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y;
		g_suraimu[EnemyNum].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_suraimu[EnemyNum].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_suraimu[EnemyNum].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[4].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_suraimu[EnemyNum].vertexWk[5].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY);
		g_suraimu[EnemyNum].vertexWk[6].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[7].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[8].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[9].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[10].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[11].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[12].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[13].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[14].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_suraimu[EnemyNum].vertexWk[15].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		break;
	}
	case TYPE_HINOTAMA:
	{
		int x = cntPattern % TEXTURE_HINOTAMA_PATTERN_DIVIDE_X;
		int y = cntPattern / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y;
		float sizeXofs = 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X;
		float sizeYofs = 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y;
		g_hinotama[EnemyNum].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_hinotama[EnemyNum].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_hinotama[EnemyNum].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[4].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_hinotama[EnemyNum].vertexWk[5].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY);
		g_hinotama[EnemyNum].vertexWk[6].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[7].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[8].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[9].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[10].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[11].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[12].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[13].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[14].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_hinotama[EnemyNum].vertexWk[15].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		break;
	}
	case TYPE_UFO:
	{
		int x = cntPattern % TEXTURE_UFO_PATTERN_DIVIDE_X;
		int y = cntPattern / TEXTURE_UFO_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y;
		float sizeXofs = 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X;
		float sizeYofs = 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y;
		g_ufo[EnemyNum].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_ufo[EnemyNum].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_ufo[EnemyNum].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_ufo[EnemyNum].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[EnemyNum].vertexWk[4].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_ufo[EnemyNum].vertexWk[5].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY);
		g_ufo[EnemyNum].vertexWk[6].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[EnemyNum].vertexWk[7].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[EnemyNum].vertexWk[8].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_ufo[EnemyNum].vertexWk[9].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[EnemyNum].vertexWk[10].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_ufo[EnemyNum].vertexWk[11].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_ufo[EnemyNum].vertexWk[12].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[EnemyNum].vertexWk[13].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[EnemyNum].vertexWk[14].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_ufo[EnemyNum].vertexWk[15].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		break;
	}
	default:
		break;
	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy(int EnemyNum, int EnemyType)
{
	switch (EnemyType)
	{
	case TYPE_CAT:
	{
		// 頂点座標の設定 
		g_cat[EnemyNum].vertexWk[0].vtx.x = g_cat[EnemyNum].pos.x - TEXTURE_CAT_SIZE_X - g_cat[EnemyNum].chengeval - g_cat[EnemyNum].ppos[0].x;
		g_cat[EnemyNum].vertexWk[0].vtx.y = g_cat[EnemyNum].pos.y - TEXTURE_CAT_SIZE_Y - g_cat[EnemyNum].chengeval - g_cat[EnemyNum].ppos[0].y;
		g_cat[EnemyNum].vertexWk[0].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[1].vtx.x = g_cat[EnemyNum].pos.x - g_cat[EnemyNum].ppos[0].x;
		g_cat[EnemyNum].vertexWk[1].vtx.y = g_cat[EnemyNum].pos.y - TEXTURE_CAT_SIZE_Y - g_cat[EnemyNum].chengeval - g_cat[EnemyNum].ppos[0].y;
		g_cat[EnemyNum].vertexWk[1].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[2].vtx.x = g_cat[EnemyNum].pos.x - TEXTURE_CAT_SIZE_X - g_cat[EnemyNum].chengeval - g_cat[EnemyNum].ppos[0].x;
		g_cat[EnemyNum].vertexWk[2].vtx.y = g_cat[EnemyNum].pos.y - g_cat[EnemyNum].ppos[0].y;
		g_cat[EnemyNum].vertexWk[2].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[3].vtx.x = g_cat[EnemyNum].pos.x - g_cat[EnemyNum].ppos[0].x;
		g_cat[EnemyNum].vertexWk[3].vtx.y = g_cat[EnemyNum].pos.y - g_cat[EnemyNum].ppos[0].y;
		g_cat[EnemyNum].vertexWk[3].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[4].vtx.x = g_cat[EnemyNum].pos.x + g_cat[EnemyNum].ppos[1].x;
		g_cat[EnemyNum].vertexWk[4].vtx.y = g_cat[EnemyNum].pos.y - TEXTURE_CAT_SIZE_Y - g_cat[EnemyNum].chengeval + g_cat[EnemyNum].ppos[1].y;
		g_cat[EnemyNum].vertexWk[4].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[5].vtx.x = g_cat[EnemyNum].pos.x + TEXTURE_CAT_SIZE_X + g_cat[EnemyNum].chengeval + g_cat[EnemyNum].ppos[1].x;
		g_cat[EnemyNum].vertexWk[5].vtx.y = g_cat[EnemyNum].pos.y - TEXTURE_CAT_SIZE_Y - g_cat[EnemyNum].chengeval + g_cat[EnemyNum].ppos[1].y;
		g_cat[EnemyNum].vertexWk[5].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[6].vtx.x = g_cat[EnemyNum].pos.x + g_cat[EnemyNum].ppos[1].x;
		g_cat[EnemyNum].vertexWk[6].vtx.y = g_cat[EnemyNum].pos.y + g_cat[EnemyNum].ppos[1].y;
		g_cat[EnemyNum].vertexWk[6].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[7].vtx.x = g_cat[EnemyNum].pos.x + TEXTURE_CAT_SIZE_X + g_cat[EnemyNum].chengeval + g_cat[EnemyNum].ppos[1].x;
		g_cat[EnemyNum].vertexWk[7].vtx.y = g_cat[EnemyNum].pos.y + g_cat[EnemyNum].ppos[1].y;
		g_cat[EnemyNum].vertexWk[7].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[8].vtx.x = g_cat[EnemyNum].pos.x - TEXTURE_CAT_SIZE_X - g_cat[EnemyNum].chengeval - g_cat[EnemyNum].ppos[2].x;
		g_cat[EnemyNum].vertexWk[8].vtx.y = g_cat[EnemyNum].pos.y - g_cat[EnemyNum].ppos[2].y;
		g_cat[EnemyNum].vertexWk[8].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[9].vtx.x = g_cat[EnemyNum].pos.x - g_cat[EnemyNum].ppos[2].x;
		g_cat[EnemyNum].vertexWk[9].vtx.y = g_cat[EnemyNum].pos.y - g_cat[EnemyNum].ppos[2].y;
		g_cat[EnemyNum].vertexWk[9].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[10].vtx.x = g_cat[EnemyNum].pos.x - TEXTURE_CAT_SIZE_X - g_cat[EnemyNum].chengeval - g_cat[EnemyNum].ppos[2].x;
		g_cat[EnemyNum].vertexWk[10].vtx.y = g_cat[EnemyNum].pos.y + TEXTURE_CAT_SIZE_Y + g_cat[EnemyNum].chengeval - g_cat[EnemyNum].ppos[2].y;
		g_cat[EnemyNum].vertexWk[10].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[11].vtx.x = g_cat[EnemyNum].pos.x - g_cat[EnemyNum].ppos[2].x;
		g_cat[EnemyNum].vertexWk[11].vtx.y = g_cat[EnemyNum].pos.y + TEXTURE_CAT_SIZE_Y + g_cat[EnemyNum].chengeval - g_cat[EnemyNum].ppos[2].y;
		g_cat[EnemyNum].vertexWk[11].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[12].vtx.x = g_cat[EnemyNum].pos.x + g_cat[EnemyNum].ppos[3].x;
		g_cat[EnemyNum].vertexWk[12].vtx.y = g_cat[EnemyNum].pos.y + g_cat[EnemyNum].ppos[3].y;
		g_cat[EnemyNum].vertexWk[12].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[13].vtx.x = g_cat[EnemyNum].pos.x + TEXTURE_CAT_SIZE_X + g_cat[EnemyNum].chengeval + g_cat[EnemyNum].ppos[3].x;
		g_cat[EnemyNum].vertexWk[13].vtx.y = g_cat[EnemyNum].pos.y + g_cat[EnemyNum].ppos[3].y;
		g_cat[EnemyNum].vertexWk[13].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[14].vtx.x = g_cat[EnemyNum].pos.x + g_cat[EnemyNum].ppos[3].x;
		g_cat[EnemyNum].vertexWk[14].vtx.y = g_cat[EnemyNum].pos.y + TEXTURE_CAT_SIZE_Y + g_cat[EnemyNum].chengeval + g_cat[EnemyNum].ppos[3].y;
		g_cat[EnemyNum].vertexWk[14].vtx.z = 0.0f;
		g_cat[EnemyNum].vertexWk[15].vtx.x = g_cat[EnemyNum].pos.x + TEXTURE_CAT_SIZE_X + g_cat[EnemyNum].chengeval + g_cat[EnemyNum].ppos[3].x;
		g_cat[EnemyNum].vertexWk[15].vtx.y = g_cat[EnemyNum].pos.y + TEXTURE_CAT_SIZE_Y + g_cat[EnemyNum].chengeval + g_cat[EnemyNum].ppos[3].y;
		g_cat[EnemyNum].vertexWk[15].vtx.z = 0.0f;

		break;
	}
	case TYPE_SURAIMU:
	{
		g_suraimu[EnemyNum].vertexWk[0].vtx.x = g_suraimu[EnemyNum].pos.x - TEXTURE_SURAIMU_SIZE_X - g_suraimu[EnemyNum].chengeval - g_suraimu[EnemyNum].ppos[0].x;
		g_suraimu[EnemyNum].vertexWk[0].vtx.y = g_suraimu[EnemyNum].pos.y - TEXTURE_SURAIMU_SIZE_Y - g_suraimu[EnemyNum].chengeval - g_suraimu[EnemyNum].ppos[0].y;
		g_suraimu[EnemyNum].vertexWk[0].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[1].vtx.x = g_suraimu[EnemyNum].pos.x - g_suraimu[EnemyNum].ppos[0].x;
		g_suraimu[EnemyNum].vertexWk[1].vtx.y = g_suraimu[EnemyNum].pos.y - TEXTURE_SURAIMU_SIZE_Y - g_suraimu[EnemyNum].chengeval - g_suraimu[EnemyNum].ppos[0].y;
		g_suraimu[EnemyNum].vertexWk[1].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[2].vtx.x = g_suraimu[EnemyNum].pos.x - TEXTURE_SURAIMU_SIZE_X - g_suraimu[EnemyNum].chengeval - g_suraimu[EnemyNum].ppos[0].x;
		g_suraimu[EnemyNum].vertexWk[2].vtx.y = g_suraimu[EnemyNum].pos.y - g_suraimu[EnemyNum].ppos[0].y;
		g_suraimu[EnemyNum].vertexWk[2].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[3].vtx.x = g_suraimu[EnemyNum].pos.x - g_suraimu[EnemyNum].ppos[0].x;
		g_suraimu[EnemyNum].vertexWk[3].vtx.y = g_suraimu[EnemyNum].pos.y - g_suraimu[EnemyNum].ppos[0].y;
		g_suraimu[EnemyNum].vertexWk[3].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[4].vtx.x = g_suraimu[EnemyNum].pos.x + g_suraimu[EnemyNum].ppos[1].x;
		g_suraimu[EnemyNum].vertexWk[4].vtx.y = g_suraimu[EnemyNum].pos.y - TEXTURE_SURAIMU_SIZE_Y - g_suraimu[EnemyNum].chengeval + g_suraimu[EnemyNum].ppos[1].y;
		g_suraimu[EnemyNum].vertexWk[4].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[5].vtx.x = g_suraimu[EnemyNum].pos.x + TEXTURE_SURAIMU_SIZE_X + g_suraimu[EnemyNum].chengeval + g_suraimu[EnemyNum].ppos[1].x;
		g_suraimu[EnemyNum].vertexWk[5].vtx.y = g_suraimu[EnemyNum].pos.y - TEXTURE_SURAIMU_SIZE_Y - g_suraimu[EnemyNum].chengeval + g_suraimu[EnemyNum].ppos[1].y;
		g_suraimu[EnemyNum].vertexWk[5].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[6].vtx.x = g_suraimu[EnemyNum].pos.x + g_suraimu[EnemyNum].ppos[1].x;
		g_suraimu[EnemyNum].vertexWk[6].vtx.y = g_suraimu[EnemyNum].pos.y + g_suraimu[EnemyNum].ppos[1].y;
		g_suraimu[EnemyNum].vertexWk[6].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[7].vtx.x = g_suraimu[EnemyNum].pos.x + TEXTURE_SURAIMU_SIZE_X + g_suraimu[EnemyNum].chengeval + g_suraimu[EnemyNum].ppos[1].x;
		g_suraimu[EnemyNum].vertexWk[7].vtx.y = g_suraimu[EnemyNum].pos.y + g_suraimu[EnemyNum].ppos[1].y;
		g_suraimu[EnemyNum].vertexWk[7].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[8].vtx.x = g_suraimu[EnemyNum].pos.x - TEXTURE_SURAIMU_SIZE_X - g_suraimu[EnemyNum].chengeval - g_suraimu[EnemyNum].ppos[2].x;
		g_suraimu[EnemyNum].vertexWk[8].vtx.y = g_suraimu[EnemyNum].pos.y - g_suraimu[EnemyNum].ppos[2].y;
		g_suraimu[EnemyNum].vertexWk[8].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[9].vtx.x = g_suraimu[EnemyNum].pos.x - g_suraimu[EnemyNum].ppos[2].x;
		g_suraimu[EnemyNum].vertexWk[9].vtx.y = g_suraimu[EnemyNum].pos.y - g_suraimu[EnemyNum].ppos[2].y;
		g_suraimu[EnemyNum].vertexWk[9].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[10].vtx.x = g_suraimu[EnemyNum].pos.x - TEXTURE_SURAIMU_SIZE_X - g_suraimu[EnemyNum].chengeval - g_suraimu[EnemyNum].ppos[2].x;
		g_suraimu[EnemyNum].vertexWk[10].vtx.y = g_suraimu[EnemyNum].pos.y + TEXTURE_SURAIMU_SIZE_Y + g_suraimu[EnemyNum].chengeval - g_suraimu[EnemyNum].ppos[2].y;
		g_suraimu[EnemyNum].vertexWk[10].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[11].vtx.x = g_suraimu[EnemyNum].pos.x - g_suraimu[EnemyNum].ppos[2].x;
		g_suraimu[EnemyNum].vertexWk[11].vtx.y = g_suraimu[EnemyNum].pos.y + TEXTURE_SURAIMU_SIZE_Y + g_suraimu[EnemyNum].chengeval - g_suraimu[EnemyNum].ppos[2].y;
		g_suraimu[EnemyNum].vertexWk[11].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[12].vtx.x = g_suraimu[EnemyNum].pos.x + g_suraimu[EnemyNum].ppos[3].x;
		g_suraimu[EnemyNum].vertexWk[12].vtx.y = g_suraimu[EnemyNum].pos.y + g_suraimu[EnemyNum].ppos[3].y;
		g_suraimu[EnemyNum].vertexWk[12].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[13].vtx.x = g_suraimu[EnemyNum].pos.x + TEXTURE_SURAIMU_SIZE_X + g_suraimu[EnemyNum].chengeval + g_suraimu[EnemyNum].ppos[3].x;
		g_suraimu[EnemyNum].vertexWk[13].vtx.y = g_suraimu[EnemyNum].pos.y + g_suraimu[EnemyNum].ppos[3].y;
		g_suraimu[EnemyNum].vertexWk[13].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[14].vtx.x = g_suraimu[EnemyNum].pos.x + g_suraimu[EnemyNum].ppos[3].x;
		g_suraimu[EnemyNum].vertexWk[14].vtx.y = g_suraimu[EnemyNum].pos.y + TEXTURE_SURAIMU_SIZE_Y + g_suraimu[EnemyNum].chengeval + g_suraimu[EnemyNum].ppos[3].y;
		g_suraimu[EnemyNum].vertexWk[14].vtx.z = 0.0f;
		g_suraimu[EnemyNum].vertexWk[15].vtx.x = g_suraimu[EnemyNum].pos.x + TEXTURE_SURAIMU_SIZE_X + g_suraimu[EnemyNum].chengeval + g_suraimu[EnemyNum].ppos[3].x;
		g_suraimu[EnemyNum].vertexWk[15].vtx.y = g_suraimu[EnemyNum].pos.y + TEXTURE_SURAIMU_SIZE_Y + g_suraimu[EnemyNum].chengeval + g_suraimu[EnemyNum].ppos[3].y;
		g_suraimu[EnemyNum].vertexWk[15].vtx.z = 0.0f;
		break;
	}
	case TYPE_HINOTAMA:
	{
		g_hinotama[EnemyNum].vertexWk[0].vtx.x = g_hinotama[EnemyNum].pos.x - TEXTURE_HINOTAMA_SIZE_X - g_hinotama[EnemyNum].chengeval - g_hinotama[EnemyNum].ppos[0].x;
		g_hinotama[EnemyNum].vertexWk[0].vtx.y = g_hinotama[EnemyNum].pos.y - TEXTURE_HINOTAMA_SIZE_Y - g_hinotama[EnemyNum].chengeval - g_hinotama[EnemyNum].ppos[0].y;
		g_hinotama[EnemyNum].vertexWk[0].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[1].vtx.x = g_hinotama[EnemyNum].pos.x - g_hinotama[EnemyNum].ppos[0].x;
		g_hinotama[EnemyNum].vertexWk[1].vtx.y = g_hinotama[EnemyNum].pos.y - TEXTURE_HINOTAMA_SIZE_Y - g_hinotama[EnemyNum].chengeval - g_hinotama[EnemyNum].ppos[0].y;
		g_hinotama[EnemyNum].vertexWk[1].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[2].vtx.x = g_hinotama[EnemyNum].pos.x - TEXTURE_HINOTAMA_SIZE_X - g_hinotama[EnemyNum].chengeval - g_hinotama[EnemyNum].ppos[0].x;
		g_hinotama[EnemyNum].vertexWk[2].vtx.y = g_hinotama[EnemyNum].pos.y - g_hinotama[EnemyNum].ppos[0].y;
		g_hinotama[EnemyNum].vertexWk[2].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[3].vtx.x = g_hinotama[EnemyNum].pos.x - g_hinotama[EnemyNum].ppos[0].x;
		g_hinotama[EnemyNum].vertexWk[3].vtx.y = g_hinotama[EnemyNum].pos.y - g_hinotama[EnemyNum].ppos[0].y;
		g_hinotama[EnemyNum].vertexWk[3].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[4].vtx.x = g_hinotama[EnemyNum].pos.x + g_hinotama[EnemyNum].ppos[1].x;
		g_hinotama[EnemyNum].vertexWk[4].vtx.y = g_hinotama[EnemyNum].pos.y - TEXTURE_HINOTAMA_SIZE_Y - g_hinotama[EnemyNum].chengeval + g_hinotama[EnemyNum].ppos[1].y;
		g_hinotama[EnemyNum].vertexWk[4].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[5].vtx.x = g_hinotama[EnemyNum].pos.x + TEXTURE_HINOTAMA_SIZE_X + g_hinotama[EnemyNum].chengeval + g_hinotama[EnemyNum].ppos[1].x;
		g_hinotama[EnemyNum].vertexWk[5].vtx.y = g_hinotama[EnemyNum].pos.y - TEXTURE_HINOTAMA_SIZE_Y - g_hinotama[EnemyNum].chengeval + g_hinotama[EnemyNum].ppos[1].y;
		g_hinotama[EnemyNum].vertexWk[5].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[6].vtx.x = g_hinotama[EnemyNum].pos.x + g_hinotama[EnemyNum].ppos[1].x;
		g_hinotama[EnemyNum].vertexWk[6].vtx.y = g_hinotama[EnemyNum].pos.y + g_hinotama[EnemyNum].ppos[1].y;
		g_hinotama[EnemyNum].vertexWk[6].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[7].vtx.x = g_hinotama[EnemyNum].pos.x + TEXTURE_HINOTAMA_SIZE_X + g_hinotama[EnemyNum].chengeval + g_hinotama[EnemyNum].ppos[1].x;
		g_hinotama[EnemyNum].vertexWk[7].vtx.y = g_hinotama[EnemyNum].pos.y + g_hinotama[EnemyNum].ppos[1].y;
		g_hinotama[EnemyNum].vertexWk[7].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[8].vtx.x = g_hinotama[EnemyNum].pos.x - TEXTURE_HINOTAMA_SIZE_X - g_hinotama[EnemyNum].chengeval - g_hinotama[EnemyNum].ppos[2].x;
		g_hinotama[EnemyNum].vertexWk[8].vtx.y = g_hinotama[EnemyNum].pos.y - g_hinotama[EnemyNum].ppos[2].y;
		g_hinotama[EnemyNum].vertexWk[8].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[9].vtx.x = g_hinotama[EnemyNum].pos.x - g_hinotama[EnemyNum].ppos[2].x;
		g_hinotama[EnemyNum].vertexWk[9].vtx.y = g_hinotama[EnemyNum].pos.y - g_hinotama[EnemyNum].ppos[2].y;
		g_hinotama[EnemyNum].vertexWk[9].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[10].vtx.x = g_hinotama[EnemyNum].pos.x - TEXTURE_HINOTAMA_SIZE_X - g_hinotama[EnemyNum].chengeval - g_hinotama[EnemyNum].ppos[2].x;
		g_hinotama[EnemyNum].vertexWk[10].vtx.y = g_hinotama[EnemyNum].pos.y + TEXTURE_HINOTAMA_SIZE_Y + g_hinotama[EnemyNum].chengeval - g_hinotama[EnemyNum].ppos[2].y;
		g_hinotama[EnemyNum].vertexWk[10].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[11].vtx.x = g_hinotama[EnemyNum].pos.x - g_hinotama[EnemyNum].ppos[2].x;
		g_hinotama[EnemyNum].vertexWk[11].vtx.y = g_hinotama[EnemyNum].pos.y + TEXTURE_HINOTAMA_SIZE_Y + g_hinotama[EnemyNum].chengeval - g_hinotama[EnemyNum].ppos[2].y;
		g_hinotama[EnemyNum].vertexWk[11].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[12].vtx.x = g_hinotama[EnemyNum].pos.x + g_hinotama[EnemyNum].ppos[3].x;
		g_hinotama[EnemyNum].vertexWk[12].vtx.y = g_hinotama[EnemyNum].pos.y + g_hinotama[EnemyNum].ppos[3].y;
		g_hinotama[EnemyNum].vertexWk[12].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[13].vtx.x = g_hinotama[EnemyNum].pos.x + TEXTURE_HINOTAMA_SIZE_X + g_hinotama[EnemyNum].chengeval + g_hinotama[EnemyNum].ppos[3].x;
		g_hinotama[EnemyNum].vertexWk[13].vtx.y = g_hinotama[EnemyNum].pos.y + g_hinotama[EnemyNum].ppos[3].y;
		g_hinotama[EnemyNum].vertexWk[13].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[14].vtx.x = g_hinotama[EnemyNum].pos.x + g_hinotama[EnemyNum].ppos[3].x;
		g_hinotama[EnemyNum].vertexWk[14].vtx.y = g_hinotama[EnemyNum].pos.y + TEXTURE_HINOTAMA_SIZE_Y + g_hinotama[EnemyNum].chengeval + g_hinotama[EnemyNum].ppos[3].y;
		g_hinotama[EnemyNum].vertexWk[14].vtx.z = 0.0f;
		g_hinotama[EnemyNum].vertexWk[15].vtx.x = g_hinotama[EnemyNum].pos.x + TEXTURE_HINOTAMA_SIZE_X + g_hinotama[EnemyNum].chengeval + g_hinotama[EnemyNum].ppos[3].x;
		g_hinotama[EnemyNum].vertexWk[15].vtx.y = g_hinotama[EnemyNum].pos.y + TEXTURE_HINOTAMA_SIZE_Y + g_hinotama[EnemyNum].chengeval + g_hinotama[EnemyNum].ppos[3].y;
		g_hinotama[EnemyNum].vertexWk[15].vtx.z = 0.0f;
		break;
	}
	case TYPE_UFO:
	{
		g_ufo[EnemyNum].vertexWk[0].vtx.x = g_ufo[EnemyNum].pos.x - TEXTURE_UFO_SIZE_X  - g_ufo[EnemyNum].ppos[0].x;
		g_ufo[EnemyNum].vertexWk[0].vtx.y = g_ufo[EnemyNum].pos.y - TEXTURE_UFO_SIZE_Y  - g_ufo[EnemyNum].ppos[0].y;
		g_ufo[EnemyNum].vertexWk[0].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[1].vtx.x = g_ufo[EnemyNum].pos.x - g_ufo[EnemyNum].ppos[0].x;
		g_ufo[EnemyNum].vertexWk[1].vtx.y = g_ufo[EnemyNum].pos.y - TEXTURE_UFO_SIZE_Y  - g_ufo[EnemyNum].ppos[0].y;
		g_ufo[EnemyNum].vertexWk[1].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[2].vtx.x = g_ufo[EnemyNum].pos.x - TEXTURE_UFO_SIZE_X  - g_ufo[EnemyNum].ppos[0].x;
		g_ufo[EnemyNum].vertexWk[2].vtx.y = g_ufo[EnemyNum].pos.y - g_ufo[EnemyNum].ppos[0].y;
		g_ufo[EnemyNum].vertexWk[2].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[3].vtx.x = g_ufo[EnemyNum].pos.x - g_ufo[EnemyNum].ppos[0].x;
		g_ufo[EnemyNum].vertexWk[3].vtx.y = g_ufo[EnemyNum].pos.y - g_ufo[EnemyNum].ppos[0].y;
		g_ufo[EnemyNum].vertexWk[3].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[4].vtx.x = g_ufo[EnemyNum].pos.x + g_ufo[EnemyNum].ppos[1].x;
		g_ufo[EnemyNum].vertexWk[4].vtx.y = g_ufo[EnemyNum].pos.y - TEXTURE_UFO_SIZE_Y + g_ufo[EnemyNum].ppos[1].y;
		g_ufo[EnemyNum].vertexWk[4].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[5].vtx.x = g_ufo[EnemyNum].pos.x + TEXTURE_UFO_SIZE_X + g_ufo[EnemyNum].ppos[1].x;
		g_ufo[EnemyNum].vertexWk[5].vtx.y = g_ufo[EnemyNum].pos.y - TEXTURE_UFO_SIZE_Y + g_ufo[EnemyNum].ppos[1].y;
		g_ufo[EnemyNum].vertexWk[5].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[6].vtx.x = g_ufo[EnemyNum].pos.x + g_ufo[EnemyNum].ppos[1].x;
		g_ufo[EnemyNum].vertexWk[6].vtx.y = g_ufo[EnemyNum].pos.y + g_ufo[EnemyNum].ppos[1].y;
		g_ufo[EnemyNum].vertexWk[6].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[7].vtx.x = g_ufo[EnemyNum].pos.x + TEXTURE_UFO_SIZE_X + g_ufo[EnemyNum].ppos[1].x;
		g_ufo[EnemyNum].vertexWk[7].vtx.y = g_ufo[EnemyNum].pos.y + g_ufo[EnemyNum].ppos[1].y;
		g_ufo[EnemyNum].vertexWk[7].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[8].vtx.x = g_ufo[EnemyNum].pos.x - TEXTURE_UFO_SIZE_X - g_ufo[EnemyNum].ppos[2].x;
		g_ufo[EnemyNum].vertexWk[8].vtx.y = g_ufo[EnemyNum].pos.y - g_ufo[EnemyNum].ppos[2].y;
		g_ufo[EnemyNum].vertexWk[8].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[9].vtx.x = g_ufo[EnemyNum].pos.x - g_ufo[EnemyNum].ppos[2].x;
		g_ufo[EnemyNum].vertexWk[9].vtx.y = g_ufo[EnemyNum].pos.y - g_ufo[EnemyNum].ppos[2].y;
		g_ufo[EnemyNum].vertexWk[9].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[10].vtx.x = g_ufo[EnemyNum].pos.x - TEXTURE_UFO_SIZE_X - g_ufo[EnemyNum].ppos[2].x;
		g_ufo[EnemyNum].vertexWk[10].vtx.y = g_ufo[EnemyNum].pos.y + TEXTURE_UFO_SIZE_Y - g_ufo[EnemyNum].ppos[2].y;
		g_ufo[EnemyNum].vertexWk[10].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[11].vtx.x = g_ufo[EnemyNum].pos.x - g_ufo[EnemyNum].ppos[2].x;
		g_ufo[EnemyNum].vertexWk[11].vtx.y = g_ufo[EnemyNum].pos.y + TEXTURE_UFO_SIZE_Y  - g_ufo[EnemyNum].ppos[2].y;
		g_ufo[EnemyNum].vertexWk[11].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[12].vtx.x = g_ufo[EnemyNum].pos.x + g_ufo[EnemyNum].ppos[3].x;
		g_ufo[EnemyNum].vertexWk[12].vtx.y = g_ufo[EnemyNum].pos.y + g_ufo[EnemyNum].ppos[3].y;
		g_ufo[EnemyNum].vertexWk[12].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[13].vtx.x = g_ufo[EnemyNum].pos.x + TEXTURE_UFO_SIZE_X  + g_ufo[EnemyNum].ppos[3].x;
		g_ufo[EnemyNum].vertexWk[13].vtx.y = g_ufo[EnemyNum].pos.y + g_ufo[EnemyNum].ppos[3].y;
		g_ufo[EnemyNum].vertexWk[13].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[14].vtx.x = g_ufo[EnemyNum].pos.x + g_ufo[EnemyNum].ppos[3].x;
		g_ufo[EnemyNum].vertexWk[14].vtx.y = g_ufo[EnemyNum].pos.y + TEXTURE_UFO_SIZE_Y  + g_ufo[EnemyNum].ppos[3].y;
		g_ufo[EnemyNum].vertexWk[14].vtx.z = 0.0f;
		g_ufo[EnemyNum].vertexWk[15].vtx.x = g_ufo[EnemyNum].pos.x + TEXTURE_UFO_SIZE_X  + g_ufo[EnemyNum].ppos[3].x;
		g_ufo[EnemyNum].vertexWk[15].vtx.y = g_ufo[EnemyNum].pos.y + TEXTURE_UFO_SIZE_Y  + g_ufo[EnemyNum].ppos[3].y;
		g_ufo[EnemyNum].vertexWk[15].vtx.z = 0.0f;
		break;
	}
	default :
		break;
	}
}

//=============================================================================
// 各エネミーのアドレスを返す
//=============================================================================
CAT *GetCat(int i)
{
	return &g_cat[i];
}
SURAIMU *GetSuraimu(int i)
{
	return &g_suraimu[i];
}
HINOTAMA *GetHinotama(int i)
{
	return &g_hinotama[i];
}
UFO *GetUfo(int i)
{
	return &g_ufo[i];
}
