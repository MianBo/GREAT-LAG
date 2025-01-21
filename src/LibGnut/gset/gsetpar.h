/**
*

* @verbatim
  The format of this block:
	<parameters>
	     <GEO   sigCX    = "0.001"  sigCY    = "0.001" sigCZ  = "0.001"/>   
		 <STA   ID = "AIRA" sigCLK = "9000" sigZTD = "0.201"    sigION = "1.000"     sigPOS = "0.1_0.1_0.1"/>
		 <SAT   ID = "G01"  sigCLK = "5000" sigPOS = "10_10_10" sigVEL = "10_10_10"  sigECOM = "0.1_0.1_0.1_0.1_0.1_0.1_0.1_0.1_0.1"/>
	</parameters>
  @endverbatim

* @verbatim
	History
	 -1.0 jdhuang	 2019-04-07 creat the file.
	 -1.1 jdhuang    2019-05-12 add the ion par for site.
  @endverbatim
* Copyright (c) 2018, Wuhan University. All rights reserved.
*
* @file			gsetpar.h
* @brief		set pars from XML
*
* @author       jdhuang, Wuhan University
* @version		1.0.0
* @date			2019-04-07
*
*/

#ifndef GSETPARS_H
#define GSETPARS_H

#define XMLKEY_PARS        "parameters"
#define XMLKEY_PARS_GEO    "GEO"
#define XMLKEY_PARS_SAT    "SAT"
#define XMLKEY_PARS_STA    "STA"
#define XMLKEY_PARS_AMB    "AMB"

#include "gset/gsetbase.h"
#include "gexport/ExportLibGnut.h"
#include "gutils/gtriple.h"
namespace gnut
{
	/** @brief class for setting of parameter in XML file */
	class LibGnut_LIBRARY_EXPORT t_gsetpar : public virtual t_gsetbase
	{
	public:
		/** @brief constructor */
		t_gsetpar();

		/** @brief destructor */
		virtual ~t_gsetpar();

		/** @brief settings help */
		void help();

		/** @brief settings check */
		void check() {};
	private:

		/** @brief get child value */
		string _child_value(const string& child);

		/** @brief get child attribute value */
		string _child_attribute_value(const string& child, const string& attribute);

		/** @brief get attribute value */
		string _attribute_value(const string & index_name, const string & index_value, const string & attribute);

		/** @brief split string */
		void  split(const std::string& s, std::string delim, std::vector< std::string >& ret);
		
	};
}

#endif