#include "camera.h"

ConstCamera::ConstCamera()
{
	Position = glm::vec3(0.f, 0.f, 55.f);
	Zoom = ZOOM;
}

float ConstCamera::getZoom()
{
	return Zoom;
}

glm::mat4 ConstCamera::GetViewMatrix()
{
	return glm::lookAt(Position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void ConstCamera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

glm::vec3 ConstCamera::getPosition()
{
	return Position;
}

void ToBallCamera::updateBallPosition(glm::vec3 ballPosition)
{
	BallPosition = ballPosition;
}

ToBallCamera::ToBallCamera(glm::vec3 ballPosition)
{
	Zoom = ZOOM;
	Position = glm::vec3(0.0f, 0.0f, 10.0f);
	BallPosition = ballPosition;
}

float ToBallCamera::getZoom()
{
	return Zoom;
}

glm::mat4 ToBallCamera::GetViewMatrix()
{
	return glm::lookAt(Position, BallPosition, glm::vec3(0.0f, 1.0f, 0.0f));
}

void ToBallCamera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

glm::vec3 ToBallCamera::getPosition()
{
	return Position;
}

void FollowCamera::updateBallPosition(glm::vec3 ballPosition)
{
	BallPosition = ballPosition;
	Position = ballPosition + glm::vec3(3.0f, 3.0f, 3.0f);
}

FollowCamera::FollowCamera(glm::vec3 ballPosition)
{
	Zoom = ZOOM;
	BallPosition = ballPosition;
	Position = ballPosition + glm::vec3(3.0f, 3.0f, 3.0f);
}

float FollowCamera::getZoom()
{
	return Zoom;
}

glm::vec3 FollowCamera::getPosition()
{
	return Position;
}

glm::mat4 FollowCamera::GetViewMatrix()
{
	return glm::lookAt(Position, BallPosition, glm::vec3(0.0f, 0.0f, 1.0f));
}

void FollowCamera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}
