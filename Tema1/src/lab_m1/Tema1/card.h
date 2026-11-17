#pragma once

#include <glm/glm.hpp>

namespace m1 {
	class Tema1;
}

class Card {
public:
	Card(int handCost, int attackPoints, int healthPoints, bool isPlayerCard, int cardType = 0);
	~Card();

	void RenderCard(m1::Tema1* scene, const glm::vec3& cardColor);
	void RenderCardSymbol(m1::Tema1* scene);
	void RenderCardStatShape(m1::Tema1* scene, int shapeType, 
		const glm::vec3& color, const glm::vec2& offset, const glm::vec2& statSize);
	void DrawCardStats(m1::Tema1* scene);
	void DrawOutline(m1::Tema1* scene);

	void DrawCard(m1::Tema1* scene); // draw card face up
	void DrawCardBack(m1::Tema1* scene); // draw card face down

	int GetHandCost();
	int GetAttackPoints();
	int GetHealthPoints();
	glm::vec2 GetPosition();
	bool IsPlayerCard();
	bool GetCanAttack();

	void TakeDamage(int damagePoints);
	bool IsDead();

	void SetPosition(const glm::vec2& pos);
	void SetTargetPosition(const glm::vec2& pos);
	void SetCanAttack(bool value);

	void UpdateAnimation(float deltaTimeSeconds);

	void SetTargetScale(float s);
	void UpdateScale(float deltaTimeSeconds);
	glm::mat4 GetBaseMatrix();

private:
	int handCost;
	int attackPoints;
	int healthPoints;
	bool isPlayerCard;
	int cardType;
	bool canAttack;

	float scale = 1.0f;
	float targetScale = 1.0f;

	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 targetPosition;
};
