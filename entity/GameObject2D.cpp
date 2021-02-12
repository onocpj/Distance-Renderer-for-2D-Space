#include "GameObject2D.h"


namespace Strave {

	GameObject2D::GameObject2D(std::string name, const Vector2f& pos)
		: m_Name(name), m_Position(pos)
	{}
	GameObject2D::~GameObject2D() {}

}
