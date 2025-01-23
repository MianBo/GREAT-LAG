# GREAT-LAG: 武汉大学GREAT团队低轨导航增强软件（内测版）

## 概述

&emsp;&emsp;GREAT (GNSS+ REsearch, Application and Teaching) 软件由武汉大学测绘学院设计开发，是一个用于空间大地测量数据处理、精密定位和定轨以及多源融合导航的综合性软件平台。<br />
&emsp;&emsp;GREAT-LAG是GREAT软件中的一个重要模块，主要用于低轨卫星观测值仿真与导航增强。软件中，核心计算模块使用C++语言(C++17)编写，辅助脚本模块使用Python3和C-Shell语言实现自动化数据处理。GREAT-LAG软件使用CMAKE工具进行编译管理，用户可以灵活选择GCC、Clang、MSVC等主流C++编译器。目前软件提供了Windows和Linux平台的命令行应用程序。<br />
&emsp;&emsp;GREAT-LAG由2个可移植程序库组成，分别是LibGREAT和LibGnut。LibGREAT库主要用于低轨卫星观测值仿真与导航增强滤波解算，包括滤波估计中涉及的数据解码、存储以及低轨增强PPP算法的实现，LibGnut库来源于开源GNSS软件G-nut，包括GNSS数据的解码和存储以及基本参数配置模块。<br />
&emsp;&emsp;GREAT-LAG软件在GREAT-PVT基础上进一步扩展了以下功能：
1. 支持低轨星座增强GNSS PPP、低轨星座增强GNSS PPP固定解

2. 支持低轨星座PPP、低轨星座PPP固定解

3. 支持双频无电离层组合、非差非组合低轨卫星观测值组合方式

4. 支持GPS、Galileo、BDS-2/3、LEO四系统原始观测数据仿真(rinex 3.0格式)

5. 支持使用电离层格网数据、对流层格网数据仿真低轨卫星电离层延迟、对流层延迟
   

&emsp;&emsp;此外，软件包还提供定位结果绘图脚本，便于用户对数据进行解算与结果分析。

## 软件包目录结构
```shell
GREAT-LAG_<ver>	
  ./src	                源代码 *
    ./app                  GREAT-PVT、GREAT-SimuObs主程序 *
    ./LibGREAT             PPP、PPP-AR解算库、低轨卫星仿真库 *
    ./LibGnut              Gnut库 *
    ./third-party          第三方库 *
  ./sample_data          算例数据 *
    ./PPPFLT_2021100       产品仿真算例 *
    ./PPPFLT_2023305       模型仿真算例 *
  ./plot                 画图脚本 *
  ./doc                  文档 *
    GREAT_PPP.xml          PPP配置文件模板 *
    GREAT_SimuObs.xml      SIMU配置文件模板 * 
    GREAT-LAG_1.0.pdf      GREAT-LAG用户指南 *
```

## 安装和使用

参见GREAT-LAG_1.0.pdf

## 修改记录
### 版本1.0
1. 增加LEO系统并初步完成低轨增强
2. 完成LEO数据读取功能，新增加rinexc文件输出功能
3. 增加观测值仿真功能
4. 加入对流层、电离层产品读取功能
5. 完成代码注释


## 参与贡献

开发人员：

武汉大学GREAT团队, Wuhan University.

三方库：

* GREAT-LAG使用G-Nut库(http://www.pecny.cz)
  Copyright (C) 2011-2016 GOP - Geodetic Observatory Pecny, RIGTC.
  
* GREAT-LAG使用pugixml库(http://pugixml.org)
Copyright (C) 2006-2014 Arseny Kapoulkine.

* GREAT-LAG使用Newmat库(http://www.robertnz.net/nm_intro.htm)
Copyright (C) 2008: R B Davies.

* GREAT-LAG使用spdlog库(https://github.com/gabime/spdlog)
  Copyright(c) 2015-present, Gabi Melman & spdlog contributors.

* GREAT-LAG使用Eigen库(https://eigen.tuxfamily.org)
  Copyright (C) 2008-2011 Gael Guennebaud

* 脚本工具使用部分FAST源码(https://github.com/ChangChuntao/FAST)
Copyright (C) The GNSS Center, Wuhan University & Chinese Academy of Surveying and mapping.

## 下载地址

GitHub：https://github.com/GREAT-WHU/GREAT-LAG

欢迎加入QQ群(1009827379)参与讨论与交流。

