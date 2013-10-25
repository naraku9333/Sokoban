#ifndef SV_SOKOBAN_TILE_HPP
#define SV_SOKOBAN_TILE_HPP
#include <SFML/Graphics.hpp>
#include <cstdint>

namespace sv
{
	namespace sokoban
	{
		enum class tile_type
		{
			wall = '#', box = '$', player = '@', free = '.', used = '*', blank = ' '
		};

		class Tile : public sf::Sprite
		{
		public:
			tile_type type;
			Tile(sf::Texture& t, int x, int y) : Sprite(t)
			{
				setPosition(x * 32, y * 32);
			}
		};
	}
}
#endif
