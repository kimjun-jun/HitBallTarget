/**
* @file tutomenu.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_TUTOMENU_SIZE_X		(200)										// �^�C�g�����S�̕�
#define TEXTURE_TUTOMENU_SIZE_Y		(100)										// �^�C�g�����S�̍���


#define	TUTOMENUMAX		(2)						//�|�[�Y��ʂ̑I������

/**
*�@@struct TITLE
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;									//!< �e�N�X�`���ւ̃|���S��
	VERTEX_2D				vertexWk[NUM_VERTEX];								//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;												
	bool					use;
}TUTOMENU;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief R18�������֐� InitR18select
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitTutomenu(int type);
/**
* @brief R18�ď������֐� ReInitR18select
*/
void ReInitTutomenu(void);
/**
* @brief R18�J���֐� UninitR18select
*/
void UninitTutomenu(void);
/**
* @brief R18�X�V�֐� UpdateR18select
*/
void UpdateTutomenu(void);
/**
* @brief R18�X�V�֐� UpdateR18select
*/
void UpdateInTutomenu(void);
/**
* @brief R18�`��֐� DrawR18select
*/
void DrawTutomenu(void);
void SetVertexTutomenu(void);
/**
* @brief R18�擾�֐� GetR18select
*/
TUTOMENU *GetTutomenu(void);
