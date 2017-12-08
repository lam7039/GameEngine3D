#ifndef VECTOR3_H
#define VECTOR3_H

#include "std.h"

namespace se {

	template<class T>
	class Vector3 {
	public:
		T X;
		T Y;
		T Z;

		Vector3() {
			X = NULL;
			Y = NULL;
			Z = NULL;
		}

		Vector3(T x, T y, T z) {
			X = x;
			Y = y;
			Z = z;
		}

		void Set(T x, T y, T z) {
			X = x;
			Y = y;
			Z = z;
		}
	};

}

#endif