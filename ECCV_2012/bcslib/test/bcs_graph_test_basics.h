/**
 * @file bcs_graph_test_basics.h
 *
 * Some useful devices for testing graphs
 * 
 * @author Dahua Lin
 */

#ifndef BCS_GRAPH_TEST_BASICS_H_
#define BCS_GRAPH_TEST_BASICS_H_

#include "bcs_test_basics.h"
#include <bcslib/graph/gview_base.h>
#include <bcslib/base/type_traits.h>

namespace bcs { namespace test {

	template<typename TInt, typename TIter>
	inline bool vertices_equal(TIter vbegin, TIter vend, const gvertex<TInt>* vertices, TInt n)
	{
		return collection_equal(vbegin, vend, vertices, (size_t)n);
	}

	template<typename TInt, typename TIter>
	inline bool vertices_equal(TIter vbegin, TIter vend, const TInt* vertex_ids, TInt n)
	{
		return collection_equal(vbegin, vend, (const gvertex<TInt>*)(vertex_ids), (size_t)n);
	}

	template<typename TInt, typename TIter>
	inline bool edges_equal(TIter vbegin, TIter vend, const gedge<TInt>* edges, TInt n)
	{
		return collection_equal(vbegin, vend, edges, (size_t)n);
	}

	template<typename TInt, typename TIter>
	inline bool edges_equal(TIter vbegin, TIter vend, const TInt* edge_ids, TInt n)
	{
		return collection_equal(vbegin, vend, (const gedge<TInt>*)(edge_ids), (size_t)n);
	}

} }



#endif 
