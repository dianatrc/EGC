#pragma once

#include <glm/glm.hpp>

namespace m1 {
	class Tema1;
}

class Hero {
public:
	Hero(bool isPlayerHero);
	~Hero();

	void RenderHero(m1::Tema1* scene, const glm::vec3& heroColor, const glm::ivec2& resolution);
	void DrawHero(m1::Tema1* scene, const glm::ivec2& resolution);
	void RenderHandCrystals(m1::Tema1* scene, const glm::vec3& crystalColor, int index);
	void DrawHandCrystals(m1::Tema1* scene);
	void RenderHealthPoints(m1::Tema1* scene, const glm::vec3& color, int index);
	void DrawHealth(m1::Tema1* scene);

	int GetAttackPoints();
	int GetHealthPoints();
	int GetMaxHand();
	int GetCurrentHand();
	bool IsPlayerHero();
	glm::vec2 GetCenter();

	void TakeDamage(int damagePoints);
	bool IsPointInside(float x, float y);

	void StartTurn();
	void SpendCost(int cost);

private:
	int attackPoints;
	int healthPoints;
	int maxHealthPoints;
	int maxHand;
	int currentHand;
	bool isPlayerHero;

	glm::vec2 position;
	glm::vec2 size;
};
