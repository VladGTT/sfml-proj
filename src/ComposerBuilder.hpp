#pragma once
#include "Composer.hpp"

class ComposerBuilder
{
	Composer* composer = nullptr;

public:
	ComposerBuilder();
	ComposerBuilder* add(Figure* arg);
	ComposerBuilder* scale(sf::Vector2f scale);
	ComposerBuilder* setHidden(bool is_hidden);
	ComposerBuilder* setColor(sf::Color color);
	Composer* completeBuild();
	~ComposerBuilder();

};