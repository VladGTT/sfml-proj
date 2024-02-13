#include "ComposerBuilder.hpp"

ComposerBuilder::ComposerBuilder()
{
	composer = new Composer();
}
ComposerBuilder::~ComposerBuilder()
{
	if (composer)
		delete composer;
}

ComposerBuilder* ComposerBuilder::add(Figure* arg)
{
	composer->addFigure(arg->clone());
	
	return this;
}

ComposerBuilder* ComposerBuilder::scale(sf::Vector2f scale)
{
	composer->setScale(scale);

	return this;
}
ComposerBuilder* ComposerBuilder::setHidden(bool is_hidden)
{
	composer->setHidden(is_hidden);
	
	return this;
}

ComposerBuilder* ComposerBuilder::setColor(sf::Color color)
{
	composer->setColor(color);
	return this;
}

Composer* ComposerBuilder::completeBuild()
{
	Composer* retval = composer->clone();
	composer = nullptr;
	return retval;
}