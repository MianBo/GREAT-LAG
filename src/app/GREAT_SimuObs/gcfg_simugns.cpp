/**
*
* @verbatim
	History
	 -1.0 xjhan		2021-05-16  creat
  @endverbatim
* Copyright (c) 2018, Wuhan University. All rights reserved.
*
* @file		    gcfg_simugns.cpp
* @brief		gnss simu config
* @author       xjhan, Wuhan University
* @version		1.0.0
* @date		    2021-05-16
*
*/

#include "gcfg_simugns.h"

using namespace std;
using namespace pugi;

namespace gnut
{
	t_gcfg_simugns::t_gcfg_simugns() : t_gsetbase(),
		t_gsetgen(),
		t_gsetinp(),
		t_gsetout(),
		t_gsetgnss(),
		t_gsetproc(),
		t_gsetrec(),
		t_gsetsimu()
	{
		_IFMT_supported.insert(IFMT::RINEXO_INP);
		_IFMT_supported.insert(IFMT::RINEXC_INP);
		_IFMT_supported.insert(IFMT::RINEXN_INP);
		_IFMT_supported.insert(IFMT::ATX_INP);
		_IFMT_supported.insert(IFMT::BLQ_INP);
		_IFMT_supported.insert(IFMT::SP3_INP);
		_IFMT_supported.insert(IFMT::UPD_INP);
		_IFMT_supported.insert(IFMT::DE_INP);
		_IFMT_supported.insert(IFMT::IONEX_INP);
		_IFMT_supported.insert(IFMT::SP3SIMU_INP);
		_IFMT_supported.insert(IFMT::RINEXCSIMU_INP);
		_IFMT_supported.insert(IFMT::TRPZTD_INP);
		_IFMT_supported.insert(IFMT::BIAS_INP);
		_IFMT_supported.insert(IFMT::EOP_INP);
		_OFMT_supported.insert(LOG_OUT);
		_OFMT_supported.insert(PPP_OUT);
		_OFMT_supported.insert(FLT_OUT);
		_OFMT_supported.insert(RINEXO_OUT);
	}

	t_gcfg_simugns::~t_gcfg_simugns()
	{
	}

	void t_gcfg_simugns::check()
	{
		t_gsetgen::check();
		t_gsetinp::check();
		t_gsetout::check();
		t_gsetrec::check();
		t_gsetproc::check();
		t_gsetgnss::check();
	}

	void t_gcfg_simugns::help()
	{
		t_gsetbase::help_header();
		t_gsetgen::help();
		t_gsetinp::help();
		t_gsetout::help();
		t_gsetrec::help();
		t_gsetproc::help();
		t_gsetgnss::help();
		t_gsetbase::help_footer();
	}

}