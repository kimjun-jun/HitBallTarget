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
#define	TEXTURE_EASY		_T("data/TEXTURE/sozai/select/easy.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_EASY_SIZE_X		(200)										// �^�C�g�����S�̕�
#define TEXTURE_EASY_SIZE_Y		(100)										// �^�C�g�����S�̍���

#define	TEXTURE_NORMAL		_T("data/TEXTURE/sozai/select/normal.png")		
#define	TEXTURE_HARD		_T("data/TEXTURE/sozai/select/hard.png")			
#define	TEXTURE_LEVEL		_T("data/TEXTURE/sozai/level.png")			
#define	TEXTURE_RANKING 		_T("data/TEXTURE/sozai/select/ranking.png")		


#define EASY_POS_Y					(SCREEN_H-650)		// �|���S���̏����ʒuX
#define NORMAL_POS_Y				(SCREEN_H-400)		// �|���S���̏����ʒuX
#define HRAD_POS_Y					(SCREEN_H-150)		// �|���S���̏����ʒuX
#define LEVEL_POS_Y					(SCREEN_H-850)		// �|���S���̏����ʒuX


#define EASY_POS_X					(SCREEN_W-900)		// ����
#define LEVEL_POS_X					(SCREEN_W-1000)		// �|���S���̏����ʒuX


#define	TEXTURE_ENTER		_T("data/TEXTURE/sozai/enterstart.png")			
#define	TEXTURE_ENTER_SIZE_X		(300)					
#define	TEXTURE_ENTER_SIZE_Y		(200)					
#define ENTERorSTART_POS_Y			(SCREEN_H-400)		// �|���S���̏����ʒuX
#define ENTERorSTART_POS_X			(SCREEN_W-350)		// ����


#define	SMAX		(5)													//�I�����̐�

/**
*�@@struct TITLE
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N

	D3DXVECTOR3				pos;						// ?���S���̈ړ���
}SELECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief R18�������֐� InitR18select
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitSelect(int type);
/**
* @brief R18�J���֐� UninitR18select
*/
void UninitSelect(void);
/**
* @brief R18�X�V�֐� UpdateR18select
*/
void UpdateSelect(void);
/**
* @brief R18�`��֐� DrawR18select
*/
void DrawSelect(void);
void SetTextureSelect(void);
void SetVertexSelect(void);
/**
* @brief R18�擾�֐� GetR18select
*/
int GetSpos(void);
