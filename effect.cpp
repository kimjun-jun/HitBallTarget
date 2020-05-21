/**
* @file effect.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "enemy.h"
#include "score.h"
#include "ui.h"
#include "ball.h"
#include "effect.h"


//*****************************************************************************
// グローバル変数
//*****************************************************************************
BE g_be[BALL_COUNT_MAX];
static int g_type;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBE(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < BALL_COUNT_MAX; i++)
	{
		// テクスチャーの初期化を行う？
		if (type == 0)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				BE_TEXTURE_FILE_00,		// ファイルの名前
				&g_be[i].pD3DTexture);		// 読み込むメモリー

		}
		g_be[i].nCountAnim = 0;
		g_be[i].nPatternAnim = 0;
		g_be[i].motion = false;
		g_be[i].use = false;
		g_be[i].pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
		g_type = 0;
	}
	// 頂点情報の作成
	MakeVertexBE();

	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitBE(void)
{
	for (int i = 0; i < BALL_COUNT_MAX; i++)
	{
		g_be[i].nCountAnim = 0;
		g_be[i].nPatternAnim = 0;
		g_be[i].motion = false;
		g_be[i].use = false;
		g_be[i].pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
		g_type = 0;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBE(void)
{
	for (int i = 0; i < BALL_COUNT_MAX; i++)
	{
		if (g_be[i].pD3DTexture != NULL)
		{	// テクスチャの開放
			g_be[i].pD3DTexture->Release();
			g_be[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBE(void)
{
	for (int i = 0; i < BALL_COUNT_MAX; i++)
	{
		if (g_be[i].use==true)
		{
			g_be[i].nCountAnim++;
			if (g_be[i].nCountAnim % BE_TIME_ANIMATION == 0) g_be[i].nPatternAnim++;
			if (g_be[i].nPatternAnim > BE_ANIM_PATTERN_NUM)
			{
				g_be[i].nPatternAnim = 0;
				g_be[i].use = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBE(void)
{
	BALL *b = GetBall();
	for (int i = 0; i < BALL_COUNT_MAX; i++)
	{
		if (g_be[i].use == true)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_be[i].pD3DTexture);
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_be[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBE(void)
{
	// 頂点座標の設定
	SetVertexBE();

	// rhwの設定
	g_be[0].vertexWk[0].rhw =
		g_be[0].vertexWk[1].rhw =
		g_be[0].vertexWk[2].rhw =
		g_be[0].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_be[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_be[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_be[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_be[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_be[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_be[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_be[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_be[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBe(int cntPattern)
{
		// テクスチャ座標の設定
		int x = cntPattern % TEXTURE_PITCHER_PATTERN_DIVIDE_X;
		int y = cntPattern / TEXTURE_PITCHER_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_Y;

		g_be[0].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_be[0].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		g_be[0].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		g_be[0].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBE(void)
{
	// 頂点座標の設定 
	g_be[0].vertexWk[0].vtx.x = g_be[0].pos.x - BE_SIZE_W;
	g_be[0].vertexWk[0].vtx.y = g_be[0].pos.y - BE_SIZE_H;
	g_be[0].vertexWk[0].vtx.z = 0.0f;
	g_be[0].vertexWk[1].vtx.x = g_be[0].pos.x + BE_SIZE_W;
	g_be[0].vertexWk[1].vtx.y = g_be[0].pos.y - BE_SIZE_H;
	g_be[0].vertexWk[1].vtx.z = 0.0f;
	g_be[0].vertexWk[2].vtx.x = g_be[0].pos.x - BE_SIZE_W;
	g_be[0].vertexWk[2].vtx.y = g_be[0].pos.y + BE_SIZE_H;
	g_be[0].vertexWk[2].vtx.z = 0.0f;
	g_be[0].vertexWk[3].vtx.x = g_be[0].pos.x + BE_SIZE_W;
	g_be[0].vertexWk[3].vtx.y = g_be[0].pos.y + BE_SIZE_H;
	g_be[0].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// 描画させる背景を変更
//=============================================================================
void SelectBE(int type)
{
	if (type == BALL_EFFECT1) g_type = BALL_EFFECT1;
	else if (type == BALL_EFFECT2)g_type = BALL_EFFECT2;
}


//=============================================================================
// エフェクト関数(update)
//=============================================================================
void DeadEffect(int i,int type)
{
	switch (type)
	{
	case TYPE_CAT:
	{
		CAT *cat = GetCat(i);
		cat->colori -= TEXTURE_COROLSPEED;
		cat->ppos[0] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		cat->ppos[1] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		cat->ppos[2] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		cat->ppos[3] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		cat->vertexWk[0].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[1].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[2].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[3].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[4].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[5].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[6].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[7].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[8].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[9].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[10].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[11].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[12].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[13].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[14].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[15].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		//死んでcoloriが変色終わると消す
		if (cat->use == true && cat->colori <= 0)
		{
			cat->use = false;
			AddScore(1, ENEMY_VAL);
			AddScore(cat->point, SCORE_VAL);
		}
		break;
	}
	case TYPE_SURAIMU:
	{
		SURAIMU *suraimu = GetSuraimu(i);
		suraimu->colori -= TEXTURE_COROLSPEED;
		suraimu->ppos[0] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		suraimu->ppos[1] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		suraimu->ppos[2] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		suraimu->ppos[3] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		suraimu->vertexWk[0].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[1].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[2].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[3].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[4].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[5].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[6].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[7].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[8].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[9].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[10].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[11].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[12].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[13].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[14].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[15].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		//死んでcoloriが変色終わると消す
		if (suraimu->use == true && suraimu->colori <= 0)
		{
			suraimu->use = false;
			AddScore(1, ENEMY_VAL);
			AddScore(suraimu->point, SCORE_VAL);
		}
		break;
	}
	case TYPE_HINOTAMA:
	{
		HINOTAMA *hinotama = GetHinotama(i);
		hinotama->colori -= TEXTURE_COROLSPEED;
		hinotama->ppos[0] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		hinotama->ppos[1] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		hinotama->ppos[2] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		hinotama->ppos[3] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		hinotama->vertexWk[0].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[1].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[2].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[3].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[4].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[5].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[6].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[7].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[8].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[9].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[10].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[11].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[12].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[13].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[14].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[15].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		//死んでcoloriが変色終わると消す
		if (hinotama->use == true && hinotama->colori <= 0)
		{
			hinotama->use = false;
			AddScore(1, ENEMY_VAL);
			AddScore(hinotama->point, SCORE_VAL);
		}
		break;
	}
	case TYPE_UFO:
	{
		UFO *ufo = GetUfo(i);
		ufo->colori -= TEXTURE_COROLSPEED;
		ufo->ppos[0] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		ufo->ppos[1] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		ufo->ppos[2] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		ufo->ppos[3] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		ufo->vertexWk[0].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[1].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[2].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[3].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[4].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[5].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[6].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[7].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[8].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[9].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[10].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[11].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[12].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[13].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[14].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[15].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		//死んでcoloriが変色終わると消す
		if (ufo->use == true && ufo->colori <= 0)
		{
			ufo->use = false;
		}
		break;
	}
	}
}

BE *GetBE(int i)
{
	return &g_be[i];
}