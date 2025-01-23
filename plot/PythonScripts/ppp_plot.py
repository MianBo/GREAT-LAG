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
    "ABMF"
]

# 数据的年份
year = 2021
# 数据的年积日
day = 100
# 设置数据类型：浮点解(ppp-float)或者固定解(ppp-fixed)
type1 = "LEO-float"
type2 = "LEO-fixed"

# 对应 type1 的测站数据
fltPath1 = rf"..\data_ppp\kin_float"
# 对应 type2 的测站数据
fltPath2 = rf"..\data_ppp\kin_fix"
# 保存的结果目录
savePath = rf"..\output"
# gnss_crd_io.py 脚本输出的 crd 文件路径
crdPath = rf"..\data_ppp\crd\snx_igs_2021_100.crd"

crdData = readCrdFile(crdPath)
for doy in tqdm(range(day, day + 1)):
    yeardoy_savePath = os.path.join(savePath, f"{year:04d}_{doy:03d}_kin")
    for site in siteList:
        logging.info(f"{site}")
        for i in range(1):
            fltFilePath1 = os.path.join(fltPath1, f"{site}-LEO.flt")
            fltFilePath2 = os.path.join(fltPath2, f"{site}-LEO.flt")
            if not os.path.exists(fltFilePath2):
                continue
            fltData2 = readGreatFltFile_v2(fltFilePath2)
            if not os.path.exists(fltFilePath1):
                continue
            fltData1 = readGreatFltFile_v2(fltFilePath1)
            gnss_great_draw_compare_flt(site, type1, type2, fltData1, fltData2, crdData, yeardoy_savePath)
