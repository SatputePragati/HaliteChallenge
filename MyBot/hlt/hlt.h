#pragma once
#include "log.h"
#include "hlt_in.h"
#include "hlt_out.h"
#include <chrono> 
#include<map>
#include<algorithm>


namespace hlt {
    struct Metadata {
        const PlayerId player_id;
        const Map initial_map;
    };

	bool sort_by_size(Planet p1, Planet p2) {
		return p1.radius < p2.radius;
	}

    /// Initialize our bot with the given name, getting back some metadata.
    static Metadata initialize(const std::string& bot_name) {

        std::cout.sync_with_stdio(true);

        std::stringstream iss1(in::get_string());
        int player_id;
        iss1 >> player_id;

        std::stringstream iss2(in::get_string());
        int map_width;
        int map_height;
        iss2 >> map_width >> map_height;

        Log::open(std::to_string(player_id) + "_" + bot_name + ".log");

        in::setup(bot_name, map_width, map_height);

			//Get initial map
			Map initial_map = hlt::in::get_map();

			//get planets sorted by size
			std::sort(initial_map.planets.begin(), initial_map.planets.end(), sort_by_size);
			std::map<unsigned, unsigned> Planet_Value_Map;//<PlanetID,Value>
			for (unsigned i = 0;i < initial_map.planets.size(); ++i) {
				Planet_Value_Map.insert({ initial_map.planets[i].entity_id, i});
			}
			
			//sort planetsby distance from your first ship
			std::vector<Ship> my_ships = initial_map.ships.at(player_id);
			//std::vector<Planet> Planet_target_order;
			std::map<double,Planet> Planet_distance_map;
			std::map<double, Planet> Planet_costvalue_map;
			std::multimap<unsigned, Planet> Planet_Cost_Map;//<CostValueFunc,PlanetID>
			unsigned cost = 0;
			for (unsigned i = 0;i <  initial_map.planets.size(); ++i) {
				double distance = my_ships[0].location.get_distance_to(initial_map.planets[i].location);
				Planet_distance_map.insert({ distance, initial_map.planets[i] });
			}

			for (auto &p:Planet_distance_map) {
				Planet_Value_Map.insert({ p.second.entity_id, cost++});
				unsigned value = Planet_Value_Map.find(p.second.entity_id)->second;
				Planet_Cost_Map.insert({ value - p.first,p.second });
			}
			initial_map.planets.clear();
			for (auto &p : Planet_Cost_Map) {
				initial_map.planets.push_back(p.second);
			}

			return {
					static_cast<PlayerId>(player_id),
					initial_map
        };
    }
}
