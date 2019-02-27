#pragma once

namespace Illusion
{
	class AnimationComponent
	{
	public:

		class Animation
		{
		public:
			Animation(sf::Sprite &sprite, sf::Texture &textureSheet,
				float animTimer, int startFrameX, int startFrameY, int framesX, int framesY,
				int width, int height)
				:sprite_(sprite), textureSheet_(textureSheet), animTimer_(animTimer),
				startFrameX_(startFrameX), startFrameY_(startFrameY), framesX_(framesX), framesY_(framesY),
				width_(width), height_(height)
			{
				this->timer_ = 0.0f;
				startRect_ = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
				currentRect_ = startRect_;
				endRect_ = sf::IntRect(framesX * width, framesY * height, width, height);

				sprite.setTexture(this->textureSheet_, true);
				sprite.setTextureRect(startRect_);
			}

			~Animation()
			{

			}

			bool play(const float &dt)
			{
				done_ = false;
				timer_ += 100.0f * dt;
				if (timer_ >= animTimer_)
				{
					timer_ = 0.0f;

					//animate
					/*if (currentRect.left != 7)
					{
						currentRect.left += width;
					}*/
					if (currentRect_ != endRect_)
					{
						currentRect_.left += width_;
					}
					else //reset
					{
						currentRect_.left = startRect_.left;
						done_ = true;
					}

					sprite_.setTextureRect(currentRect_);
				}
				return done_;
			}

			void reset()
			{
				timer_ = 0.0f;
				currentRect_ = startRect_;
			}

			const bool isDone()const { return done_; }

		private:
			sf::Sprite &sprite_;
			sf::Texture &textureSheet_;

		private:
			float animTimer_;
			float timer_;
			int width_, height_;
			int startFrameX_, startFrameY_;
			int framesX_, framesY_;
			bool done_;

			sf::IntRect startRect_, currentRect_, endRect_;
		};

		AnimationComponent(sf::Sprite &sprite, sf::Texture &textureSheet);
		~AnimationComponent();

	public:
		bool play(const std::string key, const float &dt, const bool priority);

		void addAnimation(const std::string key, float animTimer, 
			int startFrameX, int startFrameY, 
			int framesX, int framesY,
			int width, int height);
		void startAnimation(const std::string anim);


	public:
		const bool isDone(const std::string key);

	private:
		std::map<std::string, Animation*> animations_;
		Animation *lastAnimation_;
		Animation *priorityAnimation_;
		bool done;

		sf::Sprite &sprite_;
		sf::Texture &textureSheet_;

	};
}