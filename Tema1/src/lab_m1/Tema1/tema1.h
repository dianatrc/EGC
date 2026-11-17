#pragma once

#include "components/simple_scene.h"
#include "board.h"
#include "card.h"
#include "hero.h"
#include "timer.h"
#include "deck.h"
#include "gameOver.h"
#include "arrow.h"
#include <vector>
#include <string>

using namespace std;

namespace m1 {
	class Tema1 : public gfxc::SimpleScene
	{
	public:
		Tema1();
		~Tema1();

		void Init() override;
		void RenderSquare(const glm::mat4& modelMatrix, const glm::vec3& color);
		void RenderShape(int shapeType, const glm::mat4& modelMatrix, const glm::vec3& color);
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void DrawPlayerBoardCards();
		void DrawPlayerHandCards();
		void DrawEnemyBoardCards();
		void DrawEnemyHandCards();

		vector<int> GetPlayableCardIndices();
		void PlayEnemyCards();

		// Extract card from deck
		void DrawCardFromDeck(Deck& deck, vector<Card>& hand);
		void UpdateCardRow(vector<Card>& cards, float rowY, int skipIndex,
			float deltaTimeSeconds);

		void EndTurn();

		// Drag and Drop functions
		void HandleCardSelection(int mouseX, int mouseY);
		void UpdateDraggedCardPosition(int mouseX, int mouseY);
		bool IsValidBoardDrop(float mouseX, float oglMouseY, const glm::ivec2& resolution);
		void PlaceCardOnBoard(int cardIndex);
		void HandleCardRelease(int mouseX, int mouseY);

		// Attack functions
		void SetBoardCanAttack(vector<Card>& board, bool value);
		bool IsOverCard(Card& card, float x, float y);
		void HandleAttackClick(int mouseX, int mouseY);
		void AttackCard(int targetCardIndex);
		void AttackHero();
		void RemoveDeadCards(vector<Card>& cards);

		bool EnemyChooseAttack();
		void EnemyExecuteAttack();
		void DrawEnemyAttackArrow();
		void EnemyAttackPlayerCard(int attackerIndex, int targetIndex);
		void EnemyAttackHeroCard(int attackerIndex);

		void DrawArrowAttack();

	private:
		Board game_board;

		Timer timer;
		bool isPlayerTurn;

		Hero playerHero;
		Hero enemyHero;

		int selectedCardIndex = -1;
		int hoveredCardIndex = -1;
		bool isDragged = false;
		int attackerIndex = -1;
		bool enemyAttackPending = false;
		int enemyAttackIndex = -1;
		int enemyTargetIndex = -1;
		float enemyArrowTimer = 0.0f;
		float enemyTurnTime = 0.0f;
		bool enemyHasPlayed = false;
		float enemyAttackTimer = 0.0f;
		glm::vec2 mousePos = glm::vec2(0.0f, 0.0f);

		vector<Card> playerHand;
		vector<Card> playerBoard;
		vector<Card> enemyHand;
		vector<Card> enemyBoard;

		Deck playerDeck;
		Deck enemyDeck;

		GameOver gameOver;
		Arrow arrow;
	};
}
