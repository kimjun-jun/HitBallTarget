/**
* @file main.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "ball.h"
#include "meetstrike.h"
#include "collision.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "bg.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "tutorial.h"
#include "select.h"
#include "effect.h"
#include "pause.h"
#include "register.h"
#include "ranking.h"
#include "countdown.h"
#include "option.h"
#include "R18.h"
#include "controltype.h"
#include "sensitivity.h"
#include "tutomenu.h"
#include "balleffect.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
/**
* @brief ウインドウのクラス名
*/
#define CLASS_NAME			_T("AppClass")				

/**
* @brief ウインドウのキャプション名
*/
#define WINDOW_NAME			_T("HitBallTarget")			

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
* @brief 初期化関数
* @param[in]　HWND hWnd, BOOL bWindow
* @return HRESULT
* @details 起動時の初期化
*/
HRESULT Init(HWND hWnd, BOOL bWindow);

/**
* @brief メモリ開放関数
* @details ゲーム終了時にメモリ開放する
*/
void Uninit(void);

/**
* @brief アップデート関数
* @details オブジェクトを更新する
*/
void Update(void);

/**
* @brief 描画関数
* @details オブジェクトを描画する
*/
void Draw(void);

#ifdef _DEBUG
/**
* @brief FPS表示関数
* @details デバッグ実行時FPSを表示する
*/
void DrawFPS(void);
#endif

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//! Direct3Dオブジェクト
LPDIRECT3D9				g_pD3D = NULL;			

//!  Deviceオブジェクト(描画に必要)
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;	

#ifdef _DEBUG
//! フォントへのポインタ
LPD3DXFONT				g_pD3DXFont = NULL;		
//! FPSカウンタ
int						g_nCountFPS;			
//! 一時停止変数
int						stop = 0;
#endif

//! 表示させるテキスト
char					g_text[256] = { 0 };	

//! ゲームシーン番号
int						g_nScene = SCENE_TITLE;	

//! ランダム変数
float					g_random;				

//! 時間計測用
DWORD					dwFrameCount;			


/**
* @brief メイン関数
* @param[in] HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
* @return int
*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned)time(NULL));

	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;


	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		SCREEN_W + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// ウィンドウ横幅
		SCREEN_H + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	bool mode;
	//戻り値がint型で戻ってくる
	//ここのMessageBoxを呼ぶとwindowが出せる。
	//引数1はNULL。引数2は本文。
	//引数3はwindou名。
	//引数4はMB_YESNOCANCELこれでイエスノーキャンセルの三択が出せる。ここはいろんな種類があるから自分で調べるMB_OKでOKだけ
	//引数4の後ろに「| MB_ICONQUESTION」でアイコンを出すことができる。
	int id = MessageBox(NULL, "Windowモードでプレイしますか？", "起動モード", MB_YESNOCANCEL | MB_ICONQUESTION);

	//押された選択肢でスイッチ分岐
	switch (id)
	{
	case IDYES:		// YesならWindowモードで起動
		mode = true;
		break;
	case IDNO:		// Noならフルスクリーンモードで起動
		mode = false;
		break;
	case IDCANCEL:	// CANCELなら終了
	default:
		return -1;
		break;
	}

	if (FAILED(Init(hWnd, mode)))
	{
		return -1;
	}

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);//ウィンドウ表示ここから始まる
	UpdateWindow(hWnd);
	PlaySound(SOUND_LABEL_BGM_title01);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)//ウィンドウの×ボタン
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

				Update();			// 更新処理
				Draw();				// 描画処理
				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

/**
* @brief プロシージャ関数
* @param[in] HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
* @return LRESULT
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得 使ってるPCのスペックを調べてる
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;						// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_W;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_H;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// デプスバッファとして16bitを使う
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定

	if (bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード　各々のPCGPUに依存するため、対応しているのを考える必要がある
		//d3dpp.BackBufferFormat = D3DFMT_R5G6B5;					// バックバッファ
		//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成　GPUを積載しているとIF一つでゲームが動く。描画や頂点処理をGPUで処理させるとCPU処理速度の負荷が少なくなる
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// ディスプレイアダプタ
		D3DDEVTYPE_HAL,								// ディスプレイタイプ
		hWnd,										// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,		// デバイス作成制御の組み合わせ
		&d3dpp,										// デバイスのプレゼンテーションパラメータ
		&g_pD3DDevice)))							// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージ加算合成処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数


#ifdef _DEBUG
	// 情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif

	// ポリゴンとサウンドの初期化処理
	InitSound(hWnd);
	//InitKey();
	InitPlayer(0);
	InitEnemy(0);
	InitBall(0);
	InitMeetStrike(0);
	InitScore(0);
	InitBG(0);
	InitTitle(0);
	InitResult(0);
	InitFade();
	InitTutorial(0);
	InitSelect(0);
	InitPause(0);
	InitCountdown(0);
	InitOption(0);
	InitR18select(0);
	InitContype(0);
	InitSensitivity(0);
	InitTutomenu(0);
	InitBalleffect(0);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
	}

	// ポリゴンとサウンドの終了処理
	UninitBall();
	UninitPlayer();
	UninitEnemy();
	UninitInput();
	UninitScore();
	UninitBG();
	UninitMeetStrike();
	UninitTitle();
	UninitResult();
	UninitFade();
	UninitFade();
	UninitTutorial();
	UninitSelect();
	UninitPause();
	UninitCountdown();
	UninitOption();
	UninitR18select();
	UninitContype();
	UninitSensitivity();
	UninitTutomenu();
	UninitBalleffect();
	UninitSound();

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力の更新処理
	UpdateInput();

	if (GetKeyboardTrigger(DIK_F12) || IsButtonTriggered(0, BUTTON_SELECT)) stop++;
	if (GetKeyboardTrigger(DIK_F11) || IsButtonTriggered(0, BUTTON_SELECT))
	{
		MasterVolumeChange(1);
		InitGame();
		SetFade(FADE_OUT, SCENE_TITLE, SOUND_LABEL_BGM_title01);
	}
	if (stop % 2 == 0)
	{
		UpdateBG();
		switch (g_nScene)
		{
		case SCENE_TITLE:
			UpdateTitle();
			break;
		case SCENE_TUTORIAL:
			UpdateTutorial();
			UpdatePlayer();
			UpdateMeetStrike();
			UpdateBall();
			CheakHit();
			Hitball();
			//UpdateBalleffect();
			UpdateBE();
			UpdateInTutomenu();
			break;
		case SCENE_TUTORIALMENU:
			UpdateTutomenu();
			break;
		case SCENE_SELECT:
			UpdateSelect();
			break;
		case SCENE_GAMECOUNTDOWN:
			UpdateCountdown();
			UpdatePlayer();
			UpdateMeetStrike();
			AddCountdown(-1);
			break;
		case SCENE_GAME:
			// ポリゴンの更新処理
			UpdateScore();
			UpdatePlayer();
			UpdateMeetStrike();
			UpdateEnemy();
			UpdateBall();
			CheakHit();		// 当たり判定
			Hitball();
			//UpdateBalleffect();
			UpdateBE();
			AddScore(-1, 0);
			UpdateInPause();
			break;
		case SCENE_PAUSE:
			UpdatePause();
			break;
		case SCENE_OPTION:
			UpdateOption();
			break;
		case SCENE_SENSITIVITY:
			UpdateSensitivity();
			break;
		case SCENE_TUTOSENSITIVITY:
			UpdateTUTOSensitivity();
			break;
		case SCENE_CONTYPE:
			UpdateContype();
			break;
		case SCENE_TUTOCONTYPE:
			UpdateTUTOContype();
			break;
		case SCENE_R18SELECT:
			UpdateR18select();
			break;
		case SCENE_RESULT_CLEAR:
			UpdateResult();
			break;
		case SCENE_RESULT_FIELD:
			UpdateResult();
			break;
		case SCENE_REGISTER:
			UpdateSave();
			break;
		case SCENE_RANKING:
			UpdateRanking();
			break;
		}
		// フェード処理
		UpdateFade();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		DrawBG();
		// 画面遷移
		switch (g_nScene)
		{
		case SCENE_TITLE:
			DrawTitle();
			break;
		case SCENE_TUTORIAL:
			DrawBall();
			DrawBE();
			DrawMeetStrike();
			DrawPlayer();
			DrawBalleffect();
			DrawTutorial();
			break;
		case SCENE_TUTORIALMENU:
			DrawTutomenu();
			break;
		case SCENE_SELECT:
			DrawSelect();
			break;
		case SCENE_GAMECOUNTDOWN:
			DrawScore();
			DrawMeetStrike();
			DrawPlayer();
			DrawEnemy();
			DrawBall();
			DrawBE();
			DrawCountdown();
			break;
		case SCENE_GAME:
			// ポリゴンの描画処理
			DrawEnemy();
			DrawScore();
			DrawPlayer();
			DrawBall();
			DrawBE();
			DrawBalleffect();
			DrawMeetStrike();
			break;
		case SCENE_PAUSE:
			DrawScore();
			DrawPause();
			break;
		case SCENE_OPTION:
			DrawScore();
			DrawOption();
			break;
		case SCENE_SENSITIVITY:
			DrawScore();
			DrawSensitivity();
			break;
		case SCENE_TUTOSENSITIVITY:
			DrawSensitivity();
			break;
		case SCENE_CONTYPE:
			DrawScore();
			DrawContype();
			break;
		case SCENE_TUTOCONTYPE:
			DrawContype();
			break;
		case SCENE_R18SELECT:
			DrawScore();
			DrawR18select();
			break;
		case SCENE_RESULT_CLEAR:
			DrawResult(CLEAR);
			break;
		case SCENE_RESULT_FIELD:
			DrawResult(FIELD);
			break;
		case SCENE_REGISTER:
			DrawSave();
			break;
		case SCENE_RANKING:
			DrawRanking();
			break;
		}
		// フェード描画
		DrawFade();
#ifdef _DEBUG
		// FPS表示
		DrawFPS();
		DrawTextType();
#endif		
		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイス取得関数
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}

#ifdef _DEBUG
//=============================================================================
// デバッグ時に表示させる文字列をg_textに書き込む
//=============================================================================
void SelectText(char *moji)
{
	strcpy(g_text,moji);
}

//=============================================================================
// デバッグ時にg_textの中身を描画
//=============================================================================
void DrawTextType(void)
{
	TCHAR str[256];
	RECT rect = { 10, 90, SCREEN_W, SCREEN_H };
	wsprintf(str, _T("%s\n"), g_text);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
}

//=============================================================================
// デバッグ時にFPS表示処理　ついでにゲームパッドの対応ボタンも入力されるとビットを立てて表示
//=============================================================================
void DrawFPS(void)
{
	TCHAR str[256];
	int GetPadData(int no);

	//ここのセットを加えることでデバッグ時の表示項目を増やせる
	{
		RECT rect = { 0, 0, SCREEN_W, SCREEN_H };
		wsprintf(str, _T("FPS:%d\n"), g_nCountFPS);
		// テキスト描画
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0xff));//ARGBで色変えれる
	}

	{
		RECT rect = { 0, 50, SCREEN_W, SCREEN_H };
		wsprintf(str, _T("%d %d %d %d %d %d %d %d \n"), GetPadData(0), GetPadData(1), GetPadData(2), GetPadData(3), GetPadData(4), GetPadData(5), GetPadData(6), GetPadData(7));
		// テキスト描画
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0x00));
	}

	{
		RECT rect = { 0, 70, SCREEN_W, SCREEN_H };
		wsprintf(str, _T("%d %d %d %d %d %d %d %d \n"), GetPadData(8), GetPadData(9), GetPadData(10), GetPadData(11), GetPadData(12), GetPadData(13), GetPadData(14), GetPadData(15));
		// テキスト描画
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0x00));
	}

}
#endif

//=============================================================================
// Scene遷移
//=============================================================================
void SetScene(int Scene)
{
	g_nScene = Scene;
}

//=============================================================================
// GetScene遷移
//=============================================================================
int GetScene(void)
{
	return g_nScene;
}

//=============================================================================
// ゲームループ時の再初期化処理
//=============================================================================
void InitGame(void)
{
	InitPlayer(1);
	InitEnemy(1);
	InitBall(1);		
	InitScore(1);		
	InitBG(1);			
	InitMeetStrike(1);
	InitTitle(1);
	InitResult(1);
	InitFade();
	InitTutorial(1);
	InitSelect(1);
	InitCountdown(1);
}

//=============================================================================
// チュートリアル後の最初期化
//=============================================================================
void ReInitTuto(void)
{
	ReInitPlayer();
	ReInitEnemy();
	ReInitBall();
	ReInitMeetStrike();
	ReInitCountdown();
}

//=============================================================================
// はじめからの最初期化
//=============================================================================
void UpdateReInit(void)
{
	ReInitPlayer();
	ReInitScore();
	ReInitEnemy();
	ReInitBall();
	ReInitMeetStrike();
	ReInitCountdown();
	ReInitPause();
	ReInitOption();
	ReInitR18select();
	ReInitContype();
	ReInitSensitivity();
	ReInitTutomenu();
	ReInitBG();
}

//=============================================================================
// ランダム関数
//=============================================================================
float Random(int type)
{
	float n = 0.0;
	switch (type)
	{
	case X:
	{
		switch ((rand() % 6))
		{
		case 0:
			n = 300.0;
			break;
		case 1:
			n = 400.0;
			break;
		case 2:
			n = 500.0;
			break;
		case 3:
			n = 700.0;
			break;
		case 4:
			n = 200.0;
			break;
		default:
			n = 220.0;
			break;
		}
		break;
	}
	case Y:
	{
		switch ((rand() % 6))
		{
		case 0:
			n = 200.0;
			break;
		case 1:
			n = 300.0;
			break;
		case 2:
			n = 300.0;
			break;
		case 3:
			n = 320.0;
			break;
		case 4:
			n = 250.0;
			break;
		default:
			n = 200.0;
			break;
		}
		break;
	}
	}
	return n;
}

