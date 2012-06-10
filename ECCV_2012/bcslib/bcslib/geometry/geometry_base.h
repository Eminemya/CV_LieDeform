/**
 * @file geometry_base.h
 *
 * Basic definitions of geometric constructs
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_GEOMETRY_BASE_H
#define BCSLIB_GEOMETRY_BASE_H

#include <bcslib/base/basic_defs.h>
#include <cmath>

namespace bcs
{

	typedef int32_t geo_index_t;

	// points

	template<typename T>
	struct point2d
	{
		typedef T coordinate_type;

		T x;
		T y;
	};

	template<typename T>
	inline bool operator == (const point2d<T>& lhs, const point2d<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template<typename T>
	inline bool operator != (const point2d<T>& lhs, const point2d<T>& rhs)
	{
		return !(lhs == rhs);
	}


	template<typename T>
	struct point3d
	{
		typedef T coordinate_type;

		T x;
		T y;
		T z;
	};

	template<typename T>
	inline bool operator == (const point3d<T>& lhs, const point3d<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	template<typename T>
	inline bool operator != (const point3d<T>& lhs, const point3d<T>& rhs)
	{
		return !(lhs == rhs);
	}


	template<typename T>
	inline point2d<T> pt(T x, T y)
	{
		point2d<T> p;
		p.x = x;
		p.y = y;
		return p;
	}

	template<typename T>
	inline point3d<T> pt(T x, T y, T z)
	{
		point3d<T> p;
		p.x = x;
		p.y = y;
		p.z = z;
		return p;
	}


	inline double distance(const point2d<double>& pt1, const point2d<double>& pt2)
	{
		double dx = pt1.x - pt2.x;
		double dy = pt1.y - pt2.y;
		return std::sqrt(dx * dx + dy * dy);
	}


	inline float distance(const point2d<float>& pt1, const point2d<float>& pt2)
	{
		float dx = pt1.x - pt2.x;
		float dy = pt1.y - pt2.y;
		return std::sqrt(dx * dx + dy * dy);
	}


	inline double distance(const point3d<double>& pt1, const point3d<double>& pt2)
	{
		double dx = pt1.x - pt2.x;
		double dy = pt1.y - pt2.y;
		double dz = pt1.z - pt2.z;
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}


	inline float distance(const point3d<float>& pt1, const point3d<float>& pt2)
	{
		float dx = pt1.x - pt2.x;
		float dy = pt1.y - pt2.y;
		float dz = pt1.z - pt2.z;
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}



	// line segments and lines

	template<typename T>
	struct lineseg2d
	{
		typedef T coordinate_type;
		typedef point2d<T> point_type;

		point_type pt1;
		point_type pt2;
	};


	template<typename T>
	struct lineseg3d
	{
		typedef T coordinate_type;
		typedef point3d<T> point_type;

		point_type pt1;
		point_type pt2;
	};


	template<typename T>
	inline bool operator == (const lineseg2d<T>& lhs, const lineseg2d<T>& rhs)
	{
		return lhs.pt1 == rhs.pt1 && lhs.pt2 == rhs.pt2;
	}

	template<typename T>
	inline bool operator != (const lineseg2d<T>& lhs, const lineseg2d<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	inline bool operator == (const lineseg3d<T>& lhs, const lineseg3d<T>& rhs)
	{
		return lhs.pt1 == rhs.pt1 && lhs.pt2 == rhs.pt2;
	}

	template<typename T>
	inline bool operator != (const lineseg3d<T>& lhs, const lineseg3d<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	inline lineseg2d<T> lineseg(const point2d<T>& pt1, const point2d<T>& pt2)
	{
		lineseg2d<T> line;
		line.pt1 = pt1;
		line.pt2 = pt2;
		return line;
	}

	template<typename T>
	inline lineseg3d<T> lineseg(const point3d<T>& pt1, const point3d<T>& pt2)
	{
		lineseg3d<T> line;
		line.pt1 = pt1;
		line.pt2 = pt2;
		return line;
	}


	inline double length(const lineseg2d<double>& line)
	{
		return distance(line.pt1, line.pt2);
	}

	inline float length(const lineseg2d<float>& line)
	{
		return distance(line.pt1, line.pt2);
	}

	inline double length(const lineseg3d<double>& line)
	{
		return distance(line.pt1, line.pt2);
	}

	inline float length(const lineseg3d<float>& line)
	{
		return distance(line.pt1, line.pt2);
	}


	template<typename T>
	struct line2d
	{
		typedef T coordinate_type;
		typedef point2d<T> point_type;

		T a; 	// ax + by + c = 0
		T b;
		T c;

		bool is_horizontal() const
		{
			return a == 0;
		}

		bool is_vertical() const
		{
			return b == 0;
		}

		T slope() const
		{
			return - a / b;
		}

		T horiz_intersect() const
		{
			return -c / a;
		}

		T horiz_intersect(T y) const
		{
			return -(b * y + c) / a;
		}

		T vert_intersect() const
		{
			return -c / b;
		}

		T vert_intersect(T x) const
		{
			return -(a * x + c) / b;
		}

		T evaluate(const point2d<T>& pt) const
		{
			return a * pt.x + b * pt.y + c;
		}

		bool operator == (const line2d<T>& rhs) const
		{
			return a == rhs.a && b == rhs.b && c == rhs.c;
		}

		bool operator != (const line2d<T>& rhs) const
		{
			return !(operator == (rhs));
		}

		static line2d<T> from_segment(const point_type& pt1, const point_type& pt2)
		{
			line2d<T> l;
			l.a = pt2.y - pt1.y;
			l.b = pt1.x - pt2.x;
			l.c = pt2.x * pt1.y - pt1.x * pt2.y;
			return l;
		}

		static line2d<T> from_segment(const lineseg2d<T>& s)
		{
			return from_segment(s.pt1, s.pt2);
		}
	};


	template<typename T>
	inline line2d<T> line(T a, T b, T c)
	{
		line2d<T> l;
		l.a = a;
		l.b = b;
		l.c = c;
		return l;
	}


	// rectangles

	template<typename T>
	struct rectangle
	{
		typedef T coordinate_type;
		typedef point2d<T> point_type;

		T x;	// x-coordinate of left
		T y;	// y-coordinate of top
		T w;	// width
		T h;	// height

		T left() const
		{
			return x;
		}

		T right() const
		{
			return x + w;
		}

		T top() const
		{
			return y;
		}

		T bottom() const
		{
			return y + h;
		}

		T width() const
		{
			return w;
		}

		T height() const
		{
			return h;
		}

		point_type top_left() const
		{
			return pt(left(), top());
		}

		point_type top_right() const
		{
			return pt(right(), top());
		}

		point_type bottom_left() const
		{
			return pt(left(), bottom());
		}

		point_type bottom_right() const
		{
			return pt(right(), bottom());
		}

		bool is_empty() const
		{
			return width() == 0 || height() == 0;
		}

		bool operator == (const rectangle<T>& rhs) const
		{
			return x == rhs.x && y == rhs.y && w == rhs.w && h == rhs.h;
		}

		bool operator != (const rectangle<T>& rhs) const
		{
			return !(operator == (rhs));
		}
	};


	template<typename T>
	inline rectangle<T> rect(T x, T y, T w, T h)
	{
		rectangle<T> rc;
		rc.x = x;
		rc.y = y;
		rc.w = w;
		rc.h = h;
		return rc;
	}

	template<typename T>
	inline rectangle<T> rect(const point2d<T>& pt1, const point2d<T>& pt2)
	{
		T x, y, w, h;

		if (pt1.x <= pt2.x)
		{
			x = pt1.x;
			w = pt2.x - pt1.x;
		}
		else
		{
			x = pt2.x;
			w = pt1.x - pt2.x;
		}

		if (pt1.y <= pt2.y)
		{
			y = pt1.y;
			h = pt2.y - pt1.y;
		}
		else
		{
			y = pt2.y;
			h = pt1.y - pt2.y;
		}

		return rect(x, y, w, h);
	}


	template<typename T>
	inline T area(const rectangle<T>& rc)
	{
		return rc.width() * rc.height();
	}


	// triangle

	template<typename T>
	struct triangle
	{
		typedef T coordinate_type;
		typedef point2d<T> point_type;

		point_type pt1;
		point_type pt2;
		point_type pt3;

		bool is_empty() const
		{
			T dx1 = pt2.x - pt1.x;
			T dy1 = pt2.y - pt1.y;

			T dx2 = pt3.x - pt1.x;
			T dy2 = pt3.y - pt1.y;

			return dx1 * dy2 - dx2 * dy1 == 0;
		}

		bool operator == (const triangle<T>& rhs) const
		{
			return pt1 == rhs.pt1 && pt2 == rhs.pt2 && pt3 == rhs.pt3;
		}

		bool operator != (const triangle<T>& rhs) const
		{
			return !(operator == (rhs));
		}
	};


	inline double area(const triangle<double>& tri)
	{
		double dx1 = tri.pt2.x - tri.pt1.x;
		double dy1 = tri.pt2.y - tri.pt1.y;

		double dx2 = tri.pt3.x - tri.pt1.x;
		double dy2 = tri.pt3.y - tri.pt1.y;

		return std::abs(dx1 * dy2 - dx2 * dy1) / 2;
	}


	inline float area(const triangle<float>& tri)
	{
		float dx1 = tri.pt2.x - tri.pt1.x;
		float dy1 = tri.pt2.y - tri.pt1.y;

		float dx2 = tri.pt3.x - tri.pt1.x;
		float dy2 = tri.pt3.y - tri.pt1.y;

		return std::abs(dx1 * dy2 - dx2 * dy1) / 2;
	}


	template<typename T>
	inline triangle<T> make_tri(const point2d<T>& pt1, const point2d<T>& pt2, const point2d<T>& pt3)
	{
		triangle<T> tri;
		tri.pt1 = pt1;
		tri.pt2 = pt2;
		tri.pt3 = pt3;
		return tri;
	}



}

#endif 
