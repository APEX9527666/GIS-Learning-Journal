# csv文件基础认识
# 完成时间：2026-6-29
# 练习内容：认识csv文件格式

import csv
filename = r'E:\GIS_Learning\data\sitka_weather_07-2018_simple.csv'
with open(filename) as f:
    reader = csv.reader(f) # 将前面存储的文件对象f作为实参传递给reader
    header_row = next(reader) # 当调用时将返回文件中的下一行
    highs=[]
    for row in reader:
        high=int(row[5])
        highs.append(high)
print(highs)