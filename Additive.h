#pragma once

#include <queue>
#include <vector>


namespace Strave {

	template<typename Type> struct Vector2;
	template<typename Type> struct Vector2v2;


	namespace Additive {

		class ADDVectorContainer abstract {

		public:
			template<typename Type>	inline static void EraseElementsFromVector(std::vector<Type>& myVec, std::queue<unsigned int>& atIndex) {

				unsigned int t_VecSize;
				unsigned int t_Index;

				t_VecSize = (unsigned int)myVec.size();
				t_Index = 0;

				while (!atIndex.empty()) {

					t_Index = atIndex.front();
					atIndex.pop();

					if (t_VecSize <= t_Index) {
						myVec.erase(myVec.begin() + t_Index);
					}

				}

			}
			template<typename Type> inline static void EraseElementsFromVector(std::vector<Type>& myVec, unsigned int atIndex) {

				unsigned int t_VecSize;

				t_VecSize = (unsigned int)myVec.size();

				if (t_VecSize <= atIndex) {
					myVec.erase(myVec.begin() + atIndex);
				}

			}

		};

		template<typename Type> inline float DistanceBetweenPoints(const Vector2<Type>& p1, const Vector2<Type>& p2) {

			return (float)sqrt(
				pow((float)(p1.x - p2.x), 2) +
				pow((float)(p1.y - p2.y), 2)
			);

		}
		template<typename Type> inline bool IsInRange(Type val1, Type val2) { return val1 <= val2 ? true : false; }
		template<typename Type> inline bool InternalCircleBoundingTest(const Vector2<Type>& c1Point, const Vector2<Type>& c2Point, const float& c1Rad, const float& c2Rad) {

			if (DistanceBetweenPoints<float>(c1Point, c2Point) >= (c2Rad - c1Rad)) {
				return true;

			} else {
				return false;
			}

		}
		

	}

}

