/**
* @file register.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define SAVE_TEXTURE_FILE_00		_T("data/TEXTURE/SAVE/save.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define SAVE_SIZE_W					(880)										//!< �e�N�X�`���T�C�YX
#define SAVE_SIZE_H					(660)										//!< �e�N�X�`���T�C�YY
#define SAVE_POS_X					(0)											//!< �|���S���̏����ʒuX
#define SAVE_POS_Y					(0)											//!< �|���S���̏����ʒuY

/*******************************************************************************
* �\���̒�`
*******************************************************************************/
/**
*�@@struct SAVEDATA
*�@@brief 2D�|���S�����`����\����
*/
typedef struct					// �Z�[�u�f�[�^�̍\����
{
	int ftime;																	//!< �^�C���̕ۑ�
	int fscore;																	//!< �X�R�A�̕ۑ�
} SAVEDATA;

/**
*�@@struct SAVE
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;									//!< �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];								//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;												//!< �w�i�̈ʒu
}SAVE;

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
/**
* @brief Save�������֐� InitSave
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitSave(int type);

/**
* @brief Save�J���֐� UninitSave
*/
void UninitSave(void);

/**
* @brief Save�X�V�֐� UpdateSave
*/
void UpdateSave(void);

/**
* @brief Save�`��֐� DrawSave
*/
void DrawSave(void);

/**
* @brief Save�J���֐� SaveData
* @details �Z�[�u�f�[�^���쐬���A�t�@�C���֏o�͂���
*/
void SaveData(void);

/**
* @brief Save�J���֐� LoadData
* @details �Z�[�u�f�[�^���t�@�C������ǂݍ���
*/
void LoadData(void);
