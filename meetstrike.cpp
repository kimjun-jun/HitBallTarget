/**
* @file meetstrike.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "ball.h"
#include "meetstrike.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief 頂点生成関数 MakeVertexMeetStrike
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT MakeVertexMeetStrike(int type);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
STRIKE g_strike;									//!< ストライクゾーン構造体変数
CURSOR g_cursor;									//!< ミートカーソル構造体変数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMeetStrike(int type)
{
	for (int i = 0; i < MEETSTRIKE_GOUKEI; i++)
	{
		switch (i)
		{
		case 0:
		{
			g_strike.s.use = true;								
			g_strike.s.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y+250.0f, 0.0f);
			g_strike.s.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			MakeVertexMeetStrike(i);
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			// テクスチャの読み込み  
			if (type == 0)	// 初回のみ読み込む
			{
				D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
					TEXTURE_GAME_STRIKE,				// ファイルの名前
					&g_strike.s.pD3DTexture);			// 読み込むメモリのポインタ
			}
			break;
		}
		case 1:
		{
			g_cursor.c.use = true;
			g_cursor.c.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 250.0f, 0.0f);
			g_cursor.c.rot = D3DXVECTOR3(0, 0, 0);
			g_cursor.c.meet = 0;
			MakeVertexMeetStrike(i);
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
					TEXTURE_GAME_CURSOR,				// ファイルの名前
					&g_cursor.c.pD3DTexture);			// 読み込むメモリのポインタ
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
void ReInitMeetStrike(void)
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
void UninitMeetStrike(void)
{
	if (g_strike.s.pD3DTexture != NULL)
	{	// テクスチャの開放
		g_strike.s.pD3DTexture->Release();
		g_strike.s.pD3DTexture = NULL;
	}
	if (g_cursor.c.pD3DTexture != NULL)
	{	// テクスチャの開放
		g_cursor.c.pD3DTexture->Release();
		g_cursor.c.pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeetStrike(void)
{
	BALL *b = GetBall();
	if (b->OorD == true && IsButtonTriggered(0, BUTTON_X) || GetKeyboardTrigger(DIK_C))
	{
		g_cursor.c.meet++;
	}
	SetVertexMeetStrike(g_cursor.c.meet);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeetStrike(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	if (g_strike.s.use == true && g_cursor.c.use == true)
	{
		// テクスチャの設定  
		pDevice->SetTexture(0, g_strike.s.pD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_strike.s.vertexWk, sizeof(VERTEX_2D));
		// テクスチャの設定  
		pDevice->SetTexture(0, g_cursor.c.pD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_cursor.c.vertexWk, sizeof(VERTEX_2D));
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMeetStrike(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	switch (type)
	{
	case 0:
		// 頂点座標の設定
		SetVertexMeetStrike(type);
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
		// テクスチャ座標の設定  
		g_strike.s.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_strike.s.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_strike.s.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_strike.s.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;

	case 1:
		// 頂点座標の設定
		SetVertexMeetStrike(type);
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
		// テクスチャ座標の設定  
		g_cursor.c.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_cursor.c.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_cursor.c.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_cursor.c.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;
	}
	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexMeetStrike(int CursorType)
{
	switch (CursorType %2)
	{
	case BIG:
		// 頂点座標の設定 
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
// ストライクのアドレスを返す
//=============================================================================
STRIKE *GetStrike(void)
{
	return &g_strike;
}

//=============================================================================
// ミートのアドレスを返す
//=============================================================================
CURSOR *Get_Cursor(void)
{
	return &g_cursor;
}

