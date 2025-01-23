# -*- coding: utf-8 -*-
# ===================================================================
# 读取rtklib的pos格式
# ===================================================================
import logging
import os
import sys

pyDirName, pyFileName = os.path.split(os.path.abspath(__file__))
sys.path.append(f"{pyDirName}/../")

from dependency.gnss_file_tool import isFileExist

# %  GPST              x-ecef(m)      y-ecef(m)      z-ecef(m)   Q  ns   sdx(m)   sdy(m)   sdz(m)  vx(m/s)  vy(m/s)  vz(m/s) age(s)  ratio
class t_pos_data(object):  # meter
    """
    存储pos文件中一行的结果
    """
    def __init__(self):
        self.gpst = str()
        self.intv = 0       # 采样间隔
        self.x = 0.0
        self.y = 0.0
        self.z = 0.0
        self.Q = 0
        self.ns = 0
        self.sdx = 0.0
        self.sdy = 0.0
        self.sdz = 0.0
        self.vx = 0.0
        self.vy = 0.0
        self.vz = 0.0
        self.age = 0.0
        self.ratio = 0.0
        self.VPL = 999
        self.HPL1 = 999
        self.HPL2 = 999
        self.HPL = 999
        self.dataline = str()

class t_great_pos_data(object):  # meter
    """
    存储great输出的pos文件中一行的结果
    """
    def __init__(self):
        self.gpst = str()
        self.intv = 0       # 采样间隔
        self.x = 0.0
        self.y = 0.0
        self.z = 0.0
        self.Q = 0
        self.ns = 0
        self.pdop = 0
        self.sdx = 0.0
        self.sdy = 0.0
        self.sdz = 0.0
        self.e = 0.0
        self.n = 0.0
        self.u = 0.0
        self.age = 0.0
        self.ratio = 0.0
        self.VPL = 999
        self.HPL1 = 999
        self.HPL2 = 999
        self.HPL = 999
        self.dataline = str()


# ==================================================================
# 读取并存储enu文件
# ==================================================================
# 格式如下
# 289371.000000  -0.011289  -0.028786  -0.049688
# 289372.000000  -0.010637  -0.029137  -0.043173
# 289373.000000  -0.007493  -0.030170  -0.043389
# 289374.000000  -0.007987  -0.031222  -0.045545
# 289375.000000  -0.008818  -0.030420  -0.042963
# 289376.000000  -0.010064  -0.027494  -0.038076
# 289377.000000  -0.010479  -0.029679  -0.038306
# 289378.000000  -0.008245  -0.031363  -0.039388
# 289379.000000  -0.010064  -0.030080  -0.039597
# ==================================================================
def readVisEnuFile(VisEnuFilePath):
    """
    读取多源融合的ENU文件, 并返回dict[sod] = t_great_pos_data()
    """
    ## 读取文件
    if not isFileExist(VisEnuFilePath):
        logging.error(f"Check your path : {VisEnuFilePath}")
    fr = open(VisEnuFilePath)
    lines = fr.readlines()
    fr.close()

    ## 存储数据
    posData = dict()

    ## 解码文件
    for line in lines:
        if "%" in line or "RMS" in line:
            continue

        tmpData = ' '.join(line.split()).split()
        sow = float(tmpData[0])
        sod = sow % 86400
        eErr = float(tmpData[1])
        nErr = float(tmpData[2])
        uErr = float(tmpData[3])

        epoData = t_great_pos_data()
        epoData.e = eErr
        epoData.n = nErr
        epoData.u = uErr

        if len(tmpData) >= 5:
            epoData.ns = float(tmpData[4])
        if len(tmpData) >= 6:
            epoData.pdop = float(tmpData[5])

        if sod not in posData:
            posData[sod] = epoData

    return posData
