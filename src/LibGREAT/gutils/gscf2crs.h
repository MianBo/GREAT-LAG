/**
 * @file         gtrs2crs.h
 * @author       GREAT-WHU (https://github.com/GREAT-WHU)
 * @brief        calculate the rotation matrix from TRS to CRS and the corresponding partial derivation matrix
 * @version      1.0
 * @date         2024-08-29
 * 
 * @copyright Copyright (c) 2024, Wuhan University. All rights reserved.
 * 
 */
#ifndef GSCF2CRS_H
#define GSCF2CRS_H
#include "gexport/ExportLibGREAT.h"
#include <vector>
#include "newmat/newmat.h"
#include "gmodels/gattitudemodel.h"

using namespace std;

namespace great
{
	/**
	*@brief	   Class for computing rotation from GNSS satellite-fixed system to CRS
	*/
	class LibGREAT_LIBRARY_EXPORT t_gscf2crs
	{
	public:
		/** @brief default constructor. */
		t_gscf2crs();

		/** @brief default destructor. */
		virtual ~t_gscf2crs();

		/**
		* @brief calculate rotation matrix of scf to crs
		* @param[in]  xsat		position of satellite
		* @param[in]  vsat		velocity of satellite
		* @param[in]  xsun		position of satellite
		* @param[out] rotmat	rotation matrix of scf to crs
		*/
		void calcRotMat(ColumnVector& xsat, ColumnVector& vsat, ColumnVector& xsun, Matrix& rotmat);                                       // main funtion , calculate rotation matrix scf to crs
		// extended by yqyuan
		void calcRotMat(string blocktype, string prn, ColumnVector& xsat, ColumnVector& vsat, ColumnVector& xsun, Matrix& rotmat);           // main funtion , calculate rotation matrix scf to crs


	protected:
		/**
		* @brief get number of block type(not used for now)
		* @param[in]  type		block type
		* @return   number
		*/
		int _blocktype_nam2num(string type);

		/**
		* @brief Remove string trailing spaces
		* @param[in]  str		string need to be removed trailing space
		* @return   string after removing trailing space
		*/
		string _trimR(string str);
	};
} // namespace

#endif