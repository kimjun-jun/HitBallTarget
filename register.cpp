/**
* @file register.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "score.h"
#include "register.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief 頂点生成関数 MakeVertexSave
* @return HRESULT
*/
HRESULT MakeVertexSave(void);

/**
* @brief 頂点設定関数 SetVertexSave
*/
void SetVertexSave(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
SAVEDATA g_savedate;				//!< セーブデータ	構造体変数
SAVE g_save;						//!< セーブポリゴン	構造体変数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSave(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			SAVE_TEXTURE_FILE_00,		// ファイルの名前
			&g_save.pD3DTexture);		// 読み込むメモリー
	}
	g_save.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 頂点情報の作成
	MakeVertexSave();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSave(void)
{
	if (g_save.pD3DTexture != NULL)
	{	// テクスチャの開放
		g_save.pD3DTexture->Release();
		g_save.pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSave(void)
{
	SaveData();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSave(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_save.pD3DTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_save.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexSave(void)
{
	// 頂点座標の設定
	SetVertexSave();

	// rhwの設定
	g_save.vertexWk[0].rhw =
		g_save.vertexWk[1].rhw =
		g_save.vertexWk[2].rhw =
		g_save.vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_save.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_save.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_save.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_save.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_save.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_save.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_save.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_save.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexSave(void)
{
	// 頂点座標の設定
	g_save.vertexWk[0].vtx = D3DXVECTOR3(SAVE_POS_X, SAVE_POS_Y, 0.0f);
	g_save.vertexWk[1].vtx = D3DXVECTOR3(SAVE_POS_X + SAVE_SIZE_W, SAVE_POS_Y, 0.0f);
	g_save.vertexWk[2].vtx = D3DXVECTOR3(SAVE_POS_X, SAVE_POS_Y + SAVE_SIZE_H, 0.0f);
	g_save.vertexWk[3].vtx = D3DXVECTOR3(SAVE_POS_X + SAVE_SIZE_W, SAVE_POS_Y + SAVE_SIZE_H, 0.0f);
}

/*******************************************************************************
関数名:	void SaveData( void )
引数:	void
戻り値:	void
説明:	セーブデータを作成し、ファイルへ出力する
*******************************************************************************/
void SaveData(void)
{
	int *time = GetTimemaneger();
	int *score = GetScoremaneger();
	g_savedate.ftime = *time;
	g_savedate.fscore = *score;
	char str[256] = { 0 };

	// SAVEDATA構造体ごと全部をファイルに出力する
	FILE* fp;
#ifdef _DEBUG
	sprintf(str, "セーブ開始");
	SelectText(str);
#endif			
	fp = fopen("savedata.text", "wb");			// ファイルをバイナリ書き込みモードでOpenする
	if (fp != NULL)								// ファイルがあれば書き込み、無ければ無視
	{
		fwrite(&g_savedate, 1, sizeof(SAVEDATA), fp);	// 指定したアドレスから指定したバイト数分ファイルへ書き込む
		fclose(fp);								// Openしていたファイルを閉じる
#ifdef _DEBUG
		sprintf(str, "セーブ完了");
		SelectText(str);
#endif			
	}
	else
	{
#ifdef _DEBUG
		sprintf(str, "セーブエラー");
		SelectText(str);
#endif			
	}
	rewind(stdin);
	getchar();
}

/*******************************************************************************
関数名:	void LoadData( void )
引数:	void
戻り値:	void
説明:	セーブデータをファイルから読み込む
*******************************************************************************/
void LoadData(void)
{
	int *time = GetTimemaneger();
	int *score = GetScoremaneger();
	g_savedate.ftime = *time;
	g_savedate.fscore = *score;
	char str[256] = { 0 };

	// ファイルからセーブデータを読み込む
	FILE* fp;
#ifdef _DEBUG
	sprintf(str, "ロード開始");
	SelectText(str);
#endif			
	fp = fopen("savedata.text", "rb");			// ファイルをバイナリ読み込みモードでOpenする
	if (fp != NULL)								// ファイルがあれば書き込み、無ければ無視
	{
		fread(&g_savedate, 1, sizeof(SAVEDATA), fp);	// 指定したアドレスへ指定したバイト数分ファイルから読み込む
		fclose(fp);								// Openしていたファイルを閉じる
#ifdef _DEBUG
		sprintf(str, "ロード終了");
		SelectText(str);
#endif			
	}
	else
	{
#ifdef _DEBUG
		sprintf(str, "ロードエラー");
		SelectText(str);
#endif			
	}

	*time = g_savedate.ftime;					// ファイルから読み込んだデータを現在のワークへ戻す
	*score = g_savedate.fscore;					// ファイルから読み込んだデータを現在のワークへ戻す
	rewind(stdin);
	getchar();
}

