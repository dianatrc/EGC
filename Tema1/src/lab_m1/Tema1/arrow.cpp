#include "arrow.h"
#include "tema1.h"
#include "colors.h"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Arrow::Arrow() : thickness(5.0f), headLength(20.0f), headWidth(20.0f) {}

Arrow::~Arrow() {}

void Arrow::DrawBody(m1::Tema1* scene, const glm::mat4& base_matrix, float bodyLength) {
	glm::mat4 model_matrix = base_matrix;
	glm::vec3 color = Colors::BLACK;

	model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, -thickness / 2.0f, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(bodyLength, thickness, 1.0f));
	scene->RenderSquare(model_matrix, color);
}

void Arrow::DrawHead(m1::Tema1* scene, const glm::mat4& base_matrix, float bodyLength) {
	glm::mat4 model_matrix = base_matrix;
	glm::vec3 color = Colors::BLACK;

	model_matrix = glm::translate(model_matrix, glm::vec3(bodyLength, headWidth / 2.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(headWidth, headLength, 1.0f));
	scene->RenderShape(0, model_matrix, color);
}
bool Arrow::ArrowGeometry(const glm::vec2& start, const glm::vec2& end,
	float& angle, float& bodyLength) {
	glm::vec2 diff = end - start;
	float length = glm::length(diff);

	if (length < 1.0f)
		return false;
	angle = atan2(diff.y, diff.x);
	bodyLength = length - headLength;
	if (bodyLength < 0.0f)
		bodyLength = 0.0f;
	return true;
}

void Arrow::DrawArrow(m1::Tema1* scene, const glm::vec2& start, const glm::vec2& end) {
	float angle = 0.0f;
	float bodyLength = 0.0f;

	if (!ArrowGeometry(start, end, angle, bodyLength))
		return;
	glm::mat4 base_matrix = glm::mat4(1.0f);
	base_matrix = glm::translate(base_matrix, glm::vec3(start.x, start.y, 0.0f));
	base_matrix = glm::rotate(base_matrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	DrawBody(scene, base_matrix, bodyLength);
	DrawHead(scene, base_matrix, bodyLength);
}
