#include "timer.h"
#include "tema1.h"
#include "colors.h"
#include <iostream>

using namespace std;

Timer::Timer() : duration(30.0f), timeLeft(30.0f) {}
Timer::~Timer() {}

void Timer::Update(float deltaTimeSeconds) {
	if (timeLeft > 0.0f) {
		timeLeft -= deltaTimeSeconds;
		if (timeLeft < 0.0f)
			timeLeft = 0.0f;
	}
}

void Timer::Reset() {
	timeLeft = duration;
}

bool Timer::IsExpired() {
	if (timeLeft <= 0.0f)
		return true;
	return false;
}

void Timer::DrawTimerBackground(m1::Tema1* scene, const glm::ivec2& resolution) {
	float width = 100.0f;
	float heigth = 50.0f;

	float posX = resolution.x - 30.0f - width;
	float posY = (resolution.y - heigth) / 2.0f;

	glm::mat4 backgroundMatrix = glm::mat4(1.0f);
	backgroundMatrix = glm::translate(backgroundMatrix, glm::vec3(posX, posY, 0.0f));
	backgroundMatrix = glm::scale(backgroundMatrix, glm::vec3(width, heigth, 1.0f));

	glm::vec3 backgroundColor = Colors::TIMER_BACKGROUND_COLOR;
	scene->RenderSquare(backgroundMatrix, backgroundColor);
}

void Timer::DrawTimerBar(m1::Tema1* scene, const glm::ivec2& resolution) {
	float width = 100.0f;
	float heigth = 50.0f;

	float posX = resolution.x - 30.0f - width;
	float posY = (resolution.y - heigth) / 2.0f;

	float timeRatio = timeLeft / duration;

	glm::mat4 foregroundMatrix = glm::mat4(1.0f);
	foregroundMatrix = glm::translate(foregroundMatrix, glm::vec3(posX, posY, 0.0f));
	foregroundMatrix = glm::scale(foregroundMatrix, glm::vec3(width * timeRatio, heigth, 1.0f));

	glm::vec3 barColor;
	if (timeLeft < 5.0f)
		barColor = Colors::TIMER_BAR_CRTICAL_COLOR;
	else
		barColor = Colors::TIMER_BAR_NORMAL_COLOR;

	scene->RenderSquare(foregroundMatrix, barColor);
}

void Timer::DrawTimer(m1::Tema1* scene, const glm::ivec2& resolution) {
	DrawTimerBackground(scene, resolution);
	DrawTimerBar(scene, resolution);
}

void Timer::DrawButton(m1::Tema1* scene, const glm::ivec2& resolution) {
	float width = 100.0f;
	float heigth = 50.0f;

	float posX = resolution.x - 30.0f - width;
	float posY = (resolution.y - heigth) / 2.0f - 70.0f;

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(posX, posY, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(width, heigth, 1.0f));

	glm::vec3 buttonColor = Colors::BUTTON_END_TURN;
	scene->RenderSquare(modelMatrix, buttonColor);
}

bool Timer::CheckButtonClick(double mouseX, double mouseY, const glm::ivec2& resolution) {
	float width = 100.0f;
	float heigth = 50.0f;

	float posX = resolution.x - 30.0f - width;
	float posY = (resolution.y - heigth) / 2.0f - 70.0f;

	float oglMouseY = (float)resolution.y - (float)mouseY;

	if ((mouseX >= posX && mouseX <= posX + width) &&
		(oglMouseY >= posY && oglMouseY <= posY + heigth))
		return true;
	return false;
}
