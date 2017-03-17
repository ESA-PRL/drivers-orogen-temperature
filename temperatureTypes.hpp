#ifndef temperature_TYPES_HPP
#define temperature_TYPES_HPP

#include <base/Time.hpp>
#include <base/Temperature.hpp>
#include <vector>

namespace temperature
{
    namespace samples
    {
        struct Temperature
        {
	        base::Time time;
	        std::vector<base::Temperature> temp;
	        
	        void resize(int size)
            {
                    temp.resize(size);
            }

            size_t size()
            {
                return temp.size();
            }
	    };
	}
}

#endif

