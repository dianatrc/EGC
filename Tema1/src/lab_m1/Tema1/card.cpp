#include "card.h"
#include "tema1.h"
#include "colors.h"

#include <glm/gtc/matrix_transform.hpp>

Card::Card(int handCost, int attackPoints, int healthPoints, bool isPlayerCard, int cardType)
	: handCost(handCost), attackPoints(attackPoints), healthPoints(healthPoints), isPlayerCard(isPlayerCard),
	cardType(cardType), position(0.0f, 0.0f), size(100.0f, 80.0f), targetPosition(0.0f, 0.0f),
	canAttack(false) {}

Card::~Card() {}

void Card::RenderCard(m1::Tema1* scene, const glm::vec3& cardColor) {
	glm::mat4 model_matrix = GetBaseMatrix();

	model_matrix = glm::translate(model_matrix, glm::vec3(position.x, position.y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(size.x, size.y, 1.0f));
	scene->RenderSquare(model_matrix, cardColor);
}

void Card::RenderCardSymbol(m1::Tema1* scene) {
	glm::vec2 symbolSize = glm::vec2(20.0f, 20.0f);
	glm::vec2 offset = glm::vec2(75.0f, size.y / 2.0f - 10.0f);
	glm::mat4 model_matrix = GetBaseMatrix();

	model_matrix = glm::translate(model_matrix, glm::vec3(position.x + offset.x,
		position.y + offset.y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(symbolSize.x, symbolSize.y, 1.0f));
	scene->RenderShape(cardType, model_matrix, Colors::WHITE);
}

void Card::RenderCardStatShape(m1::Tema1* scene, int shapeType, const glm::vec3& color,
	const glm::vec2& offset, const glm::vec2& statSize) {
	glm::mat4 model_matrix = GetBaseMatrix();

	model_matrix = glm::translate(model_matrix, glm::vec3(position.x + offset.x,
		position.y + offset.y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(statSize.x, statSize.y, 1.0f));
	scene->RenderShape(shapeType, model_matrix, color);
}

void Card::DrawCardStats(m1::Tema1* scene) {
	glm::vec2 statSize = glm::vec2(10.0f, 10.0f);
	glm::vec3 color;
	glm::vec2 offset;

	for (int i = 0; i < handCost; i++) {
		// handcost -> circles
		color = Colors::BLUE;
		offset = glm::vec2(8.0f + i * 13.0f, size.y - 18.0f);

		RenderCardStatShape(scene, 1, color, offset, statSize);
	}
	for (int i = 0; i < attackPoints; i++) {
		// attackPoints -> swords
		color = Colors::RED;
		offset = glm::vec2(8.0f + i * 13.0f, size.y / 2.0f - 5.0f);

		RenderCardStatShape(scene, 5, color, offset, statSize);
	}
	for (int i = 0; i < healthPoints; i++) {
		// healthPoints -> hearts
		color = Colors::GREEN;
		offset = glm::vec2(8.0f + i * 13.0f, 8.0f);

		RenderCardStatShape(scene, 4, color, offset, statSize);
	}
}

void Card::DrawOutline(m1::Tema1* scene) {
	float thickness = 3.0f;
	float outlineX = position.x - thickness;
	float outlineY = position.y - thickness;
	float outlineWidth = size.x + 2.0f * thickness;
	float outlineHeight = size.y + 2.0f * thickness;
	glm::vec3 outlineColor = Colors::CARD_OUTLINE;

	glm::mat4 model_matrix = GetBaseMatrix();
	model_matrix = glm::translate(model_matrix, glm::vec3(outlineX, outlineY, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(outlineWidth, outlineHeight, 1.0f));

	scene->RenderSquare(model_matrix, outlineColor);
}

void Card::DrawCard(m1::Tema1* scene) {
	glm::vec3 cardColor;

	if (canAttack)
		DrawOutline(scene);
	if (cardType == 0)
		cardColor = Colors::CARD_RED;
	else if (cardType == 1)
		cardColor = Colors::CARD_BLUE;
	else if (cardType == 2)
		cardColor = Colors::CARD_GREEN;
	else
		cardColor = Colors::CARD_YELLOW;

	RenderCard(scene, cardColor);
	RenderCardSymbol(scene);
	DrawCardStats(scene);
}

void Card::DrawCardBack(m1::Tema1* scene) {
	RenderCard(scene, Colors::ENEMY_CARD);

	glm::vec2 innerOffset = glm::vec2(10.0f, 10.0f);
	glm::vec2 innerSize = glm::vec2(size.x - 20.0f, size.y - 20.0f);
	glm::mat4 model_matrix = GetBaseMatrix();

	model_matrix = glm::translate(model_matrix, glm::vec3(position.x + innerOffset.x,
		position.y + innerOffset.y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(innerSize.x, innerSize.y, 1.0f));
	scene->RenderSquare(model_matrix, Colors::DECK_COLOR);
}

int Card::GetHandCost() {
	return handCost;
}

int Card::GetAttackPoints() {
	return attackPoints;
}

int Card::GetHealthPoints() {
	return healthPoints;
}

glm::vec2 Card::GetPosition() {
	return position;
}

bool Card::IsPlayerCard() {
	return isPlayerCard;
}

bool Card::GetCanAttack() {
	return canAttack;
}

void Card::TakeDamage(int damagePoints) {
	healthPoints -= damagePoints;
}

bool Card::IsDead() {
	if (healthPoints <= 0)
		return true;
	return false;
}

void Card::SetPosition(const glm::vec2& pos) {
	position = pos;
}

void Card::SetTargetPosition(const glm::vec2& pos) {
	targetPosition = pos;
}

void Card::SetCanAttack(bool value) {
	canAttack = value;
}

void Card::UpdateAnimation(float deltaTimeSeconds) {
	glm::vec2 diff = targetPosition - position;
	float distance = glm::length(diff);
	float step = 800.0f * deltaTimeSeconds;

	if (distance <= step)
		position = targetPosition;
	else
		position += diff / distance * step;
}

void Card::SetTargetScale(float s) {
	targetScale = s;
}

void Card::UpdateScale(float deltaTimeSeconds) {
	float speed = 15.0f;
	float step = speed * deltaTimeSeconds;

	if (step > 1.0f)
		step = 1.0f;
	scale += (targetScale - scale) * step;
}

glm::mat4 Card::GetBaseMatrix() {
	float centerX = position.x + size.x / 2.0f;
	float centerY = position.y + size.y / 2.0f;

	glm::mat4 base_matrix = glm::mat4(1.0f);
	
	base_matrix = glm::translate(base_matrix, glm::vec3(centerX, centerY, 0.0f));
	base_matrix = glm::scale(base_matrix, glm::vec3(scale, scale, 1.0f));
	base_matrix = glm::translate(base_matrix, glm::vec3(-centerX, -centerY, 0.0f));
	return base_matrix;
}
