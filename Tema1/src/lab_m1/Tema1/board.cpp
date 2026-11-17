#include "board.h"
#include "tema1.h"
#include "colors.h"

#include <glm/gtc/matrix_transform.hpp>

Board::Board() {}

Board::~Board() {}

void Board::RenderRectangle(m1::Tema1* scene, const glm::vec2& position,
	const glm::vec2& size, const glm::vec3& color) {
	glm::mat4 model_matrix = glm::mat4(1.0f);

	model_matrix = glm::translate(model_matrix, glm::vec3(position.x, position.y, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(size.x, size.y, 1.0f));
	scene->RenderSquare(model_matrix, color);
}

void Board::DrawBackground(m1::Tema1* scene, const glm::ivec2& resolution) {
	glm::vec2 background_pos = glm::vec2(0.0f, 0.0f); // starting position
	glm::vec2 background_size = glm::vec2(resolution.x, resolution.y); // 100% of screen
	glm::vec3 background_color = Colors::BOARD_BACKGROUND;

	RenderRectangle(scene, background_pos, background_size, background_color);
}

void Board::DrawEnemyHand(m1::Tema1* scene, const glm::ivec2& resolution) {
	float width = (float)resolution.x;
	float height = (float)resolution.y;
	float margin = 50.0f;
	float play_area_width = width - (2.0f * margin) - 120.0f;

	glm::vec2 enemy_hand_pos = glm::vec2(margin, height - 90.0f); // starting position
	glm::vec2 enemy_hand_size = glm::vec2(play_area_width, 80.0f); //!!
	glm::vec3 enemy_hand_color = Colors::ENEMY_HAND_ZONE;

	RenderRectangle(scene, enemy_hand_pos, enemy_hand_size, enemy_hand_color);
}

void Board::DrawPlayerHand(m1::Tema1* scene, const glm::ivec2& resolution) {
	float width = (float)resolution.x;
	float margin = 50.0f;
	float play_area_width = width - (2.0f * margin) - 120.0f;

	glm::vec2 player_hand_pos = glm::vec2(margin, 10.0f); // starting position
	glm::vec2 player_hand_size = glm::vec2(play_area_width, 80.0f);
	glm::vec3 player_hand_color = Colors::PLAYER_HAND_ZONE;

	RenderRectangle(scene, player_hand_pos, player_hand_size, player_hand_color);
}

void Board::DrawEnemyBoard(m1::Tema1* scene, const glm::ivec2& resolution) {
	float width = (float)resolution.x;
	float height = (float)resolution.y;
	float margin = 50.0f;
	float play_area_width = width - (2.0f * margin) - 120.0f;

	glm::vec2 enemy_board_pos = glm::vec2(margin, height - 230.0f); // starting position
	glm::vec2 enemy_board_size = glm::vec2(play_area_width, 130.0f);
	glm::vec3 enemy_board_color = Colors::ENEMY_BOARD;

	RenderRectangle(scene, enemy_board_pos, enemy_board_size, enemy_board_color);
}

void Board::DrawPlayerBoard(m1::Tema1* scene, const glm::ivec2& resolution) {
	float width = (float)resolution.x;
	float margin = 50.0f;
	float play_area_width = width - (2.0f * margin) - 120.0f;

	glm::vec2 player_board_pos = glm::vec2(margin, 100.0f); // starting position
	glm::vec2 player_board_size = glm::vec2(play_area_width, 130.0f);
	glm::vec3 player_board_color = Colors::PLAYER_BOARD;

	RenderRectangle(scene, player_board_pos, player_board_size, player_board_color);
}

void Board::DrawDecks(m1::Tema1* scene, const glm::ivec2& resolution) {
	float width = (float)resolution.x;
	float height = (float)resolution.y;
	float margin = 50.0f;
	glm::vec2 deck_size = glm::vec2(90.0f, 130.0f);
	float deck_x = width - margin - 100.0f;

	glm::vec2 enemy_deck_pos = glm::vec2(deck_x, height - 230.0f); // starting position
	glm::vec2 player_deck_pos = glm::vec2(deck_x, 100.0f);
	glm::vec3 deck_color = Colors::DECK_COLOR;

	RenderRectangle(scene, enemy_deck_pos, deck_size, deck_color);
	RenderRectangle(scene, player_deck_pos, deck_size, deck_color);
}

void Board::DrawMiddleLine(m1::Tema1* scene, const glm::ivec2& resolution) {
	float margin = 50.0f;
	float lineHeight = 4.0f;
	float play_area_width = (float)resolution.x - (2.0f * margin) - 120;
	glm::vec2 line_pos = glm::vec2(margin, ((float)resolution.y - lineHeight) / 2.0f);
	glm::vec2 line_size = glm::vec2(play_area_width, lineHeight);
	glm::vec3 lineColor = Colors::WHITE;

	RenderRectangle(scene, line_pos, line_size, lineColor);
}

void Board::DrawTable(m1::Tema1* scene, const glm::ivec2& resolution) {
	DrawBackground(scene, resolution);
	DrawEnemyHand(scene, resolution);
	DrawPlayerHand(scene, resolution);
	DrawEnemyBoard(scene, resolution);
	DrawPlayerBoard(scene, resolution);
	DrawDecks(scene, resolution);
	DrawMiddleLine(scene, resolution);
}