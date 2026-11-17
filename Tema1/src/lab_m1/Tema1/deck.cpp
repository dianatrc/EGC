#include "deck.h"
#include "tema1.h"
#include "colors.h"

#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>

Deck::Deck(bool isPlayerDeck) : isPlayerDeck(isPlayerDeck),
	position(0.0f, 0.0f), size(90.0f, 130.0f) {}

Deck::~Deck() {}

Card Deck::CreateRandomCard() {
	// cost, attackPoints and healthPoints random from 1 to 5
	// type random from 0 to 3 (triangle, circle, diamond and star)
	int cost = rand() % 5 + 1;
	int attack = rand() % 5 + 1;
	int health = rand() % 5 + 1;
	int type = rand() % 4;

	return Card(cost, attack, health, isPlayerDeck, type);
}

void Deck::FillDeck(int numCards) {
	for (int i = 0; i < numCards; i++)
		cards.push_back(CreateRandomCard());
}

bool Deck::IsEmpty() {
	if (cards.empty())
		return true;
	return false;
}

glm::vec2 Deck::GetCardSpawnPosition() {
	float cardWidth = 100.0f;
	float cardHeight = 80.0f;
	float x = position.x + (size.x - cardWidth) / 2.0f;
	float y = position.y + (size.y - cardHeight) / 2.0f;

	return glm::vec2(x, y);
}

Card Deck::DrawTopCard() {
	Card topCard = cards.back();
	cards.pop_back();

	topCard.SetPosition(GetCardSpawnPosition());
	return topCard;
}

void Deck::UpdatePosition(const glm::ivec2& resolution) {
	float margin = 50.0f;
	position.x = (float)resolution.x - margin - 100.0f;

	if (isPlayerDeck)
		position.y = 100.0f;
	else
		position.y = (float)resolution.y - 230.0f;
}

void Deck::RenderRectangle(m1::Tema1* scene, const glm::vec2& pos,
	glm::vec2& rectangleSize, const glm::vec3& color) {
	glm::mat4 model_matrix = glm::mat4(1.0f);

	model_matrix = glm::translate(model_matrix, glm::vec3(pos.x, pos.y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(rectangleSize.x, rectangleSize.y, 1.0f));
	scene->RenderSquare(model_matrix, color);
}

void Deck::RenderDeckLayer(m1::Tema1* scene, float offset) {
	glm::vec2 layerPosition = position - glm::vec2(offset, offset);
	glm::vec2 border = glm::vec2(4.0f, 4.0f);
	glm::vec2 innerSize = size - 2.0f * border;

	RenderRectangle(scene, layerPosition, size, Colors::BLACK);
	RenderRectangle(scene, layerPosition + border, innerSize, Colors::ENEMY_CARD);
}

void Deck::DrawDeck(m1::Tema1* scene) {
	int layers = ((int)cards.size() + 4) / 5;

	for (int i = 0; i < layers; i++) {
		float offset = (layers - 1 - i) * 2.0f;
		RenderDeckLayer(scene, offset);
	}
}
