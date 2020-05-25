/**
* @file result.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT_OK		_T("data/TEXTURE/result/result_gameclear.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_NO		_T("data/TEXTURE/result/result_gameover.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_POS_X			(0)														//!< �|���S���̕\���ʒuX
#define	RESULT_POS_Y			(0)														//!< �|���S���̕\���ʒuY
#define	RESULT_SIZE_X			(SCREEN_W)												//!< �|���S���̕�
#define	RESULT_SIZE_Y			(SCREEN_H)												//!< �|���S���̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Result�������֐� InitResult
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitResult(int type);

/**
* @brief Result�J���֐� UninitResult
*/
void UninitResult(void);

/**
* @brief Result�X�V�֐� UpdateResult
*/
void UpdateResult(void);

/**
* @brief Result�`��֐� DrawResult
* @param[in] type �`��^�C�v
*/
void DrawResult(int type);

