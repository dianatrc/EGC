#include "tema1.h"
#include "colors.h"
#include "core/engine.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace m1;
using namespace std;

const float CARD_WIDTH = 100.0f;
const float CARD_HEIGHT = 80.0f;
const float CARD_SPACING = 20.0f;
const float AREA_MARGIN = 50.0f;
const size_t MAX_HAND = 8;
const size_t MAX_BOARD = 8;

Tema1::Tema1() : isPlayerTurn(true), playerHero(true), enemyHero(false),
	playerDeck(true), enemyDeck(false) {}

Tema1::~Tema1() {}

void Tema1::Init() {
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400.0f);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glDisable(GL_DEPTH_TEST);

	srand(time(nullptr));
	// init player and enemy deck -> 25 cards
	playerDeck.FillDeck(25);
	enemyDeck.FillDeck(25);

	playerDeck.UpdatePosition(resolution);
	enemyDeck.UpdatePosition(resolution);

	// init player and enemy hand -> 5 cards
	for (int i = 0; i < 5; i++) {
		DrawCardFromDeck(playerDeck, playerHand);
		DrawCardFromDeck(enemyDeck, enemyHand);
	}

	playerHero.StartTurn();
}

void Tema1::DrawCardFromDeck(Deck& deck, vector<Card>& hand) {
	if (deck.IsEmpty())
		return;

	Card card = deck.DrawTopCard();
	if (hand.size() < MAX_HAND)
		hand.push_back(card);
}

void Tema1::UpdateCardRow(vector<Card>& cards, float rowY, int skipIndex,
	float deltaTimeSeconds) {
	int n = (int)cards.size();
	if (n == 0)
		return;

	float areaWidth = (float)window->GetResolution().x - 2.0f * AREA_MARGIN - 120.0f;
	float spacing = CARD_SPACING;
	if (n > 1 && n * CARD_WIDTH + (n - 1) * spacing > areaWidth)
		spacing = (areaWidth - n * CARD_WIDTH) / (n - 1);

	float totalWidth = n * CARD_WIDTH + (n - 1) * spacing;
	float startX = AREA_MARGIN + (areaWidth - totalWidth) / 2.0f;

	for (int i = 0; i < n; i++) {
		cards[i].SetTargetPosition(glm::vec2(startX + i * (CARD_WIDTH + spacing), rowY));
		cards[i].UpdateScale(deltaTimeSeconds);
		if (i != skipIndex)
			cards[i].UpdateAnimation(deltaTimeSeconds);
	}
}

void Tema1::RenderSquare(const glm::mat4& modelMatrix, const glm::vec3& color) {
	string name = to_string(color.r) + to_string(color.g) + to_string(color.b);

	if (meshes.find(name) == meshes.end()) {
		vector<VertexFormat> vertices = {
			VertexFormat(glm::vec3(0.0f, 0.0f, 0.0f), color),
			VertexFormat(glm::vec3(1.0f, 0.0f, 0.0f), color),
			VertexFormat(glm::vec3(1.0f, 1.0f, 0.0f), color),
			VertexFormat(glm::vec3(0.0f, 1.0f, 0.0f), color)
		};

		vector<unsigned int> indices = {
			0, 1, 2,
			0, 2, 3
		};

		Mesh* square = new Mesh(name);
		square->InitFromData(vertices, indices);
		AddMeshToList(square);

	}
	RenderMesh(meshes[name], shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderShape(int shapeType, const glm::mat4& modelMatrix, const glm::vec3& color) {
	string name = to_string(shapeType) + to_string(color.r) + to_string(color.g) + to_string(color.b);

	if (meshes.find(name) == meshes.end()) {
		vector<VertexFormat> vertices;
		vector<unsigned int> indices;

		if (shapeType == 0) {
			// triangle shape
			vertices = {
				VertexFormat(glm::vec3(0.0f, 0.0f, 0.0f), color),
				VertexFormat(glm::vec3(1.0f, 0.0f, 0.0f), color),
				VertexFormat(glm::vec3(0.5f, 1.0f, 0.0f), color)
			};
			indices = {
				0, 1, 2
			};
		}
		else if (shapeType == 1) {
			// circle shape
			int numSegments = 32;
			float radius = 0.5f;
			float PI = 3.14159f;
			glm::vec3 center = glm::vec3(0.5f, 0.5f, 0.0f);

			vertices.push_back(VertexFormat(center, color));

			for (int i = 0; i < numSegments; i++) {
				float angle = 2.0f * PI * i / numSegments;
				float x = center.x + radius * cos(angle);
				float y = center.y + radius * sin(angle);

				vertices.push_back(VertexFormat(glm::vec3(x, y, 0.0f), color));
			}
			for (int i = 1; i <= numSegments; i++) {
				indices.push_back(0);
				indices.push_back(i);
				if (i == numSegments)
					indices.push_back(1);
				else
					indices.push_back(i + 1);
			}
		}
		else if (shapeType == 2) {
			// diamond shape
			vertices = {
				VertexFormat(glm::vec3(0.5f, 0.0f, 0.0f), color),
				VertexFormat(glm::vec3(1.0f, 0.5f, 0.0f), color),
				VertexFormat(glm::vec3(0.5f, 1.0f, 0.0f), color),
				VertexFormat(glm::vec3(0.0f, 0.5f, 0.0f), color)
			};
			indices = {
				0, 1, 2,
				0, 2, 3
			};
		}
		else if (shapeType == 3) {
			// star shape
			int numPoints = 10;
			float outerRadius = 0.5f;
			float innerRadius = 0.2f;
			float PI = 3.14159f;
			glm::vec3 center = glm::vec3(0.5f, 0.5f, 0.0f);

			vertices.push_back(VertexFormat(center, color));

			for (int i = 0; i < numPoints; i++) {
				float angle = PI / 2.0f + 2.0f * PI * i / numPoints;
				float radius = 0.0f;
				if (i % 2 == 0)
					radius = outerRadius;
				else
					radius = innerRadius;
				float x = center.x + radius * cos(angle);
				float y = center.y + radius * sin(angle);

				vertices.push_back(VertexFormat(glm::vec3(x, y, 0.0f), color));
			}
			for (int i = 1; i <= numPoints; i++) {
				indices.push_back(0);
				indices.push_back(i);
				if (i == numPoints)
					indices.push_back(1);
				else
					indices.push_back(i + 1);
			}
		}
		else if (shapeType == 4) {
			// heart shape -> healthPoints (2 semicircles + bottom triangle)
			int halfSegments = 16;
			float PI = 3.14159f;
			float radius = 0.25f;

			glm::vec3 rightCenter = glm::vec3(0.75f, 0.7f, 0.0f);
			glm::vec3 leftCenter = glm::vec3(0.25f, 0.7f, 0.0f);

			vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.55f, 0.0f), color));
			vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.0f, 0.0f), color));

			for (int i = 0; i <= halfSegments; i++) {
				float angle = PI * i / halfSegments;

				float x = rightCenter.x + radius * cos(angle);
				float y = rightCenter.y + radius * sin(angle);

				vertices.push_back(VertexFormat(glm::vec3(x, y, 0.0f), color));
			}
			for (int i = 0; i <= halfSegments; i++) {
				float angle = PI * i / halfSegments;

				float x = leftCenter.x + radius * cos(angle);
				float y = leftCenter.y + radius * sin(angle);

				vertices.push_back(VertexFormat(glm::vec3(x, y, 0.0f), color));
			}

			int startRight = 2;
			int endRight = startRight + halfSegments;
			int startLeft = endRight + 1;
			int endLeft = startLeft + halfSegments;

			for (int i = startRight; i < endRight; i++) {
				indices.push_back(0);
				indices.push_back(i);
				indices.push_back(i + 1);
			}
			for (int i = startLeft; i < endLeft; i++) {
				indices.push_back(0);
				indices.push_back(i);
				indices.push_back(i + 1);
			}

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(startRight);

			indices.push_back(0);
			indices.push_back(endLeft);
			indices.push_back(1);
		}
		else if (shapeType == 5) {
			// sword shape -> attackPoints
			vertices = {
				// blade tip + body
				VertexFormat(glm::vec3(0.5f, 1.0f, 0.0f), color), // top tip
				VertexFormat(glm::vec3(0.35f, 0.72f, 0.0f), color), // blade top-left
				VertexFormat(glm::vec3(0.65f, 0.72f, 0.0f), color), // blade top-right
				VertexFormat(glm::vec3(0.35f, 0.32f, 0.0f), color), // blade bottom-left
				VertexFormat(glm::vec3(0.65f, 0.32f, 0.0f), color), // blade bottom-right

				// horizontal crossguard
				VertexFormat(glm::vec3(0.15f, 0.32f, 0.0f), color), // top-left
				VertexFormat(glm::vec3(0.85f, 0.32f, 0.0f), color), // top-right
				VertexFormat(glm::vec3(0.15f, 0.2f, 0.0f), color), // bottom-left
				VertexFormat(glm::vec3(0.85f, 0.2f, 0.0f), color), // bottom-right

				// bottom handle
				VertexFormat(glm::vec3(0.42f, 0.2f, 0.0f), color), // top-right
				VertexFormat(glm::vec3(0.58f, 0.2f, 0.0f), color), // top-right
				VertexFormat(glm::vec3(0.42f, 0.0f, 0.0f), color), // bottom-left
				VertexFormat(glm::vec3(0.58f, 0.0f, 0.0f), color), // bottom-right
			};
			indices = {
				0, 1, 2, // tip triangle
				1, 3, 2, // blade
				2, 3, 4,
				5, 7, 6, // crossguard
				6, 7, 8,
				9, 11, 10, // handle
				10, 11, 12
			};
		}

		Mesh* shape = new Mesh(name);
		shape->InitFromData(vertices, indices);
		AddMeshToList(shape);
	}
	RenderMesh(meshes[name], shaders["VertexColor"], modelMatrix);
}

void Tema1::DrawPlayerBoardCards() {
	for (size_t i = 0; i < playerBoard.size(); i++)
		playerBoard[i].DrawCard(this);
}

void Tema1::DrawPlayerHandCards() {
	for (size_t i = 0; i < playerHand.size(); i++) {
		if ((i == hoveredCardIndex) || (isDragged && (int)i == selectedCardIndex))
			continue;
		playerHand[i].DrawCard(this);
	}
	if (hoveredCardIndex != -1)
		playerHand[hoveredCardIndex].DrawCard(this);
	if (isDragged && selectedCardIndex != -1)
		playerHand[selectedCardIndex].DrawCard(this);
}

void Tema1::DrawEnemyBoardCards() {
	for (size_t i = 0; i < enemyBoard.size(); i++)
		enemyBoard[i].DrawCard(this);
}

void Tema1::DrawEnemyHandCards() {
	for (size_t i = 0; i < enemyHand.size(); i++)
		enemyHand[i].DrawCardBack(this);
}

vector<int> Tema1::GetPlayableCardIndices() {
	vector<int> playable;

	for (int i = 0; i < enemyHand.size(); i++) {
		if (enemyHand[i].GetHandCost() <= enemyHero.GetCurrentHand())
			playable.push_back(i);
	}
	return playable;
}

void Tema1::PlayEnemyCards() {
	while (enemyBoard.size() < MAX_BOARD) {
		vector<int> playable = GetPlayableCardIndices();

		if (playable.empty())
			break;
		int randomIndex = playable[rand() % playable.size()];
		int cardCost = enemyHand[randomIndex].GetHandCost();

		enemyHero.SpendCost(cardCost);
		enemyBoard.push_back(enemyHand[randomIndex]);
		enemyHand.erase(enemyHand.begin() + randomIndex);
	}
}

void Tema1::FrameStart() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tema1::Update(float deltaTimeSeconds) {
	glm::ivec2 resolution = window->GetResolution();

	gameOver.CheckHeroes(playerHero, enemyHero);
	
	if (!gameOver.IsOver()) {
		timer.Update(deltaTimeSeconds);
		if (timer.IsExpired())
			EndTurn();

		if (!isPlayerTurn) {
			enemyTurnTime += deltaTimeSeconds;

			if (!enemyHasPlayed && enemyTurnTime >= 2.0f) {
				PlayEnemyCards();
				enemyHasPlayed = true;
			}
			if (enemyHasPlayed) {
				if (enemyAttackPending) {
					enemyArrowTimer += deltaTimeSeconds;
					if (enemyArrowTimer >= 1.5f) {
						EnemyExecuteAttack();
						enemyAttackTimer = 0.0f;
					}
				}
				else {
					enemyAttackTimer += deltaTimeSeconds;
					// enemy attacks once per second; turn ends when nobody can attack anymore
					if (enemyAttackTimer >= 1.0f) {
						enemyAttackTimer = 0.0f;
						if (EnemyChooseAttack() == false)
							EndTurn();
					}
				}
			}
		}
	}

	playerDeck.UpdatePosition(resolution);
	enemyDeck.UpdatePosition(resolution);

	int draggedIndex = -1;
	if (isDragged)
		draggedIndex = selectedCardIndex;

	UpdateCardRow(playerHand, 10.0f, draggedIndex, deltaTimeSeconds);
	UpdateCardRow(playerBoard, 125.0f, -1, deltaTimeSeconds);
	UpdateCardRow(enemyHand, resolution.y - 90.0f, -1, deltaTimeSeconds);
	UpdateCardRow(enemyBoard, resolution.y - 205.0f, -1, deltaTimeSeconds);

	// card hovered
	hoveredCardIndex = -1;
	if (isPlayerTurn && !isDragged) {
		for (int i = playerHand.size() - 1; i >= 0; i--)
			if (IsOverCard(playerHand[i], mousePos.x, mousePos.y)) {
				hoveredCardIndex = i;
				break;
			}
	}
	for (int i = 0; i < playerHand.size(); i++) {
		float s = 1.0f;

		if (isDragged && i == selectedCardIndex)
			s = 1.25f;
		else if (i == hoveredCardIndex)
			s = 1.15f;
		playerHand[i].SetTargetScale(s);
	}
	for (int i = 0; i < playerBoard.size(); i++) {
		float s = 1.0f;

		if (i == attackerIndex)
			s = 1.15f;
		playerBoard[i].SetTargetScale(s);
	}

	game_board.DrawTable(this, resolution);
	playerDeck.DrawDeck(this);
	enemyDeck.DrawDeck(this);

	playerHero.DrawHero(this, resolution);
	playerHero.DrawHandCrystals(this);
	playerHero.DrawHealth(this);

	enemyHero.DrawHero(this, resolution);
	enemyHero.DrawHealth(this);

	timer.DrawTimer(this, resolution);
	timer.DrawButton(this, resolution);

	DrawPlayerBoardCards();
	DrawEnemyBoardCards();
	DrawEnemyHandCards();
	DrawPlayerHandCards();

	DrawArrowAttack();
	DrawEnemyAttackArrow();

	gameOver.DrawGameOver(this, resolution);
}

void Tema1::EndTurn() {
	timer.Reset();

	isDragged = false;
	selectedCardIndex = -1;
	attackerIndex = -1;
	enemyAttackIndex = -1;
	enemyAttackPending = false;
	enemyTargetIndex = -1;

	if (isPlayerTurn) {
		isPlayerTurn = false;
		SetBoardCanAttack(playerBoard, false);
		SetBoardCanAttack(enemyBoard, true);
		enemyTurnTime = 0.0f;
		enemyHasPlayed = false;
		enemyAttackTimer = 0.0f;
		enemyHero.StartTurn();
		DrawCardFromDeck(enemyDeck, enemyHand);
	}
	else {
		isPlayerTurn = true;
		SetBoardCanAttack(enemyBoard, false);
		SetBoardCanAttack(playerBoard, true);
		playerHero.StartTurn();
		DrawCardFromDeck(playerDeck, playerHand);
	}
}

void Tema1::FrameEnd() {

}

void Tema1::HandleCardSelection(int mouseX, int mouseY) {
	if (!isPlayerTurn)
		return;

	glm::ivec2 resolution = window->GetResolution();
	float oglMouseY = (float)resolution.y - (float)mouseY;
	float cardWidth = 100.0f;
	float cardHeight = 80.0f;

	for (int i = (int)playerHand.size() - 1; i >= 0; i--) {
		glm::vec2 pos = playerHand[i].GetPosition();
		if ((mouseX >= pos.x && mouseX <= pos.x + cardWidth) &&
			(oglMouseY >= pos.y && oglMouseY <= pos.y + cardHeight)) {
			selectedCardIndex = i;
			isDragged = true;
			break;
		}
	}
}

void Tema1::UpdateDraggedCardPosition(int mouseX, int mouseY) {
	if (isDragged && selectedCardIndex != -1) {
		glm::ivec2 resolution = window->GetResolution();
		float oglMouseY = (float)resolution.y - (float)mouseY;
		float cardWidth = 100.0f;
		float cardHeight = 80.0f;
		glm::vec2 dragPosition = glm::vec2(mouseX - cardWidth / 2.0f, oglMouseY - cardHeight / 2.0f);

		playerHand[selectedCardIndex].SetPosition(dragPosition);
	}
}

bool Tema1::IsValidBoardDrop(float mouseX, float oglMouseY, const glm::ivec2& resolution) {
	float width = (float)resolution.x;
	float margin = 50.0f;
	float play_area_width = width - (2.0f * margin) - 120.0f;

	float boardX = margin;
	float boardY = 100.0f;
	float boardWidth = play_area_width;
	float boardHeight = 130.0f;

	if ((mouseX >= boardX && mouseX <= boardX + boardWidth) &&
		oglMouseY >= boardY && oglMouseY <= boardY + boardHeight)
		return true;
	return false;
}

void Tema1::PlaceCardOnBoard(int cardIndex) {
	Card selectedCard = playerHand[cardIndex];
	playerHand.erase(playerHand.begin() + cardIndex);
	playerBoard.push_back(selectedCard);
}

void Tema1::HandleCardRelease(int mouseX, int mouseY) {
	if (!isDragged || selectedCardIndex == -1)
		return;

	glm::ivec2 resolution = window->GetResolution();
	float oglMouseY = (float)resolution.y - (float)mouseY;
	int cost = playerHand[selectedCardIndex].GetHandCost();

	if (IsValidBoardDrop((float)mouseX, oglMouseY, resolution) &&
		playerBoard.size() < MAX_BOARD && playerHero.GetCurrentHand() >= cost) {
		playerHero.SpendCost(cost);
		PlaceCardOnBoard(selectedCardIndex);
	}
		
	isDragged = false;
	selectedCardIndex = -1;
}

void Tema1::SetBoardCanAttack(vector<Card>& board, bool value) {
	for (size_t i = 0; i < board.size(); i++)
		board[i].SetCanAttack(value);
}

bool Tema1::IsOverCard(Card& card, float x, float y) {
	glm::vec2 pos = card.GetPosition();

	if ((x >= pos.x && x <= pos.x + CARD_WIDTH) &&
		(y >= pos.y && y <= pos.y + CARD_HEIGHT))
		return true;
	return false;
}

void Tema1::AttackCard(int targetCardIndex) {
	// both cards take damage at the same time
	Card& attackingCard = playerBoard[attackerIndex];
	Card& attackedCard = enemyBoard[targetCardIndex];
	int attackingDamage = attackingCard.GetAttackPoints();
	int attackedDamage = attackedCard.GetAttackPoints();

	attackedCard.TakeDamage(attackingDamage);
	attackingCard.TakeDamage(attackedDamage);

	attackingCard.SetCanAttack(false);

	attackerIndex = -1;
	RemoveDeadCards(playerBoard);
	RemoveDeadCards(enemyBoard);
}

void Tema1::AttackHero() {
	// hero has 0 attackPoints, so attacker takes no damage
	Card& attackingCard = playerBoard[attackerIndex];
	int attackingDamage = attackingCard.GetAttackPoints();

	enemyHero.TakeDamage(attackingDamage);

	attackingCard.SetCanAttack(false);
	attackerIndex = -1;
}

void Tema1::HandleAttackClick(int mouseX, int mouseY) {
	if (!isPlayerTurn)
		return;

	glm::ivec2 resolution = window->GetResolution();
	float oglMouseY = (float)resolution.y - (float)mouseY;

	// choose attacking card
	if (attackerIndex == -1) {
		for (int i = 0; i < playerBoard.size(); i++)
			if (playerBoard[i].GetCanAttack() &&
				IsOverCard(playerBoard[i], (float)mouseX, oglMouseY)) {
				attackerIndex = i;
				return;
			}			
		return;
	}

	// choose target -> enemy card
	for (int i = 0; i < enemyBoard.size(); i++)
		if (IsOverCard(enemyBoard[i], (float)mouseX, oglMouseY)) {
			AttackCard(i);
			return;
		}

	// choose target -> enemy hero
	if (enemyHero.IsPointInside((float)mouseX, oglMouseY)) {
		AttackHero();
		return;
	}

	attackerIndex = -1;
}

void Tema1::RemoveDeadCards(vector<Card>& cards) {
	for (int i = (int)cards.size() - 1; i >= 0; i--)
		if (cards[i].IsDead())
			cards.erase(cards.begin() + i);
}

void Tema1::DrawArrowAttack() {
	if (!isPlayerTurn || attackerIndex == -1 ||
		gameOver.IsOver() || attackerIndex >= playerBoard.size())
		return;

	glm::vec2 cardPos = playerBoard[attackerIndex].GetPosition();
	glm::vec2 start = cardPos + glm::vec2(CARD_WIDTH / 2.0f, CARD_HEIGHT / 2.0f);
	arrow.DrawArrow(this, start, mousePos);
}

void Tema1::EnemyAttackPlayerCard(int attackerIndex, int targetIndex) {
	Card& attackingCard = enemyBoard[attackerIndex];
	Card& attackedCard = playerBoard[targetIndex];

	int attackingDamage = attackingCard.GetAttackPoints();
	int attackedDamage = attackedCard.GetAttackPoints();

	attackedCard.TakeDamage(attackingDamage);
	attackingCard.TakeDamage(attackedDamage);
	attackingCard.SetCanAttack(false);
}

void Tema1::EnemyAttackHeroCard(int attackerIndex) {
	Card& attackingCard = enemyBoard[attackerIndex];

	int attackingDamage = attackingCard.GetAttackPoints();
	playerHero.TakeDamage(attackingDamage);
	attackingCard.SetCanAttack(false);
}

bool Tema1::EnemyChooseAttack() {
	vector<int> attackers;

	for (int i = 0; i < enemyBoard.size(); i++)
		if (enemyBoard[i].GetCanAttack())
			attackers.push_back(i);
	if (attackers.empty())
		return false;

	enemyAttackIndex = attackers[rand() % attackers.size()];
	enemyTargetIndex = rand() % (playerBoard.size() + 1);  // [0...size - 1] for player cards, [size] for player hero
	enemyAttackPending = true;
	enemyArrowTimer = 0.0f;
	return true;
}

void Tema1::EnemyExecuteAttack() {
	if (enemyAttackIndex >= 0 && enemyAttackIndex < enemyBoard.size()) {
		if (enemyTargetIndex == playerBoard.size())
			EnemyAttackHeroCard(enemyAttackIndex);
		else
			EnemyAttackPlayerCard(enemyAttackIndex, enemyTargetIndex);
		RemoveDeadCards(playerBoard);
		RemoveDeadCards(enemyBoard);
	}
	enemyAttackIndex = -1;
	enemyAttackPending = false;
	enemyTargetIndex = -1;
}

void Tema1::DrawEnemyAttackArrow() {
	if (!enemyAttackPending || gameOver.IsOver() || enemyAttackIndex == -1)
		return;

	glm::vec2 cardPos = enemyBoard[enemyAttackIndex].GetPosition();
	glm::vec2 start = cardPos + glm::vec2(CARD_WIDTH / 2.0f, CARD_HEIGHT / 2.0f);
	glm::vec2 end;
	if (enemyTargetIndex == playerBoard.size())
		end = playerHero.GetCenter();
	else if (enemyTargetIndex != -1) {
		glm::vec2 targetPos = playerBoard[enemyTargetIndex].GetPosition();
		end = targetPos + glm::vec2(CARD_WIDTH / 2.0f, CARD_HEIGHT / 2.0f);
	}
	else
		return;
	arrow.DrawArrow(this, start, end);
		
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	if (gameOver.IsOver())
		return;

	glm::ivec2 resolution = window->GetResolution();
	mousePos = glm::vec2((float)mouseX, (float)(resolution.y - mouseY));

	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		if (isPlayerTurn && timer.CheckButtonClick(mouseX, mouseY, resolution))
			EndTurn();

		HandleCardSelection(mouseX, mouseY);
		HandleAttackClick(mouseX, mouseY);
	}
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	if (gameOver.IsOver())
		return;
	glm::ivec2 resolution = window->GetResolution();
	mousePos = glm::vec2((float)mouseX, (float)(resolution.y - mouseY));
	UpdateDraggedCardPosition(mouseX, mouseY);
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
	if (gameOver.IsOver())
		return;

	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && isDragged) {
		HandleCardRelease(mouseX, mouseY);
	}
}
