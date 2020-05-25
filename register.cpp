/**
* @file register.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "score.h"
#include "register.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief ���_�����֐� MakeVertexSave
* @return HRESULT
*/
HRESULT MakeVertexSave(void);

/**
* @brief ���_�ݒ�֐� SetVertexSave
*/
void SetVertexSave(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
SAVEDATA g_savedate;				//!< �Z�[�u�f�[�^
SAVE g_save;						//!< �Z�[�u�|���S��

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSave(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			SAVE_TEXTURE_FILE_00,		// �t�@�C���̖��O
			&g_save.pD3DTexture);		// �ǂݍ��ރ������[
	}
	g_save.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ���_���̍쐬
	MakeVertexSave();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSave(void)
{
	if (g_save.pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_save.pD3DTexture->Release();
		g_save.pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSave(void)
{
	SaveData();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSave(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_save.pD3DTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_save.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSave(void)
{
	// ���_���W�̐ݒ�
	SetVertexSave();

	// rhw�̐ݒ�
	g_save.vertexWk[0].rhw =
		g_save.vertexWk[1].rhw =
		g_save.vertexWk[2].rhw =
		g_save.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_save.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_save.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_save.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_save.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_save.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_save.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_save.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_save.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexSave(void)
{
	// ���_���W�̐ݒ�
	g_save.vertexWk[0].vtx = D3DXVECTOR3(SAVE_POS_X, SAVE_POS_Y, 0.0f);
	g_save.vertexWk[1].vtx = D3DXVECTOR3(SAVE_POS_X + SAVE_SIZE_W, SAVE_POS_Y, 0.0f);
	g_save.vertexWk[2].vtx = D3DXVECTOR3(SAVE_POS_X, SAVE_POS_Y + SAVE_SIZE_H, 0.0f);
	g_save.vertexWk[3].vtx = D3DXVECTOR3(SAVE_POS_X + SAVE_SIZE_W, SAVE_POS_Y + SAVE_SIZE_H, 0.0f);
}

/*******************************************************************************
�֐���:	void SaveData( void )
����:	void
�߂�l:	void
����:	�Z�[�u�f�[�^���쐬���A�t�@�C���֏o�͂���
*******************************************************************************/
void SaveData(void)
{
	int *time = GetTimemaneger();
	int *score = GetScoremaneger();
	g_savedate.ftime = *time;
	g_savedate.fscore = *score;
	char str[256] = { 0 };

	// SAVEDATA�\���̂��ƑS�����t�@�C���ɏo�͂���
	FILE* fp;
#ifdef _DEBUG
	sprintf(str, "�Z�[�u�J�n");
	SelectText(str);
#endif			
	fp = fopen("savedata.text", "wb");			// �t�@�C�����o�C�i���������݃��[�h��Open����
	if (fp != NULL)								// �t�@�C��������Ώ������݁A������Ζ���
	{
		fwrite(&g_savedate, 1, sizeof(SAVEDATA), fp);	// �w�肵���A�h���X����w�肵���o�C�g�����t�@�C���֏�������
		fclose(fp);								// Open���Ă����t�@�C�������
#ifdef _DEBUG
		sprintf(str, "�Z�[�u����");
		SelectText(str);
#endif			
	}
	else
	{
#ifdef _DEBUG
		sprintf(str, "�Z�[�u�G���[");
		SelectText(str);
#endif			
	}
	rewind(stdin);
	getchar();
}

/*******************************************************************************
�֐���:	void LoadData( void )
����:	void
�߂�l:	void
����:	�Z�[�u�f�[�^���t�@�C������ǂݍ���
*******************************************************************************/
void LoadData(void)
{
	int *time = GetTimemaneger();
	int *score = GetScoremaneger();
	g_savedate.ftime = *time;
	g_savedate.fscore = *score;
	char str[256] = { 0 };

	// �t�@�C������Z�[�u�f�[�^��ǂݍ���
	FILE* fp;
#ifdef _DEBUG
	sprintf(str, "���[�h�J�n");
	SelectText(str);
#endif			
	fp = fopen("savedata.text", "rb");			// �t�@�C�����o�C�i���ǂݍ��݃��[�h��Open����
	if (fp != NULL)								// �t�@�C��������Ώ������݁A������Ζ���
	{
		fread(&g_savedate, 1, sizeof(SAVEDATA), fp);	// �w�肵���A�h���X�֎w�肵���o�C�g�����t�@�C������ǂݍ���
		fclose(fp);								// Open���Ă����t�@�C�������
#ifdef _DEBUG
		sprintf(str, "���[�h�I��");
		SelectText(str);
#endif			
	}
	else
	{
#ifdef _DEBUG
		sprintf(str, "���[�h�G���[");
		SelectText(str);
#endif			
	}

	*time = g_savedate.ftime;					// �t�@�C������ǂݍ��񂾃f�[�^�����݂̃��[�N�֖߂�
	*score = g_savedate.fscore;					// �t�@�C������ǂݍ��񂾃f�[�^�����݂̃��[�N�֖߂�
	rewind(stdin);
	getchar();
}

