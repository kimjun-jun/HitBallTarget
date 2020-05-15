///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	ui.cpp
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#include "main.h"
#include "input.h"
#include "ball.h"
#include "ui.h"

//*****************************************************************************
// ?クロ定?
//*****************************************************************************


//*****************************************************************************
// プロト?イプ宣言
//*****************************************************************************

//*****************************************************************************
// グロ?バル変数
//*****************************************************************************
STRIKE g_strike;
CURSOR g_cursor;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUi(int type)
{
	for (int i = 0; i < UI_GOUKEI; i++)
	{
		switch (i)
		{
		case 0:
		{
			g_strike.s.use = true;								
			g_strike.s.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y+250.0f, 0.0f);
			g_strike.s.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_strike.s.nCountAnim = 0;
			g_strike.s.nPatternAnim = 0;
			MakeVertexUi(i);
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			// テクス?ャの読み込み  
			if (type == 0)	// 初回のみ読み込む
			{
				D3DXCreateTextureFromFile(pDevice,		// デバイスの?イン?
					TEXTURE_GAME_STRIKE,				// フ?イルの名前
					&g_strike.s.pD3DTexture);			// 読み込むメモリの?イン?
			}
			break;
		}
		case 1:
		{
			g_cursor.c.use = true;
			g_cursor.c.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 250.0f, 0.0f);
			g_cursor.c.rot = D3DXVECTOR3(0, 0, 0);
			g_cursor.c.nCountAnim = 0;
			g_cursor.c.nPatternAnim = 0;
			g_cursor.c.meet = 0;
			MakeVertexUi(i);
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			// テクス?ャの読み込み  
			if (type == 0)	// 初回のみ読み込む
			{
				D3DXCreateTextureFromFile(pDevice,		// デバイスの?イン?
					TEXTURE_GAME_CURSOR,				// フ?イルの名前
					&g_cursor.c.pD3DTexture);			// 読み込むメモリの?イン?
			}
			break;
		}
		}
	}
	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitUi(void)
{
	g_strike.s.use = true;
	g_strike.s.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 250.0f, 0.0f);
	g_strike.s.rot = D3DXVECTOR3(0, 0, 0);

	g_cursor.c.use = true;
	g_cursor.c.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 250.0f, 0.0f);
	g_cursor.c.rot = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUi(void)
{
	if (g_strike.s.pD3DTexture != NULL)
	{	// テクス?ャの開放
		g_strike.s.pD3DTexture->Release();
		g_strike.s.pD3DTexture = NULL;
	}
	if (g_cursor.c.pD3DTexture != NULL)
	{	// テクス?ャの開放
		g_cursor.c.pD3DTexture->Release();
		g_cursor.c.pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUi(void)
{
	BALL *b = GetBall();
	if (b->OorD == true && IsButtonTriggered(0, BUTTON_X) || GetKeyboardTrigger(DIK_C))
	{
		g_cursor.c.meet++;
	}
	SetVertexUi(g_cursor.c.meet);
}

//=============================================================================
// ?画処理
//=============================================================================
void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂?フォ??ットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	if (g_strike.s.use == true && g_cursor.c.use == true)
	{
		// テクス?ャの設定  
		pDevice->SetTexture(0, g_strike.s.pD3DTexture);
		// ?リゴンの?画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_strike.s.vertexWk, sizeof(VERTEX_2D));

		// テクス?ャの設定  
		pDevice->SetTexture(0, g_cursor.c.pD3DTexture);
		// ?リゴンの?画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_cursor.c.vertexWk, sizeof(VERTEX_2D));
	}

}

//=============================================================================
// 頂?の作成
//=============================================================================
HRESULT MakeVertexUi(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	switch (i)
	{
	case 0:
		// 頂?座標の設定
		SetVertexUi(i);
		// rhwの設定
		g_strike.s.vertexWk[0].rhw =
			g_strike.s.vertexWk[1].rhw =
			g_strike.s.vertexWk[2].rhw =
			g_strike.s.vertexWk[3].rhw = 1.0f;
		// 反射光の設定  
		g_strike.s.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_strike.s.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_strike.s.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_strike.s.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		// テクス?ャ座標の設定  
		g_strike.s.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_strike.s.vertexWk[1].tex = D3DXVECTOR2(1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		g_strike.s.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_Y);
		g_strike.s.vertexWk[3].tex = D3DXVECTOR2(1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_Y);
		break;

	case 1:
		// 頂?座標の設定
		SetVertexUi(i);
		// rhwの設定
		g_cursor.c.vertexWk[0].rhw =
			g_cursor.c.vertexWk[1].rhw =
			g_cursor.c.vertexWk[2].rhw =
			g_cursor.c.vertexWk[3].rhw = 1.0f;
		// 反射光の設定  
		g_cursor.c.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cursor.c.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cursor.c.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cursor.c.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		// テクス?ャ座標の設定  
		g_cursor.c.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_cursor.c.vertexWk[1].tex = D3DXVECTOR2(1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		g_cursor.c.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_Y);
		g_cursor.c.vertexWk[3].tex = D3DXVECTOR2(1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_X, 1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_Y);
		break;
	}
	return S_OK;
}

//=============================================================================
// テクス?ャ座標の設定
//=============================================================================
void SetTextureUi(int cntPattern,int i)
{
	switch (i)
	{
	case 0:
	{
		int x_s = cntPattern % STRIKE_TEXTURE_PATTERN_DIVIDE_X;
		int y_s = cntPattern / STRIKE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX_s = 1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY_s = 1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_Y;

		// テクス?ャ座標の設定
		g_strike.s.vertexWk[0].tex = D3DXVECTOR2((float)(x_s)* sizeX_s, (float)(y_s)* sizeY_s);
		g_strike.s.vertexWk[1].tex = D3DXVECTOR2((float)(x_s)* sizeX_s + sizeX_s, (float)(y_s)* sizeY_s);
		g_strike.s.vertexWk[2].tex = D3DXVECTOR2((float)(x_s)* sizeX_s, (float)(y_s)* sizeY_s + sizeY_s);
		g_strike.s.vertexWk[3].tex = D3DXVECTOR2((float)(x_s)* sizeX_s + sizeX_s, (float)(y_s)* sizeY_s + sizeY_s);
		break;
	}
	case 1:
	{
		int x_c = cntPattern % CURSOR_TEXTURE_PATTERN_DIVIDE_X;
		int y_c = cntPattern / CURSOR_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX_c = 1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY_c = 1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_Y;

		// テクス?ャ座標の設定
		g_cursor.c.vertexWk[0].tex = D3DXVECTOR2((float)(x_c)* sizeX_c, (float)(y_c)* sizeY_c);
		g_cursor.c.vertexWk[1].tex = D3DXVECTOR2((float)(x_c)* sizeX_c + sizeX_c, (float)(y_c)* sizeY_c);
		g_cursor.c.vertexWk[2].tex = D3DXVECTOR2((float)(x_c)* sizeX_c, (float)(y_c)* sizeY_c + sizeY_c);
		g_cursor.c.vertexWk[3].tex = D3DXVECTOR2((float)(x_c)* sizeX_c + sizeX_c, (float)(y_c)* sizeY_c + sizeY_c);
		break;
	}
	}

}

//=============================================================================
// 頂?座標の設定
//=============================================================================
void SetVertexUi(int i)
{
	switch (i%2)
	{
	case BIG:
		// 頂?座標の設定 
		g_cursor.c.vertexWk[0].vtx.x = g_cursor.c.pos.x - TEXTURE_CURSOR_BIG_SIZE_X;
		g_cursor.c.vertexWk[0].vtx.y = g_cursor.c.pos.y - TEXTURE_CURSOR_BIG_SIZE_Y;
		g_cursor.c.vertexWk[0].vtx.z = 0.0f;							
		g_cursor.c.vertexWk[1].vtx.x = g_cursor.c.pos.x + TEXTURE_CURSOR_BIG_SIZE_X;
		g_cursor.c.vertexWk[1].vtx.y = g_cursor.c.pos.y - TEXTURE_CURSOR_BIG_SIZE_Y;
		g_cursor.c.vertexWk[1].vtx.z = 0.0f;							
		g_cursor.c.vertexWk[2].vtx.x = g_cursor.c.pos.x - TEXTURE_CURSOR_BIG_SIZE_X;
		g_cursor.c.vertexWk[2].vtx.y = g_cursor.c.pos.y + TEXTURE_CURSOR_BIG_SIZE_Y;
		g_cursor.c.vertexWk[2].vtx.z = 0.0f;							 
		g_cursor.c.vertexWk[3].vtx.x = g_cursor.c.pos.x + TEXTURE_CURSOR_BIG_SIZE_X;
		g_cursor.c.vertexWk[3].vtx.y = g_cursor.c.pos.y + TEXTURE_CURSOR_BIG_SIZE_Y;
		g_cursor.c.vertexWk[3].vtx.z = 0.0f;
		break;

	case SMALL:
		g_cursor.c.vertexWk[0].vtx.x = g_cursor.c.pos.x - TEXTURE_CURSOR_SMALL_SIZE_X;
		g_cursor.c.vertexWk[0].vtx.y = g_cursor.c.pos.y - TEXTURE_CURSOR_SMALL_SIZE_Y;
		g_cursor.c.vertexWk[0].vtx.z = 0.0f;								  
		g_cursor.c.vertexWk[1].vtx.x = g_cursor.c.pos.x + TEXTURE_CURSOR_SMALL_SIZE_X;
		g_cursor.c.vertexWk[1].vtx.y = g_cursor.c.pos.y - TEXTURE_CURSOR_SMALL_SIZE_Y;
		g_cursor.c.vertexWk[1].vtx.z = 0.0f;							 	  
		g_cursor.c.vertexWk[2].vtx.x = g_cursor.c.pos.x - TEXTURE_CURSOR_SMALL_SIZE_X;
		g_cursor.c.vertexWk[2].vtx.y = g_cursor.c.pos.y + TEXTURE_CURSOR_SMALL_SIZE_Y;
		g_cursor.c.vertexWk[2].vtx.z = 0.0f;							 	  
		g_cursor.c.vertexWk[3].vtx.x = g_cursor.c.pos.x + TEXTURE_CURSOR_SMALL_SIZE_X;
		g_cursor.c.vertexWk[3].vtx.y = g_cursor.c.pos.y + TEXTURE_CURSOR_SMALL_SIZE_Y;
		g_cursor.c.vertexWk[3].vtx.z = 0.0f;
		break;
	}
	g_strike.s.vertexWk[0].vtx.x = g_strike.s.pos.x - TEXTURE_STRIKE_SIZE_X;
	g_strike.s.vertexWk[0].vtx.y = g_strike.s.pos.y - TEXTURE_STRIKE_SIZE_Y;
	g_strike.s.vertexWk[0].vtx.z = 0.0f;

	g_strike.s.vertexWk[1].vtx.x = g_strike.s.pos.x + TEXTURE_STRIKE_SIZE_X;
	g_strike.s.vertexWk[1].vtx.y = g_strike.s.pos.y - TEXTURE_STRIKE_SIZE_Y;
	g_strike.s.vertexWk[1].vtx.z = 0.0f;

	g_strike.s.vertexWk[2].vtx.x = g_strike.s.pos.x - TEXTURE_STRIKE_SIZE_X;
	g_strike.s.vertexWk[2].vtx.y = g_strike.s.pos.y + TEXTURE_STRIKE_SIZE_Y;
	g_strike.s.vertexWk[2].vtx.z = 0.0f;

	g_strike.s.vertexWk[3].vtx.x = g_strike.s.pos.x + TEXTURE_STRIKE_SIZE_X;
	g_strike.s.vertexWk[3].vtx.y = g_strike.s.pos.y + TEXTURE_STRIKE_SIZE_Y;
	g_strike.s.vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ??ルのアドレスを返す.
//=============================================================================
STRIKE *GetStrike(void)
{
	return &g_strike;
}

//=============================================================================
// ??ルのアドレスを返す.
//=============================================================================
CURSOR *Get_Cursor(void)
{
	return &g_cursor;
}

