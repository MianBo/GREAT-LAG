# ===================================================================
# 统计值计算
# ===================================================================
from decimal import Decimal
import math

RE_WGS84 = 6378137.0           # earth semimajor axis (WGS84) (m)
FE_WGS84 = 1.0/298.257223563   # earth flattening (WGS84)
PI = 3.1415926535897932        # pi

# ==============================================
# 按照精度阈值取四舍五入
# ==============================================
def get_round(value, thrld):
    """
    四舍五入, thrld = "0.001" or "0.01"
    """
    #将数字变为字符串
    strValue=str(value)
    #保留几位小数由像第二个Decimal括号中的几位小数决定，即保留两位小数，精确到0.01
    #如果想要四舍五入保留整数，那么第二个括号中就应该为"1."
    a_int = Decimal(strValue).quantize(Decimal(thrld), rounding = "ROUND_HALF_UP")#保留后三位
    return a_int

# ==============================================
# 取平均值
# ==============================================
def get_average(records):
    """
    平均值
    """
    if len(records) == 0:
        return 999
    else:
        return sum(records) / len(records)

# ==============================================
# 取方差
# ==============================================

def get_variance(records):
    """
    方差 反映一个数据集的离散程度
    """
    average = get_average(records)
    if len(records) == 0:
        return 999
    else:
        return sum([(x - average) ** 2 for x in records]) / len(records)


# ==============================================
# 取标准差
# ==============================================

def get_standard_deviation(records):
    """
    标准差 == 均方差 反映一个数据集的离散程度
    """
    variance = get_variance(records)
    return math.sqrt(variance)


# ==============================================
# 取rms（均方根误差）
# ==============================================

def get_rms(records):
    """
    均方根值 反映的是有效值而不是平均值
    """
    if len(records) == 0:
        return 999.0
    else:
        return math.sqrt(sum([x ** 2 for x in records]) / len(records))
