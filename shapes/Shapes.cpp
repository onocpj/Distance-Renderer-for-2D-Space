#include "Shapes.h"

#include "UDT.h"


namespace Strave {

	namespace Shapes {
		
		Circle::Circle()
			: m_Position(UNDEF_VECTOR2F), m_Radius(UNDEF_FLOAT)
		{}
		Circle::Circle(const Vector2f& position, float radius)
			: m_Position(position), m_Radius(radius)
		{}
		Circle::~Circle() {}

	}

}