#ifndef SV_SOKOBAN_TEX_MAN
#define SV_SOKOBAN_TEX_MAN
#include <SFML/Graphics.hpp>
#include <map>

// # = wall
// $ = box
// @ = player
// . = free space
// * = used space
// ' ' = blank
namespace sv
{
	namespace sokoban
	{
		class TextureManager
		{
			/*sf::Texture wall;
			sf::Texture box;
			sf::Texture player;
			sf::Texture free;
			sf::Texture used;
			sf::Texture ground;*/

			static std::map<char, sf::Texture> textures;
			static void init_tile(char c)
			{
				switch (c)
				{
				case '#':
					textures['#'].loadFromFile("../data/img/brick_wall.png");
					break;
				case '$':
				case '*':
					textures['$'].loadFromFile("../data/img/crate3.png");
					break;
				case '@':
					textures['@'].loadFromFile("../data/img/yellow_guy1.png");
					break;
				case '.':
					textures['.'].loadFromFile("../data/img/dot.png");
					break;
				case ' ':
					textures[' '].loadFromFile("../data/img/blank.png");
					break;
				}
			}
		public:
			static sf::Texture& get(char c)
			{
				try
				{
					return textures.at(c);
				}
				catch (...)
				{
					init_tile(c);
					return textures.at(c);
				}
			}
		};
	}
}
#endif