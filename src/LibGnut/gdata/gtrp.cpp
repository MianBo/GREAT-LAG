/**
 *
 * @verbatim
 History
 -1.0 Yujie Qin	  2019-01-06 creat the file.
 -1.1 Wei Zhang   2019-03-27 Adding Doxygen Style Code Remarks
 @endverbatim
 * Copyright (c) 2018, Wuhan University. All rights reserved.
 *
 * @file			gattitude.cpp
 * @brief		    Storage the LEO attitude data for one satellite
 *
 * @author		    Yujie Qin, Wuhan University
 * @version		    1.0.0
 * @date			2019-03-27
 *
 */

#include "gtrp.h"
using namespace std;

namespace gnut {

	/** @brief default constructor. */
	t_trp_record::t_trp_record()
	{
		TROTOT = 0.0;
		STDDEV_TRO = 0.0;
		TGNTOT = 0.0;
		STDDEV_TGN = 0.0;
		TGETOT = 0.0;
		STDDEV_TGE = 0.0;
	}

	/** @brief default destructor. */
	t_trp_record::~t_trp_record()
	{

	}

	/** @brief default constructor. */
	t_gtrp::t_gtrp()
	{
		id_type(t_gdata::ALLTRPZTD);
	}

	/** @brief default destructor. */
	t_gtrp::~t_gtrp()
	{

	}

	/**
	* @brief push time and _onerec into the map.
	* @param [in]  time        time of attitude data
	* @param [in]  onerec      one record of attitude data
	*/
	void t_gtrp::set_trp_record(t_gtime time, t_trp_record onerec)
	{
		_trp[time] = onerec;
		return;
	}

	/**
	* @brief set begin and end time of the attitude data.
	* @param [in]  begtime       begin time of attitude file
	* @param [in]  endtime       end time of attitude file
	*/
	void t_gtrp::set_time(const t_gtime& begtime, const t_gtime& endtime)
	{
		_beg = begtime;
		_end = endtime;
		return;
	}

	/**
	* @brief set interval of the data.
	* @param [in]  inter       interval of attitude data
	*/
	void t_gtrp::set_inter(int inter)
	{
		_inter = inter;
		return;
	}

	/**
	* @brief return begin time of the attitude data
	* @return    begin time 
	*/
	t_gtime t_gtrp::beg()
	{
		return _beg;
	}

	/**
	* @brief return end time of the attitude data
	* @return    end time
	*/
	t_gtime t_gtrp::end()
	{
		return _end;
	}

	/**
	* @brief return _inter.
	* @return   interval of the attitude data
	*/
	int t_gtrp::interval()
	{
		return _inter;
	}

	/**
	* @brief return attitude data map for one LEO satellite
	* @return  attitude data map for one LEO satellite
	*/
	map<t_gtime, t_trp_record>* t_gtrp::trp()
	{
		return &_trp;
	}
}