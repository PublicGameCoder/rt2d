/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include "scene04.h"

Scene04::Scene04() : SuperScene()
{
	t.start();
	rt.start();
	
	text[0]->message("Scene04: Dynamic PixelBuffer as Texture");
	//text[1]->message("");
	text[2]->message("<ESC> next scene");
	text[3]->message("<SPACE> pause state");
	
	// container for Sprite with custom Texture
	pixel_container = new BasicEntity();
	pixel_container->position = Point2(SWIDTH/2, SHEIGHT/2);
	pixel_container->scale = Point2(5.0f, 5.0f);
	
	// width, height, bitdepth, filter
	PixelBuffer* pixels = new PixelBuffer(128, 128, 3, 0);
	pixel_container->addDynamicSprite(pixels);
	delete pixels;

	layers[0]->addChild(pixel_container);
}


Scene04::~Scene04()
{
	layers[0]->removeChild(pixel_container);
	delete pixel_container;
}

void Scene04::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);
	
	// ###############################################################
	// pixel_container
	// ###############################################################
	pixel_container->rotation += PI / 16 * deltaTime;
	//pixel_container->sprite()->uvoffset += Point2(deltaTime/8, deltaTime/8);
	
	// change state every n seconds, pause timer when SPACE is pressed
	static int state = 0;
	if (input()->getKey( GLFW_KEY_SPACE )) {
		t.pause();
	}
	if (input()->getKeyUp( GLFW_KEY_SPACE )) {
		t.unpause();
	}
	
	if (t.seconds() > 1.0f) {
		state++;
		if (state > 13) { state = 0; }
		t.start();
	}
	
	// change pixels according to state
	float statetime = 0.02f; // 0.0167 is 60 fps
	if (rt.seconds() > statetime) {
		// get the pixels
		PixelBuffer* buff = pixel_container->sprite()->texture()->pixels();
		switch (state) {
			case 0:
				spectrumPixels(buff, 0);
				text[3]->message("<SPACE> pause state (spectrum unfiltered)");
				break;
			case 1:
				spectrumPixels(buff, 1);
				text[3]->message("<SPACE> pause state (spectrum filtered)");
				break;
			case 2:
				checkerPixels(buff, 32, WHITE, BLACK);
				text[3]->message("<SPACE> pause state (checker 32 px)");
				break;
			case 3:
				checkerPixels(buff, 16, RED, BLUE);
				text[3]->message("<SPACE> pause state (checker 16 px)");
				break;
			case 4:
				checkerPixels(buff, 8, ORANGE, CYAN);
				text[3]->message("<SPACE> pause state (checker 8 px)");
				break;
			case 5:
				checkerPixels(buff, 4, YELLOW, RED);
				text[3]->message("<SPACE> pause state (checker 4 px)");
				break;
			case 6:
				checkerPixels(buff, 2, YELLOW, BLUE);
				text[3]->message("<SPACE> pause state (checker 2 px)");
				break;
			case 7:
				checkerPixels(buff, 1, WHITE, BLACK);
				text[3]->message("<SPACE> pause state (checker 1 px)");
				break;
			case 8:
				randomPixels(buff, 0);
				text[3]->message("<SPACE> pause state (random unfiltered)");
				break;
			case 9:
				randomPixels(buff, 1);
				text[3]->message("<SPACE> pause state (random filtered)");
				break;
			case 10:
				rainbowPixels(buff, 2, 0);
				text[3]->message("<SPACE> pause state (rainbow full unfiltered)");
				break;
			case 11:
				rainbowPixels(buff, 2, 3);
				text[3]->message("<SPACE> pause state (rainbow full filtered)");
				break;
			case 12:
				rainbowPixels(buff, 4, 0);
				text[3]->message("<SPACE> pause state (double rainbow unfiltered)");
				break;
			case 13:
				rainbowPixels(buff, 4, 3);
				text[3]->message("<SPACE> pause state (double rainbow filtered)");
				break;
			default:
				break;
		}
		rt.start();
	}
}

void Scene04::spectrumPixels(PixelBuffer* pixels, int filter)
{
	// hue, saturation, brightness
	HSVColor hsv = HSVColor(0.0f, 0.0f, 1.0f); // initially white
	
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		if (y < pixels->height/2) {
			hsv.s += 1.0f/pixels->height*2; if (hsv.s > 1.0f) { hsv.s -= 1.0f; } // Saturation
		} else {
			hsv.v -= 1.0f/pixels->height*2; if (hsv.v < 0.0f) { hsv.v += 1.0f; } // Brightness
		}
		
		for (long x=0; x<pixels->width; x++) {
			hsv.h += 1.0f/pixels->width; if (hsv.h > 1.0f) { hsv.h -= 1.0f; } // Hue
			RGBAColor rgb = Color::HSV2RGBA(hsv);
			
			pixels->data[counter+0] = rgb.r;
			pixels->data[counter+1] = rgb.g;
			pixels->data[counter+2] = rgb.b;
			if (pixels->bitdepth == 4) {
				pixels->data[counter+3] = 1.0f;
			}
			
			counter += pixels->bitdepth;
		}
	}
	pixels->filter = filter;
}

void Scene04::randomPixels(PixelBuffer* pixels, int filter)
{
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		for (long x=0; x<pixels->width; x++) {
			pixels->data[counter+0] = rand()%255;
			pixels->data[counter+1] = rand()%255;
			pixels->data[counter+2] = rand()%255;
			if (pixels->bitdepth == 4) {
				pixels->data[counter+3] = rand()%255;
			}
			
			counter += pixels->bitdepth;
		}
	}
	pixels->filter = filter;
}

void Scene04::rainbowPixels(PixelBuffer* pixels, float step, int filter)
{
	RGBAColor c = RED;
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		c = Color::rotate(c, step/255);
	
		for (long x=0; x<pixels->width; x++) {
			pixels->data[counter+0] = c.r;
			pixels->data[counter+1] = c.g;
			pixels->data[counter+2] = c.b;
			if (pixels->bitdepth == 4) {
				pixels->data[counter+3] = c.a;
			}
			
			counter += pixels->bitdepth;
		}
	}
	pixels->filter = filter;
}

void Scene04::checkerPixels(PixelBuffer* pixels, int cellwidth, RGBAColor a, RGBAColor b)
{
	RGBAColor color;
	int swapper = 1;
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		if (y%cellwidth == 0) { swapper *= -1; }
		for (long x=0; x<pixels->width; x++) {
			if (x%cellwidth == 0) { swapper *= -1; }
			
			if (swapper == 1) { color = a; }
			if (swapper == -1) { color = b; }
			
			pixels->data[counter+0] = color.r;
			pixels->data[counter+1] = color.g;
			pixels->data[counter+2] = color.b;
			if (pixels->bitdepth == 4) {
				pixels->data[counter+3] = color.a;
			}
			
			counter += pixels->bitdepth;
		}
	}
	pixels->filter = 0;
}
