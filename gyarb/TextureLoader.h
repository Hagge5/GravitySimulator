#pragma once

#include <deque>
#include <string>
#include <SFML\Graphics.hpp>

struct NamedTexture {
	NamedTexture(std::string n) {
		this->fname = n;
		this->texture.loadFromFile(n);
	}

	sf::Texture texture;
	std::string fname;
};

static std::deque<NamedTexture> LoadedTextures;

sf::Texture* LoadTexture(std::string fname);