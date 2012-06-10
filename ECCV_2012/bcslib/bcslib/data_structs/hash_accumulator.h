/**
 * @file hash_accumulator.h
 *
 * A counter class based on hash set
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_HASH_ACCUMULATOR_H
#define BCSLIB_HASH_ACCUMULATOR_H

#include <bcslib/base/basic_defs.h>
#include <bcslib/base/tr1_containers.h>
#include <functional>

namespace bcs
{

	template<typename TKey, typename TValue, typename Hasher=hash<TKey> >
	class hash_accumulator
	{
	public:
		typedef TKey key_type;
		typedef TValue value_type;
		typedef Hasher hasher;

		typedef unordered_map<key_type, value_type, hasher> map_type;
		typedef typename map_type::size_type size_type;
		typedef typename map_type::const_iterator const_iterator;
		typedef typename map_type::iterator iterator;

	public:
		size_type size() const
		{
			return m_map.size();
		}

		const_iterator begin() const
		{
			return m_map.begin();
		}

		const_iterator end() const
		{
			return m_map.end();
		}

		void add(const key_type& key, const value_type& add_value)
		{
			iterator it = m_map.find(key);
			if (it != m_map.end())
			{
				it->second += add_value;
			}
			else
			{
				m_map[key] = add_value;
			}
		}

		bool contains(const key_type& key) const
		{
			return m_map.find(key) != m_map.end();
		}

		value_type get(const key_type& key) const
		{
			const_iterator it = m_map.find(key);
			if (it != m_map.end())
			{
				return it->second;
			}
			else
			{
				return value_type();
			}
		}

		const value_type& at(const key_type& key) const
		{
			return m_map.at(key);
		}

	private:
		 map_type m_map;

	};  // end class hash_accumulator



}


#endif 
