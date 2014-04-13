#include "TextureLoader.h"

sf::Texture* LoadTexture(std::string fname) {

	//Checking if the texture has been loaded before
	for(int i = 0; i < LoadedTextures.size(); i++) {
		if(LoadedTextures[i].fname == fname)
			return &(LoadedTextures[i].texture);
	}

	//It hasn't been loaded before, we need to load it.
	LoadedTextures.push_back(NamedTexture(fname));
	return &(LoadedTextures.back().texture);
}