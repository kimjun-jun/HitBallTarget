/**
* @file select.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EASY				_T("data/TEXTURE/sozai/select/easy.png")	//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_NORMAL				_T("data/TEXTURE/sozai/select/normal.png")	//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_HARD				_T("data/TEXTURE/sozai/select/hard.png")	//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_LEVEL				_T("data/TEXTURE/sozai/level.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKING 			_T("data/TEXTURE/sozai/select/ranking.png")	//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ENTER				_T("data/TEXTURE/sozai/enterstart.png")		//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_EASY_SIZE_X			(200)										//!< �|���S���̕�	�S��Փx
#define TEXTURE_EASY_SIZE_Y			(100)										//!< �|���S���̍���	�S��Փx
#define	TEXTURE_ENTER_SIZE_X		(300)										//!< �|���S���̕�	�G���^�[
#define	TEXTURE_ENTER_SIZE_Y		(200)										//!< �|���S���̍���	�G���^�[
#define EASY_POS_Y					(SCREEN_H-650)								//!< �|���S���̏����ʒuY	�C�[�W�[
#define NORMAL_POS_Y				(SCREEN_H-400)								//!< �|���S���̏����ʒuY	�m�[�}��
#define HRAD_POS_Y					(SCREEN_H-150)								//!< �|���S���̏����ʒuY	�n�[�h
#define LEVEL_POS_Y					(SCREEN_H-850)								//!< �|���S���̏����ʒuY	���x��
#define EASY_POS_X					(SCREEN_W-900)								//!< �|���S���̏����ʒuX	�S��Փx
#define LEVEL_POS_X					(SCREEN_W-1000)								//!< �|���S���̏����ʒuX	���x��
#define ENTERorSTART_POS_Y			(SCREEN_H-400)								//!< �|���S���̏����ʒuY	�G���^�[
#define ENTERorSTART_POS_X			(SCREEN_W-350)								//!< �|���S���̏����ʒuX	�G���^�[
#define	SMAX						(5)											//!< �I�����̍\���̐�

/**
*�@@struct SELECT
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{																				//!< �e�N�X�`���ւ̃|�C���^ 
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;									//!< ���_���i�[���[�N
	VERTEX_2D				vertexWk[NUM_VERTEX];								//!< �|���S���̍��W
	D3DXVECTOR3				pos;						
}SELECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Select�������֐� InitSelect
* @param[in] type �������^�C�v�@INIT_TIME���p�B0:����@0�ȊO: 2��ڈȍ~
* @return HRESULT
*/
HRESULT InitSelect(int type);

/**
* @brief Select�J���֐� UninitSelect
*/
void UninitSelect(void);

/**
* @brief Select�X�V�֐� UpdateSelect
*/
void UpdateSelect(void);

/**
* @brief Select�`��֐� DrawSelect
*/
void DrawSelect(void);

/**
* @brief �Z���N�g���Ă����Փx(�l�R�̐�)�擾�֐� GetSpos
* @return int
*/
int GetSpos(void);
