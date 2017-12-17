#include <cmath>

#include "location.h"

namespace hlt {
    std::ostream& operator<<(std::ostream& out, const Location& location) {
        out << '(' << location.pos_x << ", " << location.pos_y << ')';
        return out;
    }
}
