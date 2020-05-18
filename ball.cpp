/**
* @file ball.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "game.h"
#include "collision.h"
#include "ball.h"

//*****************************************************************************
// ?クロ定?
//*****************************************************************************


//*****************************************************************************
// プロト?イプ宣言
//*****************************************************************************

//*****************************************************************************
// グロ?バル変数
//*****************************************************************************
BALL g_ball[BALL_MAX];
BALLCURSOR g_ballcursor;
BALLSHADOW g_ballshadow[BALL_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBall(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// テクス?ャの読み込み  
	if (type == 0)	// 初回のみ読み込む
	{
		for (int i = 0; i < BALL_MAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// デバイスの?イン?
				TEXTURE_GAME_BALLTYPE0,				// フ?イルの名前
				&g_ball[i].pD3DTexture);			// 読み込むメモリの?イン?
		}
		for (int i = 0; i < BALL_MAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// デバイスの?イン?
				TEXTURE_GAME_BALLTYPE1,				// フ?イルの名前
				&g_ball[i].pD3DTextureEffect);			// 読み込むメモリの?イン?
		}
		D3DXCreateTextureFromFile(pDevice,		// デバイスの?イン?
			TEXTURE_GAME_BALLTYPE0,				// フ?イルの名前
			&g_ballcursor.pD3DTexture);			// 読み込むメモリの?イン?

			D3DXCreateTextureFromFile(pDevice,		// デバイスの?イン?
				TEXTURE_GAME_BALLTYPE0,				// フ?イルの名前
				&g_ballshadow[0].pD3DTexture);			// 読み込むメモリの?イン?
		for (int i = 1; i < BALL_MAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// デバイスの?イン?
				TEXTURE_GAME_BALLTYPE1,				// フ?イルの名前
				&g_ballshadow[i].pD3DTextureEffect);			// 読み込むメモリの?イン?
		}
	}

	for (int i = 0; i < BALL_MAX; i++)
	{
		g_ball[i].use = false;									//真使用している(表示描画する) 偽使用していない
		g_ball[i].OorD = true;									//真球が打たれた　偽球が打たれていない
		g_ball[i].tuto = true;									//真チュートリアル中　偽ゲーム中
		g_ball[i].effect = false;								//真チュートリアル中　偽ゲーム中
		g_ball[i].diffflag = false;								//真拡散弾ゲットflag　偽拡散弾持って無い
		g_ball[i].diffsignal = false;							//真拡散弾中　偽拡散弾無
		g_ball[i].pos = D3DXVECTOR3(-100, -100, 0);
		g_ball[i].rot = D3DXVECTOR3(0, 0, 0);
		g_ball[i].move = D3DXVECTOR3(0, 0, 0);
		g_ball[i].oldpos = D3DXVECTOR3(-100, -100, 0);
		for (int j = 0; j < 4; j++)
		{
			g_ball[i].effectoldpos[j] = D3DXVECTOR3(-100, -100, 0);
		}
		g_ball[i].oldrot = D3DXVECTOR3(0, 0, 0);
		g_ball[i].oldmove = D3DXVECTOR3(0, 0, 0);

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BALL_SIZE_X, TEXTURE_BALL_SIZE_Y);
		g_ball[i].rad = D3DXVec2Length(&temp);
		g_ball[i].BaseAngle = atan2f(TEXTURE_BALL_SIZE_Y, TEXTURE_BALL_SIZE_X);

		g_ball[i].changeVal = 1.0f;
		g_ball[i].changeValTypeA = 0;
		g_ball[i].penetcount = 0;
		g_ball[i].diffcount = 0;
		g_ball[i].effectcount = 0;
	}

	g_ballcursor.use = false;							//真使用している(表示描画する) 偽使用していない
	g_ballcursor.pos = D3DXVECTOR3(-100, -100, 0);
	g_ballcursor.rot = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.move = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.oldmove = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.direction = 0;
	g_ballcursor.changeVal = 0;
	g_ballcursor.movecount = 0;
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_ballshadow[i].use = false;						  //真使用している(表示描画する) 偽使用していない
		g_ballshadow[i].pos = D3DXVECTOR3(-100, -100, 0);
		g_ballshadow[i].rot = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].move = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].oldmove = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].changeVal = 1.0f;
	}
	MakeVertexBall();

	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitBall(void)
{
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_ball[i].use = false;									//真使用している(表示描画する) 偽使用していない
		g_ball[i].OorD = true;									//真球が打たれた　偽球が打たれていない
		g_ball[i].effect = false;								//真チュートリアル中　偽ゲーム中
		g_ball[i].tuto = true;									//真チュートリアル中　偽ゲーム中
		g_ball[i].diffflag = false;								//真拡散弾ゲットflag　偽拡散弾持って無い
		g_ball[i].diffsignal = false;							//真アイテムゲット中　偽アイテム持って無い
		g_ball[i].pos = D3DXVECTOR3(-100, -100, 0);
		g_ball[i].rot = D3DXVECTOR3(0, 0, 0);
		g_ball[i].move = D3DXVECTOR3(0, 0, 0);
		g_ball[i].oldpos = D3DXVECTOR3(-100, -100, 0);
		g_ball[i].oldrot = D3DXVECTOR3(0, 0, 0);
		g_ball[i].oldmove = D3DXVECTOR3(0, 0, 0);
		for (int j = 0; j < 4; j++)
		{
			g_ball[i].effectoldpos[j] = D3DXVECTOR3(-100, -100, 0);
		}
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BALL_SIZE_X, TEXTURE_BALL_SIZE_Y);
		g_ball[i].rad = D3DXVec2Length(&temp);
		g_ball[i].BaseAngle = atan2f(TEXTURE_BALL_SIZE_Y, TEXTURE_BALL_SIZE_X);
		g_ball[i].changeVal = 1.0f;
		g_ball[i].changeValTypeA = 0;
		g_ball[i].penetcount = 0;
		g_ball[i].diffcount = 0;
		g_ball[i].effectcount = 0;
	}

	g_ballcursor.use = false;
	g_ballcursor.pos = D3DXVECTOR3(-100, -100, 0);
	g_ballcursor.rot = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.move = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.oldmove = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.changeVal = 0;
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_ballshadow[i].use = false;
		g_ballshadow[i].pos = D3DXVECTOR3(-100, -100, 0);
		g_ballshadow[i].rot = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].move = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].oldmove = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].changeVal = 1.0f;
	}
	SetVertexBall();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBall(void)
{
	for (int i = 0; i < BALL_MAX; i++)
	{
		if (g_ball[i].pD3DTexture != NULL)
		{	// テクス?ャの開放
			g_ball[i].pD3DTexture->Release();
			g_ball[i].pD3DTexture = NULL;
		}
	}
	for (int i = 0; i < BALL_MAX; i++)
	{
		if (g_ball[i].pD3DTextureEffect != NULL)
		{	// テクス?ャの開放
			g_ball[i].pD3DTextureEffect->Release();
			g_ball[i].pD3DTextureEffect = NULL;
		}
	}
	if (g_ballcursor.pD3DTexture != NULL)
	{	// テクス?ャの開放
		g_ballcursor.pD3DTexture->Release();
		g_ballcursor.pD3DTexture = NULL;
	}
	for (int i = 0; i < BALL_MAX; i++)
	{
		if (g_ballshadow[i].pD3DTexture != NULL)
		{	// テクス?ャの開放
			g_ballshadow[i].pD3DTexture->Release();
			g_ballshadow[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBall(void)
{
	if (g_ball[0].use == true) Ball();
	if (g_ball[0].diffflag == true && g_ball[0].use == false && g_ball[1].use == false && g_ball[2].use == false)
	{
		g_ball[0].diffsignal = true;
		g_ball[0].diffflag = false;
	}
	if (g_ball[0].diffsignal == true)
	{
		g_ball[0].diffcount++;
		if (g_ball[0].diffcount >= 600)//10s
		{
			g_ball[0].diffsignal = false;
			g_ball[0].diffflag = false;
			g_ball[0].diffcount = 0;
			LoopInit();
		}
	}
	g_ball[0].rot.z += BALL_ROT;
	g_ball[1].rot.z += BALL_ROT;
	g_ball[2].rot.z += BALL_ROT;
	SetVertexBall();	// 移動後の座標で頂?を設定
}

//=============================================================================
// ?画処理
//=============================================================================
void DrawBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂?フォ??ットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < BALL_MAX; i++)
	{
		if (g_ball[i].use == true)
		{
			if (g_ball[i].effect == true)
			{
				pDevice->SetTexture(0, g_ball[i].pD3DTextureEffect);
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ball[i].vertexWk, sizeof(VERTEX_2D));

				pDevice->SetTexture(0, g_ballshadow[i].pD3DTextureEffect);
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ballshadow[i].vertexWk, sizeof(VERTEX_2D));
			}
			else
			{
				pDevice->SetTexture(0, g_ball[i].pD3DTexture);
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ball[i].vertexWk, sizeof(VERTEX_2D));

				pDevice->SetTexture(0, g_ballshadow[i].pD3DTexture);
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ballshadow[i].vertexWk, sizeof(VERTEX_2D));
			}
			pDevice->SetTexture(0, g_ballcursor.pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ballcursor.vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂?の作成
//=============================================================================
HRESULT MakeVertexBall(void)
{
	// 頂?座標の設定
	SetVertexBall();

	for (int i = 0; i < BALL_MAX; i++)
	{
		// rhwの設定
		g_ball[i].vertexWk[0].rhw =
			g_ball[i].vertexWk[1].rhw =
			g_ball[i].vertexWk[2].rhw =
			g_ball[i].vertexWk[3].rhw = 1.0f;
		// 反射光の設定  
		g_ball[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_ball[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_ball[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_ball[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		// テクス?ャ座標の設定  
		g_ball[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ball[i].vertexWk[1].tex = D3DXVECTOR2(1.0f , 0.0f);
		g_ball[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ball[i].vertexWk[3].tex = D3DXVECTOR2(1.0f , 1.0f );


		g_ballshadow[i].vertexWk[0].rhw =
		g_ballshadow[i].vertexWk[1].rhw =
		g_ballshadow[i].vertexWk[2].rhw =
		g_ballshadow[i].vertexWk[3].rhw = 1.0f;
		g_ballshadow[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 50);
		g_ballshadow[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 50);
		g_ballshadow[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 50);
		g_ballshadow[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 50);
		g_ballshadow[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ballshadow[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ballshadow[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ballshadow[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	g_ballcursor.vertexWk[0].rhw =
		g_ballcursor.vertexWk[1].rhw =
		g_ballcursor.vertexWk[2].rhw =
		g_ballcursor.vertexWk[3].rhw = 1.0f;
	g_ballcursor.vertexWk[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_ballcursor.vertexWk[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_ballcursor.vertexWk[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_ballcursor.vertexWk[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_ballcursor.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_ballcursor.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_ballcursor.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_ballcursor.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// 頂?座標の設定
//=============================================================================
void SetVertexBall(void)
{
	// 頂?座標の設定 
	for (int i = 0; i < BALL_MAX; i++)
	{
		//角度使うと回転が楽
		g_ball[i].vertexWk[0].vtx.x = g_ball[i].pos.x -(cosf(g_ball[i].BaseAngle + g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[0].vtx.y = g_ball[i].pos.y -(sinf(g_ball[i].BaseAngle + g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[0].vtx.z = 0.0f;			   															  
		g_ball[i].vertexWk[1].vtx.x = g_ball[i].pos.x +(cosf(g_ball[i].BaseAngle - g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[1].vtx.y = g_ball[i].pos.y -(sinf(g_ball[i].BaseAngle - g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[1].vtx.z = 0.0f;			   															  
		g_ball[i].vertexWk[2].vtx.x = g_ball[i].pos.x -(cosf(g_ball[i].BaseAngle - g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[2].vtx.y = g_ball[i].pos.y +(sinf(g_ball[i].BaseAngle - g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[2].vtx.z = 0.0f;			   															  
		g_ball[i].vertexWk[3].vtx.x = g_ball[i].pos.x +(cosf(g_ball[i].BaseAngle + g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[3].vtx.y = g_ball[i].pos.y +(sinf(g_ball[i].BaseAngle + g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[3].vtx.z = 0.0f;


		//g_ball[i].vertexWk[0].vtx.x = g_ball[i].pos.x - TEXTURE_BALL_SIZE_X - g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[0].vtx.y = g_ball[i].pos.y - TEXTURE_BALL_SIZE_Y - g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[0].vtx.z = 0.0f;
		//g_ball[i].vertexWk[1].vtx.x = g_ball[i].pos.x + TEXTURE_BALL_SIZE_X + g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[1].vtx.y = g_ball[i].pos.y - TEXTURE_BALL_SIZE_Y - g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[1].vtx.z = 0.0f;
		//g_ball[i].vertexWk[2].vtx.x = g_ball[i].pos.x - TEXTURE_BALL_SIZE_X - g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[2].vtx.y = g_ball[i].pos.y + TEXTURE_BALL_SIZE_Y + g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[2].vtx.z = 0.0f;
		//g_ball[i].vertexWk[3].vtx.x = g_ball[i].pos.x + TEXTURE_BALL_SIZE_X + g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[3].vtx.y = g_ball[i].pos.y + TEXTURE_BALL_SIZE_Y + g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[3].vtx.z = 0.0f;


		g_ballshadow[i].vertexWk[0].vtx.x = g_ballshadow[i].pos.x - TEXTURE_BALLSHADOW_SIZE_X;
		g_ballshadow[i].vertexWk[0].vtx.y = g_ballshadow[i].pos.y - TEXTURE_BALLSHADOW_SIZE_Y;
		g_ballshadow[i].vertexWk[0].vtx.z = 0.0f;
		g_ballshadow[i].vertexWk[1].vtx.x = g_ballshadow[i].pos.x + TEXTURE_BALLSHADOW_SIZE_X;
		g_ballshadow[i].vertexWk[1].vtx.y = g_ballshadow[i].pos.y - TEXTURE_BALLSHADOW_SIZE_Y;
		g_ballshadow[i].vertexWk[1].vtx.z = 0.0f;
		g_ballshadow[i].vertexWk[2].vtx.x = g_ballshadow[i].pos.x - TEXTURE_BALLSHADOW_SIZE_X;
		g_ballshadow[i].vertexWk[2].vtx.y = g_ballshadow[i].pos.y + TEXTURE_BALLSHADOW_SIZE_Y;
		g_ballshadow[i].vertexWk[2].vtx.z = 0.0f;
		g_ballshadow[i].vertexWk[3].vtx.x = g_ballshadow[i].pos.x + TEXTURE_BALLSHADOW_SIZE_X;
		g_ballshadow[i].vertexWk[3].vtx.y = g_ballshadow[i].pos.y + TEXTURE_BALLSHADOW_SIZE_Y;
		g_ballshadow[i].vertexWk[3].vtx.z = 0.0f;
	}


	g_ballcursor.vertexWk[0].vtx.x = g_ballcursor.pos.x - TEXTURE_BALLCURSOR_SIZE_X;
	g_ballcursor.vertexWk[0].vtx.y = g_ballcursor.pos.y - TEXTURE_BALLCURSOR_SIZE_Y;
	g_ballcursor.vertexWk[0].vtx.z = 0.0f;
	g_ballcursor.vertexWk[1].vtx.x = g_ballcursor.pos.x + TEXTURE_BALLCURSOR_SIZE_X;
	g_ballcursor.vertexWk[1].vtx.y = g_ballcursor.pos.y - TEXTURE_BALLCURSOR_SIZE_Y;
	g_ballcursor.vertexWk[1].vtx.z = 0.0f;
	g_ballcursor.vertexWk[2].vtx.x = g_ballcursor.pos.x - TEXTURE_BALLCURSOR_SIZE_X;
	g_ballcursor.vertexWk[2].vtx.y = g_ballcursor.pos.y + TEXTURE_BALLCURSOR_SIZE_Y;
	g_ballcursor.vertexWk[2].vtx.z = 0.0f;
	g_ballcursor.vertexWk[3].vtx.x = g_ballcursor.pos.x + TEXTURE_BALLCURSOR_SIZE_X;
	g_ballcursor.vertexWk[3].vtx.y = g_ballcursor.pos.y + TEXTURE_BALLCURSOR_SIZE_Y;
	g_ballcursor.vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ??ルのアドレスを返す.
//=============================================================================
BALL *GetBall(void)
{
	return &g_ball[0];
}

//=============================================================================
// ??ルのアドレスを返す.
//=============================================================================
BALLCURSOR *GetBallcursor(void)
{
	return &g_ballcursor;
}

//=============================================================================
// ??ルのアドレスを返す.
//=============================================================================
BALLSHADOW *GetBallshadow(void)
{
	return &g_ballshadow[0];
}

//=============================================================================
// ??ルの設定
//=============================================================================
void SetBall(D3DXVECTOR3 pos)
{
	if (g_ball[0].use == false)
	{
		g_ball[0].pos = pos;
		g_ball[1].pos = pos;
		g_ball[2].pos = pos;
		g_ballcursor.pos = pos;
		g_ballshadow[0].pos = pos;
		g_ballcursor.pos.y = STRIKE_REFERENCE_Y;
		g_ballcursor.pos.x = STRIKE_REFERENCE_X;
		g_ballshadow[0].pos.y = BALL_SHADOW_REFARENCE_Y;
		g_ballshadow[0].pos.x = BALL_SHADOW_REFARENCE_X;
		g_ball[0].use = true;
	}
}
