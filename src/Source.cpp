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

//namespaces

int main()
{
	using namespace sv::sokoban;

	auto level_set = load_levels("../data/puzzles/sasquatch.slc");
	uint8_t level_index = 0;
	Level current_level = level_set.levels[level_index];

	std::vector<Tile> tiles;
	int y = 0;
	for (auto& a : current_level.data)
	{
		int x = 0;
		for (auto b : a)
		{
			tiles.push_back(Tile(TextureManager::get(b), x++, y));
		}
		++y;
	}
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sokoban");

	while (window.isOpen())
	{
		sf::Event event;
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
			}
		}
		window.clear();
		for (auto& a : tiles)
			window.draw(a);
		window.display();
	}
}
