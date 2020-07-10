/**
* @file player.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once


//*****************************************************************************
//* �\���̒�`
//******************************************************************************* /
/**
*�@@struct PLAYER_PIT
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	CHARACTER pp;			//!< �v���C���[�s�b�`���[
} PLAYER_PIT;

/**
*�@@struct PLAYER_BAT
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	CHARACTER pb;			//!< �v���C���[�o�b�^�[
} PLAYER_BAT;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Player�������֐� InitPlayer
* @param[in] type �������^�C�v�@INIT_TIME���p�B0:����@0�ȊO: 2��ڈȍ~
* @return HRESULT
*/
HRESULT InitPlayer(int type);

/**
* @brief Player�ď������֐� ReInitPlayer
* @details �Q�[�����[�v��̏������ȂǂŎg�p�B���d�Ńe�N�X�`�����̓ǂݍ��݂�h�����߂��̊֐��ŏ��������Ă���
*/
void ReInitPlayer(void);

/**
* @brief Player�J���֐� UninitPlayer
*/
void UninitPlayer(void);

/**
* @brief Player�X�V�֐� UpdatePlayer
*/
void UpdatePlayer(void);

/**
* @brief Player�`��֐� DrawPlayer
*/
void DrawPlayer(void);

/**
* @brief PlayerPit�擾�֐� GetPlayerPit
* @return PLAYER_PIT
*/
PLAYER_PIT *GetPlayerPit(void);

/**
* @brief PlayerBat�擾�֐� GetPlayerBat
* @return PLAYER_BAT
*/
PLAYER_BAT *GetPlayerBat(void);

/**
* @brief �e�N�X�`���ݒ�֐� SetTexturePlayer
* @param[in] int cntPattern �A�j���p�^�[��, int PLYAER_TYPE �v���C���[�^�C�v
*/
void SetTexturePlayer(int cntPattern, int PLYAER_TYPE);

/**
* @brief �|���S�����_�ݒ�֐� SetVertexPlayer
* @param[in] int PLYAER_TYPE �v���C���[�^�C�v
*/
void SetVertexPlayer(int PLYAER_TYPE);
