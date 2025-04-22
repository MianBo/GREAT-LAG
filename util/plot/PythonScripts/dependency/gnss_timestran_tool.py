#!/usr/bin/python3
# -*- coding: utf-8 -*-
# GNSS_Timestran : GNSS_Timestran
# Author         : Chang Chuntao
# Copyright(C)   : The GNSS Center, Wuhan University & Chinese Academy of Surveying and mapping
# Latest Version : 1.25
# Creation Date  : 2022.03.27 - Version 1.00
# Date           : 2022.11.02 - Version 1.25

def doy2gpswd(year, doy):
    """
    2022.09.30 : year doy -> gpswd
             by ChangChuntao -> Version : 1.00
    """
    import datetime
    day1Time = datetime.datetime(year, 1, 1)
    specTime = day1Time + datetime.timedelta(days=int(doy) - 1)
    gpsWeekdDelTime = specTime - datetime.datetime(year=1980, month=1, day=6)
    gpsWeek = gpsWeekdDelTime.days // 7
    gpsWeekD = gpsWeekdDelTime.days - gpsWeek * 7
    return gpsWeek, gpsWeekD
