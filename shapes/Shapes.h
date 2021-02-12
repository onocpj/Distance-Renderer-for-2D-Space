#pragma once

#include "DataTypes.h"


namespace Strave {

	namespace Shapes {

		class Circle {

		public:
			Circle();
			Circle(const Vector2f& position, float radius);
			virtual ~Circle();

			inline void SetPosition(const Vector2f& position) { m_Position = position; }
			inline void SetRadius(float radius) { m_Radius = radius; }
			inline const Vector2f& GetPostion(void) const { return m_Position; }
			inline const float& GetRadius(void) const { return m_Radius; }

		private:
			Vector2f	m_Position;
			float		m_Radius;

		};

	};

};

