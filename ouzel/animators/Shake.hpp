// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <cstdint>
#include <vector>
#include "animators/Animator.hpp"
#include "math/Vector3.hpp"

namespace ouzel
{
    namespace scene
    {
        class Shake: public Animator
        {
        public:
            Shake(float initLength, const Vector3& initDistance, float initTimeScale);

            void play() override;

        protected:
            virtual void updateProgress() override;

            uint32_t seedX;
            uint32_t seedY;
            uint32_t seedZ;
            Vector3 distance;
            float timeScale;
            Vector3 startPosition;
        };
    } // namespace scene
} // namespace ouzel
