#ifndef SV_PLAYER_TILE_HPP
#define SV_PLAYER_TILE_HPP
#include "Tile.hpp"

namespace sv
{
	namespace sokoban
	{
		class Player
		{
			Tile& tile;
		public:
			Player(Tile& t) : tile(t){}	
			void move(int x, int y)
			{
				tile.move(sf::Vector2f(x * 32.f, y * 32.f));
			}
			int type(){ return static_cast<int>(tile.type); }
		};
	}
}
#endif