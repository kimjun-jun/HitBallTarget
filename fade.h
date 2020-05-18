/**
* @file fade.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once


//*************************************
// �t�F�[�h�̏��
//*************************************
enum FADE
{
	FADE_NONE = 0,		// �����Ȃ����
	FADE_IN,			// �t�F�[�h�C������
	FADE_MUSIC_STOP,
	FADE_OUT,			// �t�F�[�h�A�E�g����
	FADE_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFade(int type);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(FADE fade, E_STAGE next, int sno);
FADE GetFade(void);

