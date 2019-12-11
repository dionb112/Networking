#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>


struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};


std::vector<int> static numFromString(std::string t_message)
{
	//bool redWin = true;
	not_digit notADigit;

	std::string message = t_message;

	std::string::iterator end = std::remove_if(message.begin(), message.end(), notADigit);

	std::string all_numbers(message.begin(), end);

	std::stringstream ss(all_numbers);
	std::vector<int> vec;
    int i;
	for (; ss >> i;)
	{
		vec.push_back(i);
	}

	return vec;
}

