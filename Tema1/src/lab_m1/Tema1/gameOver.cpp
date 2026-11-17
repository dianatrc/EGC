#include "gameOver.h"
#include "tema1.h"
#include "colors.h"

#include <glm/gtc/matrix_transform.hpp>

GameOver::GameOver() : isOver(false), playerWon(false) {}

GameOver::~GameOver() {}

bool GameOver::IsOver() {
	if (isOver)
		return true;
	return false;
}

void GameOver::CheckHeroes(Hero& playerHero, Hero& enemyHero) {
	if (isOver)
		return;

	if (enemyHero.GetHealthPoints() <= 0) {
		isOver = true;
		playerWon = true;
	} else if (playerHero.GetHealthPoints() <= 0) {
		isOver = true;
		playerWon = false;
	}
}

void GameOver::DrawRectangle(m1::Tema1* scene, const glm::vec2& center) {
	glm::vec2 size = glm::vec2(400.0f, 150.0f);
	glm::vec2 position = center - size / 2.0f;

	glm::mat4 model_matrix = glm::mat4(1.0f);
	glm::vec3 color;

	if (playerWon)
		color = Colors::WIN_COLOR;
	else
		color = Colors::LOSE_COLOR;
	model_matrix = glm::translate(model_matrix, glm::vec3(position.x, position.y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(size.x, size.y, 1.0f));
	scene->RenderSquare(model_matrix, color);
}

void GameOver::DrawSymbol(m1::Tema1* scene, const glm::vec2& center) {
	float symbolSize = 100.0f;
	float posX = center.x - symbolSize / 2.0f;
	float posY = center.y - symbolSize / 2.0f;

	glm::mat4 model_matrix = glm::mat4(1.0f);
	glm::vec3 color;

	model_matrix = glm::translate(model_matrix, glm::vec3(posX, posY, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(symbolSize, symbolSize, 1.0f));

	if (playerWon) {
		// white colored star for player win
		color = Colors::WHITE;
		scene->RenderShape(3, model_matrix, color);
	} else {
		// black colored diamond for enemy win
		color = Colors::BLACK;
		scene->RenderShape(2, model_matrix, color);
	}
}

void GameOver::DrawGameOver(m1::Tema1* scene, const glm::ivec2& resolution) {
	if (!isOver)
		return;

	float margin = 50.0f;
	float play_area_width = (float)resolution.x - (2.0f * margin) - 120.0f;
	glm::vec2 center = glm::vec2(margin + play_area_width / 2.0f, (float)resolution.y / 2.0f);

	DrawRectangle(scene, center);
	DrawSymbol(scene, center);
}
