/**
*
* The format :
* @verbatim
	History
	 -1.0 jdhuang	 2019-04-07 creat the file.
  @endverbatim
* Copyright (c) 2018, Wuhan University. All rights reserved.
*
* @file			gsetpar.cpp
* @brief		set pars from XML
*
* @author       jdhuang, Wuhan University
* @version		1.0.0
* @date			2019-04-07
*
*/

#include "gset/gsetpar.h"

using namespace gnut;

t_gsetpar::t_gsetpar() : t_gsetbase()
{
	_set.insert(XMLKEY_PARS);
}

t_gsetpar::~t_gsetpar()
{
}

void t_gsetpar::help()
{
	cerr << "<!--> One example for this block : <!-->                       " << endl
		<< "<!--> The index of sigECOM is sigD0,sigDc,sigDs,sigY0,sigYC,sigYs,sigB0,sigBc,sigBs. <!-->" << endl
		<< "<parameters>" << endl
		<< "<GEO   sigCX    = \"0.001\"  sigCY    = \"0.001\" sigCZ  = \"0.001\" / >" << endl
		<< "<station   ID = \"AIRA\" sigCLK = \"9000\" sigZTD = \"0.201\"    sigION = \"9000\"     sigPOS = \"0.1_0.1_0.1\" / >" << endl
		<< "<satellite ID = \"G01\"  sigCLK = \"5000\" sigPOS = \"10_10_10\" sigVEL = \"10_10_10\"  sigECOM = \"0.1_0.1_0.1_0.1_0.1_0.1_0.1_0.1_0.1\"/>  " << endl
		<< "< / parameters>                          " << endl
		<< endl;
}

string t_gsetpar::_child_value(const string& child)
{
	return _doc.child(XMLKEY_ROOT).child(XMLKEY_PARS).child_value(child.c_str());
}

string t_gsetpar::_attribute_value(const string& index_name, const string& index_value, const string& attribute)
{
	xml_node index = _doc.child(XMLKEY_ROOT).child(XMLKEY_PARS).find_child_by_attribute(index_name.c_str(), index_value.c_str());
	if (index)
	{
		return index.attribute(attribute.c_str()).value();
	}
	else
	{
		return string();
	}
}

string t_gsetpar::_child_attribute_value(const string& child, const string& attribute)
{
	return _doc.child(XMLKEY_ROOT).child(XMLKEY_PARS).child(child.c_str()).attribute(attribute.c_str()).value();
}

//注意：当字符串为空时，也会返回一个空字符串
void  t_gsetpar::split(const std::string& s, std::string delim, std::vector< std::string >& ret)
{
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);

	while (index != std::string::npos)
	{
		ret.push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last > 0)
	{
		ret.push_back(s.substr(last, index - last));
	}
}


