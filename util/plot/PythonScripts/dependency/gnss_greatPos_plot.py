# -*- coding: utf-8 -*-
# ===================================================================
# 读取GREAT输出的pos文件，并绘制成图
# ===================================================================

from math import floor
import os
import sys

pyDirName, pyFileName = os.path.split(os.path.abspath(__file__))
sys.path.append(f"{pyDirName}/../")

from dependency.gnss_math_tool import get_round

# ===================================================================
# 获取完整的时间索引，主要是考虑到跨周、历元缺失的情况
# ===================================================================
def getPosTimeIndex(posData, intv):
    tmp_index = set()

    begTime = +9999
    endTime = -9999
    
    gpsw=0
        
    
    
    #pppflt
    for gpsw in posData:        
        for sow in posData[gpsw]:
            time = float(gpsw) + float(sow) / 10e6
            if begTime > time:
                begTime = time
            if endTime < time:
                endTime = time

    time_index = list()

    time = begTime
    gpsw = floor(time)
    while(True):
        gsow = (time - floor(time))  * 10e6
        if gsow > 86400 * 7:
            gpsw = gpsw + 1
            gsow = 1
        str_gpsw = f"{gpsw:04d}"
        str_gsow = get_round(float(gsow),"0.01")
        str_gsow = f"{int(str_gsow)}"
        time_index.append(str_gpsw + "." + str_gsow)
        if time > endTime:
            break

        time = time + intv / 10e6

    return time_index

