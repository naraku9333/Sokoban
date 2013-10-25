#ifndef SV_SOKOBAN_MAP
#define SV_SOKOBAN_MAP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
// # = wall
// $ = box
// @ = player
// . = free space
// * = used space
namespace sv
{
	namespace sokoban
	{		
		struct Level
		{
			uint16_t width, height;
			std::vector<std::string> data;
			Level() : width(0), height(0) {}
			Level(uint16_t w, uint16_t h, std::vector<std::string>& d)
				: width(w), height(h), data(std::move(d)){}
		};

		struct LevelSet
		{
			std::string title;
			std::string author;
			std::string description;
			std::vector<Level> levels;
		};

		auto load_levels(std::string filename)->LevelSet
		{
			using namespace boost::property_tree;

			ptree pt;
			read_xml(filename, pt);
			LevelSet L;
			L.title = pt.get<std::string>("SokobanLevels.Title");
			L.description = pt.get<std::string>("SokobanLevels.Description");
			L.author = pt.get<std::string>("SokobanLevels.LevelCollection.<xmlattr>.Copyright");
			for (auto& a : pt.get_child("SokobanLevels.LevelCollection"))
			{
				uint16_t width = a.second.get<uint16_t>("<xmlattr>.Width", 0);
				uint16_t height = a.second.get<uint16_t>("<xmlattr>.Height", 0);
				std::vector<std::string> v;
				for (auto& b : a.second)
				{
					if (b.second.data().size() > 0)
						v.push_back(b.second.data());
				}
				if (v.size() > 3)
					L.levels.push_back(Level(width, height, v));
			}
			return std::move(L);
		}
	}
}
#endif