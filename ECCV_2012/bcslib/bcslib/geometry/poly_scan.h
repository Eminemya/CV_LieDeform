/**
 * @file polyscan.h
 *
 * The structure to facilitate the scanning of pixels in a polygon
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_POLYSCAN_H
#define BCSLIB_POLYSCAN_H

#include <bcslib/geometry/geometry_base.h>
#include <cmath>

#include <cstdio>

namespace bcs
{

	struct rowscan_segment
	{
		geo_index_t y;
		geo_index_t x0;  // inclusive
		geo_index_t x1;  // inclusive

		bool is_empty() const
		{
			return x1 < x0;
		}

		bool operator == (const rowscan_segment& rhs) const
		{
			return y == rhs.y && x0 == rhs.x0 && x1 == rhs.x1;
		}

		bool operator != (const rowscan_segment& rhs) const
		{
			return !(operator == (rhs));
		}
	};

	inline rowscan_segment make_rowscan_segment(geo_index_t y, geo_index_t x0, geo_index_t x1)
	{
		rowscan_segment s;
		s.y = y;
		s.x0 = x0;
		s.x1 = x1;
		return s;
	}


	template<typename T>
	class triangle_scanner
	{
	public:
		typedef point2d<T> point_type;

	public:
		triangle_scanner(const triangle<T>& tri)
		{
			T y1 = tri.pt1.y;
			T y2 = tri.pt2.y;
			T y3 = tri.pt3.y;

			if (y1 <= y3)
			{
				if (y2 < y1)  // y2 < y1 <= y3
				{
					m_pt0 = tri.pt2;
					m_pt1 = tri.pt1;
					m_pt2 = tri.pt3;
				}
				else if (y2 > y3) // y1 <= y3 < y2
				{
					m_pt0 = tri.pt1;
					m_pt1 = tri.pt3;
					m_pt2 = tri.pt2;
				}
				else // y1 <= y2 <= y3
				{
					m_pt0 = tri.pt1;
					m_pt1 = tri.pt2;
					m_pt2 = tri.pt3;
				}
			}
			else // y3 < y1
			{
				if (y2 < y3) // y2 < y3 < y1
				{
					m_pt0 = tri.pt2;
					m_pt1 = tri.pt3;
					m_pt2 = tri.pt1;
				}
				else if (y2 > y1) // y3 < y1 < y2
				{
					m_pt0 = tri.pt3;
					m_pt1 = tri.pt1;
					m_pt2 = tri.pt2;
				}
				else  // y3 <= y2 <= y1
				{
					m_pt0 = tri.pt3;
					m_pt1 = tri.pt2;
					m_pt2 = tri.pt1;
				}
			}

			m_line01 = line2d<T>::from_segment(m_pt0, m_pt1);
			m_line02 = line2d<T>::from_segment(m_pt0, m_pt2);
			m_line12 = line2d<T>::from_segment(m_pt1, m_pt2);
		}


		T top() const
		{
			return m_pt0.y;
		}

		T bottom() const
		{
			return m_pt2.y;
		}


		rowscan_segment get_rowscan_segment(geo_index_t y) const
		{
			T x0 = 0;
			T x1 = -1;

			if (y >= m_pt0.y)
			{
				if (y == m_pt0.y)
				{
					x0 = m_pt0.x;
					x1 = (y == m_pt1.y ? m_pt1.x : m_pt0.x);
				}
				else if (y < m_pt1.y)
				{
					x0 = m_line01.horiz_intersect((T)y);
					x1 = m_line02.horiz_intersect((T)y);
				}
				else if (y <= m_pt2.y)
				{
					x0 = ( y == m_pt2.y ? m_pt2.x : m_line02.horiz_intersect((T)y) );
					x1 = ( y == m_pt1.y ? m_pt1.x : m_line12.horiz_intersect((T)y) );
				}
			}

			if (x1 < x0)
			{
				T t = x1;
				x1 = x0;
				x0 = t;
			}

			rowscan_segment s;
			s.y = y;
			s.x0 = (geo_index_t)std::ceil(x0);
			s.x1 = (geo_index_t)std::floor(x1);
			return s;
		}


	private:
		point_type m_pt0;  	// re-arrange such that pt0.y <= pt1.y <= pt2.y
		point_type m_pt1;
		point_type m_pt2;

		line2d<T> m_line01;
		line2d<T> m_line02;
		line2d<T> m_line12;

	}; // end class triangle_scanner


}

#endif


