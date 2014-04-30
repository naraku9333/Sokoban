/********************************************************************
aim:
-
********************************************************************/
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "Map.hpp"
#include <cstdint>
#include "Tile.hpp"
#include "TexManager.hpp"
#include "Player.hpp"
#include <memory>
#include "SFMLResMan.hpp"

using namespace sv::sokoban;

bool collision(Tile& a, Tile& b)
{
    if (a.type == tile_type::free || b.type == tile_type::free)
        return false;
    return a.getLocalBounds().intersects(b.getLocalBounds());
}

void print_map(std::vector<std::string> v)
{
    for (auto& s : v)
        std::cout << s << std::endl;
}

bool checkMove(std::vector<std::string>& map, sf::Vector2f v, sf::Vector2f u)
{
    if (map[v.y + u.y][v.x + u.x] == '#')
        return false;
    else if (map[v.y + u.y][v.x + u.x] == '$' || map[v.y + u.y][v.x + u.x] == '*')
    {
        if (map[v.y + 2 * u.y][v.x + 2 * u.x] == ' ')
        {            
            std::swap(map[v.y + u.y][v.x + u.x], map[v.y + 2 * u.y][v.x + 2 * u.x]);//swap box
            std::swap(map[v.y][v.x], map[v.y + u.y][v.x + u.x]);//swap player
            print_map(map);
            return true;
        }
        return false;
    }
    else if (map[v.y + u.y][v.x + u.x] == ' ' || map[v.y + u.y][v.x + u.x] == '.')
    {
        std::swap(map[v.y][v.x], map[v.y + u.y][v.x + u.x]);
        print_map(map);
        return true;
    }
    return false;
}

int main()
{
	auto level_set = load_levels("puzzles/sasquatch.slc");
	uint8_t level_index = 0;
	Level current_level = level_set.levels[level_index];
    std::vector<std::string> map = current_level.data;

	std::vector<Tile> tiles;
	tiles.reserve(current_level.width * current_level.height);

	int y = 0;
	Tile* player = nullptr;
    sv::SFMLResMan<sf::Texture> textures;
	for (auto& a : current_level.data)
	{
		int x = 0;
		for (auto b : a)
		{
			tiles.emplace_back(Tile(textures.get(b), x++, y, b));
			if (b == '@')
				player = &tiles.back();
		}
		++y;
	}
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sokoban");

    window.setFramerateLimit(30);
	while (window.isOpen())
	{
		sf::Event event;
        sf::Vector2f u = { 0,0 }, v = player->getPosition();//{ 0, 0 };

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				return 0;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Key::Escape)
				{
					window.close();
					return 0;
				}
                if (event.key.code == sf::Keyboard::Key::Up)
                {
                    u.y = -1;
                    break;
                }
                else if (event.key.code == sf::Keyboard::Key::Down)
                {
                    u.y = 1;
                    break;
                }
                else if (event.key.code == sf::Keyboard::Key::Left)
                {
                    u.x = -1;
                    break;
                }
                else if (event.key.code == sf::Keyboard::Key::Right)
                {
                    u.x = 1;
                    break;
                }
                /*if (!checkMove(u.x, u.y))
                    u = { 0, 0 };*/
			}
		}
	
        if (checkMove(map, player->pos, u))
        {
            std::cout << "v.x = " << v.x << " v.y = " << v.y << std::endl;
            player->setPosition(v + 32.f * u);
            player->pos += u;  
            //tiles[player->pos.y + u.y * player->pos.x + u.x].setPosition(v + 32.f * u * 2.f);//
        }

		window.clear();
		for (auto& a : tiles)
			window.draw(a);

		window.draw(*player);
		window.display();
	}
}
