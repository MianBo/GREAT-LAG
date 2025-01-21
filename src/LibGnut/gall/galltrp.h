/**
  *
  * @verbatim
	History
	-1.0    Jiande Huang : Optimizing the efficiency of "get" function
  *
  @endverbatim
  * Copyright (c) 2018 G-Nut Software s.r.o. (software@gnutsoftware.com)
  *
  * @file     galltrp.h
  * @brief    container for all trp
  *
  * @author   JD
  * @version  1.0.0
  * @date     2012-11-05
  *
  */

#ifndef GALLTRP_H
#define GALLTRP_H

#include "gexport/ExportLibGnut.h"
#include "gdata/gtrp.h"

namespace gnut
{
	/**
	*@brief	   Class for all trp data storaging
	*/
	class LibGnut_LIBRARY_EXPORT t_galltrp : public t_gdata
	{
	public:
		/** @brief default constructor. */
		t_galltrp();

		/** @brief default destructor. */
		virtual ~t_galltrp();

		/**
		* @brief push trp data for one site into the alltrp data map.
		* @param [in]  site   site name.
		* @param [in]  trp    trp data for one site.
		*/
		void add_trp(string site, t_gtrp& trp);         

		/** 
		* @brief whether the trp data is empty.
	    * @return  bool
	    *	@retval   true    trp data is empty
	    *   @retval   false   trp data is existent
	    */
		bool isEmpty();

		/**
		* @brief return trp data map for all sites.
		* @return    trp data map for all sites.
		*/
		map<string, t_gtrp>*	trps();	
		
		/**
		* @brief return trp data map for all sites.
		* @return    trp data map for all sites.
		*/
		t_gtrp*				trp(string site);			

	protected:
		map<string, t_gtrp>    _trps;  ///< map of satellite name and trp data for all satellites

	};
} // namespace

#endif
