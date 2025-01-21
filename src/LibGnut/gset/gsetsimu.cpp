/*
*
* @verbatim
	 (c) 2018 G-Nut Software s.r.o. (software@gnutsoftware.com)
  @endverbatim
*
* @file		gsetsimu.cpp
* @brief	implements simugns setting class
* @author   xjhan
* @version	1.0.0
* @date		2021-07-10
*
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

#include "gset/gsetsimu.h"
#include "gutils/gtypeconv.h"
#include <omp.h>

using namespace std;
using namespace pugi;

namespace gnut
{
	t_gsetsimu::t_gsetsimu()
		:t_gsetbase()
	{
		_set.insert(XMLKEY_SIMU);
	}

	t_gsetsimu::~t_gsetsimu()
	{
	}

	void t_gsetsimu::check()
	{
		_gmutex.lock();
		_gmutex.unlock();
	}

	void t_gsetsimu::help()
	{
		_gmutex.lock();
		cerr << " <simu \n"
			<< " />\n";
		cerr << "\t<!-- simu description:\n"
			<< "\t choose simulated objects \n"
			<< "\t -->\n\n";
		_gmutex.unlock(); 
		return;
			
	}
	bool t_gsetsimu::clk()
	{
		_gmutex.lock();
		set<string> src = t_gsetbase::_setval(XMLKEY_SIMU, "clk");
		if (src.size() > 0 && ((*src.begin() == "YES") || (*src.begin() == "yes")))
		{
			_gmutex.unlock();
			return true;
		}

		_gmutex.unlock(); return false;
	}
	bool t_gsetsimu::ion()
	{
		_gmutex.lock();
		set<string> src = t_gsetbase::_setval(XMLKEY_SIMU, "ion");
		if (src.size() > 0 && ((*src.begin() == "YES") || (*src.begin() == "yes")))
		{
			_gmutex.unlock();
			return true;
		}

		_gmutex.unlock(); return false;
	}
	bool t_gsetsimu::zwd()
	{
		_gmutex.lock();
		set<string> src = t_gsetbase::_setval(XMLKEY_SIMU, "ztd");
		if (src.size() > 0 && ((*src.begin() == "YES") || (*src.begin() == "yes")))
		{
			_gmutex.unlock();
			return true;
		}

		_gmutex.unlock(); return false;
	}
	bool t_gsetsimu::isb()
	{
		_gmutex.lock();
		set<string> src = t_gsetbase::_setval(XMLKEY_SIMU, "isb");
		if (src.size() > 0 && ((*src.begin() == "YES") || (*src.begin() == "yes")))
		{
			_gmutex.unlock();
			return true;
		}

		_gmutex.unlock(); return false;
	}
	bool t_gsetsimu::ifb()
	{
		_gmutex.lock();
		set<string> src = t_gsetbase::_setval(XMLKEY_SIMU, "ifb");
		if (src.size() > 0 && ((*src.begin() == "YES") || (*src.begin() == "yes")))
		{
			_gmutex.unlock();
			return true;
		}

		_gmutex.unlock(); return false;
	}
	bool t_gsetsimu::upd()
	{
		_gmutex.lock();
		set<string> src = t_gsetbase::_setval(XMLKEY_SIMU, "upd");
		if (src.size() > 0 && ((*src.begin() == "YES") || (*src.begin() == "yes")))
		{
			_gmutex.unlock();
			return true;
		}

		_gmutex.unlock(); return false;
	}

	double t_gsetsimu::sig_simu_amb()
	{
		_gmutex.lock();
		double sig = 10.0;//default
		set<string> src = t_gsetbase::_setval(XMLKEY_SIMU, "sig_amb");
		if (src.size() > 0 )
		{
			_gmutex.unlock();
			sig = str2dbl(*src.begin());
			return sig;
		}

		_gmutex.unlock(); return sig;
	}

	double t_gsetsimu::sig_simu_clk()
	{
		_gmutex.lock();
		double sig = 0;//default
		set<string> src = t_gsetbase::_setval(XMLKEY_SIMU, "sig_clk");
		if (src.size() > 0)
		{
			_gmutex.unlock();
			sig = str2dbl(*src.begin());
			return sig;
		}

		_gmutex.unlock(); return sig;
	}
}
