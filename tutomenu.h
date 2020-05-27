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
#define TEXTURE_TUTOMENU_SIZE_X		(200)										//!< �|���S���̕�
#define TEXTURE_TUTOMENU_SIZE_Y		(100)										//!< �|���S���̍���
#define	TUTOMENUMAX					(2)											//!< �`���[�g���A�����j���[�\���̉�ʂ̑I������

/**
*�@@struct TUTOMENU
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;									//!< �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];								//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;												//!< �|���S���̍��W
	bool					use;												//!< �g�p���Ă��邩�ǂ���
}TUTOMENU;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Tutomenu�������֐� InitTutomenu
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitTutomenu(int type);
/**
* @brief Tutomenu�ď������֐� ReInitTutomenu
*/
void ReInitTutomenu(void);
/**
* @brief Tutomenu�J���֐� UninitTutomenu
*/
void UninitTutomenu(void);
/**
* @brief Tutomenu�X�V�֐� UpdateTutomenu
*/
void UpdateTutomenu(void);
/**
* @brief Tutomenu�X�V�֐� UpdateInTutomenu
*/
void UpdateInTutomenu(void);
/**
* @brief Tutomenu�`��֐� DrawTutomenu
*/
void DrawTutomenu(void);
/**
* @brief Tutomenu�擾�֐� GetTutomenu
* @return TUTOMENU
*/
TUTOMENU *GetTutomenu(void);
