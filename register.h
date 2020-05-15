/*******************************************************************************
* タイトル:		キムジュンデンセツ(3)
* プログラム名:	file.h
* 作成者:			GP11B292 08 キムラジュン
********************************************************************************/
#pragma once

// マクロ定義
#define SAVE_TEXTURE_FILE_00		_T("data/TEXTURE/SAVE/save.png")	// サンプル用画像
#define SAVE_SIZE_W			(880)	// テクスチャサイズ
#define SAVE_SIZE_H			(660)	// 同上
#define SAVE_POS_X			(0)		// ポリゴンの初期位置X(左上)
#define SAVE_POS_Y			(0)		// 同上

/*******************************************************************************
* 構造体定義
*******************************************************************************/
typedef struct					// セーブデータの構造体
{
	int ftime;
	int fscore;
} SAVEDATA;

typedef struct					// セーブデータの構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// 背景の位置
}SAVE;

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitSave(int type);
void UninitSave(void);
void UpdateSave(void);
void DrawSave(void);
HRESULT MakeVertexSave(void);
void SetVertexSave(void);
void SaveData(void);
void LoadData(void);
