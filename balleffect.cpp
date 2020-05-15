//=============================================================================
//
// �G�t�F�N�g���� [balleffect.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "ball.h"
#include "balleffect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define EMISSION_FULL 0
#define EMISSION_RATE 1

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBalleffect(int i);
void SetTextureBalleffect(int i, int n, int cntPattern);
void SetVertexBalleffect(int i, int n);
void ResetParticle(int i, int n);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureBalleffectType0 = NULL;		// �e�N�X�`���ւ̃|���S��
static LPDIRECT3DTEXTURE9		g_pD3DTextureBalleffectType1 = NULL;		// �e�N�X�`���ւ̃|���S��

static BALLEFFECT					balleffectWk[BALLEFFECT_NUM_BALLEFFECTS];	// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBalleffect(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			BALLEFFECT_TEXTURETYPE0,										// �t�@�C���̖��O
			&g_pD3DTextureBalleffectType0);								// �ǂݍ��ރ������̃|�C���^
				// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			BALLEFFECT_TEXTURETYPE1,										// �t�@�C���̖��O
			&g_pD3DTextureBalleffectType1);								// �ǂݍ��ރ������̃|�C���^
	}

	// ����������
	for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
	{
		balleffectWk[i].use = false;
		balleffectWk[i].elapsed = 0;

		MakeVertexBalleffect(i);										// ���_���̍쐬

		for (int n = 0; n < BALLEFFECT_NUM_PARTS; n++)
		{
			balleffectWk[i].pParticle[n].Texture = g_pD3DTextureBalleffectType0;
			ResetParticle(i, n);
		}
	}

	return S_OK;
}

//=============================================================================
// �p�[�e�B�N���̃��Z�b�g
//=============================================================================
void ResetParticle(int i, int n)
{
	balleffectWk[i].pParticle[n].pos = D3DXVECTOR3(balleffectWk[i].pos.x + rand() % 30 - 15, balleffectWk[i].pos.y + rand() % 30 - 15, 0.0f);	// ���W�f�[�^��������
	balleffectWk[i].pParticle[n].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ���

	balleffectWk[i].pParticle[n].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
	balleffectWk[i].pParticle[n].CountAnim = 0;										// �A�j���J�E���g��������
	balleffectWk[i].pParticle[n].liveTime = 10;
	balleffectWk[i].pParticle[n].isFinish = 0;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBalleffect(void)
{
	if (g_pD3DTextureBalleffectType0 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBalleffectType0->Release();
		g_pD3DTextureBalleffectType0 = NULL;
	}
	if (g_pD3DTextureBalleffectType1 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBalleffectType1->Release();
		g_pD3DTextureBalleffectType1 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBalleffect(void)
{
	for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
	{
		if (balleffectWk[i].use)
		{
			if (balleffectWk[i].isEnding) {
				balleffectWk[i].use = FALSE;
				continue;
			}

			//�G�~�b�g���L���ł���΃G�t�F�N�g�쐬�������s��
			if (balleffectWk[i].isRemoveOnFinish == FALSE)
			{

				//�G�t�F�N�g�쐬���[�g�̑�������
				if (balleffectWk[i].balleffectCount < BALLEFFECT_NUM_PARTS)
					balleffectWk[i].emitCounter++;

				//�o�b�t�@�ɋ󂫂�����A�ǉ��^�C�~���O�����Ă���ΐV���ȃG�t�F�N�g��ǉ�����
				while ((balleffectWk[i].balleffectCount < BALLEFFECT_NUM_PARTS) && (balleffectWk[i].emitCounter > EMISSION_RATE))
				{
					//�S�̒ǉ��t���O��ON�ł���΋󂫗̈�S�ĂɐV���ȃG�t�F�N�g��ǉ�����
					if (EMISSION_FULL)
						balleffectWk[i].balleffectCount = BALLEFFECT_NUM_PARTS;
					else
						balleffectWk[i].balleffectCount++;

					//�G�t�F�N�g�쐬���[�g�̏�����
					balleffectWk[i].emitCounter = 0;
				}

				balleffectWk[i].elapsed++;

				//���Ԓ���
				if ((balleffectWk[i].duration != -1) && (balleffectWk[i].duration < balleffectWk[i].elapsed)) {
					balleffectWk[i].isRemoveOnFinish = TRUE;
				}
			}

			int balleffectIndex = 0;

			//�G�t�F�N�g�̍X�V����
			while (balleffectIndex < balleffectWk[i].balleffectCount)
			{
				if (balleffectWk[i].pParticle[balleffectIndex].liveTime > 0)
				{
					//�����t���[������
					balleffectWk[i].pParticle[balleffectIndex].liveTime--;

					//�A�j���p�^�[���i�s
					if (++balleffectWk[i].pParticle[balleffectIndex].CountAnim > BALLEFFECT_TIME_ANIMATION) {
						//�A�j���p�^�[�����ő�l�ɒB�����ꍇ�ł��I��
						if (++balleffectWk[i].pParticle[balleffectIndex].PatternAnim >= (BALLEFFECT_ANIM_PATTERN_NUM - 1))
						{
							balleffectWk[i].pParticle[balleffectIndex].PatternAnim = BALLEFFECT_ANIM_PATTERN_NUM - 1;
							balleffectWk[i].pParticle[balleffectIndex].liveTime = 0;
						}

						balleffectWk[i].pParticle[balleffectIndex].CountAnim = 0;
					}

					SetTextureBalleffect(i, balleffectIndex, balleffectWk[i].pParticle[balleffectIndex].PatternAnim);

					SetVertexBalleffect(i, balleffectIndex);						// �ړ���̍��W�Œ��_��ݒ�

					balleffectIndex++;
				}
				else {
					if (balleffectWk[i].isRemoveOnFinish) {
						if (balleffectWk[i].pParticle[balleffectIndex].isFinish == 0)
						{
							balleffectWk[i].pParticle[balleffectIndex].isFinish = 1;
							balleffectWk[i].numFinish++;
						}
						//�I������
						if (balleffectWk[i].pParticle[balleffectIndex].pos.x <= SCREEN_W - SCREEN_W || balleffectWk[i].pParticle[balleffectIndex].pos.x >= SCREEN_W ||
							balleffectWk[i].pParticle[balleffectIndex].pos.y <= SCREEN_H - SCREEN_H || balleffectWk[i].pParticle[balleffectIndex].pos.y >= SCREEN_H)
						{
							balleffectWk[i].isEnding = TRUE;
							break;
						}
						if (balleffectWk[i].numFinish == balleffectWk[i].balleffectCount)
						{
							balleffectWk[i].isEnding = TRUE;
							break;
						}
						balleffectIndex++;
					}
					else {
						//�o�b�t�@������������
						ResetParticle(i, balleffectIndex);

						//�����łȂ���΃C���f�b�N�X���l�߂�
						if (balleffectIndex != (balleffectWk[i].balleffectCount - 1))
						{
							balleffectWk[i].pParticle[balleffectIndex] = balleffectWk[i].pParticle[balleffectWk[i].balleffectCount - 1];
							ResetParticle(i, (balleffectWk[i].balleffectCount - 1));
						}
						balleffectWk[i].balleffectCount--;
					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBalleffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (GetBall()->effect==false)
	{
		for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
		{
			if (balleffectWk[i].use)
			{
				for (int n = 0; n < balleffectWk[i].balleffectCount; n++)
				{
					if (balleffectWk[i].pParticle[n].isFinish == 0) {
						// �e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, balleffectWk[i].pParticle[n].Texture);
						// �|���S���̕`��
						pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, balleffectWk[i].pParticle[n].vertexWk, sizeof(VERTEX_2D));
					}
				}
			}
		}
	}
	else if (GetBall()->effect == true)
	{
		for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
		{
			if (balleffectWk[i].use)
			{
				for (int n = 0; n < balleffectWk[i].balleffectCount; n++)
				{
					if (balleffectWk[i].pParticle[n].isFinish == 0) {
						// �e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, g_pD3DTextureBalleffectType1);
						// �|���S���̕`��
						pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, balleffectWk[i].pParticle[n].vertexWk, sizeof(VERTEX_2D));
					}
				}
			}
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBalleffect(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int n = 0; n < BALLEFFECT_NUM_PARTS; n++) {

		// ���_���W�̐ݒ�
		SetVertexBalleffect(i, n);
		// ���_���W�̐ݒ�
		SetTextureBalleffect(i, n, 0);

		// rhw�̐ݒ�
		balleffectWk[i].pParticle[n].vertexWk[0].rhw =
			balleffectWk[i].pParticle[n].vertexWk[1].rhw =
			balleffectWk[i].pParticle[n].vertexWk[2].rhw =
			balleffectWk[i].pParticle[n].vertexWk[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		balleffectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		balleffectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		balleffectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		balleffectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBalleffect(int i, int n, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / BALLEFFECT_TEXTURE_PATTERN_DIVIDE_Y;

	balleffectWk[i].pParticle[n].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	balleffectWk[i].pParticle[n].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	balleffectWk[i].pParticle[n].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	balleffectWk[i].pParticle[n].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBalleffect(int i, int n)
{
	// ���_���W�̐ݒ�
	balleffectWk[i].pParticle[n].vertexWk[0].vtx.x = balleffectWk[i].pParticle[n].pos.x - BALLEFFECT_TEXTURE_SIZE_X;
	balleffectWk[i].pParticle[n].vertexWk[0].vtx.y = balleffectWk[i].pParticle[n].pos.y - BALLEFFECT_TEXTURE_SIZE_Y;
	balleffectWk[i].pParticle[n].vertexWk[0].vtx.z = 0.0f;

	balleffectWk[i].pParticle[n].vertexWk[1].vtx.x = balleffectWk[i].pParticle[n].pos.x + BALLEFFECT_TEXTURE_SIZE_X;
	balleffectWk[i].pParticle[n].vertexWk[1].vtx.y = balleffectWk[i].pParticle[n].pos.y - BALLEFFECT_TEXTURE_SIZE_Y;
	balleffectWk[i].pParticle[n].vertexWk[1].vtx.z = 0.0f;

	balleffectWk[i].pParticle[n].vertexWk[2].vtx.x = balleffectWk[i].pParticle[n].pos.x - BALLEFFECT_TEXTURE_SIZE_X;
	balleffectWk[i].pParticle[n].vertexWk[2].vtx.y = balleffectWk[i].pParticle[n].pos.y + BALLEFFECT_TEXTURE_SIZE_Y;
	balleffectWk[i].pParticle[n].vertexWk[2].vtx.z = 0.0f;

	balleffectWk[i].pParticle[n].vertexWk[3].vtx.x = balleffectWk[i].pParticle[n].pos.x + BALLEFFECT_TEXTURE_SIZE_X;
	balleffectWk[i].pParticle[n].vertexWk[3].vtx.y = balleffectWk[i].pParticle[n].pos.y + BALLEFFECT_TEXTURE_SIZE_Y;
	balleffectWk[i].pParticle[n].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�t�F�N�g�̃Z�b�g
//=============================================================================
void SetBalleffect(D3DXVECTOR3 pos, int duration)
{
	// �������g�p�̃G�t�F�N�g��������������s���Ȃ�( =����ȏ�\���ł��Ȃ����Ď� )
	for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
	{
		if (balleffectWk[i].use == false)		// ���g�p��Ԃ̃G�t�F�N�g��������
		{
			balleffectWk[i].use = true;
			balleffectWk[i].isEnding = false;
			balleffectWk[i].isRemoveOnFinish = FALSE;

			balleffectWk[i].duration = duration;
			balleffectWk[i].pos.x = pos.x;			// ���W���Z�b�g
			balleffectWk[i].pos.y = pos.y;			// ���W���Z�b�g

			balleffectWk[i].balleffectCount = 0;
			balleffectWk[i].elapsed = 0;
			balleffectWk[i].emitCounter = 0;
			balleffectWk[i].numFinish = 0;

			//�p�[�e�B�N���̏�����
			for (int n = 0; n < BALLEFFECT_NUM_PARTS; n++)
			{
				ResetParticle(i, n);
			}
			return;							// 1�Z�b�g�����̂ŏI������
		}
	}
}
