#ifndef HITMAN_BOXER_HPP
#define HITMAN_BOXER_HPP

#include "animation_clip.hpp"
#include <array>
#include <memory>
#include <string>
#include <unordered_map>

struct HitmanAnimationDescriptor {
    const char* id;
    const char* texturePath;
    unsigned int frames;
    float frameTime;
};

class HitmanBoxer {
public:
    bool load();
    AnimationClip* clip(const std::string& id);
    const AnimationClip* clip(const std::string& id) const;

private:
    bool loadClip(const HitmanAnimationDescriptor& descriptor);

    std::unordered_map<std::string, std::unique_ptr<AnimationClip>> clips_;
};

inline bool HitmanBoxer::load()
{
    static constexpr std::array<HitmanAnimationDescriptor, 22> descriptors = {
        HitmanAnimationDescriptor{"back-dash", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/back-dash.png", 3, 0.08f},
        HitmanAnimationDescriptor{"back-walk", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/back-walk.png", 8, 0.08f},
        HitmanAnimationDescriptor{"block", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/block.png", 2, 0.08f},
        HitmanAnimationDescriptor{"cross", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/cross.png", 5, 0.08f},
        HitmanAnimationDescriptor{"damage-1", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/damage-1.png", 3, 0.08f},
        HitmanAnimationDescriptor{"damage-2", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/damage-2.png", 3, 0.08f},
        HitmanAnimationDescriptor{"damage-3", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/damage-3.png", 3, 0.08f},
        HitmanAnimationDescriptor{"dodge-1", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/dodge-1.png", 4, 0.08f},
        HitmanAnimationDescriptor{"dodge-2", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/dodge-2.png", 4, 0.08f},
        HitmanAnimationDescriptor{"flicker-jab1", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/flicker-jab1.png", 4, 0.06f},
        HitmanAnimationDescriptor{"flicker-jab2", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/flicker-jab2.png", 4, 0.06f},
        HitmanAnimationDescriptor{"forward-dash", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/forward-dash.png", 3, 0.08f},
        HitmanAnimationDescriptor{"forward-walk", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/forward-walk.png", 8, 0.08f},
        HitmanAnimationDescriptor{"hook", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/hook.png", 5, 0.08f},
        HitmanAnimationDescriptor{"idle", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/idle.png", 6, 0.1f},
        HitmanAnimationDescriptor{"knockdown", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/knockdown.png", 7, 0.1f},
        HitmanAnimationDescriptor{"knockout", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/knockout.png", 5, 0.1f},
        HitmanAnimationDescriptor{"overhand", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/overhand.png", 5, 0.08f},
        HitmanAnimationDescriptor{"parry-1", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/parry-1.png", 2, 0.08f},
        HitmanAnimationDescriptor{"parry-2", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/parry-2.png", 2, 0.08f},
        HitmanAnimationDescriptor{"uppercut", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/uppercut.png", 5, 0.08f},
        HitmanAnimationDescriptor{"win", "assets/Pixel Art Hitman Stance Boxer Character - v1.1/charater/Separate Animations/win.png", 4, 0.08f}
    };

    clips_.clear();
    for (const auto& descriptor : descriptors)
    {
        if (!loadClip(descriptor))
        {
            clips_.clear();
            return false;
        }
    }

    return true;
}

inline AnimationClip* HitmanBoxer::clip(const std::string& id)
{
    auto it = clips_.find(id);
    if (it == clips_.end())
    {
        return nullptr;
    }
    return it->second.get();
}

inline const AnimationClip* HitmanBoxer::clip(const std::string& id) const
{
    auto it = clips_.find(id);
    if (it == clips_.end())
    {
        return nullptr;
    }
    return it->second.get();
}

inline bool HitmanBoxer::loadClip(const HitmanAnimationDescriptor& descriptor)
{
    auto clipPtr = std::make_unique<AnimationClip>();
    if (!clipPtr->load(descriptor.texturePath, descriptor.frames))
    {
        return false;
    }
    clipPtr->setFrameTime(descriptor.frameTime);
    clips_.emplace(descriptor.id, std::move(clipPtr));
    return true;
}

#endif // HITMAN_BOXER_HPP
