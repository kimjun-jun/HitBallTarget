/**
* @file ranking.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "ball.h"
#include "register.h"
#include "ranking.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief 頂点生成関数 MakeVertexRanking
* @return HRESULT
*/
HRESULT MakeVertexRanking(void);

/**
* @brief テクスチャ設定関数 SetTextureRanking
*/
void SetTextureRanking(void);

/**
* @brief 頂点設定関数 SetVertexRanking
*/
void SetVertexRanking(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
RANKING g_ranking[RANKINGMAX];						//!< ランキング	構造体変数
RANKINGLOGO g_rankinglogo[RANKINGLOGO_MAX];			//!< ランキングロゴ	構造体変数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRanking(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		for (int i = 0; i < RANKINGMAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,
				TEXTURE_ALPHA,
				&g_ranking[i].namepD3DTexture);

			D3DXCreateTextureFromFile(pDevice,
				TEXTURE_NUM,
				&g_ranking[i].numpD3DTexture);

			D3DXCreateTextureFromFile(pDevice,
				TEXTURE_NUM,
				&g_ranking[i].scorepD3DTexture);
		}
	}

	// 頂点情報の作成
	MakeVertexRanking();

	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitRanking(int type)
{

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	for (int i = 0; i < RANKINGMAX; i++)
	{
		if (g_ranking[i].namepD3DTexture != NULL)
		{// テクスチャの開放
			g_ranking[i].namepD3DTexture->Release();
			g_ranking[i].namepD3DTexture = NULL;
		}
		if (g_ranking[i].numpD3DTexture != NULL)
		{// テクスチャの開放
			g_ranking[i].numpD3DTexture->Release();
			g_ranking[i].numpD3DTexture = NULL;
		}
		if (g_ranking[i].scorepD3DTexture != NULL)
		{// テクスチャの開放
			g_ranking[i].scorepD3DTexture->Release();
			g_ranking[i].scorepD3DTexture = NULL;
		}
	}

	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		if (g_rankinglogo[i].pD3DTexture != NULL)
		{// テクスチャの開放
			g_rankinglogo[i].pD3DTexture->Release();
			g_rankinglogo[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理　
//=============================================================================
void UpdateRanking(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < RANKINGMAX; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_ranking[i].namepD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ranking[i].namevertexWk, sizeof(VERTEX_2D));



		pDevice->SetTexture(0, g_ranking[i].numpD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ranking[i].numvertexWk, sizeof(VERTEX_2D));
		


		pDevice->SetTexture(0, g_ranking[i].scorepD3DTexture);
		for (int j = 0; j < RANKINGSOCRED; j++)
		{
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ranking[i].scorevertexWk[j], sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		pDevice->SetFVF(FVF_VERTEX_2D);
		pDevice->SetTexture(0, g_rankinglogo[i].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_rankinglogo[i].vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRanking(void)
{
	// テクスチャのパースペクティブコレクト用
	for (int i = 0; i < RANKINGMAX; i++)
	{
		g_ranking[i].namevertexWk[0].rhw =
			g_ranking[i].namevertexWk[1].rhw =
			g_ranking[i].namevertexWk[2].rhw =
			g_ranking[i].namevertexWk[3].rhw = 1.0f;
		g_ranking[i].namevertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].namevertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].namevertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].namevertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].namevertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ranking[i].namevertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ranking[i].namevertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ranking[i].namevertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_ranking[i].numvertexWk[0].rhw =
		g_ranking[i].numvertexWk[1].rhw =
		g_ranking[i].numvertexWk[2].rhw =
		g_ranking[i].numvertexWk[3].rhw = 1.0f;
		g_ranking[i].numvertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].numvertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].numvertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].numvertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].numvertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ranking[i].numvertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ranking[i].numvertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ranking[i].numvertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		for (int j = 0; j < RANKINGSOCRED;j++)
		{
			g_ranking[i].scorevertexWk[0][j].rhw =
			g_ranking[i].scorevertexWk[1][j].rhw =
			g_ranking[i].scorevertexWk[2][j].rhw =
			g_ranking[i].scorevertexWk[3][j].rhw = 1.0f;
			g_ranking[i].scorevertexWk[0][j].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_ranking[i].scorevertexWk[1][j].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_ranking[i].scorevertexWk[2][j].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_ranking[i].scorevertexWk[3][j].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_ranking[i].scorevertexWk[0][j].tex = D3DXVECTOR2(0.0f, 0.0f);
			g_ranking[i].scorevertexWk[1][j].tex = D3DXVECTOR2(1.0f, 0.0f);
			g_ranking[i].scorevertexWk[2][j].tex = D3DXVECTOR2(0.0f, 1.0f);
			g_ranking[i].scorevertexWk[3][j].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}

	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		g_rankinglogo[i].vertexWk[0].rhw =
		g_rankinglogo[i].vertexWk[1].rhw =
		g_rankinglogo[i].vertexWk[2].rhw =
		g_rankinglogo[i].vertexWk[3].rhw = 1.0f;
		g_rankinglogo[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rankinglogo[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rankinglogo[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rankinglogo[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rankinglogo[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_rankinglogo[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_rankinglogo[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_rankinglogo[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureRanking(void)
{
	for (int i = 0; i < RANKINGMAX; i++)
	{
		g_ranking[i].namevertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ranking[i].namevertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ranking[i].namevertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ranking[i].namevertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_ranking[i].numvertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ranking[i].numvertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ranking[i].numvertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ranking[i].numvertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		for (int j = 0; j < RANKINGSOCRED; j++)
		{
			g_ranking[i].scorevertexWk[0][j].tex = D3DXVECTOR2(0.0f, 0.0f);
			g_ranking[i].scorevertexWk[1][j].tex = D3DXVECTOR2(1.0f, 0.0f);
			g_ranking[i].scorevertexWk[2][j].tex = D3DXVECTOR2(0.0f, 1.0f);
			g_ranking[i].scorevertexWk[3][j].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		g_rankinglogo[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_rankinglogo[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_rankinglogo[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_rankinglogo[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexRanking(void)
{
	// 頂点座標の設定 
	for (int i = 0; i < RANKINGMAX; i++)
	{
		g_ranking[i].namevertexWk[0].vtx.x = g_ranking[i].namepos.x - TEXTURE_RANKING_NAME_SIZE_X;
		g_ranking[i].namevertexWk[0].vtx.y = g_ranking[i].namepos.y - TEXTURE_RANKING_NAME_SIZE_Y;
		g_ranking[i].namevertexWk[0].vtx.z = 0.0f;		  			  
		g_ranking[i].namevertexWk[1].vtx.x = g_ranking[i].namepos.x + TEXTURE_RANKING_NAME_SIZE_X;
		g_ranking[i].namevertexWk[1].vtx.y = g_ranking[i].namepos.y - TEXTURE_RANKING_NAME_SIZE_Y;
		g_ranking[i].namevertexWk[1].vtx.z = 0.0f;		  			  
		g_ranking[i].namevertexWk[2].vtx.x = g_ranking[i].namepos.x - TEXTURE_RANKING_NAME_SIZE_X;
		g_ranking[i].namevertexWk[2].vtx.y = g_ranking[i].namepos.y + TEXTURE_RANKING_NAME_SIZE_Y;
		g_ranking[i].namevertexWk[2].vtx.z = 0.0f;		  			  
		g_ranking[i].namevertexWk[3].vtx.x = g_ranking[i].namepos.x + TEXTURE_RANKING_NAME_SIZE_X;
		g_ranking[i].namevertexWk[3].vtx.y = g_ranking[i].namepos.y + TEXTURE_RANKING_NAME_SIZE_Y;
		g_ranking[i].namevertexWk[3].vtx.z = 0.0f;

		g_ranking[i].numvertexWk[0].vtx.x = g_ranking[i].numpos.x - TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[0].vtx.y = g_ranking[i].numpos.y - TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[0].vtx.z = 0.0f;					
		g_ranking[i].numvertexWk[1].vtx.x = g_ranking[i].numpos.x + TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[1].vtx.y = g_ranking[i].numpos.y - TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[1].vtx.z = 0.0f;					
		g_ranking[i].numvertexWk[2].vtx.x = g_ranking[i].numpos.x - TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[2].vtx.y = g_ranking[i].numpos.y + TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[2].vtx.z = 0.0f;					
		g_ranking[i].numvertexWk[3].vtx.x = g_ranking[i].numpos.x + TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[3].vtx.y = g_ranking[i].numpos.y + TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[3].vtx.z = 0.0f;

		for (int j = 0; j < RANKINGSOCRED; j++)
		{
			g_ranking[i].scorevertexWk[j][0].vtx.x = g_ranking[i].scorepos[j].x - TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][0].vtx.y = g_ranking[i].scorepos[j].y - TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][0].vtx.z = 0.0f;			  
			g_ranking[i].scorevertexWk[j][1].vtx.x = g_ranking[i].scorepos[j].x + TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][1].vtx.y = g_ranking[i].scorepos[j].y - TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][1].vtx.z = 0.0f;			   
			g_ranking[i].scorevertexWk[j][2].vtx.x = g_ranking[i].scorepos[j].x - TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][2].vtx.y = g_ranking[i].scorepos[j].y + TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][2].vtx.z = 0.0f;			   
			g_ranking[i].scorevertexWk[j][3].vtx.x = g_ranking[i].scorepos[j].x + TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][3].vtx.y = g_ranking[i].scorepos[j].y + TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][3].vtx.z = 0.0f;
		}
	}
	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		g_rankinglogo[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_rankinglogo[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_rankinglogo[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_rankinglogo[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

}

//=============================================================================
// ランクのアドレスを返す
//=============================================================================
RANKING *GetRanking(void)
{
	return &g_ranking[0];
}

