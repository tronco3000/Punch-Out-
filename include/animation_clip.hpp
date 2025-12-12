#ifndef ANIMATION_CLIP_HPP
#define ANIMATION_CLIP_HPP

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <string>
#include <vector>

// Simple helper to play horizontal sprite-sheet clips.
class AnimationClip {
public:
    bool load(const std::string& texturePath, unsigned int frameCount);

    void start(bool loop = false);
    void stop();
    void update(float deltaSeconds);

    bool isPlaying() const { return playing_; }
    bool hasFinished() const { return finished_; }

    void setFrameTime(float secondsPerFrame) { frameDuration_ = secondsPerFrame; }

    void setPosition(float x, float y) { sprite_.setPosition(x, y); }
    void setScale(float x, float y) { sprite_.setScale(x, y); }
    void setOrigin(float x, float y) { sprite_.setOrigin(x, y); }

    sf::Sprite& sprite() { return sprite_; }
    const sf::Sprite& sprite() const { return sprite_; }

private:
    void applyFrame();

    sf::Texture texture_;
    sf::Sprite sprite_;
    std::vector<sf::IntRect> frames_;
    float frameDuration_ = 0.08f;
    float accumulator_ = 0.0f;
    std::size_t frameIndex_ = 0;
    bool playing_ = false;
    bool loop_ = false;
    bool finished_ = false;
};

inline bool AnimationClip::load(const std::string& texturePath, unsigned int frameCount)
{
    if (frameCount == 0)
    {
        return false;
    }

    if (!texture_.loadFromFile(texturePath))
    {
        return false;
    }

    const sf::Vector2u size = texture_.getSize();
    if (size.x == 0 || size.y == 0 || size.x % frameCount != 0)
    {
        return false;
    }

    const unsigned int frameWidth = size.x / frameCount;
    frames_.clear();
    frames_.reserve(frameCount);
    for (unsigned int i = 0; i < frameCount; ++i)
    {
        frames_.emplace_back(static_cast<int>(i * frameWidth), 0, static_cast<int>(frameWidth), static_cast<int>(size.y));
    }

    sprite_.setTexture(texture_);
    frameIndex_ = 0;
    accumulator_ = 0.0f;
    playing_ = false;
    finished_ = false;
    applyFrame();

    return true;
}

inline void AnimationClip::start(bool loop)
{
    if (frames_.empty())
    {
        return;
    }

    loop_ = loop;
    playing_ = true;
    finished_ = false;
    accumulator_ = 0.0f;
    frameIndex_ = 0;
    applyFrame();
}

inline void AnimationClip::stop()
{
    playing_ = false;
    finished_ = true;
}

inline void AnimationClip::update(float deltaSeconds)
{
    if (!playing_ || frames_.size() <= 1)
    {
        return;
    }

    accumulator_ += deltaSeconds;
    while (accumulator_ >= frameDuration_ && playing_)
    {
        accumulator_ -= frameDuration_;
        ++frameIndex_;

        if (frameIndex_ >= frames_.size())
        {
            if (loop_)
            {
                frameIndex_ = 0;
            }
            else
            {
                frameIndex_ = frames_.size() - 1;
                playing_ = false;
                finished_ = true;
            }
        }

        applyFrame();
    }
}

inline void AnimationClip::applyFrame()
{
    if (!frames_.empty())
    {
        sprite_.setTextureRect(frames_[frameIndex_]);
    }
}

#endif // ANIMATION_CLIP_HPP
