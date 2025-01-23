# =====================================================================================================
# 读取sinex文件，并将其中的测站名称，测站天线类型，测站精密坐标存储下来！！！
# =====================================================================================================
import logging
import os
import sys

pyDirName, pyFileName = os.path.split(os.path.abspath(__file__))
sys.path.append(f"{pyDirName}/../")

from dependency.gnss_file_tool import isFileExist

# diff struct for plot
class t_sinex(object): 
    def __init__(self):
        """
        构建sinex的数据存储类
        """
        # 文件相关
        self.file_name = ""
        self.file_path = ""

        # 数据相关
        # _LONGITUDE_ _LATITUDE__ HEIGHT_
        # ___RECEIVER_TYPE____ _S/N_ _FIRMWARE__
        # ____ANTENNA_TYPE____ _S/N_ _DAZ
        self.site_list = set()
        self.site_longitude = dict()
        self.site_latitude = dict()
        self.site_height = dict()
        self.site_receiver = dict()
        self.site_antenna = dict()
        self.site_stax = dict()
        self.site_stay = dict()
        self.site_staz = dict()
        self.site_stadx = dict()
        self.site_stady = dict()
        self.site_stadz = dict()

    def getXYZ(self, site_name):
        """
        从数据类中获取x，y，z的坐标
        """
        if site_name not in self.site_stax or site_name not in self.site_stay or site_name not in self.site_staz:
            raise Exception
        
        return (self.site_stax[site_name], self.site_stay[site_name], self.site_staz[site_name])

# ==================================================================
# 读取并存储sinex文件
# ==================================================================
def readSinexFile(sinex_path, historyData):
    """
    读取Sinex文件
    """
    if not isFileExist(sinex_path):
        logging.error(f"Check your path : {sinex_path}")
        return historyData
    fr = open(sinex_path)
    lines = fr.readlines()
    fr.close()

    # 存储路径等信息
    dataSnx = t_sinex()
    if historyData != None:
        dataSnx = historyData
    dataSnx.file_name = os.path.basename(sinex_path)
    dataSnx.file_path = os.path.dirname(sinex_path)

    # 解码文件
    isBLH = False
    isXYZ = False
    isAtx = False
    isRec = False
    for line in lines:
        # 备注行，直接跳过
        if line[0] == "*":
            continue

        # 大地坐标部分部分
        if "+SITE/ID" in line:
            isBLH = True
            continue
        if "-SITE/ID" in line:
            isBLH = False
            continue

        # 接收机部分
        if "+SITE/RECEIVER" in line:
            isRec = True
            continue
        if "-SITE/RECEIVER" in line:
            isRec = False
            continue

        # 接收机天线部分
        if "+SITE/ANTENNA" in line:
            isAtx = True
            continue
        if "-SITE/ANTENNA" in line:
            isAtx = False
            continue

        # 接收机地固坐标部分
        if "+SOLUTION/ESTIMATE" in line:
            isXYZ = True
            continue
        if "-SOLUTION/ESTIMATE" in line:
            isXYZ = False
            continue

        # 跳过无用的数据块
        if not isAtx and not isBLH and not isXYZ and not isRec:
            continue
        # if "----" in line:
        #     continue

        # 解码，存储为数组
        data = ' '.join(line.split()).split()

        # 根据情况存储到不同的类中
        if True == isAtx:
            # +SITE/ANTENNA
            # *CODE PT SOLN T _DATA START_ __DATA_END__ ____ANTENNA_TYPE____ _S/N_ _DAZ
            # AB09  A ---- P 07:202:00000 00:000:00000 TRM29659.00     SCIT 4622A    0
            rec = data[0]
            dataSnx.site_list.add(rec)
            if rec not in dataSnx.site_antenna:
                dataSnx.site_antenna[rec] = line[42:62]
                logging.debug(f"Add {rec} : ____ANTENNA_TYPE____")

        if True == isBLH:
            # +SITE/ID
            # *CODE PT __DOMES__ T _STATION DESCRIPTION__ _LONGITUDE_ _LATITUDE__ HEIGHT_
            #  AB09  A 49419M001 P Wales - Alaska, UNITED 191 56 16.3  65 36 53.9   162.1
            # 大地坐标部分
            rec = data[0]
            dataSnx.site_list.add(rec)
            site_longitude  = line[44:55]
            site_latitude = line[56:67]
            site_height    = line[68:75]

            data_longitude = ' '.join(site_longitude.split()).split()  
            data_latitude  = ' '.join(site_latitude.split()).split()   
            data_height    = ' '.join(site_height.split()).split()     

            if rec not in dataSnx.site_longitude:
                dataSnx.site_longitude[rec] = float(data_longitude[0]) + float(data_longitude[1]) / 60.0 + float(data_longitude[2]) / 360.0
                dataSnx.site_latitude[rec] = float(data_latitude[0]) + float(data_latitude[1]) / 60.0 + float(data_latitude[2]) / 360.0
                dataSnx.site_height[rec] = float(data_height[0])

                logging.debug(f"Add {rec} : _LONGITUDE_ _LATITUDE__ HEIGHT_")

        if True == isRec:
            # +SITE/RECEIVER
            # *CODE PT SOLN T _DATA START_ __DATA_END__ ___RECEIVER_TYPE____ _S/N_ _FIRMWARE__
            # AB09  A ---- P 16:220:72240 00:000:00000 TRIMBLE NETRS        46252 1.3-2      
            # 接收机信息部分
            rec = data[0]
            dataSnx.site_list.add(rec)

            if rec not in dataSnx.site_receiver:
                dataSnx.site_receiver[rec] = line[42:62]
                logging.debug(f"Add {rec} : ___RECEIVER_TYPE____")

        if True == isXYZ:
            # +SOLUTION/APRIORI
            # *INDEX _TYPE_ CODE PT SOLN _REF_EPOCH__ UNIT S ____APRIORI_VALUE____ __STD_DEV__
            #      1 STAX   AB09  A    1 23:010:43200 m    2 -2.58361495570524e+06 0.00000e+00
            #      2 STAY   AB09  A    1 23:010:43200 m    2 -5.46237013012254e+05 0.00000e+00
            #      3 STAZ   AB09  A    1 23:010:43200 m    2  5.78650164392446e+06 0.00000e+00
            rec = data[2]
            dataSnx.site_list.add(rec)

            if data[1] == "STAX":
                if rec not in dataSnx.site_stax:
                    dataSnx.site_stax[rec] = float(line[47:68])
                    dataSnx.site_stadx[rec] = float(line[69:80])
                    logging.debug(f"Add {rec} : ____APRIORI_VALUE____ __STD_DEV__")
            elif data[1] == "STAY":
                if rec not in dataSnx.site_stay:
                    dataSnx.site_stay[rec] = float(line[47:68])
                    dataSnx.site_stady[rec] = float(line[69:80])
                    logging.debug(f"Add {rec} : ____APRIORI_VALUE____ __STD_DEV__")
            elif data[1] == "STAZ":
                if rec not in dataSnx.site_staz:
                    dataSnx.site_staz[rec] = float(line[47:68])
                    dataSnx.site_stadz[rec] = float(line[69:80])
                    logging.debug(f"Add {rec} : ____APRIORI_VALUE____ __STD_DEV__")
            else:
                continue

    # 返回结果类
    return dataSnx

# if __name__ == '__main__':
#     snx_path = "/home/jdhuang/gitCodes/Wind-Scripts/A-project/run_data_pool/2023/sinex/IGS0OPSSNX_20230100000_01D_01D_SOL.SNX"
#     crd_path = "/home/jdhuang/gitCodes/Wind-Scripts/A-project/run_great_ppplsq/snx.crd"
#     logging.basicConfig(level=logging.DEBUG)
#     sinex_data = readSinexFile(snx_path)

    #WriteCrdFile(sinex_data, crd_path)