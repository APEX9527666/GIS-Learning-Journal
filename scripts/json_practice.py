# JSON格式文件制作全球地震散点图
# 完成时间：2026-6-30
# 练习内容：利用Python处理JSON格式的文件，提取数据以后利用plotly绘图

import json
import plotly.express as px
import pandas as pd


# 探索数据的结构
filename=r'E:\GIS_Learning\data\eq_data_1_day_m1.json'
with open(filename) as f: # 以只读模式打开，with会在代码结束后自动关闭文件
    all_eq_data = json.load(f) # .load()将数据转换为Python能处理的格式

readable_file=r'E:\GIS_Learning\data\readable_eq_data.json' # 创建一个文件以便将这些数据以易于阅读的方式写入其中
with open(readable_file, 'w') as f: # 以写入模式打开文件，若文件不存在则自动创建，若已存在则覆盖原内容
    json.dump(all_eq_data, f,indent=4) # json.dump()接收一个JSON数据对象和一个文件对象，
    # 并将数据写入这个文件当中，indent=4让dump()使用与数据结构匹配的缩进量来设置数据格式

all_eq_dicts=all_eq_data['features'] # 创建所有地震条目的字典集合
# GeoJSON 规范中，features是一个列表，列表里的每个元素都是单次地震的完整字典数据（包含属性、坐标等信息）

mags,titles,lons,lats=[],[],[],[] # 创建空列表以存储地震震级、地震位置描述标题、经度、纬度
for eq_dict in all_eq_dicts: #  遍历列表，并把单条地震的字典赋值
    mag=eq_dict['properties']['mag'] # 先取字典，再取键，然后赋值
    title=eq_dict['properties']['title']
    lon=eq_dict['geometry']['coordinates'][0]
    lat=eq_dict['geometry']['coordinates'][1]
    mags.append(mag) # 调用.append()把提取的内容分别添加到对应的列表末尾
    titles.append(title)
    lons.append(lon)
    lats.append(lat)

# pd.DataFrame()：创建 Pandas 的二维表格对象（DataFrame），是后续绘图的数据源
# zip()函数会把 4 个列表按位置一一打包，生成一个个元组（例如(经度1, 纬度1, 位置1, 震级1)），每一个元组对应表格的一行
# 最后指定表格的列名，顺序必须和zip里的列表顺序一一对应。
data = pd.DataFrame(data=zip(lons, lats, titles, mags), columns=['经度', '纬度', '位置', '震级'])

fig = px.scatter(
    data, # 指定绘图数据源，即刚才创建的DataFrame
    x='经度',
    y='纬度',
    range_x=[-200, 200],
    range_y=[-90, 90],
    width=800,
    height=800,
    title='全球地震散点图',
    size='震级', # 散点的大小由 “震级” 列决定，震级越大，散点面积越大
    size_max=10, # 限制散点的最大尺寸为 10 像素，避免大地震的点过大导致重叠遮挡
    color='震级', # 散点的颜色根据 “震级” 数值做颜色渐变映射，震级越高颜色越深 / 越醒目，直观区分震级大小
    hover_name='位置', # 鼠标悬停在散点上时，最顶部显示的主信息是地震位置文本
)
fig.write_html('global_earthquakes.html') # 将可视图保存为html文件
# HTML 文件保留全部交互功能，可以直接用浏览器打开，无需依赖 Python 环境
fig.show() # 在当前运行环境中渲染并显示图表
# 如果在 Jupyter Notebook 中运行，会直接在单元格下方展示交互式图表
# 如果在普通 Python 脚本中运行，会自动调用默认浏览器打开图表

if __name__ == '__main__': # 当直接运行这个脚本文件时，__name__变量的值会自动变为'__main__'，下方的代码会执行
    # 当这个脚本被其他文件import作为模块使用时，__name__是文件名，下方代码不会执行
    print(mags[:5])
    print(title[:5])
    print(lons[:5])
    print(lats[:5])







