#include <string>
#include <string.h>
#include <iostream>
#include <vector>

#include "Matcher.h"

void			debugVerbose()
{
	Edge		edge('d');
	Edge		edge2('e');
	State		state = State::create();
	State		state2 = State::create(true);
	std::vector<Edge> vec;

	std::cout << "edge1 = " << edge.getKey() << " edge2 = " << edge2.getKey() << std::endl;
	if (edge(edge2.getKey()))
		std::cout << "Edge1 key == Edge2 key" << std::endl;
	else
		std::cout << "Edge1 key != Edge2 key" << std::endl;
	std::cout << "Edge1 = Edge2" << std::endl;
	edge = edge2;
	if (edge(edge2.getKey()))
		std::cout << "Edge1 key == Edge2 key" << std::endl;
	else
		std::cout << "Edge1 key != Edge2 key" << std::endl;
	if (edge == edge2)
		std::cout << "Edge1 key == Edge2 key" << std::endl;
	else
		std::cout << "Edge1 key != Edge2 key" << std::endl;
	std::cout << "Add Edge1 and Edge2 in vector" << std::endl;
	vec.push_back(edge);
	vec.push_back(edge2);
	std::cout << "State : " << state.getName() << " State2 : " << state2.getName() << std::endl;
	if (state.isFinal())
		std::cout << "state is final" << std::endl;
	else if (state2.isFinal())
		std::cout << "state2 is final" << std::endl;
}

int				main(int ac, char **av)
{
	FSA			fsat1;
	Matcher		matchert1(fsat1);
	int i = 0;

	if (ac < 3)
	{
		std::cerr << "Usage : ./ test_dynamic_fsa alpha str [verbose]" << std::endl;
		return (1);
	}
	matchert1.init(av[1]);
	matchert1.find(av[2], i);
	std::cout << "Token find : " << i << std::endl;
	if (ac == 4)
		debugVerbose();
	return (0);
}