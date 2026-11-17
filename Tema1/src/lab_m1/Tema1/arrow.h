#pragma once

#include <glm/glm.hpp>

namespace m1 {
	class Tema1;
}

class Arrow {
public:
	Arrow();
	~Arrow();

	void DrawArrow(m1::Tema1* scene, const glm::vec2& start, const glm::vec2& end);

private:
	bool ArrowGeometry(const glm::vec2& start, const glm::vec2& end,
		float& angle, float& bodyLength);

	void DrawBody(m1::Tema1* scene, const glm::mat4& base_matrix, float bodyLength);
	void DrawHead(m1::Tema1* scene, const glm::mat4& base_matrix, float bodyLength);

private:
	float thickness;
	float headLength;
	float headWidth;
};
