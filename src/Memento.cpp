#include "Memento.hpp"

std::ofstream& operator<<(std::ofstream& str, Memento& obj)
{
	str << obj.trail << " " <<obj.deformation<<" " << obj.active << " " << obj.storage.size() << "\n";
	for (int i = 0; i < obj.storage.size(); i++)
		str << obj.storage[i]->toString() << "\n";
	return str;
}

std::ifstream& operator>>(std::ifstream& str, Memento& obj)
{
	int size;
	str >> obj.trail >> obj.deformation>>obj.active >> size;
	std::string data;
	for (int i = 0; i < size; i++)
	{
		str >> data;
		try
		{
			obj.storage.push_back(Figure::fromString(data));
		}
		catch (std::exception exp)
		{
			continue;
		}
	}
	return str;
}

void clear(Memento& memento)
{
	for (uint64_t i = 0; i < memento.storage.size(); i++)
		delete memento.storage[i];
	memento.storage.clear();
}