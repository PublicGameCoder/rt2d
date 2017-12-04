#include "LilyPad.h"

LilyPad::LilyPad() : Entity()
{
	this->addSprite("assets/lilypad.tga");
	this->sprite()->size = Point2(96, 96);
	//this->sprite()->setupSprite("assets/lilypad.tga", 0,0, 1.0f / 128, 1.0f / 128);
	this->scale = Point3(0.85,0.85,1);
}

LilyPad::~LilyPad()
{

}

void LilyPad::update(float deltaTime)
{
	/*
	if (input()->getMouseDown(0) && this->isCursorOnObject2d()) {
		std::cout << "Clicked on lilypad!" << std::endl;
	}
	*/
}

bool LilyPad::isCursorOnObject2d() {
	int mouseX = this->input()->getMouseX();
	int mouseY = this->input()->getMouseY();
	Point3 pos = this->worldposition();
	int halfwidth = (this->sprite()->size.x *this->scale.x) / 2;
	int halfheight = (this->sprite()->size.y *this->scale.y) / 2;
	int left = pos.x - halfwidth;
	int right = pos.x + halfwidth;
	int top = pos.y - halfheight;
	int bottom = pos.y + halfheight;

	if (mouseX > left && mouseX < right && mouseY > top && mouseY < bottom) {
		return true;
	}
	return false;
}