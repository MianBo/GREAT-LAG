/**
*
* @verbatim
	History
	 -1.0 xjhan		2021-05-16  creat
  @endverbatim
* Copyright (c) 2018, Wuhan University. All rights reserved.
*
* @file		    gcfg_simugns.h
* @brief		gnss simu config
* @author       xjhan, Wuhan University
* @version		1.0.0
* @date		    2021-05-16
*
*/

#ifndef GCFG_SIMUGNS_H
#define GCFG_SIMUGNS_H


#include "gset/gsetgen.h"
#include "gset/gsetinp.h"
#include "gset/gsetout.h"
#include "gset/gsetproc.h"
#include "gset/gsetgnss.h"
#include "gset/gsetpar.h"
#include "gset/gsetrec.h"
#include "gset/gsetsimu.h"
#include "gset/gsetbase.h"

#include "gall/gallproc.h"
#include "gall/gallprec.h"
#include "gcoders/gcoder.h"
#include "gcoders/rinexo.h"
#include "gcoders/rinexc.h"
#include "gcoders/rinexn.h"
#include "gcoders/biasinex.h"
#include "gcoders/biabernese.h"
#include "gcoders/sp3.h"
#include "gcoders/atx.h"
#include "gcoders/blq.h"
#include "gcoders/dvpteph405.h"
#include "gcoders/poleut1.h"
#include "gio/gfile.h"
#include "gdata/gifcb.h"
#include "gcoders/ifcb.h"
#include "gcoders/ionex.h"
#include "gcoders/trp.h"
#include "gproc/gsimugns.h"
#include "gutils/gtypeconv.h"
#include "gdata/gnavde.h"
#include "gproc/gpppflt.h"

using namespace std;
using namespace pugi;

namespace gnut
{
	class t_gcfg_simugns : public t_gsetgen,
		public t_gsetinp,
		public t_gsetout,
		public t_gsetgnss,
		public t_gsetproc,
		public t_gsetrec,
		public t_gsetpar,
		public t_gsetsimu,
		public t_gsetflt
	{
	public:
		/** @brief default constructor. */
		t_gcfg_simugns();

		/** @brief default destructor. */
	    ~t_gcfg_simugns();

		/** @brief settings check. */
		void check();

		/** @brief settings help. */
		void help();

	protected:

	};

}



#endif