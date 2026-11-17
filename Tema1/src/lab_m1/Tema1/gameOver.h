#pragma once

#include <glm/glm.hpp>
#include "hero.h"

namespace m1 {
	class Tema1;
}

class GameOver {
public:
	GameOver();
	~GameOver();

	void CheckHeroes(Hero& playerHero, Hero& enemyHero);
	bool IsOver();
	void DrawGameOver(m1::Tema1* scene, const glm::ivec2& resolution);

private:
	void DrawRectangle(m1::Tema1* scene, const glm::vec2& center);
	void DrawSymbol(m1::Tema1* scene, const glm::vec2& center);

private:
	bool isOver;
	bool playerWon;
};
