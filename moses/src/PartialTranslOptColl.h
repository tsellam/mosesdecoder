// $Id$

/***********************************************************************
Moses - factored phrase-based language decoder
Copyright (C) 2006 University of Edinburgh

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************/

#pragma once

#include <list>
#include <iostream>
#include "TranslationOption.h"
#include "Util.h"
#include "StaticData.h"

/** Contains partial translation options, while these are constructed in the class TranslationOption.
 *  The factored translation model allows for multiple translation and 
 *  generation steps during a single Hypothesis expansion. For efficiency, 
 *  all these expansions are precomputed and stored as TranslationOption.
 *  The expansion process itself may be still explode, so efficient handling
 *  of partial translation options during expansion is required. 
 *  This class assists in this tasks by implementing pruning. 
 *  This implementation is similar to the one in HypothesisCollection. */

class PartialTranslOptColl
{
 protected:
	std::vector<TranslationOption*> m_list;
	float m_bestScore; /**< score of the best translation option */
	float m_worstScore; /**< score of the worse translation option */
	size_t m_maxSize; /**< maximum number of translation options allowed */
	size_t m_totalPruned; /**< number of options pruned */
	std::vector<bool> m_outputFactorsCovered; /**< element is true if the factor type is handled by the translation options in this set */

public:
  PartialTranslOptColl();

	/** destructor, cleans out list */
	~PartialTranslOptColl()
	{
		RemoveAllInColl<std::vector<TranslationOption*>::iterator>( m_list );
	}
	
	void AddNoPrune(TranslationOption *partialTranslOpt);
	void Add(TranslationOption *partialTranslOpt);
	void Prune();

	/** returns list of translation options */
	std::vector<TranslationOption*> GetList() {
		return m_list;
	}

	/** clear out the list */
	void DetachAll()
	{
		m_list.clear();
		//		std::cerr << "clearing out list of " << m_list.size() << " partial translation options\n";
	}

	/** return number of pruned partial hypotheses */
	size_t GetPrunedCount() {
		return m_totalPruned;
	}
	
};
