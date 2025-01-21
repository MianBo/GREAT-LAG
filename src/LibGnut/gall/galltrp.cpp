
/* ----------------------------------------------------------------------
 * G-Nut - GNSS software development library
 *
  (c) 2018 G-Nut Software s.r.o. (software@gnutsoftware.com)
  This file is part of the G-Nut C++ library.
-*/

#include "gall/galltrp.h"

using namespace std;

namespace gnut
{
	/** default constructor */
	t_galltrp::t_galltrp()
	{
		id_type(t_gdata::ALLTRPZTD);
	}

	/** default destructor */
	t_galltrp:: ~t_galltrp()
	{

	}

	/**
	* @brief push trp data for one site into the alltrp data map.
	* @param [in]  site   site name.
	* @param [in]  trp    trp data for one site.
	*/
	void t_galltrp::add_trp(string site, t_gtrp& trp)
	{
		if (_trps.find(site) != _trps.end())
		{
			t_gtrp& old = _trps[site];
			map<t_gtime, t_trp_record>* newtrp = trp.trp();
			t_gtime begold = old.beg();
			t_gtime endold = old.end();
			t_gtime begnew = trp.beg();
			t_gtime endnew = trp.end();
			if (begold > begnew)
			{
				begold = begnew;
			}
			if (endold < endnew)
			{
				endold = endnew;
			}
			old.set_time(begold, endold);
			auto onetrp = newtrp->begin();
			auto lasttrp = newtrp->end();
			while (onetrp != lasttrp)
			{
				old.set_trp_record(onetrp->first, onetrp->second);
				onetrp++;
			}
		}
		else
		{
			_trps[site] = trp;
		}
		
	}

	/** @brief whether the trp data is empty.
	* @return  bool
	*	@retval   true    trp data is empty
	*   @retval   false   trp data is existent
	*/
	bool t_galltrp::isEmpty()
	{
		if (_trps.size() == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	* @brief return trp data map for all sites.
	* @return    trp data map for all sites.
	*/
	map<string,t_gtrp>* t_galltrp::trps()
	{
		return &_trps;
	}

	/**
	* @brief return trp data for one sites.
	* @return    trp data for one sites.
	*/
	t_gtrp * t_galltrp::trp(string site)
	{
		if (_trps.count(site) == 0)
		{
			if (_spdlog)
			{
				SPDLOG_LOGGER_INFO(_spdlog,  "WARNING : t_galltrp::trp ==> Can not find the trp of " + site);
			}
			else
			{
				cout << "WARNING : t_galltrp::trp ==> Can not find the trp of " + site << endl;
			}
			return NULL;
		}
		return &_trps[site];
	}
}