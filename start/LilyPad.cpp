#include "LilyPad.h"

LilyPad::LilyPad() : Entity()
{
	this->addSprite("assets/lilypad.tga");
	this->scale = Point3(0.8,0.8,0.8);
	//std::cout << "LilypadSprite added" << std::endl;
}

LilyPad::~LilyPad()
{

}

void LilyPad::update(float deltaTime)
{
	if (this == NULL) return;
	if (input()->getMouseDown(0) && this->isCursorOnObject2d()) {
		std::cout << "Clicked on lilypad!" << std::endl;
	}
}

Point3 LilyPad::getSizePerspective() {
	return Point3(this->sprite()->size.x * this->scale.x, this->sprite()->size.y * this->scale.y, 0);
}

Point3 LilyPad::getSize() {
	return Point3(this->sprite()->size.x, this->sprite()->size.y, 0);
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