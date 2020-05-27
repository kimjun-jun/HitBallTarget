/**
* @file bg.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "bg.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief ポリゴン頂点生成関数 MakeVertexBG
* @return HRESULT
*/
HRESULT MakeVertexBG(void);

/**
* @brief ポリゴン頂点設定関数 SetVertexBG
*/
void SetVertexBG(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
BG g_bg[BG_MAX];											//!< 通常背景構造体変数
static int g_bgtype;										//!< 各シーン中の背景
static int g_gameR18bgtype;									//!< -1標準,0魔女っ子,1スイーツ
static LPDIRECT3DTEXTURE9 g_gameR18bg[GAMER18BG_MAX];		//!< R18用背景テクスチャ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャーの初期化を行う
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_TITLEBG,								// ファイルの名前
			&g_bg[0].pD3DTexture);							// 読み込むメモリー
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_TUTORIALBG,
			&g_bg[1].pD3DTexture);	
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_GAMEBG,
			&g_bg[5].pD3DTexture);	
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_PAUSETBG,
			&g_bg[6].pD3DTexture);

		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_GAMEBGR1801,
			&g_gameR18bg[0]);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_GAMEBGR1802,
			&g_gameR18bg[1]);
	}

	for (int i = 0; i < BG_MAX; i++)
	{
		g_bg[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_bgtype = 0;
	g_gameR18bgtype = -1;
	// 頂点情報の作成
	MakeVertexBG();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBG(void)
{
	for (int i = 0; i < BG_MAX; i++)
	{
		if (g_bg[i].pD3DTexture != NULL)
		{	// テクスチャの開放
			g_bg[i].pD3DTexture->Release();
			g_bg[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitBG(void)
{
	g_bgtype = 0;
	g_gameR18bgtype = -1;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBG(void)
{
	int scene = GetScene();
	switch (scene)
	{
	case SCENE_TITLE:
		g_bgtype = SCENE_TITLE;
		break;
	case SCENE_TUTORIAL:
		g_bgtype = SCENE_TUTORIAL;
		break;
	case SCENE_TUTORIALMENU:
		g_bgtype = SCENE_TUTORIALMENU;
		break;
	case SCENE_SELECT:
		g_bgtype = SCENE_SELECT;
		break;
	case SCENE_GAMECOUNTDOWN:
		g_bgtype = SCENE_GAMECOUNTDOWN;
		break;
	case SCENE_GAME:
		g_bgtype = SCENE_GAME;
		break;
	case SCENE_PAUSE:
		g_bgtype = SCENE_PAUSE;
		break;
	case SCENE_OPTION:
		g_bgtype = SCENE_OPTION;
		break;
	case SCENE_R18SELECT:
		g_bgtype = SCENE_R18SELECT;
		break;
	case SCENE_SENSITIVITY:
		g_bgtype = SCENE_SENSITIVITY;
		break;
	case SCENE_TUTOSENSITIVITY:
		g_bgtype = SCENE_TUTOSENSITIVITY;
		break;
	case SCENE_CONTYPE:
		g_bgtype = SCENE_CONTYPE;
		break;
	case SCENE_TUTOCONTYPE:
		g_bgtype = SCENE_TUTOCONTYPE;
		break;
	case SCENE_RESULT_CLEAR:
		g_bgtype = SCENE_RESULT_CLEAR;
		break;
	case SCENE_RESULT_FIELD:
		g_bgtype = SCENE_RESULT_FIELD;
		break;
	case SCENE_REGISTER:
		g_bgtype = SCENE_REGISTER;
		break;
	case SCENE_RANKING:
		g_bgtype = SCENE_RANKING;
		break;
	default:
		break;
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	switch (g_bgtype)
	{
	case SCENE_TITLE:
		pDevice->SetTexture(0, g_bg[g_bgtype].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[g_bgtype].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_TUTORIAL:
		pDevice->SetTexture(0, g_bg[g_bgtype].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[g_bgtype].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_TUTORIALMENU:
		pDevice->SetTexture(0, g_bg[SCENE_TUTORIAL].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_TUTORIAL].vertexWk, sizeof(VERTEX_2D));
		pDevice->SetTexture(0, g_bg[SCENE_PAUSE].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_PAUSE].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_SELECT:
		pDevice->SetTexture(0, g_bg[g_bgtype].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[g_bgtype].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_GAMECOUNTDOWN:
		pDevice->SetTexture(0, g_bg[SCENE_GAME].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_GAME:
		if (g_gameR18bgtype == -1)
		{
			pDevice->SetTexture(0, g_bg[SCENE_GAME].pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 0)
		{
			pDevice->SetTexture(0, g_gameR18bg[0]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 1)
		{
			pDevice->SetTexture(0, g_gameR18bg[1]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		break;
	case SCENE_PAUSE:
		if (g_gameR18bgtype == -1)
		{
			pDevice->SetTexture(0, g_bg[SCENE_GAME].pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype== 0)
		{
			pDevice->SetTexture(0, g_gameR18bg[0]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 1)
		{
			pDevice->SetTexture(0, g_gameR18bg[1]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		pDevice->SetTexture(0, g_bg[g_bgtype].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[g_bgtype].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_OPTION:
		if (g_gameR18bgtype == -1)
		{
			pDevice->SetTexture(0, g_bg[SCENE_GAME].pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 0)
		{
			pDevice->SetTexture(0, g_gameR18bg[0]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 1)
		{
			pDevice->SetTexture(0, g_gameR18bg[1]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		pDevice->SetTexture(0, g_bg[SCENE_PAUSE].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_PAUSE].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_SENSITIVITY:
		if (g_gameR18bgtype == -1)
		{
			pDevice->SetTexture(0, g_bg[SCENE_GAME].pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 0)
		{
			pDevice->SetTexture(0, g_gameR18bg[0]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 1)
		{
			pDevice->SetTexture(0, g_gameR18bg[1]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		pDevice->SetTexture(0, g_bg[SCENE_PAUSE].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_PAUSE].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_TUTOSENSITIVITY:
		pDevice->SetTexture(0, g_bg[SCENE_TUTORIAL].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_TUTORIAL].vertexWk, sizeof(VERTEX_2D));
		pDevice->SetTexture(0, g_bg[SCENE_PAUSE].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_PAUSE].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_CONTYPE:
		if (g_gameR18bgtype == -1)
		{
			pDevice->SetTexture(0, g_bg[SCENE_GAME].pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 0)
		{
			pDevice->SetTexture(0, g_gameR18bg[0]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 1)
		{
			pDevice->SetTexture(0, g_gameR18bg[1]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		pDevice->SetTexture(0, g_bg[SCENE_PAUSE].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_PAUSE].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_TUTOCONTYPE:
		pDevice->SetTexture(0, g_bg[SCENE_TUTORIAL].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_TUTORIAL].vertexWk, sizeof(VERTEX_2D));
		pDevice->SetTexture(0, g_bg[SCENE_PAUSE].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_PAUSE].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_R18SELECT:
		if (g_gameR18bgtype == -1)
		{
			pDevice->SetTexture(0, g_bg[SCENE_GAME].pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 0)
		{
			pDevice->SetTexture(0, g_gameR18bg[0]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		else if (g_gameR18bgtype == 1)
		{
			pDevice->SetTexture(0, g_gameR18bg[1]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_GAME].vertexWk, sizeof(VERTEX_2D));
		}
		pDevice->SetTexture(0, g_bg[SCENE_PAUSE].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[SCENE_PAUSE].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_RESULT_CLEAR:
		pDevice->SetTexture(0, g_bg[g_bgtype].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[g_bgtype].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_RESULT_FIELD:
		pDevice->SetTexture(0, g_bg[g_bgtype].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[g_bgtype].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_REGISTER:
		pDevice->SetTexture(0, g_bg[g_bgtype].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[g_bgtype].vertexWk, sizeof(VERTEX_2D));
		break;
	case SCENE_RANKING:
		pDevice->SetTexture(0, g_bg[g_bgtype].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_bg[g_bgtype].vertexWk, sizeof(VERTEX_2D));
		break;
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBG(void)
{
	// 頂点座標の設定
	SetVertexBG();

	for (int i = 0; i < BG_MAX; i++)
	{
		// rhwの設定
		g_bg[i].vertexWk[0].rhw =
			g_bg[i].vertexWk[1].rhw =
			g_bg[i].vertexWk[2].rhw =
			g_bg[i].vertexWk[3].rhw = 1.0f;

		// 反射光の設定
		g_bg[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_bg[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_bg[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_bg[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		g_bg[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_bg[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_bg[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_bg[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBG(void)
{
	for (int i = 0; i < BG_MAX; i++)
	{
		// 頂点座標の設定
		g_bg[i].vertexWk[0].vtx = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
		g_bg[i].vertexWk[1].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_W, BG_POS_Y, 0.0f);
		g_bg[i].vertexWk[2].vtx = D3DXVECTOR3(BG_POS_X, BG_POS_Y + BG_SIZE_H, 0.0f);
		g_bg[i].vertexWk[3].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_W, BG_POS_Y + BG_SIZE_H, 0.0f);
	}
}

//=============================================================================
// ゲーム中背景設定関数
//=============================================================================
void SetGameBGtype(int num)
{
	g_gameR18bgtype = num;
}