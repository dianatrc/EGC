#include "hero.h"
#include "tema1.h"
#include "colors.h"

#include <glm/gtc/matrix_transform.hpp>

Hero::Hero(bool isPlayerHero) : isPlayerHero(isPlayerHero), healthPoints(30), maxHealthPoints(30),
	attackPoints(0), maxHand(0), currentHand(0), position(0.0f, 0.0f), size(100.0f, 120.0f) {}

Hero::~Hero() {}

void Hero::RenderHero(m1::Tema1* scene, const glm::vec3& heroColor, const glm::ivec2& resolution) {
	float margin = 50.0f;
	float play_area_width = (float)resolution.x - (2.0f * margin) - 120.0f;

	float posX = margin + (play_area_width - size.x) / 2.0f;
	float posY = 0.0f;

	if (IsPlayerHero())
		posY = 230.0f + (130.0f - size.y) / 2.0f; // player board
	else
		posY = ((float)resolution.y - 360.0f) + (130.0f - size.y) / 2.0f; // enemy board

	position = glm::ivec2(posX, posY);
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, glm::vec3(position.x, position.y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(size.x, size.y, 1.0f));
	scene->RenderSquare(model_matrix, heroColor);
}

void Hero::DrawHero(m1::Tema1* scene, const glm::ivec2& resolution) {
	glm::vec3 heroColor;

	if (IsPlayerHero())
		heroColor = Colors::PLAYER_HERO;
	else
		heroColor = Colors::ENEMY_HERO;

	RenderHero(scene, heroColor, resolution);
}

void Hero::RenderHandCrystals(m1::Tema1* scene, const glm::vec3& crystalColor, int index) {
	float crystalSize = 10.0f;
	float spacing = 5.0f;

	float startX = position.x - 10.0f - crystalSize;
	float x = startX - index * (crystalSize + spacing);
	float y = position.y + (size.y - crystalSize) / 2.0f; // !!!!!

	glm::mat4 model_matrix = glm::mat4(1.0f);

	model_matrix = glm::translate(model_matrix, glm::vec3(x, y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(crystalSize, crystalSize, 1.0f));
	scene->RenderSquare(model_matrix, crystalColor);
}

void Hero::DrawHandCrystals(m1::Tema1* scene) {
	// only show player crystals
	if (!IsPlayerHero())
		return;

	for (int i = 0; i < 10; i++) {
		glm::vec3 crystalColor;

		if (i < currentHand)
			crystalColor = Colors::BLUE;
		else if (i < maxHand)
			crystalColor = Colors::WHITE;
		else
			crystalColor = Colors::BLACK;
		RenderHandCrystals(scene, crystalColor, i);
	}
}

void Hero::RenderHealthPoints(m1::Tema1* scene, const glm::vec3& color, int index) {
	float pointSize = 10.0f;
	float spacing = 5.0f;
	int pointPerRow = 10;
	int rows = 3;
	float gridHeight = rows * pointSize + (rows - 1) * spacing;
	int row = index / pointPerRow;
	int column = index % pointPerRow;
	float startX = position.x + size.x + 10.0f;
	float topY = position.y + (size.y + gridHeight) / 2.0f - pointSize;
	float x = startX + column * (pointSize + spacing);
	float y = topY - row * (pointSize + spacing);
	glm::mat4 model_matrix = glm::mat4(1.0f);

	model_matrix = glm::translate(model_matrix, glm::vec3(x, y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(pointSize, pointSize, 1.0f));
	scene->RenderSquare(model_matrix, color);
}

void Hero::DrawHealth(m1::Tema1* scene) {
	glm::vec3 color;

	for (int i = 0; i < maxHealthPoints; i++) {
		if (i < healthPoints)
			color = Colors::GREEN;
		else
			color = Colors::BLACK;
		RenderHealthPoints(scene, color, i);
	}
}

int Hero::GetAttackPoints() {
	return attackPoints;
}

int Hero::GetHealthPoints() {
	return healthPoints;
}

int Hero::GetMaxHand() {
	return maxHand;
}

int Hero::GetCurrentHand() {
	return currentHand;
}

glm::vec2 Hero::GetCenter() {
	glm::vec2 center;

	center.x = position.x + size.x / 2.0f;
	center.y = position.y + size.y / 2.0f;
	return center;
}

bool Hero::IsPlayerHero() {
	return isPlayerHero;
}

void Hero::TakeDamage(int damagePoints) {
	healthPoints -= damagePoints;
	if (healthPoints < 0)
		healthPoints = 0;
}

bool Hero::IsPointInside(float x, float y) {
	if ((x >= position.x && x <= position.x + size.x) &&
		(y >= position.y && y <= position.y + size.y))
		return true;
	return false;
}

void Hero::StartTurn() {
	if (maxHand < 10)
		maxHand++;
	currentHand = maxHand;
}

void Hero::SpendCost(int cost) {
	currentHand -= cost;
	if (currentHand < 0)
		currentHand = 0;
}
