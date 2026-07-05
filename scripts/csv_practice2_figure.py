# csv文件读取数据绘制折线图
# 完成时间：2026-6-29
# 练习内容：读取csv文件数据并利用matplotlib绘制并美化折线图

import csv
from datetime import datetime
import matplotlib.pyplot as plt

# 1. 先加载样式（会重置全局配置）
plt.style.use('seaborn-v0_8')

# 2. 再配置中文字体（最后生效，不会被样式覆盖）
plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'Heiti TC']
plt.rcParams['axes.unicode_minus'] = False

"""
first_data=datetime.strptime('2018-07-01', '%Y-%m-%d')
  strptime()将包含所需的字符串作为第一个实参，第二个实参告诉Python如何设置日期的格式
  ‘%Y-’让Python将字符串中第一个连字符前面的部分视为四位的年份，(y视为两位的年份，如18)
  ‘%m-’让Python将第二个连字符前面的部分视为表示月份的数
  ‘%d-’让Python将字符串的最后一部分视为月份中的一天
  else:
  '%A':星期几(Monday) '%B':月份名(January) '%H':24小时制的小时数 '%h':12小时制的小时数
  '%p':am或pm '%M':分钟数 '%S':秒数
print(first_data)
"""

# ========== 画布1：7月最高温 ==========
filename1 = r'E:\GIS_Learning\data\sitka_weather_07-2018_simple.csv'
with open(filename1) as f:
    reader = csv.reader(f)
    header_row = next(reader)

    # 提取日期和最高温度
    dates_1, highs_1 = [], []
    for row in reader:
        current_date = datetime.strptime(row[2], '%Y-%m-%d')
        high = int(row[5])
        dates_1.append(current_date)
        highs_1.append(high)

# 创建第一个画布和坐标轴
fig1, ax1 = plt.subplots()
ax1.plot(dates_1, highs_1, color='red')

# 设置第一个画布格式
ax1.set_title("2018年7月每日最高温度", fontsize=24)
ax1.set_xlabel('', fontsize=16)
fig1.autofmt_xdate()
ax1.set_ylabel("温度(F)", fontsize=16)
ax1.tick_params(axis='both', which='major', labelsize=15)


# ========== 画布2：全年最高温和最低温 ==========
filename2 = r'E:\GIS_Learning\data\sitka_weather_2018_simple.csv'
with open(filename2) as f:
    reader = csv.reader(f)
    header_row = next(reader)

    # 提取日期和最高、最低温度
    dates_2, highs_2, lows_2 = [], [], []
    for row in reader:
        current_date = datetime.strptime(row[2], '%Y-%m-%d')
        high = int(row[5])
        low = int(row[6])
        dates_2.append(current_date)
        highs_2.append(high)
        lows_2.append(low)

# 创建第二个画布和坐标轴
fig2, ax2 = plt.subplots()
ax2.plot(dates_2, highs_2, color='red',alpha=0.5)
ax2.plot(dates_2, lows_2, c='blue',alpha=0.5)
# fill_between填充高低温之间区域
ax2.fill_between(dates_2, highs_2, lows_2, facecolor='blue', alpha=0.1)

# 设置第二个画布格式
ax2.set_title("2018年每日最高温度", fontsize=24)
ax2.set_xlabel('', fontsize=16)
fig2.autofmt_xdate()
ax2.set_ylabel("温度(F)", fontsize=16)
ax2.tick_params(axis='both', which='major', labelsize=15)

plt.show()