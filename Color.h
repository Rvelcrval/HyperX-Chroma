#pragma once
#include "HXChroma.h"

struct Color {
	Color ( ) { 
		r = 0;
		g = 0;
		b = 0;
	}
	Color ( BYTE r, BYTE g, BYTE b ) : r(r), g(g), b(b) {
	}
	Color ( BYTE inr, BYTE ing, BYTE inb, BYTE a ) {
		this->r = (float)inr * ((float)a / 255.f);
		this->g = (float)ing * ((float)a / 255.f);
		this->b = (float)inb * ((float)a / 255.f);
	}

	static Color hsv2rgb ( float H, float S, float V ) {
		float r, g, b;

		float h = H / 360;
		float s = S;
		float v = V;

		int i = floor ( h * 6 );
		float f = h * 6 - i;
		float p = v * (1 - s);
		float q = v * (1 - f * s);
		float t = v * (1 - (1 - f) * s);

		switch ( i % 6 ) {
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
		}

		Color color;
		color.r = r * 255;
		color.g = g * 255;
		color.b = b * 255;

		return color;
	}

	BYTE r, g, b;
};