# =================================================================
# PPP画图主程序
# =================================================================
import logging
import os
from tqdm import tqdm

from dependency.gnss_flt_io import readGreatFltFile_v2
from snx_to_crd import readCrdFile
from dependency.gnss_great_draw_flt import gnss_great_draw_compare_flt

siteList = [
    "AC23", "AC24", "WUH2", "POTS", "GODN", "GODS", 
    "MBAR", "SGOC", "ASCG", "PARK", "CPVG","ALIC","HERS"
]

# 数据的年份
year = 2023
# 数据的年积日
day = 305
# 设置数据类型：浮点解(ppp-float)或者固定解(ppp-fixed)
type1 = "PPP-float"
type2 = "PPP-fixed"

# 对应 type1 的测站数据
fltPath1 = rf"..\data_ppp\sta_float"
# 对应 type2 的测站数据
fltPath2 = rf"..\data_ppp\sta_fix"
# 保存的结果目录
savePath = rf"..\output"
# gnss_crd_io.py 脚本输出的 crd 文件路径
crdPath = rf"..\data_ppp\crd\snx_igs_2023_305.crd"

crdData = readCrdFile(crdPath)
for doy in tqdm(range(day, day + 1)):
    yeardoy_savePath = os.path.join(savePath, f"{year:04d}_{doy:03d}")
    for site in siteList:
        logging.info(f"{site}")
        for i in range(1):
            fltFilePath1 = os.path.join(fltPath1, f"{site}-PPP.flt")
            fltFilePath2 = os.path.join(fltPath2, f"{site}-PPP.flt")
            if not os.path.exists(fltFilePath2):
                continue
            fltData2 = readGreatFltFile_v2(fltFilePath2)
            if not os.path.exists(fltFilePath1):
                continue
            fltData1 = readGreatFltFile_v2(fltFilePath1)
            gnss_great_draw_compare_flt(site, type1, type2, fltData1, fltData2, crdData, yeardoy_savePath)
