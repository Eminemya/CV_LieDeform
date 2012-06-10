/**
 * @file triangle_mesh.h
 *
 * The class to represent a triangle mesh over a 2D space
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_TRIANGLE_MESH_H
#define BCSLIB_TRIANGLE_MESH_H

#include <bcslib/geometry/geometry_base.h>
#include <bcslib/base/basic_mem.h>

namespace bcs
{

	/**
	 * The class to represent the topological structure of
	 * the triangle mesh
	 */
	class triangle_mesh
	{
	public:
		struct entry_type
		{
			int32_t v[3];

			int32_t operator[] (int i) const
			{
				return v[i];
			}
		};

	public:
		triangle_mesh(size_t nv, size_t nf, const entry_type *entries, ref_t)
		: m_nvertices(nv), m_nfaces(nf)
		, m_entries(ref_t(), nf, entries)
		{
		}

		triangle_mesh(size_t nv, size_t nf, const entry_type *entries, clone_t)
		: m_nvertices(nv), m_nfaces(nf)
		, m_entries(clone_t(), nf, entries)
		{

		}

		triangle_mesh(size_t nv, block<entry_type> *pblk)
		: m_nvertices(nv), m_nfaces(pblk->nelems())
		, m_entries(pblk)
		{
		}

		size_t nvertices() const
		{
			return m_nvertices;
		}

		size_t nfaces() const
		{
			return m_nfaces;
		}

		const entry_type& entry(size_t i) const
		{
			return m_entries[i];
		}

		template<typename T>
		triangle<T> get_triangle(size_t i, const point2d<T> *vertices) const
		{
			const entry_type& e = m_entries[i];
			return make_tri(vertices[e[0]], vertices[e[1]], vertices[e[2]]);
		}

		template<typename T>
		triangle<T> get_triangle(size_t i, const T *x, const T *y) const
		{
			const entry_type& e = m_entries[i];
			return make_tri(
					pt(x[e[0]], y[e[0]]),
					pt(x[e[1]], y[e[1]]),
					pt(x[e[2]], y[e[2]]));
		}


	private:
		size_t m_nvertices;
		size_t m_nfaces;
		const_memory_proxy<entry_type> m_entries;

	}; // end class triangle_mesh



}

#endif 
