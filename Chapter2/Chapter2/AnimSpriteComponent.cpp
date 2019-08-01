#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder) 
	:SpriteComponent(owner, drawOrder), 
	mCurrentFrame(0.0f),
	mAnimFPS(24.0f){

}

void AnimSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);
	
	int tex_num = 0;
	for (auto AnimTexture : mAnimTextures) {

		if (AnimTexture.size() > 0) {
			// �t���[�����[�g�ƃf���^�^�C���Ɋ�Â���
			// �J�����g�t���[�����X�V����
			mCurrentFrame[tex_num] += mAnimFPS * deltaTime;

			// �K�v�ɉ����ăJ�����g�t���[���������߂�
			while (mCurrentFrame[tex_num] >= AnimTexture.size()) {
				mCurrentFrame[tex_num] -= AnimTexture.size();
			}

			// �����_�ł̃e�N�X�`����ݒ肷��
			SetTexture(AnimTexture[static_cast<int>(mCurrentFrame[tex_num])]);
		}
		tex_num++;
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures) {
	mAnimTextures.emplace_back();
	for (auto texture : textures) {
		mAnimTextures.back().emplace_back(texture);
	}
	
	if (mAnimTextures.size() > 0) {
		// �A�N�e�B�u�ȃe�N�X�`�����ŏ��̃t���[���ɐݒ肷��
		mCurrentFrame.emplace_back(0.0f);
		SetTexture(mAnimTextures.back()[0]);
	}
}