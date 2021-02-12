#pragma once


#include "UDT.h"


namespace Strave {

	template<typename Type> struct Vector2 {

		inline Vector2(Type x, Type y) : x(x), y(y) {}
		inline virtual ~Vector2() {}

		Type x;
		Type y;

	};
	template<typename Type> struct Vector2v2 {

		inline Vector2v2(Vector2<Type> min, Vector2<Type> max) : min(min), max(max) {}
		inline virtual ~Vector2v2() {}

		Vector2<Type> min;
		Vector2<Type> max;

	};

	typedef struct Vector2f : Vector2<float> {

		inline Vector2f() : Vector2(UNDEF_FLOAT, UNDEF_FLOAT) {}
		inline Vector2f(float x, float y) : Vector2(x, y) {}

	} Vector2f;
	typedef struct Vector2u : Vector2<unsigned> {

		inline Vector2u() : Vector2(UNDEF_UINT, UNDEF_UINT) {}
		inline Vector2u(unsigned x, unsigned y) : Vector2(x, y) {}

	} Vector2u;
	typedef struct Vector2v2u : Vector2v2<unsigned int> {

		inline Vector2v2u() : Vector2v2(Vector2u(), Vector2u()) {}
		inline Vector2v2u(Vector2u min, Vector2u max) : Vector2v2(min, max) {}

	} Vector2v2u;
	typedef struct Vector2v2f : Vector2v2<float> {

		inline Vector2v2f() : Vector2v2(Vector2f(), Vector2f()) {}
		inline Vector2v2f(Vector2f min, Vector2f max) : Vector2v2(min, max) {}

	} Vector2v2f;

}

