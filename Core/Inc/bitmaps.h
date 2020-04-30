/*
 * bitmaps.h
 *
 *  Created on: 29 apr. 2020
 *      Author: Rutger
 */

#ifndef INC_BITMAPS_H_
#define INC_BITMAPS_H_

/**
 * Made with Marlin Bitmap Converter
 * https://marlinfw.org/tools/u8glib/converter.html
 *
 * This bitmap from the file 'megaman-sprite.bmp'
 */

#pragma once

#define MEGAMAN_WIDTH  21
#define MEGAMAN_HEIGHT  24

const unsigned char megaman[] = {
    0B11111111, 0B11000111, 0B11111111, // ##########...###########
    0B11111111, 0B00000011, 0B11111111, // ########......##########
	0B11111110, 0B00001001, 0B11111111, // #######.....#..#########
	0B11111100, 0B00000000, 0B11111111, // ######..........########
	0B11111100, 0B00000000, 0B01111111, // ######...........#######
	0B11111000, 0B00000000, 0B01111111, // #####............#######
	0B11111000, 0B01111001, 0B01111111, // #####....####..#.#######
	0B11111000, 0B11100101, 0B01111111, // #####...###..#.#.#######
	0B11111100, 0B11100101, 0B01111111, // ######..###..#.#.#######
	0B11111000, 0B11111111, 0B01111111, // #####...########.#######
	0B11100010, 0B01000010, 0B00111111, // ###...#..#....#...######
	0B11001111, 0B01111101, 0B10011111, // ##..####.#####.##..#####
	0B11000101, 0B10000001, 0B00011111, // ##...#.##......#...#####
	0B10000000, 0B11111000, 0B00001111, // #.......#####.......####
	0B10000000, 0B11111100, 0B00001111, // #.......######......####
	0B10000000, 0B11111000, 0B00001111, // #.......#####.......####
	0B10000000, 0B00000000, 0B00001111, // #...................####
	0B11000100, 0B00000001, 0B00011111, // ##...#.........#...#####
	0B11111001, 0B00001100, 0B11111111, // #####..#....##..########
	0B11110001, 0B10001110, 0B01111111, // ####...##...###..#######
	0B11100000, 0B00100000, 0B00111111, // ###.......#.......######
	0B10000000, 0B01110000, 0B00001111, // #........###........####
	0B00000000, 0B01110000, 0B00000111, // .........###.........###
	0B00000000, 0B01110000, 0B00000111  // .........###.........###
};




#endif /* INC_BITMAPS_H_ */