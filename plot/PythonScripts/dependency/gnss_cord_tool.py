# -*- coding: utf-8 -*-
# ===================================================================
# 主要是坐标相关的函数，包含如下功能：
# xyz, blh, enu坐标相互转换
# ===================================================================

#! python3
# coding:utf-8
import math
from math import sqrt
from numpy import *

OMGE = 7.2921151467E-5         # earth angular velocity (IS-GPS) (rad/s)
RE_WGS84 = 6378137.0           # earth semimajor axis (WGS84) (m)
FE_WGS84 = 1.0/298.257223563   # earth flattening (WGS84)
PI = 3.1415926535897932        # pi


def matmul(tr, n, k, m, alpha, A, B, beta):
    C = zeros(n*k)
    if tr[0] == 'N':
        if tr[1] == 'N':
            f = 1
        else:
            f = 2
    else:
        if tr[1] == 'N':
            f = 3
        else:
            f = 4
    for i in range(0, n):
        for j in range(0, k):
            d = 0.0
            if f == 1:
                for x in range(0, m):
                    d += A[i + x * n] * B[x + j * m]
            if f == 2:
                for x in range(0, m):
                    d += A[i + x * n] * B[j + x * k]
            if f == 3:
                for x in range(0, m):
                    d += A[x + i * m] * B[x + j * m]
            if f == 4:
                for x in range(0, m):
                    d += A[x + i * m] * B[j + x * k]
            if (beta == 0.0):
                C[i + j * n] = alpha * d
            else:
                C[i + j * n] = alpha * d + beta * C[i + j * n]
    return C


def ecef2pos(r):
    pos = zeros(3)
    e2 = FE_WGS84 * (2.0 - FE_WGS84)
    r2 = r[0]*r[0]+r[1]*r[1]
    v = RE_WGS84
    z = r[2]
    zk = 0.0
    while (1):
        zk = z
        sinp = z / math.sqrt(r2 + z * z)
        v = RE_WGS84 / math.sqrt(1.0 - e2 * sinp * sinp)
        z = r[2] + v * e2 * sinp
        if math.fabs(z - zk) < 1E-4:
            break
    if r2 > 1E-12:
        pos[0] = math.atan(z / math.sqrt(r2))
        pos[1] = math.atan2(r[1], r[0])
    else:
        if r[2] > 0.0:
            pos[0] = PI / 2.0
        else:
            pos[0] = -PI / 2.0
        pos[1] = 0.0
    pos[2] = sqrt(r2 + z * z) - v
    return pos


##############################################
#(X,Y,Z) to (E,N,U)
##############################################
def xyz2enu(pos):
    E = zeros(9)
    sinp = math.sin(pos[0])
    cosp = math.cos(pos[0])
    sinl = math.sin(pos[1])
    cosl = math.cos(pos[1])
    E[0] = -sinl
    E[3] = cosl
    E[6] = 0.0
    E[1] = -sinp * cosl
    E[4] = -sinp * sinl
    E[7] = cosp
    E[2] = cosp * cosl
    E[5] = cosp * sinl
    E[8] = sinp
    return E

##############################################
#(Earth-Centered, Earth-Fixed) to (E,N,U)
##############################################
def ecef2enu(pos, r):
    E = xyz2enu(pos)
    e = matmul("NN", 3, 1, 3, 1.0, E, r, 0.0)
    return e


