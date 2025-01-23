/**
 * @file         gsetsimu.h
 * @author       GREAT-WHU (https://github.com/GREAT-WHU)
 * @brief        control set from XML
 * @version      1.0
 * @date         2025-01-12
 *
 * @copyright Copyright (c) 2024, Wuhan University. All rights reserved.
 *
 */

#ifndef GSETSIMU_H
#define GSETSIMU_H

#define XMLKEY_SIMU "simu" ///< The defination of npp node in XML

#include <string>
#include <iostream>
#include "gset/gsetbase.h"

using namespace std;
using namespace pugi;

namespace gnut
{

	/// The class for setting of simuobs in XML file
	class LibGnut_LIBRARY_EXPORT t_gsetsimu : public virtual t_gsetbase
	{
	public:
		/** @brief constructor */
		t_gsetsimu();

		/** @brief destructor */
		~t_gsetsimu();

		/** @brief settings check */
		void check();

		/** @brief settings help */
		void help();

		/** @brief get whether clk simu  */
		bool clk();

		/** @brief get whether ion simu */
		bool ion();

		/** @brief get whether ztd simu */
		bool zwd();

		/** @brief get whether upd simu */
		bool upd();

		/** @brief get whether isb simu */
		bool isb();

		/** @brief get whether ifb simu */
		bool ifb();

		/** @brief get amb simu sig */
		double sig_simu_amb();

		/** @brief get clk simu sig */
		double sig_simu_clk();

	protected:

	private:
	};

} // namespace
#endif
