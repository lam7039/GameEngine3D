#ifndef VECTOR3_H
#define VECTOR3_H

namespace se {

	///
	/// For all your transformation needs.
	///
	template<class T>
	class Vector3 {
	public:
		T x, y, z;

		Vector3() {
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
		}

		Vector3(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		void Set(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
}

#endif