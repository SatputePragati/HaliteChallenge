#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

//const double M_PI = 3.14;
namespace hlt {
    namespace util {
        static int angle_rad_to_deg_clipped(const double angle_rad) {
            const long deg_unclipped = lround(angle_rad * 180.0 / M_PI);
            // Make sure return value is in [0, 360) as required by game engine.
            return static_cast<int>(((deg_unclipped % 360L) + 360L) % 360L);
        }
    }
}
