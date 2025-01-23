/**
*
* @verbatim
History
	-1.0 Jiande huang  2019-11-14  creat the file.
@endverbatim
* Copyright (c) 2018, Wuhan University. All rights reserved.
*
* @file		gion.h
* @brief	Storage the ion files' data
*
* @author   Jiande huang, Wuhan University
* @version	1.0.0
* @date		2019-11-14
*
*/

#ifndef GION_H
#define GION_H

#include "gexport/ExportLibGnut.h"
#include "gdata/gdata.h"
#include "gutils/gtime.h"

namespace gnut
{
	/**
	*@brief	 Class for record ion record
	*/
	class LibGnut_LIBRARY_EXPORT t_gion_record
	{
	public:
		/** @brief constructor. */
		t_gion_record();

		/**
		* @brief push trp data for one site into the alltrp data map.
		* @param [in]  type   SION or VION.
		* @param [in]  rec    receiver.
		* @param [in]  sat    sat.
		* @param [in]  value  ion value.
		* @param [in]  beg    beg.
		* @param [in]  end    end.
		*/
		t_gion_record(const string& type, const string& rec, const string& sat,
			const double& value, const double& sigma,
			const t_gtime& beg, const t_gtime& end);

		/** @brief default destructor. */
		virtual ~t_gion_record();

		string ion_type; // SION or VION
		double value;    // ion vale
		double sigma;    // ion sigma
		string sat;      //sat
		string rec;      // receiver
		t_gtime beg;     //begin
		t_gtime end;     // end
	};

	/**
	*@brief	 Class for storaging ion record data
	*/
	class LibGnut_LIBRARY_EXPORT t_gion : public t_gdata
	{
	public:

		/** @brief default constructor. */
		t_gion();

		/** @brief default destructor. */
		virtual ~t_gion();

		/**
		 * @brief set_header
		 *
		 * @param beg
		 * @param end
		 * @param intv
		 * @param num_amb
		 * @param sats
		 * @param recs
		 * @return 
		 */
		void    set_header(const t_gtime& beg, const t_gtime& end, const double& intv, const int& num_amb, const set<string>& sats, const set<string>& recs);

		/**
		 * @brief get_header
		 *
		 * @param beg
		 * @param end
		 * @param intv
		 * @param sats
		 * @param recs
		 * @return
		 */
		void    get_header(t_gtime& beg,t_gtime& end, double& intv, set<string>& sats, set<string>& recs);

		/**
		 * @brief get_value
		 *
		 * @param beg
		 * @param end
		 * @param sats
		 * @param recs
		 * @return gion_record value
		 */
		double  get_value(const string& rec, const string& sat, const t_gtime& beg, const t_gtime& end);

		/**
		 * @brief add_record
		 *
		 * @param record
		 * @return 
		 */
		void   add_record(const t_gion_record& record);

		/**
		 * @brief get_records
		 *
		 * @param rec
		 * @param sat
		 * @return _ions
		 */
		map<t_gtime, t_gion_record>& get_records(string rec, string sat);
	protected:
		map< pair<string, string>, map<t_gtime, t_gion_record> > _ions; // rec_sat_beg
	private:
		t_gtime		_beg;
		t_gtime     _end;
		double		_intv = 300.0;
		int			_numb = 0;
		set<string> _sats;
		set<string> _recs;
	};
}

#endif // !GION_H
