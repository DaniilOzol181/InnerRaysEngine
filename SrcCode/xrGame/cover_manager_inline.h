////////////////////////////////////////////////////////////////////////////
//	Module 		: cover_manager_inline.h
//	Created 	: 24.03.2004
//  Modified 	: 24.03.2004
//	Author		: Dmitriy Iassenev
//	Description : Cover manager class inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

IC CCoverManager::CPointQuadTree& CCoverManager::covers() const
{
	VERIFY(m_covers);
	return (*m_covers);
}

IC CCoverManager::CPointQuadTree* CCoverManager::get_covers()
{
	return (m_covers);
}

IC smart_cover::storage* CCoverManager::smart_covers_storage() const
{
	return m_smart_covers_storage;
}

template<typename _evaluator_type, typename _restrictor_type>
IC bool CCoverManager::inertia(float radius, _evaluator_type& evaluator, const _restrictor_type& restrictor) const
{
	// Check if evaluator has no inertion or it's time to reevaluate
	if (!evaluator.inertia(radius))
	{
		return (false);
	}

	// So, evaluator has inertion and it's not time to search
	// Check if we didn't select cover last time
	if (!evaluator.selected())
	{
		return (true);
	}

	// So, evaluator has inertion and it's not time to search
	// So, evaluator did select cover last time
	// Check if this cover is still accessible
	if (!evaluator.accessible(evaluator.selected()->position()))
	{
		return (false);
	}

	// So, evaluator has inertion and it's not time to search
	// So, evaluator did select cover last time
	// So, cover is still accessible
	// Check if restrictor still allows this cover
	if (!restrictor(evaluator.selected()))
	{
		return (false);
	}

	// So, evaluator has inertion and it's not time to search
	// So, evaluator did select cover last time
	// So, cover is still accessible
	// So, restrictor still allows this cover
	// Therefore inertion is played
	return (true);
}

template<typename _evaluator_type, typename _restrictor_type>
IC const CCoverPoint* CCoverManager::best_cover(const Fvector& position, float radius, _evaluator_type& evaluator,
	const _restrictor_type& restrictor) const
{
	START_PROFILE("Covers/best_cover")

	if (inertia(radius, evaluator, restrictor))
	{
		return (evaluator.selected());
	}

	const CCoverPoint* last = evaluator.selected();

	evaluator.initialize(position);

	if (last)
	{
		if (position.distance_to_sqr(last->position()) < _sqr(3 * radius))
		{
			if (evaluator.accessible(last->position()))
			{
				if (restrictor(last))
				{
					evaluator.evaluate(last, restrictor.weight(last));
				}
			}
		}
	}

	covers().nearest(position, radius, m_nearest);

	float radius_sqr = _sqr(radius);

	xr_vector<CCoverPoint*>::const_iterator I = m_nearest.begin();
	xr_vector<CCoverPoint*>::const_iterator E = m_nearest.end();
	for (; I != E; ++I)
	{
		if (radius_sqr < position.distance_to_sqr((*I)->position()))
		{
			continue;
		}

		if (_abs(position.y - (*I)->position().y) > 3.f)
		{
			continue;
		}

		if (!evaluator.accessible((*I)->position()))
		{
			continue;
		}

		if (!restrictor(*I))
		{
			continue;
		}

		evaluator.evaluate(*I, restrictor.weight(*I));
	}

	evaluator.finalize();

	restrictor.finalize(evaluator.selected());

	return (evaluator.selected());

	STOP_PROFILE
}

template<typename _evaluator_type>
IC const CCoverPoint* CCoverManager::best_cover(const Fvector& position, float radius, _evaluator_type& evaluator) const
{
	return (best_cover<_evaluator_type, CCoverManager>(position, radius, evaluator, *this));
}

IC bool CCoverManager::operator() (const CCoverPoint*) const
{
	return (true);
}

IC float CCoverManager::weight(const CCoverPoint*) const
{
	return (1.f);
}

IC void CCoverManager::finalize(const CCoverPoint*) const
{}
