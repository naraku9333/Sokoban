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
			wall = '#', box = '$', player = '@', goal = '.', used = '*', free = ' '
		};

		class Tile : public sf::Sprite
		{
		public:
			tile_type type;
            sf::Vector2f pos;
            Tile(const sf::Texture& t, int x, int y, char c) : Sprite(t), pos{ x, y }
			{
                type = static_cast<tile_type>(c);
				setPosition(x * 32.f, y * 32.f);
			}
		};
	}
}
#endif
