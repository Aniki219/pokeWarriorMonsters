#include "_Headers/Sprite.h"

Sprite::Sprite() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Sprite::~Sprite() {
	free();
}

void Sprite::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

int Sprite::getWidth() {
	return mWidth;
}

int Sprite::getHeight() {
	return mHeight;
}

void Sprite::render(int x, int y, SDL_Rect* clip) {
	int camx = Game::Instance()->camera->getX();
	int camy = Game::Instance()->camera->getY();
	SDL_Rect destRect = { x + imageOffset->x - camx, y + imageOffset->y - camy, clip->w, clip->h };

	if (currentAnimation != NULL) {
		if (animSpeed != 0 && Game::Instance()->frame % animSpeed == 0) {
			animFrame++;
		}
		if (animFrame >= currentAnimation->numFrames) {
			animFrame = 0;
		}
		clip->x = animFrame * clip->w;
		clip->y = currentAnimation->rowNum * clip->h;
	}
	else if (srcRect != nullptr) {
		clip->x = srcRect->x;
		clip->y = srcRect->y;
	}

	//std::cout << mTexture << std::endl;
	SDL_RenderCopy(Game::Instance()->getRenderer(), mTexture, clip, &destRect);
	delete clip;
}

std::string Sprite::getCurrentAnimation() {
	std::cout << "hello" << std::endl;
	return currentAnimation->name;
}

void Sprite::setAnimation(std::string animName) {
	currentAnimation = animations[animName];
}

void Sprite::setTexture(std::string name) {
	mTexture = TextureManager::Instance()->getTexture(name);
}

void Sprite::createAnimation(std::string animName, int rowNumber, int numberOfFrames, int startFrame) {
	animations[animName] = new Animation(animName, rowNumber, numberOfFrames, startFrame);
}