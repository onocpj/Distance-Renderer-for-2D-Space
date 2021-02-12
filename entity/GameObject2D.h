#pragma once


#include <string>

#include "DataTypes.h"


namespace Strave {

	class GameObject2D {

	public:
		GameObject2D(std::string name, const Vector2f& pos);
		~GameObject2D();

		inline const std::string& GetName(void) const { return m_Name; }
		inline const Vector2f& GetPosition(void) const { return m_Position; }

	private:
		std::string m_Name;
		Vector2f	m_Position;

	};

}

