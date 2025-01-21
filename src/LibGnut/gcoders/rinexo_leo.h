/**
*
* @verbatim
History
-1.0 xjhan  2019-11-22  creat the file.

@endverbatim
* Copyright (c) 2018, Wuhan University. All rights reserved.
*
* @file		rinexo_leo.h
* @brief	read rinexo containing leo data.
*
* @author   xjhan , Wuhan University
* @version	1.0.0
* @date		2019-11-22
*
*/
#ifndef RINEXO_LEO_H
#define RINEXO_LEO_H

#include <string> 
#include <vector> 

#include "gall/gallobs.h"
#include "gall/gallobj.h"
#include "gutils/gtime.h"
#include "gutils/gtriple.h"
#include "gutils/gsys.h"

#include "gutils/gobs.h"
#include "gutils/gtypeconv.h"


#include "gcoders/gcoder.h"
#include "gcoders/rinexo2.h"
#include "gcoders/rinexo3_leo.h"
#include "gdata/grnxhdr.h"

using namespace std;

namespace gnut {
	/**
	*@brief Class for t_rinexo_leo derive from t_rinexo3_leo
	*/
	class LibGnut_LIBRARY_EXPORT t_rinexo_leo : public t_rinexo3_leo {

	public:
		/** @brief constructor set + version + sz. */
		t_rinexo_leo(t_gsetbase* s, string version = "", int sz = DEFAULT_BUFFER_SIZE);

		/** @brief default destructor. */
		virtual ~t_rinexo_leo() {};

		/** @brief decode head. */
		virtual  int decode_head(char* buff, int sz, vector<string>& errmsg);

		/**
		 * @brief
		 *
		 * @param buff
		 * @param sz
		 * @param cnt
		 * @param errmsg
		 * @return int
		 */
		virtual  int decode_data(char* buff, int sz, int& cnt, vector<string>& errmsg);

		/** @brief encode head. */
		virtual  int encode_head(char* buff, int sz, vector<string>& errmsg);

		/**
		 * @brief
		 *
		 * @param buff
		 * @param sz
		 * @param cnt
		 * @param errmsg
		 * @return int
		 */
		virtual  int encode_data(char* buff, int sz, int& cnt, vector<string>& errmsg);

	protected:
		/** @brief decode head. */
		virtual  int _decode_head();

		/**
		 * @brief decode data
		 *
		 * @return int
		 */
		virtual  int _decode_data();

	private:

	};

} // namespace

#endif
