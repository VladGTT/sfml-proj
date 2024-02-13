#include "ComposerStorage.hpp"

void ComposerStorage::add(Figure* composer, std::string name)
{
	storage[name] = composer->clone();
}
Figure* ComposerStorage::get(std::string name)
{
	if (storage.empty())throw std::string("Empty storage");
	try
	{
		return storage[name]->clone();
	}
	catch (std::exception exp)
	{
		throw std::string("No such composite");
	}
}