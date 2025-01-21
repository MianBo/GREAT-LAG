/**@file  main.c
* @brief       
* @details  
* @author      dengzhixu
* @date        2018-8-17
* @version     V1.0
* @copyright    Copyright (c) 2050
**********************************************************************************
* @attention
* SDK版本：v2050.0.0
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2010/02/17  <td>1.0      <td>wanghuan  <td>创建初始版本
* </table>
*
**********************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <memory> 

#include "gcoders/trp.h"
#include "gutils/gtypeconv.h"
#include "gmodels/gtropo.h"


using namespace std;

namespace gnut {

t_trp::t_trp( t_gsetbase* s, string version, int sz, string id )
 : t_gcoder( s, version, sz, id )
{   
  _ac = "";
  _beg = FIRST_TIME;   
  _end = LAST_TIME;    
  _tab_data = 0;
  _gtrp = new t_gtrp();
}


int t_trp::decode_head(char* buff, int sz, vector<string>& errmsg)
{
	if (t_gcoder::_add2buffer(buff, sz) == 0) { return 0; };
	string line;
	int consume = 0;
	int tmpsize = 0;
	size_t idx = 0;
	string year = "";
	string mon = "";
	
	while ((tmpsize = t_gcoder::_getline(line)) >= 0) {
		consume += tmpsize;
		if (line.find("%=TRO") == 0) { // first line
			_version = str2dbl(line.substr(6, 4));
			_ac = line.substr(28, 3);
			_site = line.substr(61, 4);
		}
		else if (line.find("+TROP/SOLUTION") != string::npos) {
			t_gcoder::_consume(tmpsize);
			 return -1;
		}
		else if (line.find("+SITE/RECEIVER") != string::npos) {
			t_gcoder::_consume(tmpsize);
		}
		else if (line.find("+SITE/ANTENNA") != string::npos) {
			t_gcoder::_consume(tmpsize);
		}
		else if (line.find("+SITE/GPS_PHASE_CENTER") != string::npos) {
			t_gcoder::_consume(tmpsize);
		}
		else if (line.find("+SITE/ECCENTRICITY") != string::npos) {
			t_gcoder::_consume(tmpsize);
		}
		else if (line.find("+TROP/DESCRIPTION") != string::npos) {
			t_gcoder::_consume(tmpsize);
		}
		else if (line.find("+TROP/STA_COORDINATES") != string::npos) {
			t_gcoder::_consume(tmpsize);
		}
		t_gcoder::_consume(tmpsize);
	}

	return consume;
}
  
int t_trp::decode_data(char* buff, int sz, int& cnt, vector<string>& errmsg)
{
	if (t_gcoder::_add2buffer(buff, sz) == 0)
	{
		_mutex.unlock();
		return 0;
	}

	int tmpsize = 0;
	int sitsize = 0;
	string line;
	string sitename;
	double year, GPSWeek, SOW;
	int num1, num2, num3;
	string site;
	string epoch;
	t_gtime epo;
	while ((tmpsize = t_gcoder::_getline(line)) >= 0)
	{
		sitsize += tmpsize;
		if (line.find("%=ENDTRO") != string::npos)
		{
			_mutex.unlock();
			return -1;
		}
		if (line.find("-TROP/SOLUTION") != string::npos)
		{	
			map<t_gtime, t_trp_record>* tmp_trp = (*_gtrp).trp();
			auto beg = tmp_trp->begin();
			auto end = tmp_trp->end();
			--end;
			(*_gtrp).set_time(beg->first, end ->first);
			map<string, t_gdata *>::iterator it = _data.begin();
			while (it != _data.end())
			{
				if (it->second->id_type() == t_gdata::ALLTRPZTD)
				{
					((t_galltrp *)it->second)->add_trp(site, *_gtrp);
				}
				it++;
			}
			_tab_data = 0;

			t_gcoder::_consume(tmpsize);
			continue;
		}
		if (_tab_data == 0)
		{
			_tab_data++;
			t_gcoder::_consume(tmpsize);
			continue;
		}

		istringstream istr(line);
		istr >> site >> epoch >> _record.TROTOT >> _record.STDDEV_TRO >> _record.TGNTOT >> _record.STDDEV_TGN >> _record.TGETOT >> _record.STDDEV_TGE;
		epo.from_str("%y:%j:%s", epoch);
		(*_gtrp).set_trp_record(epo, _record);
		//_tab_data++;
	
		t_gcoder::_consume(tmpsize);
	}
	return -1;
}


} // namespace
