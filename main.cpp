#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define BALL_WIDTH 5
#define BALL_HEIGHT 5
#define PADDLE_HEIGHT 40
#define PADDLE_WIDTH 10

#define PIXEL_WIDTH 2
#define PIXEL_HEIGHT 2

enum CollisionType {
	Top,
	Middle,
	Bottom,
	None
};

class pong : public olc::PixelGameEngine
{
	//float fBatPos = 20.0f;
	//float fBatSpeed = 0.1f;
	//float fBatWidth = 40.0f;
	float fTargetFrameTime = 1.0f / 144.0f; // 144 vfps
	float fAccumulatedTime = 0.0f;
	olc::vf2d vBall = { 200.0f, 200.0f };
	olc::vf2d vBallVel = { -1.0f, 0.0f };
	olc::vf2d pad1 = { 20.0f / PIXEL_WIDTH, ScreenHeight() - 20 };
	olc::vf2d pad2 = { ScreenWidth() * PIXEL_WIDTH - 20.0f, ScreenHeight() - 20};
	float ball_dir_x = -1.0f;
	float ball_dir_y = 0.0f;
	float ball_speed = 1.5;
public:
	pong()
	{
		sAppName = "pong";
	}

public:
	CollisionType CheckPaddleCollision1()
	{
		float ballLeft = this->vBall.x;
		float ballRight = this->vBall.x + BALL_WIDTH;
		float ballTop = this->vBall.y;
		float ballBottom = this->vBall.y + BALL_HEIGHT;

		float paddleLeft = this->pad1.x;
		float paddleRight = this->pad1.x + PADDLE_WIDTH;
		float paddleTop = this->pad1.y;
		float paddleBottom = this->pad1.y + PADDLE_HEIGHT;

		if (ballLeft >= paddleRight)
		{
			return CollisionType::None;
		}

		if (ballRight <= paddleLeft)
		{
			return CollisionType::None;
		}

		if (ballTop >= paddleBottom)
		{
			return CollisionType::None;
		}

		if (ballBottom <= paddleTop)
		{
			return CollisionType::None;
		}

		float paddleRangeUpper = paddleBottom - (2.0f * PADDLE_HEIGHT / 3.0f);
		float paddleRangeMiddle = paddleBottom - (PADDLE_HEIGHT / 3.0f);

		if ((ballBottom > paddleTop)
			&& (ballBottom < paddleRangeUpper))
		{
			return CollisionType::Top;
		}
		else if ((ballBottom > paddleRangeUpper)
			&& (ballBottom < paddleRangeMiddle))
		{
			return CollisionType::Middle;
		}
		else
		{
			return CollisionType::Bottom;
		}
	}

	CollisionType CheckPaddleCollision2()
	{
		float ballLeft = this->vBall.x;
		float ballRight = this->vBall.x + BALL_WIDTH;
		float ballTop = this->vBall.y;
		float ballBottom = this->vBall.y + BALL_HEIGHT;

		float paddleLeft = this->pad2.x;
		float paddleRight = this->pad2.x + PADDLE_WIDTH;
		float paddleTop = this->pad2.y;
		float paddleBottom = this->pad2.y + PADDLE_HEIGHT;

		if (ballLeft >= paddleRight)
		{
			return CollisionType::None;
		}

		if (ballRight <= paddleLeft)
		{
			return CollisionType::None;
		}

		if (ballTop >= paddleBottom)
		{
			return CollisionType::None;
		}

		if (ballBottom <= paddleTop)
		{
			return CollisionType::None;
		}

		float paddleRangeUpper = paddleBottom - (2.0f * PADDLE_HEIGHT / 3.0f);
		float paddleRangeMiddle = paddleBottom - (PADDLE_HEIGHT / 3.0f);

		if ((ballBottom > paddleTop)
			&& (ballBottom < paddleRangeUpper))
		{
			return CollisionType::Top;
		}
		else if ((ballBottom > paddleRangeUpper)
			&& (ballBottom < paddleRangeMiddle))
		{
			return CollisionType::Middle;
		}
		else
		{
			return CollisionType::Bottom;
		}
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= fTargetFrameTime)
		{
			fAccumulatedTime -= fTargetFrameTime;
			fElapsedTime = fTargetFrameTime;
		}
		else
			return true; // Don't do anything this frame
		//std::this_thread::sleep_for(std::chrono::microseconds(1));
		Clear(0);
		// Handle User Input
		/*
		if (GetKey(olc::Key::LEFT).bHeld) fBatPos -= fBatSpeed;
		if (GetKey(olc::Key::RIGHT).bHeld) fBatPos += fBatSpeed;*/
		if (GetKey(olc::Key::W).bHeld && (pad1.y >= 0)) pad1.y -= 3.0f;
		if (GetKey(olc::Key::S).bHeld && (pad1.y + PADDLE_HEIGHT <= ScreenHeight())) pad1.y += 3.0f;
		if (GetKey(olc::Key::UP).bHeld && (pad2.y >= 0)) pad2.y -= 3.0f;
		if (GetKey(olc::Key::DOWN).bHeld && (pad2.y + PADDLE_HEIGHT <= ScreenHeight())) pad2.y += 3.0f;
		vBall.x += vBallVel.x * ball_speed;
		vBall.y += vBallVel.y * ball_speed;
		CollisionType collision1 = CheckPaddleCollision1();
		CollisionType collision2 = CheckPaddleCollision2();
		std::cout << pad1.y << std::endl;
		//std::cout << ScreenHeight() << std::endl;
		//std::cout << (pad1.y + PADDLE_HEIGHT >= ScreenHeight()) << std::endl;
		
		//std::cout << pad2.y << std::endl;
		if (vBall.x >= ScreenWidth()) { //right
			std::cout << "right" << std::endl;
			vBallVel.x = -vBallVel.x;
		}
		else if (vBall.x <= 0) { //left
			std::cout << "left" << std::endl;
			vBallVel.x = -vBallVel.x;
		}
		else if (vBall.y <= 0) {
			vBallVel.y = -vBallVel.y;
		}
		else if (vBall.y >= ScreenHeight()) {
			vBallVel.y = -vBallVel.y;
		}
		else if (collision1 == CollisionType::Top) {
			vBallVel.x = -vBallVel.x;
			vBallVel.y = -.75f * ball_speed;
		}
		else if (collision1 == CollisionType::Bottom) {
			vBallVel.x = -vBallVel.x;
			vBallVel.y = .75f * ball_speed;
		}
		else if (collision1 == CollisionType::Middle) {
			vBallVel.x = -vBallVel.x;
		}
		else if (collision2 == CollisionType::Top) {
			vBallVel.x = -vBallVel.x;
			vBallVel.y = -.75f * ball_speed;
		}
		else if (collision2 == CollisionType::Bottom) {
			vBallVel.x = -vBallVel.x;
			vBallVel.y = .75f * ball_speed;
		}
		else if (collision2 == CollisionType::Middle) {
			vBallVel.x = -vBallVel.x;
		}
		//std::cout << "Ball X: " << vBall.x
		//	<< std::endl << "Ball Y: " << vBall.y << std::endl;
		//std::cout << ScreenHeight() << std::endl;
		/*if (collision == CollisionType::Top) {
			std::cout << "collide" << std::endl;
		}*/
		FillRect(pad1.x, pad1.y, PADDLE_WIDTH, PADDLE_HEIGHT, olc::GREEN);
		FillRect(pad2.x, pad2.y, PADDLE_WIDTH, PADDLE_HEIGHT, olc::RED);
		FillRect(vBall.x, vBall.y, BALL_WIDTH, BALL_HEIGHT, olc::CYAN);
		
		return true;
	}
};


int main(int argc, char** argv) {
	pong demo;
	if (demo.Construct(512, 480, PIXEL_WIDTH, PIXEL_WIDTH))
		demo.Start();

	return 0;
}