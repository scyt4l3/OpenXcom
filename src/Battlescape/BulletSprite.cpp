/*
 * Copyright 2010 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include "BulletSprite.h"

namespace OpenXcom
{

// the fantastic harcoded pixel-art
const int BulletSprite::pixels[37][9] = {
{ 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00 },
{ 0x26, 0x22, 0x26, 0x22, 0x22, 0x22, 0x26, 0x22, 0x26 },
{ 0x55, 0x52, 0x55, 0x52, 0x52, 0x52, 0x55, 0x52, 0x55 },
{ 0x00, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x20, 0x00, 0x20, 0x10, 0x20, 0x00, 0x20, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00 },
{ 0x07, 0x00, 0x07, 0x00, 0x04, 0x00, 0x07, 0x00, 0x07 },
{ 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00 },
{ 0x26, 0x20, 0x26, 0x20, 0x90, 0x20, 0x26, 0x20, 0x02 },
{ 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00 },
{ 0x28, 0x22, 0x28, 0x22, 0x10, 0x22, 0x28, 0x22, 0x28 },
{ 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x81, 0x00, 0x81, 0x80, 0x81, 0x00, 0x81, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00, 0x00 },
{ 0x07, 0x00, 0x07, 0x00, 0x91, 0x00, 0x07, 0x00, 0x07 },
{ 0x00, 0x00, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x93, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00, 0x00 },
{ 0x46, 0x43, 0x46, 0x43, 0x40, 0x43, 0x46, 0x43, 0x46 },
{ 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00 },
{ 0xC6, 0xC3, 0xC6, 0xC3, 0xC0, 0xC3, 0xC6, 0xC3, 0xC6 },
{ 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

/**
 * Sets up a BulletSprite 3x3 surface.
 */
BulletSprite::BulletSprite(int type) : Surface(3, 3), _type(type)
{
}

/**
 * Deletes the BulletSprite.
 */
BulletSprite::~BulletSprite()
{

}

/**
 * Draws a BulletSprite
 */
void BulletSprite::draw()
{
	lock();
	for (int y = 0; y < 3;y++)
	{
		for (int x = 0; x < 3; x++)
		{
			this->setPixel(x, y, pixels[_type][x+(y*3)]);
		}
	}
	unlock();
}

/**
 * Blits the BulletSprite onto another surface. 
 * @param surface Pointer to another surface.
 */
void BulletSprite::blit(Surface *surface)
{
	Surface::blit(surface);
}

}
