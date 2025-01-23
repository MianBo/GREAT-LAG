# =================================================================
# RTK画图主程序
# =================================================================
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from dependency.gnss_cord_tool import ecef2pos, ecef2enu
from dependency.gnss_math_tool import get_rms

# 文件路径
calc_result_file = r'../data_rtk/SEPT-RTK.flt'
true_value_file = r'../data_rtk/TC_CombinedtoGNSS.txt'

# 指定要读取的列
calc_cols_to_use = [0, 1, 2, 3]  # 对应 second, X-ECEF, Y-ECEF, Z-ECEF
true_cols_to_use = [1, 2, 3, 4]  # 对应 second, X-ECEF, Y-ECEF, Z-ECEF

# 定义列名
calc_column_names = ['second', 'X-ECEF_calc', 'Y-ECEF_calc', 'Z-ECEF_calc']
true_column_names = ['second', 'X-ECEF_true', 'Y-ECEF_true', 'Z-ECEF_true']

# 读取数据
calc_data = pd.read_csv(calc_result_file, delim_whitespace=True, usecols=calc_cols_to_use, names=calc_column_names, comment='#')
true_data = pd.read_csv(true_value_file, delim_whitespace=True, usecols=true_cols_to_use, names=true_column_names, comment='#')

# 将所有列转换为浮点数
calc_data = calc_data.astype(float)
true_data = true_data.astype(float)

# 合并两个数据集，基于 GPS Seconds 来匹配
merged_data = pd.merge(calc_data, true_data[['second', 'X-ECEF_true', 'Y-ECEF_true', 'Z-ECEF_true']], 
                       on='second')

# 计算XYZ差值
merged_data['X_diff'] = merged_data['X-ECEF_calc'] - merged_data['X-ECEF_true']
merged_data['Y_diff'] = merged_data['Y-ECEF_calc'] - merged_data['Y-ECEF_true']
merged_data['Z_diff'] = merged_data['Z-ECEF_calc'] - merged_data['Z-ECEF_true']

# 转换为List类型方便画图
merged_data['diff_list'] = merged_data.apply(lambda row: [row['X_diff'], row['Y_diff'], row['Z_diff']], axis=1)
diff_list = merged_data['diff_list'].tolist()

merged_data['true_xyz'] = merged_data.apply(lambda row: [row['X-ECEF_true'], row['Y-ECEF_true'], row['Z-ECEF_true']], axis=1)
true_list = merged_data['true_xyz'].tolist()

t_series=merged_data['second'].tolist()

# 计算ENU
enu_list=[]
for i in range(len(diff_list)):
    pos=ecef2pos(true_list[i])
    enu=ecef2enu(pos,diff_list[i])
    enu_list.append(enu)


# 假设 enu_list 是一个包含 ENU 数据的数组
enu_list_array = np.array(enu_list)  # 确保数据是 NumPy 数组格式

# 分别提取 E, N, U 方向的数组
E_values = enu_list_array[:, 0]
N_values = enu_list_array[:, 1]
U_values = enu_list_array[:, 2]

# 计算 E, N, U 方向的 RMS
RMS_E=get_rms(E_values)
RMS_N=get_rms(N_values)
RMS_U=get_rms(U_values)

plt.figure(figsize=(12, 6))  # Adjust the width and height

# 绘制三个散点图在同一张图上
plt.scatter(t_series, E_values, c='r', label='East', marker='o', s=10)
plt.scatter(t_series, N_values, c='g', label='North', marker='o', s=10)
plt.scatter(t_series, U_values, c='b', label='Up', marker='o', s=10)

# 设置图例
# plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.0), ncol=3, frameon=True)
plt.legend(bbox_to_anchor=(0.65, 0.99),    # 0.65,0.99
           loc='upper right',
           # prop=bd.fonts['ticks'],
           ncol=3,
           frameon=False,
           facecolor='none',
           numpoints=5,
           markerscale=3,
           fontsize=16,
           handlelength=1)


# 设置Y轴的范围
plt.ylim([-1, 1])

# 设置标题和轴标签
plt.title('RTK ENU Position Error', fontsize=20, fontweight='bold')
plt.xlabel('GPS Time(s)', fontsize=20, fontweight='bold')
plt.ylabel('Position error(m)', fontsize=20, fontweight='bold')
plt.xticks(size=14)
plt.yticks(size=14)


# 标注RMS
rms_text = f'RMS:({RMS_E:.4f},{RMS_N:.4f},{RMS_U:.4f})m'
plt.figtext(0.13, 0.125, rms_text, ha='left', fontsize=16)

# 显示图像
plt.show()
