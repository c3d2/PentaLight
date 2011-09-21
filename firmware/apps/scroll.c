#include <main.h>

#ifdef __AVR__
#include <avr/pgmspace.h>
#endif


void init_scroll(void) ATTRIBUTES;

#ifdef __AVR__
const uint8_t font[][3] PROGMEM = {
#else
const uint8_t font[][3] = {
#endif
	{0x00,0x00,0x00}, //  
	{0x00,0x1D,0x00}, // !
	{0x18,0x00,0x18}, // "
	{0x1F,0x0A,0x1F}, // #
	{0x0A,0x1F,0x14}, // $
	{0x12,0x04,0x09}, // %
	{0x0A,0x15,0x0B}, // &
	{0x00,0x18,0x00}, // '
	{0x00,0x0E,0x11}, // (
	{0x11,0x0E,0x00}, // )
	{0x15,0x0E,0x15}, // *
	{0x04,0x0E,0x04}, // +
	{0x01,0x02,0x00}, // ,
	{0x04,0x04,0x04}, // -
	{0x00,0x03,0x00}, // .
	{0x02,0x04,0x08}, // /
	{0x1F,0x11,0x1F}, // 0
	{0x00,0x1F,0x00}, // 1
	{0x17,0x15,0x1D}, // 2
	{0x11,0x15,0x1F}, // 3
	{0x1C,0x04,0x1F}, // 4
	{0x1D,0x15,0x17}, // 5
	{0x1F,0x15,0x17}, // 6
	{0x10,0x10,0x1F}, // 7
	{0x1F,0x15,0x1F}, // 8
	{0x1D,0x15,0x1F}, // 9
	{0x00,0x0A,0x00}, // :
	{0x01,0x0A,0x00}, // ;
	{0x04,0x0A,0x11}, // <
	{0x0A,0x0A,0x0A}, // =
	{0x11,0x0A,0x04}, // >
	{0x10,0x15,0x18}, // ?
	{0x0E,0x15,0x0D}, // @
	{0x0F,0x14,0x0F}, // A
	{0x1F,0x15,0x0A}, // B
	{0x0E,0x11,0x11}, // C
	{0x1F,0x11,0x0E}, // D
	{0x1F,0x15,0x15}, // E
	{0x1F,0x14,0x14}, // F
	{0x0E,0x15,0x17}, // G
	{0x1F,0x04,0x1F}, // H
	{0x11,0x1F,0x11}, // I
	{0x02,0x01,0x1E}, // J
	{0x1F,0x04,0x1B}, // K
	{0x1F,0x01,0x01}, // L
	{0x1F,0x0C,0x1F}, // M
	{0x1F,0x0E,0x1F}, // N
	{0x0E,0x11,0x0E}, // O
	{0x1F,0x14,0x08}, // P
	{0x0E,0x13,0x0F}, // Q
	{0x1F,0x16,0x0D}, // R
	{0x09,0x15,0x12}, // S
	{0x10,0x1F,0x10}, // T
	{0x1E,0x01,0x1F}, // U
	{0x1C,0x03,0x1C}, // V
	{0x1F,0x06,0x1F}, // W
	{0x1B,0x04,0x1B}, // X
	{0x18,0x07,0x18}, // Y
	{0x13,0x15,0x19}, // Z
	{0x1F,0x11,0x11}, // [
	{0x08,0x04,0x02}, // '\'
	{0x11,0x11,0x1F}, // ]
	{0x08,0x10,0x08}, // ^
	{0x01,0x01,0x01}, // _
	{0x10,0x08,0x00}, // `
	{0x03,0x05,0x07}, // a
	{0x1F,0x05,0x02}, // b
	{0x02,0x05,0x05}, // c
	{0x02,0x05,0x1F}, // d
	{0x06,0x0B,0x0D}, // e
	{0x04,0x0F,0x14}, // f
	{0x05,0x0D,0x0E}, // g
	{0x1F,0x04,0x03}, // h
	{0x00,0x17,0x00}, // i
	{0x01,0x01,0x16}, // j
	{0x0F,0x02,0x05}, // k
	{0x11,0x1F,0x01}, // l
	{0x07,0x06,0x07}, // m
	{0x07,0x04,0x03}, // n
	{0x02,0x05,0x02}, // o
	{0x07,0x0A,0x04}, // p
	{0x04,0x0A,0x07}, // q
	{0x0F,0x04,0x04}, // r
	{0x05,0x0F,0x0A}, // s
	{0x08,0x1F,0x08}, // t
	{0x06,0x01,0x07}, // u
	{0x06,0x03,0x06}, // v
	{0x07,0x03,0x07}, // w
	{0x05,0x02,0x05}, // x
	{0x09,0x05,0x0E}, // y
	{0x0B,0x0F,0x0D}, // z
	{0x04,0x1B,0x11}, // {
	{0x00,0x1B,0x00}, // |
	{0x11,0x1B,0x04}, // }
	{0x08,0x18,0x10}, // ~
};

#ifdef __AVR__
char text[] PROGMEM =" Hello, world! ";
#else
char text[] =" Hello, world! ";
#endif

const uint8_t text_len = 15;

uint16_t pos = 0;

static uint8_t tick(void) {
	uint8_t x, y;

	for(x = 0; x < LED_WIDTH; x++) {
		uint16_t p = pos + x;
#ifdef __AVR__
		char c = pgm_read_byte(&text[p / 4]);
#else
		char c = text[p / 4];
#endif
		uint8_t bits = 0;
#ifdef __AVR__
		if((p & 3) < 3) bits =  pgm_read_byte(&font[c - 32][p & 3]);
#else
		if((p & 3) < 3) bits =  			   font[c - 32][p & 3];
#endif

		for(y = 0; y < LED_HEIGHT; y++) {
			setLedXY(x, y, 7 * (bits & 1));
			bits >>= 1;
		}
	}
	pos++;
	if(pos + LED_WIDTH == text_len * 4) pos = 0;
	
	return 0;
}


void init_scroll(void) {
	registerAnimation(tick, 4, text_len * 4);
}


