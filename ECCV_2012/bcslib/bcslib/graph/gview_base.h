/**
 * @file gview_base.h
 *
 * Basic definitions for graph views
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_GVIEW_BASE_H_
#define BCSLIB_GVIEW_BASE_H_

#include <bcslib/base/basic_defs.h>
#include <bcslib/base/key_map.h>
#include <bcslib/base/iterator_wrappers.h>

#ifndef BCS_GRAPH_ENTITY_IDBASE
#define BCS_GRAPH_ENTITY_IDBASE 1
#endif

// interface declaration macros

#define BCS_GEDGELIST_INTERFACE_DEFS(Derived) \
	typedef typename gview_traits<Derived>::vertex_type vertex_type; \
	typedef typename gview_traits<Derived>::edge_type edge_type; \
	typedef typename gview_traits<Derived>::index_type index_type; \
	typedef typename gview_traits<Derived>::vertex_iterator vertex_iterator; \
	typedef typename gview_traits<Derived>::edge_iterator edge_iterator; \
	BCS_ENSURE_INLINE const Derived& derived() const { return *(static_cast<const Derived*>(this)); } \
	BCS_ENSURE_INLINE Derived& derived() { return *(static_cast<Derived*>(this)); }

#define BCS_GADJLIST_INTERFACE_DEFS(Derived) \
	typedef typename gview_traits<Derived>::vertex_type vertex_type; \
	typedef typename gview_traits<Derived>::edge_type edge_type; \
	typedef typename gview_traits<Derived>::index_type index_type; \
	typedef typename gview_traits<Derived>::vertex_iterator vertex_iterator; \
	typedef typename gview_traits<Derived>::neighbor_iterator neighbor_iterator; \
	BCS_ENSURE_INLINE const Derived& derived() const { return *(static_cast<const Derived*>(this)); } \
	BCS_ENSURE_INLINE Derived& derived() { return *(static_cast<Derived*>(this)); }

#define BCS_GINCLIST_INTERFACE_DEFS(Derived) \
	typedef typename gview_traits<Derived>::vertex_type vertex_type; \
	typedef typename gview_traits<Derived>::edge_type edge_type; \
	typedef typename gview_traits<Derived>::index_type index_type; \
	typedef typename gview_traits<Derived>::vertex_iterator vertex_iterator; \
	typedef typename gview_traits<Derived>::edge_iterator edge_iterator; \
	typedef typename gview_traits<Derived>::neighbor_iterator neighbor_iterator; \
	typedef typename gview_traits<Derived>::incident_edge_iterator incident_edge_iterator; \
	BCS_ENSURE_INLINE const Derived& derived() const { return *(static_cast<const Derived*>(this)); } \
	BCS_ENSURE_INLINE Derived& derived() { return *(static_cast<Derived*>(this)); }

namespace bcs
{
	/**
	 * A graph vertex
	 */
	template<typename TInt>
	struct gvertex
	{
		typedef TInt index_type;
		TInt id;

		BCS_ENSURE_INLINE TInt index() const
		{
#if BCS_GRAPH_ENTITY_IDBASE == 0
			return id;
#else
			return id - BCS_GRAPH_ENTITY_IDBASE;
#endif
		}

		BCS_ENSURE_INLINE bool operator == (const gvertex& r) const
		{
			return id == r.id;
		}

		BCS_ENSURE_INLINE bool operator != (const gvertex& r) const
		{
			return id != r.id;
		}
	};

	template<typename TInt>
	struct index_convertible<gvertex<TInt> >
	{
		static const bool value = true;
	};

	template<typename TInt>
	inline BCS_ENSURE_INLINE gvertex<TInt> make_gvertex(TInt id)
	{
		gvertex<TInt> v;
		v.id = id;
		return v;
	}


	/**
	 * A graph edge
	 */
	template<typename TInt>
	struct gedge
	{
		typedef TInt index_type;
		TInt id;

		BCS_ENSURE_INLINE TInt index() const
		{
#if BCS_GRAPH_ENTITY_IDBASE == 0
			return id;
#else
			return id - BCS_GRAPH_ENTITY_IDBASE;
#endif
		}

		BCS_ENSURE_INLINE bool operator == (const gedge& r) const
		{
			return id == r.id;
		}

		BCS_ENSURE_INLINE bool operator != (const gedge& r) const
		{
			return id != r.id;
		}
	};

	template<typename TInt>
	struct index_convertible<gedge<TInt> >
	{
		static const bool value = true;
	};

	template<typename TInt>
	inline BCS_ENSURE_INLINE gedge<TInt> make_gedge(TInt id)
	{
		gedge<TInt> e;
		e.id = id;
		return e;
	}


	/**
	 * A pair of graph vertices
	 */
	template<typename TInt>
	struct gvertex_pair
	{
		typedef TInt index_type;
		gvertex<TInt> s;
		gvertex<TInt> t;

		BCS_ENSURE_INLINE bool operator == (const gvertex_pair& r) const
		{
			return s == r.s && t == r.t;
		}

		BCS_ENSURE_INLINE bool operator != (const gvertex_pair& r) const
		{
			return !(s == r.s && t == r.t);
		}

		BCS_ENSURE_INLINE bool is_loop() const
		{
			return s == t;
		}

		BCS_ENSURE_INLINE gvertex_pair flip() const
		{
			gvertex_pair vp;
			vp.s = t;
			vp.t = s;
			return vp;
		}
	};


	template<typename TInt>
	inline BCS_ENSURE_INLINE gvertex_pair<TInt> make_vertex_pair(const gvertex<TInt>& s, const gvertex<TInt>& t)
	{
		gvertex_pair<TInt> vp;
		vp.s = s;
		vp.t = t;
		return vp;
	}

	template<typename TInt>
	inline BCS_ENSURE_INLINE gvertex_pair<TInt> make_vertex_pair(TInt s_id, TInt t_id)
	{
		gvertex_pair<TInt> vp;
		vp.s = make_gvertex(s_id);
		vp.t = make_gvertex(t_id);
		return vp;
	}


	template<typename TInt>
	inline BCS_ENSURE_INLINE bool is_incident(const gvertex<TInt>& v, const gvertex_pair<TInt>& e)
	{
		return e.s == v || e.t == v;
	}


	/********************************************
	 *
	 *   The iterators of vertices and edges
	 *
	 ********************************************/

	namespace _detail
	{
		template<typename Entity>
		class natural_gentity_iterator_impl
		{
		public:
			typedef Entity value_type;
			typedef const value_type* pointer;
			typedef const value_type& reference;
			typedef typename Entity::index_type index_type;

		public:
			natural_gentity_iterator_impl()
			{
				current.id = BCS_GRAPH_ENTITY_IDBASE;
			}

			natural_gentity_iterator_impl(index_type id)
			{
				current.id = id;
			}

			void move_next() { ++ current.id; }
			void move_prev() { -- current.id; }
			pointer ptr() const { return &current; }
			reference ref() const { return current; }

			bool operator == (const natural_gentity_iterator_impl& rhs) const
			{
				return current == rhs.current;
			}

		private:
			value_type current;

		}; // end class natural_gentity_iterator_impl

	}


	template<typename TInt>
	struct natural_vertex_iterator
	{
		typedef _detail::natural_gentity_iterator_impl<gvertex<TInt> > impl_type;
		typedef bidirectional_iterator_wrapper<impl_type> type;

		static type get_default()
		{
			return impl_type();
		}

		static type from_id(TInt id)
		{
			return impl_type(id);
		}
	};

	template<typename TInt>
	struct natural_edge_iterator
	{
		typedef _detail::natural_gentity_iterator_impl<gedge<TInt> > impl_type;
		typedef bidirectional_iterator_wrapper<impl_type> type;

		static type get_default()
		{
			return impl_type();
		}

		static type from_id(TInt id)
		{
			return impl_type(id);
		}
	};



	/********************************************
	 *
	 *   The concept interfaces
	 *
	 ********************************************/

	template<class Derived> struct gview_traits;

	template<class Derived>
	class IGraphEdgeList
	{
	public:
		BCS_GEDGELIST_INTERFACE_DEFS(Derived)

		BCS_ENSURE_INLINE index_type nvertices() const
		{
			return derived().nvertices();
		}

		BCS_ENSURE_INLINE index_type nedges() const
		{
			return derived().nedges();
		}

		BCS_ENSURE_INLINE bool is_directed() const
		{
			return derived().is_directed();
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_begin() const
		{
			return derived().vertices_begin();
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_end() const
		{
			return derived().vertices_end();
		}

		BCS_ENSURE_INLINE edge_iterator edges_begin() const
		{
			return derived().edges_begin();
		}

		BCS_ENSURE_INLINE edge_iterator edges_end() const
		{
			return derived().edges_end();
		}

		BCS_ENSURE_INLINE const vertex_type& source(const edge_type& e) const
		{
			return derived().source(e);
		}

		BCS_ENSURE_INLINE const vertex_type& target(const edge_type& e) const
		{
			return derived().target(e);
		}

	}; // end class IGraphEdgeList

	template<class Derived>
	class IGraphAdjacencyList
	{
	public:
		BCS_GADJLIST_INTERFACE_DEFS(Derived)

		BCS_ENSURE_INLINE index_type nvertices() const
		{
			return derived().nvertices();
		}

		BCS_ENSURE_INLINE index_type nedges() const
		{
			return derived().nedges();
		}

		BCS_ENSURE_INLINE bool is_directed() const
		{
			return derived().is_directed();
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_begin() const
		{
			return derived().vertices_begin();
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_end() const
		{
			return derived().vertices_end();
		}

		BCS_ENSURE_INLINE index_type out_degree(const vertex_type& v) const
		{
			return derived().out_degree(v);
		}

		BCS_ENSURE_INLINE neighbor_iterator out_neighbors_begin(const vertex_type& v) const
		{
			return derived().out_neighbors_begin(v);
		}

		BCS_ENSURE_INLINE neighbor_iterator out_neighbors_end(const vertex_type& v) const
		{
			return derived().out_neighbors_end(v);
		}
	};


	template<class Derived>
	class IGraphIncidenceList : public IGraphEdgeList<Derived>, public IGraphAdjacencyList<Derived>
	{
	public:
		BCS_GINCLIST_INTERFACE_DEFS(Derived)

		BCS_ENSURE_INLINE index_type nvertices() const
		{
			return derived().nvertices();
		}

		BCS_ENSURE_INLINE index_type nedges() const
		{
			return derived().nedges();
		}

		BCS_ENSURE_INLINE bool is_directed() const
		{
			return derived().is_directed();
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_begin() const
		{
			return derived().vertices_begin();
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_end() const
		{
			return derived().vertices_end();
		}

		BCS_ENSURE_INLINE edge_iterator edges_begin() const
		{
			return derived().edges_begin();
		}

		BCS_ENSURE_INLINE edge_iterator edges_end() const
		{
			return derived().edges_end();
		}

		BCS_ENSURE_INLINE const vertex_type& source(const edge_type& e) const
		{
			return derived().source(e);
		}

		BCS_ENSURE_INLINE const vertex_type& target(const edge_type& e) const
		{
			return derived().target(e);
		}

		BCS_ENSURE_INLINE index_type out_degree(const vertex_type& v) const
		{
			return derived().out_degree(v);
		}

		BCS_ENSURE_INLINE neighbor_iterator out_neighbors_begin(const vertex_type& v) const
		{
			return derived().out_neighbors_begin(v);
		}

		BCS_ENSURE_INLINE neighbor_iterator out_neighbors_end(const vertex_type& v) const
		{
			return derived().out_neighbors_end(v);
		}

		BCS_ENSURE_INLINE incident_edge_iterator out_edges_begin(const vertex_type& v) const
		{
			return derived().out_edges_begin(v);
		}

		BCS_ENSURE_INLINE incident_edge_iterator out_edges_end(const vertex_type& v) const
		{
			return derived().out_edges_end(v);
		}
	};


	/********************************************
	 *
	 *   Forward declaration of specific
	 *
	 *   graph view classes
	 *
	 ********************************************/

	template<typename TInt> class gedgelist_view;
	template<typename TInt> class ginclist_view;

	template<typename TInt> class gedgelist;
	template<typename TInt> class ginclist;

}

#endif 
