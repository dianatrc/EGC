#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "card.h"

using namespace std;

namespace m1 {
	class Tema1;
}

class Deck {
public:
	Deck(bool isPlayerDeck);
	~Deck();

	void FillDeck(int numCards);
	bool IsEmpty();

	glm::vec2 GetCardSpawnPosition();
	Card DrawTopCard();
	void DrawDeck(m1::Tema1* scene);

	void UpdatePosition(const glm::ivec2& resolution);

private:
	Card CreateRandomCard();

	void RenderRectangle(m1::Tema1* scene, const glm::vec2& pos,
		glm::vec2& rectangleSize, const glm::vec3& color);
	void RenderDeckLayer(m1::Tema1* scene, float offset);

private:
	bool isPlayerDeck;
	vector<Card> cards;

	glm::vec2 position;
	glm::vec2 size;
};