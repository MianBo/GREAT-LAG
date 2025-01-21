/**
*
* @verbatim
History
    -1.0 Guolong Feng  2020-07-13  creat the file.
@endverbatim
* Copyright (c) 2018, Wuhan University. All rights reserved.
*
* @file		trp.h
* @brief	 decode TRP products 

* @version	1.0.0
* @date		2025-01-13
*
*/
#ifndef TRO_H
#define TRP_H
 

#include "gcoders/gcoder.h"
#include "gutils/gtime.h"
#include "gdata/gtrp.h"
#include "gall/galltrp.h"

using namespace std;

namespace gnut {

    /**
    *@brief Class for t_trp derive from t_gcoder
    */
    class LibGnut_LIBRARY_EXPORT t_trp : public t_gcoder 
    {

    public:
        /** @brief constructor set + version + sz. */
        t_trp( t_gsetbase* s, string version, int sz = DEFAULT_BUFFER_SIZE, string id = "trp" );

        /** @brief default destructor. */
        virtual ~t_trp(){};

        /** @brief decode head. */
        virtual  int decode_head(char* buff, int bufLen,           vector<string>& errmsg);

        /**
         * @brief encode data
         *
         * @param buff
         * @param sz
         * @param cnt
         * @param errmsg
         * @return int
         */
        virtual  int decode_data(char* buff, int bufLen, int& cnt, vector<string>& errmsg);
   
    protected:
        t_gtime _beg;     
        t_gtime _end;     

        string _ac;
        double _version; // 1.00 or 0.01
        string _site;
        int _tab_data;

        t_gtrp *_gtrp;	 ///< storage TRP data for one epoch
        t_trp_record _record; ///< one record of TRP data
};

} // namespace

#endif
