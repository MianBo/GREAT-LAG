# -*- coding: utf-8 -*-
# ===================================================================
# 时间模块
# ===================================================================

#! python3
# coding:utf-8
from datetime import datetime
import os
import sys

pyDirName, pyFileName = os.path.split(os.path.abspath(__file__))
sys.path.append(f"{pyDirName}/../")

gpst0 = [1980, 1, 6, 0, 0, 0]
gst0 = [1999, 8, 22, 0, 0, 0]
bdt0 = [2006, 1, 1, 0, 0, 0]
DATETIME_1970 = datetime(1970, 1, 1, 0, 0, 0, 0)
DATETIME_GPS0 = datetime(1980, 1, 6, 0, 0, 0, 0)
DATETIME_2000 = datetime(2000, 1, 1, 0, 0, 0, 0)
SECONDS_2000 = 946_728_000.0  # Seconds from 1970-01-01T00:00:00 to 2000-01-01T00:00:00 (UTC)
MJD_2000 = 51_544.5   # Modified Julian Day at 2000-01-01T00:00:00 (UTC)
JD = 2_400_000.5  # Julian Day starting at noon on Monday, January 1, 4713 BC
JD_2000 = 2_451_545.0  # Julian Day at 2000-01-01T00:00:00 (UTC)
JD_1950 = 2_433_282.50  # Julian Day at 1950-01-01T00:00:00 (UTC)
SESSIONS = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', '0']


########################################################################
# (epoch list) to (time second)
########################################################################

def epoch2time(ep):
    """
    epoch数组转时间
    """
    year = int(ep[0])
    mon = int(ep[1])
    day = int(ep[2])
    hour = int(ep[3])
    min = int(ep[4])
    sec = ep[5]
    doy = [1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335]
    if (year < 1970 or 2099 < year or mon < 1 or 12 < mon):
        return 0
    days = (year - 1970) * 365 + (year - 1969) // 4 + doy[mon - 1] + day - 2
    if (year % 4 == 0 and mon >= 3):
        days = days + 1
    isec = days * 86400 + hour * 3600 + min * 60 + int(sec)
    fsec = sec - int(sec)
    return isec, fsec




########################################################################
# (time) to (gps week + gps second of week)
########################################################################

def time2gpst(isec, fsec):
    """
    时间转gpst
    """
    isec0, fsec0 = epoch2time(gpst0)
    sec = (isec-isec0)+(fsec-fsec0)
    gpsw = int(sec // (86400 * 7))
    gpssec = sec - gpsw * 86400 * 7
    return gpsw, gpssec


def epoch2gpst(ep):
    isec, fsec = epoch2time(ep)
    gpsw, gpssec = time2gpst(isec, fsec)
    return gpsw, gpssec
