#pragma once

#include <glm/glm.hpp>

namespace m1 {
	class Tema1;
}

class Timer {
public:
	Timer();
	~Timer();

	void Update(float deltaTimeSeconds);
	void Reset();

	bool IsExpired();

	void DrawTimerBackground(m1::Tema1* scene, const glm::ivec2& resolution);
	void DrawTimerBar(m1::Tema1* scene, const glm::ivec2& resolution);
	void DrawTimer(m1::Tema1* scene, const glm::ivec2& resolution);

	// End Turn button
	void DrawButton(m1::Tema1* scene, const glm::ivec2& resolution);
	bool CheckButtonClick(double mouseX, double mouseY, const glm::ivec2& resolution);

private:
	float duration;
	float timeLeft;
};
