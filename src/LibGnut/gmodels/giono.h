
/**
*
* @verbatim
History
	-1.0 Guolong Feng  2020-07-17  creat the file.
@endverbatim
* Copyright (c) 2018, Wuhan University. All rights reserved.
*
* @file		giono.h
* @brief	implements ionosphere model class

* @version	1.0.0
* @date		2020-07-17
*
*/


#ifndef GIONO_H
#define GIONO_H 

#include "gall/gallnav.h"
#include "gdata/gionex.h"
#include "gdata/gsatdata.h"
#include "gexport/ExportLibGnut.h"

using namespace std;

namespace gnut
{
	/**
	*@brief Class for t_giono 
	*/
	class LibGnut_LIBRARY_EXPORT t_giono
	{
	public:
		/** @brief constructor. */
		t_giono();

		/** @brief default destructor. */
		virtual ~t_giono();

		/** @brief mapping function. */
		double ionMapFunc(IONMPFUNC mapfunc, double ele);

	protected:
	};

	/**
	*@brief Class for t_giono_brdc derive from t_giono
	*/
	class LibGnut_LIBRARY_EXPORT t_giono_brdc : public t_giono 
	{
	public:
		/** @brief constructor. */
		t_giono_brdc() {}

		/** @brief default destructor. */
		~t_giono_brdc() {}

		/**
		* @brief compute ionospheric delay by broadcast ionosphere model (klobuchar model)
		* @param[in] nav         store iono model parameters {a0,a1,a2,a3,b0,b1,b2,b3}
		* @param[in] epo         curruent epoch.
		* @param[in] satdata     provide azimuth/elevation angle {az,el} (rad)
		* @param[in] site_ell    receiver position {lat,lon,h} (rad,m)
		
		* @return	             ionospheric delay (L1) (m)
        **/
		double getIonoDelay(t_gallnav* nav, t_gsatdata& satdata, const t_gtime& epo, const t_gtriple& site_ell);

	};

	/**
	*@brief Class for t_giono_sbas derive from t_giono
	*/
	class LibGnut_LIBRARY_EXPORT t_giono_sbas : public t_giono 
	{
	public:
		/** @brief constructor. */
		t_giono_sbas() {}

		/** @brief default destructor. */
		~t_giono_sbas() {}

	};
	
	
	
	/**
	*@brief Class for t_giono_tecgrid derive from t_giono
	*/
	class LibGnut_LIBRARY_EXPORT t_giono_tecgrid : public t_giono 
	{
	public:
		/** @brief constructor. */
		t_giono_tecgrid() {}

		/** @brief default destructor. */
		~t_giono_tecgrid() {}

		/**
		* @brief compute ionospheric delay by broadcast ionosphere model (klobuchar model)
		* @param[in] ionexdata      ionospheric delay by tec grid data
		* @param[in] satdata		provide azimuth/elevation angle {az,el} (rad)
		* @param[in] epo			curruent epoch.
		* @param[in] site_pos		receiver position {lat,lon,h} (rad,m)
		* @param[in] value			value of ionospheric delay (L1) (m)
		* @param[in] rms			rms of ionospheric delay (L1) (m)
		* @return	             
		**/
		bool getIonoDelay(t_gionex* ionexdata, t_gsatdata& satdata, const t_gtime& epo, t_gtriple& site_pos, double& value, double& rms);
	};
	
	
	

} // namespace

#endif
