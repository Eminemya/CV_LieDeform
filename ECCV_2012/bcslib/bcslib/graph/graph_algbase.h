/**
 * @file graph_algbase.h
 *
 * Basic facilities for Graph algorithm construction
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_GRAPH_ALGBASE_H_
#define BCSLIB_GRAPH_ALGBASE_H_

#include <bcslib/graph/gview_base.h>

namespace bcs
{
	enum gvisit_status
	{
		GVISIT_NONE = 0,
		GVISIT_DISCOVERED = 1,
		GVISIT_FINISHED = 2
	};
}

#endif /* GRAPH_ALGBASE_H_ */
