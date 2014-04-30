#ifndef SV_SF_RESOURCE_MANAGGER_HPP
#define SV_SF_RESOURCE_MANAGER_HPP
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace sv
{
    template<typename T>
    class SFMLResMan
    {
        std::map<std::string, T> data;

        public:
        SFMLResMan() : data()
        {

        }
        const T& get(const char c)
        {
            std::string p;
            switch (c)
            {
                case '#':
                    p = "data/img/brick_wall.png";
                    break;
                case '$':
                case '*':
                    p = "data/img/crate3.png";
                    break;
                case '@':
                    p = "data/img/yellow_guy1.png";
                    break;
                case '.':
                    p = "data/img/dot.png";
                    break;
                case ' ':
                    p = "data/img/blank.png";
                    break;                    
            }
            return get(p);
        }
        /*
        *
        }*/
        const T& get(const std::string& path)
        {
            if (data.find(path) == data.end())
            {
                data.insert({ path, T() });
                data[path].loadFromFile(path);
            }
            return data.at(path);
        }
    };
}
#endif