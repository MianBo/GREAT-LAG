# -*- coding:utf-8 -*-
########################################################################
# 判断文件路径是否存在
########################################################################
from functools import wraps
from genericpath import isdir
import os
import sys

pyDirName, pyFileName = os.path.split(os.path.abspath(__file__))
sys.path.append(f"{pyDirName}/../")

########################################################################
# check file exist or not
########################################################################
def isFileExist(filePath):
    """
    判断文件路径是否存在，返回true or false
    """
    if not os.path.exists(filePath):
        return False
    else:
        return True
