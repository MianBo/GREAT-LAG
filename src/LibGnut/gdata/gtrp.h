/**
 *
 * @verbatim
 	History
 	-1.0 Yujie Qin	  2019-01-06 creat the file.
 	-1.1 Wei Zhang    2019-03-27 Adding Doxygen Style Code Remarks
 	-1.2 Yujie Qin    2019-07-03 Adding Doxygen Style Code Remarks
 @endverbatim
 * Copyright (c) 2018, Wuhan University. All rights reserved.
 *
 * @file			gtrp.cpp
 * @brief		    Storage the TRP data for one site
 *
 * @author  	    Yujie Qin, Wuhan University
 * @version		    1.0.0
 * @date			2019-03-27
 *
 */


#ifndef GTRP_H
#define GTRP_H

#include <vector>
#include <map>

#include "gdata/gdata.h"
#include "gutils/gtime.h"
#include "gexport/ExportLibGnut.h"

using namespace std;

namespace gnut
{
	/**
	* @brief	   Class for one record of TRP data
	*/
	class LibGnut_LIBRARY_EXPORT t_trp_record
	{
	public:
		/** @brief defalut constructor. */
		t_trp_record();

		/** @brief default destructor. */
		virtual ~t_trp_record();

		double TROTOT;  
		double STDDEV_TRO;  
		double TGNTOT;  
		double STDDEV_TGN;  
		double TGETOT;  
		double STDDEV_TGE;  
	};

	/**
	* @brief	   Class for TRP data storaging of one epoch
	*/
	class LibGnut_LIBRARY_EXPORT t_gtrp : public t_gdata
	{
	public:
		/** @brief defalut constructor. */
		t_gtrp();

		/** @brief default destructor. */
		virtual ~t_gtrp();

		/**
	    * @brief push time and _onerec into the map.
	    * @param [in]  time        time of TRP data
	    * @param [in]  onerec      one record of TRP data
	    */
		void set_trp_record(t_gtime time, t_trp_record onerec);

		/**
	    * @brief set begin and end time of the TRP data.
	    * @param [in]  begtime       begin time of TRP file
	    * @param [in]  endtime       end time of TRP file
	    */
		void set_time(const t_gtime& begtime, const t_gtime& endtime);

		/**
	    * @brief set interval of the data.
	    * @param [in]  inter       interval of TRP data
	    */
		void set_inter(int inter);

		/**
	     * @brief return begin time of the TRP data
	     * @return    begin time
	     */
		t_gtime  beg();

		/**
	    * @brief return end time of the TRP data
	    * @return    end time
	    */
		t_gtime  end();

		/**
	    * @brief return _inter.
	    * @return   interval of the TRP data
	    */
		int      interval();

		/**
	    * @brief return TRP data map for one LEO satellite
	    * @return  TRP data map for one LEO satellite
	    */
		map<t_gtime, t_trp_record>* trp();

	protected:
		map<t_gtime, t_trp_record>  _trp;  ///< map of the epoch and the corresponding TRP record for one site
		t_gtime                     _beg;       ///< begin time of the TRP data
		t_gtime                     _end;       ///< end time of the TRP data
		int                         _inter;     ///< interval of the data
	};
};// namespace

#endif
