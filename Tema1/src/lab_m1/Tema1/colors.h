#pragma once

#include <glm/glm.hpp>

namespace Colors {
	// board.cpp
	const glm::vec3 BOARD_BACKGROUND = glm::vec3(0.2f, 0.1f, 0.08f);
	const glm::vec3 PLAYER_BOARD = glm::vec3(0.15f, 0.25f, 0.15f);
	const glm::vec3 ENEMY_BOARD = glm::vec3(0.25f, 0.15f, 0.15f);
	const glm::vec3 PLAYER_HAND_ZONE = glm::vec3(0.18f, 0.3f, 0.22f);
	const glm::vec3 ENEMY_HAND_ZONE = glm::vec3(0.3f, 0.18f, 0.18f);
	const glm::vec3 DECK_COLOR = glm::vec3(0.35f, 0.2f, 0.1f);

	// card.cpp
	const glm::vec3 ENEMY_CARD = glm::vec3(0.6f, 0.55f, 0.4f);
	const glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);

	const glm::vec3 CARD_OUTLINE = glm::vec3(0.0f, 1.0f, 1.0f);
	const glm::vec3 CARD_RED = glm::vec3(0.75f, 0.25f, 0.25f);
	const glm::vec3 CARD_BLUE = glm::vec3(0.25f, 0.45f, 0.75f);
	const glm::vec3 CARD_GREEN = glm::vec3(0.25f, 0.65f, 0.35f);
	const glm::vec3 CARD_YELLOW = glm::vec3(0.85f, 0.7f, 0.2f);

	// hero.cpp
	const glm::vec3 PLAYER_HERO = glm::vec3(0.2f, 0.5f, 0.8f);
	const glm::vec3 ENEMY_HERO = glm::vec3(0.8f, 0.3f, 0.2f);
	const glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
	const glm::vec3 WHITE = glm::vec3(1.0f, 1.0f, 1.0f);
	const glm::vec3 BLACK = glm::vec3(0.0f, 0.0f, 0.0f);

	// timer.cpp
	const glm::vec3 TIMER_BACKGROUND_COLOR = glm::vec3(0.3f, 0.3f, 0.3f);
	const glm::vec3 TIMER_BAR_NORMAL_COLOR = glm::vec3(0.2f, 0.8f, 0.2f);
	const glm::vec3 TIMER_BAR_CRTICAL_COLOR = glm::vec3(0.9f, 0.2f, 0.2f);
	const glm::vec3 BUTTON_END_TURN = glm::vec3(0.8f, 0.5f, 0.2f);

	// gameOver.cpp
	const glm::vec3 WIN_COLOR = glm::vec3(0.15f, 0.55f, 0.25f);
	const glm::vec3 LOSE_COLOR = glm::vec3(0.65f, 0.15f, 0.15f);
}
