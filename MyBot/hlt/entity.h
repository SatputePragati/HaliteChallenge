#pragma once

#include "location.h"
#include "types.h"

namespace hlt {
    struct Entity {
        EntityId entity_id;
        PlayerId owner_id;
        Location location;
        int health;
        double radius;

        bool is_alive() const {
            return health > 0;
        }
    };
}
