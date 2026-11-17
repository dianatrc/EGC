#pragma once

#include "components/simple_scene.h"
#include <glm/glm.hpp>

namespace m1 {
	class Tema1;
}

class Board {
public:
	Board();
	~Board();

	void DrawTable(m1::Tema1* scene, const glm::ivec2& resolution);

private:
	void RenderRectangle(m1::Tema1* scene, const glm::vec2& position,
		const glm::vec2& size, const glm::vec3& color);
	void DrawBackground(m1::Tema1* scene, const glm::ivec2& resolution);
	void DrawEnemyHand(m1::Tema1* scene, const glm::ivec2& resolution);
	void DrawPlayerHand(m1::Tema1* scene, const glm::ivec2& resolution);
	void DrawEnemyBoard(m1::Tema1* scene, const glm::ivec2& resolution);
	void DrawPlayerBoard(m1::Tema1* scene, const glm::ivec2& resolution);
	void DrawDecks(m1::Tema1* scene, const glm::ivec2& resolution);
	void DrawMiddleLine(m1::Tema1* scene, const glm::ivec2& resolution);
};