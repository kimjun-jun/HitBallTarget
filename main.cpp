/**
* @file main.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "ball.h"
#include "ui.h"
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
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")				// �E�C���h�E�̃N���X��
#define WINDOW_NAME			_T("HitBallTarget")			// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief �����Z�b�g����֐�
* @param[in] moji �\�����������������
* @details �ŋ���������p Debug�݂̂Ŏg�p
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
* @brief �f�o�C�X�擾�֐�
* @return LPDIRECT3DDEVICE9
*/
HRESULT Init(HWND hWnd, BOOL bWindow);

/**
* @brief ������\������֐�
* @details �ŋ���������p Debug�݂̂Ŏg�p
*/
void Uninit(void);

/**
* @brief ������\������֐�
* @details �ŋ���������p Debug�݂̂Ŏg�p
*/
void Update(void);

/**
* @brief ������\������֐�
* @details �ŋ���������p Debug�݂̂Ŏg�p
*/
void Draw(void);

/**
* @brief ������\������֐�
* @details �ŋ���������p Debug�݂̂Ŏg�p
*/
#ifdef _DEBUG
void DrawFPS(void);
#endif

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;				// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
LPD3DXFONT				g_pD3DXFont = NULL;			// �t�H���g�ւ̃|�C���^
int						g_nCountFPS;				// FPS�J�E���^
int						stop = 0;
#endif

char					g_text[256] = { 0 };		//�\��������e�L�X�g
int						g_nScene = SCENE_TITLE;		// �X�e�[�W�ԍ�
float					g_random;					// �G�l�~�[�̏������W�������_���Ō��߂�
DWORD					dwFrameCount;				// ���Ԍv���p
//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned)time(NULL));

	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		SCREEN_W + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		SCREEN_H + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	bool mode;
	//�߂�l��int�^�Ŗ߂��Ă���
	//������MessageBox���ĂԂ�window���o����B
	//����1��NULL�B����2�͖{���B
	//����3��windou���B
	//����4��MB_YESNOCANCEL����ŃC�G�X�m�[�L�����Z���̎O�����o����B�����͂����Ȏ�ނ����邩�玩���Œ��ׂ�MB_OK��OK����
	//����4�̌��Ɂu| MB_ICONQUESTION�v�ŃA�C�R�����o�����Ƃ��ł���B
	int id = MessageBox(NULL, "Window���[�h�Ńv���C���܂����H", "�N�����[�h", MB_YESNOCANCEL | MB_ICONQUESTION);

	//�����ꂽ�I�����ŃX�C�b�`����
	switch (id)
	{
	case IDYES:		// Yes�Ȃ�Window���[�h�ŋN��
		mode = true;
		break;
	case IDNO:		// No�Ȃ�t���X�N���[�����[�h�ŋN��
		mode = false;
		break;
	case IDCANCEL:	// CANCEL�Ȃ�I��
	default:
		return -1;
		break;
	}

	if (FAILED(Init(hWnd, mode)))
	{
		return -1;
	}

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�\����������n�܂�
	UpdateWindow(hWnd);
	PlaySound(SOUND_LABEL_BGM_title01);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)//�E�B���h�E�́~�{�^��
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

				Update();			// �X�V����
				Draw();				// �`�揈��
				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
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
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾 �g���Ă�PC�̃X�y�b�N�𒲂ׂĂ�
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_W;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_H;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��

	if (bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h�@�e�X��PCGPU�Ɉˑ����邽�߁A�Ή����Ă���̂��l����K�v������
		//d3dpp.BackBufferFormat = D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
		//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐����@GPU��ύڂ��Ă����IF��ŃQ�[���������B�`��Ⓒ�_������GPU�ŏ����������CPU�������x�̕��ׂ����Ȃ��Ȃ�
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,								// �f�B�X�v���C�^�C�v
		hWnd,										// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,		// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,										// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&g_pD3DDevice)))							// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W���Z��������
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����


#ifdef _DEBUG
	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif

	// �|���S���ƃT�E���h�̏���������
	InitSound(hWnd);
	//InitKey();
	InitPlayer(0);
	InitEnemy(0);
	InitBall(0);
	InitUi(0);
	InitScore(0);
	InitBG(0);
	InitTitle(0);
	InitResult(0);
	InitFade(0);
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
// �I������
//=============================================================================
void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
	}

	// �|���S���ƃT�E���h�̏I������
	UninitBall();
	UninitPlayer();
	UninitEnemy();
	UninitInput();
	UninitScore();
	UninitBG();
	UninitUi();
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
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
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
			UpdateUi();
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
			UpdateUi();
			AddCountdown(-1);
			break;
		case SCENE_GAME:
			// �|���S���̍X�V����
			UpdateScore();
			UpdatePlayer();
			UpdateUi();
			UpdateEnemy();
			UpdateBall();
			CheakHit();		// �����蔻��
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
		// �t�F�[�h����
		UpdateFade();
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		DrawBG();
		// ��ʑJ��
		switch (g_nScene)
		{
		case SCENE_TITLE:
			DrawTitle();
			break;
		case SCENE_TUTORIAL:
			DrawBall();
			DrawBE();
			DrawUi();
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
			DrawUi();
			DrawPlayer();
			DrawEnemy();
			DrawBall();
			DrawBE();
			DrawCountdown();
			break;
		case SCENE_GAME:
			// �|���S���̕`�揈��
			DrawEnemy();
			DrawScore();
			DrawPlayer();
			DrawBall();
			DrawBE();
			DrawBalleffect();
			DrawUi();
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
		// �t�F�[�h�`��
		DrawFade();
#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
		DrawTextType();
#endif		
		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�擾�֐�
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}

#ifdef _DEBUG
//=============================================================================
// �f�o�b�O���ɂǂ̐���ɂȂ������Q�[����ʂŔ��f���镶���`��֐�
//=============================================================================
void SelectText(char *moji)
{
	strcpy(g_text,moji);
}

//=============================================================================
// �f�o�b�O���ɂǂ̐���ɂȂ������Q�[����ʂŔ��f���镶���`��֐�
//=============================================================================
void DrawTextType(void)
{
	TCHAR str[256];
	RECT rect = { 10, 90, SCREEN_W, SCREEN_H };
	wsprintf(str, _T("%s\n"), g_text);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
}

//=============================================================================
// FPS�\������
//=============================================================================
int GetPadData(int no);

void DrawFPS(void)
{
	TCHAR str[256];
	//�����̃Z�b�g�������邱�ƂŃf�o�b�O���̕\�����ڂ𑝂₹��
	{
		RECT rect = { 0, 0, SCREEN_W, SCREEN_H };
		wsprintf(str, _T("FPS:%d\n"), g_nCountFPS);
		// �e�L�X�g�`��
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0xff));//ARGB�ŐF�ς����
	}

	{
		RECT rect = { 0, 50, SCREEN_W, SCREEN_H };
		wsprintf(str, _T("%d %d %d %d %d %d %d %d \n"), GetPadData(0), GetPadData(1), GetPadData(2), GetPadData(3), GetPadData(4), GetPadData(5), GetPadData(6), GetPadData(7));
		// �e�L�X�g�`��
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0x00));
	}

	{
		RECT rect = { 0, 70, SCREEN_W, SCREEN_H };
		wsprintf(str, _T("%d %d %d %d %d %d %d %d \n"), GetPadData(8), GetPadData(9), GetPadData(10), GetPadData(11), GetPadData(12), GetPadData(13), GetPadData(14), GetPadData(15));
		// �e�L�X�g�`��
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0x00));
	}

}
#endif

//=============================================================================
// Scene�J��
//=============================================================================
void SetScene(int Scene)
{
	g_nScene = Scene;
}

//=============================================================================
// GetScene�J��
//=============================================================================
int GetScene(void)
{
	return g_nScene;
}

//=============================================================================
// �Q�[�����[�v���̍ď�������������
// �߂�l�F����
//=============================================================================
void InitGame(void)
{
	//�ď�����
	//InitKey();
	InitPlayer(1);
	InitEnemy(1);
	InitBall(1);		
	InitScore(1);		
	InitBG(1);			
	InitUi(1);
	InitTitle(1);
	InitResult(1);
	InitFade(1);
	InitTutorial(1);
	InitSelect(1);
	InitCountdown(1);
}

//=============================================================================
// �Q�[�����̍ď�������������
// �߂�l�F����
//=============================================================================
void ReInitTuto(void)
{
	//�`���[�g���A����̍ŏ�����
	ReInitPlayer();
	ReInitEnemy();
	ReInitBall();
	ReInitUi();
	ReInitCountdown();
}

//=============================================================================
// �Q�[�����̍ď�������������
// �߂�l�F����
//=============================================================================
void UpdateReInit(void)
{
	//�͂��߂���̍ŏ�����
	ReInitPlayer();
	ReInitScore();
	ReInitEnemy();
	ReInitBall();
	ReInitUi();
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
// �U���
// �߂�l�F(true)offence or (false)defence
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

