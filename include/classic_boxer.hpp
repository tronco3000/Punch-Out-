#ifndef CLASSIC_BOXER_HPP
#define CLASSIC_BOXER_HPP

#include "animation_clip.hpp"
#include <array>
#include <memory>
#include <string>
#include <unordered_map>

struct AnimationDescriptor {
    const char* id;
    const char* texturePath;
    unsigned int frames;
    float frameTime;
};

class ClassicBoxer {
public:
    bool load();
    AnimationClip* clip(const std::string& id);
    const AnimationClip* clip(const std::string& id) const;

private:
    bool loadClip(const AnimationDescriptor& descriptor);

    std::unordered_map<std::string, std::unique_ptr<AnimationClip>> clips_;
};

inline bool ClassicBoxer::load()
{
    static constexpr std::array<AnimationDescriptor, 26> descriptors = {
        AnimationDescriptor{"back-dash", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/back-dash.png", 3, 0.08f},
        AnimationDescriptor{"back-walk", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/back-walk.png", 8, 0.08f},
        AnimationDescriptor{"block-hit", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/block-hit.png", 3, 0.07f},
        AnimationDescriptor{"block", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/block.png", 2, 0.08f},
        AnimationDescriptor{"body-hook", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/body-hook.png", 4, 0.08f},
        AnimationDescriptor{"cross", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/cross.png", 3, 0.08f},
        AnimationDescriptor{"damage-1", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/damage-1.png", 3, 0.08f},
        AnimationDescriptor{"damage-2", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/damage-2.png", 3, 0.08f},
        AnimationDescriptor{"damage-3", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/damage-3.png", 3, 0.08f},
        AnimationDescriptor{"dodge-1", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/dodge-1.png", 4, 0.08f},
        AnimationDescriptor{"dodge-2", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/dodge-2.png", 4, 0.08f},
        AnimationDescriptor{"forward-dash", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/forward-dash.png", 3, 0.08f},
        AnimationDescriptor{"forward-walk", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/forward-walk.png", 8, 0.08f},
        AnimationDescriptor{"hook", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/hook.png", 4, 0.08f},
        AnimationDescriptor{"idle", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/idle.png", 6, 0.08f},
        AnimationDescriptor{"jab", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/jab.png", 2, 0.06f},
        AnimationDescriptor{"knockdown", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/knockdown.png", 6, 0.1f},
        AnimationDescriptor{"knockout", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/knockout.png", 4, 0.1f},
        AnimationDescriptor{"overhand", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/overhand.png", 4, 0.08f},
        AnimationDescriptor{"parry-1", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/parry-1.png", 2, 0.08f},
        AnimationDescriptor{"parry-2", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/parry-2.png", 2, 0.08f},
        AnimationDescriptor{"pushups", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/pushups.png", 6, 0.1f},
        AnimationDescriptor{"skipping-rope", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/skipping-rope.png", 4, 0.1f},
        AnimationDescriptor{"stun", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/stun.png", 4, 0.08f},
        AnimationDescriptor{"uppercut", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/uppercut.png", 4, 0.08f},
        AnimationDescriptor{"win", "assets/Pixel Art Boxer Character Pack/character/Separate Animations/win.png", 4, 0.08f}
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

inline AnimationClip* ClassicBoxer::clip(const std::string& id)
{
    auto it = clips_.find(id);
    if (it == clips_.end())
    {
        return nullptr;
    }
    return it->second.get();
}

inline const AnimationClip* ClassicBoxer::clip(const std::string& id) const
{
    auto it = clips_.find(id);
    if (it == clips_.end())
    {
        return nullptr;
    }
    return it->second.get();
}

inline bool ClassicBoxer::loadClip(const AnimationDescriptor& descriptor)
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

#endif // CLASSIC_BOXER_HPP
