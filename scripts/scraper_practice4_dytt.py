# 电影天堂2026必看热片下载链接提取
# 完成时间：2026-7-19
# 练习内容：更换字符集修正乱码、在主页面下的多个子页面分支查找有用信息，并设置筛选项获取有用信息

import requests
import re # 内置标准库re可以处理纯文本信息，提取特定信心，但是面对复杂HTML结构不如BeautifulSoup
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                        'Chrome/150.0.0.0 Safari/537.36 Edg/150.0.0.0'}
domain = 'https://www.dytt8989.com/'
response = requests.get(domain) # 可在domain后面+,verify=False （不验证SSL证书）
# print(response.text) 直接打印发现文本内有乱码，观察发现是页面使用gb2312编码，而request默认转成utf—8编码
response.encoding='gb2312' # 指定字符集
# print(response.text)

"""
拿到源代码后需要提取2026必看热片的片源，观察页面源代码发现只能通过’2026必看热片‘相关字符去筛选
obj1 =re.compile(r'2026必看热片',re.S)
.compile():把正则规则提前编译好，存成一个正则对象，便于后面反复用这个规则匹配
re.S:匹配模式修饰符 让.可以匹配换行符\n，实现跨行匹配
观察源代码发现想要的信息有效包含在<ul>/</ul>中,进行代码优化
"""

# 获取ul里的li(具体标准每个网站页面不一样，多去观察源代码获取筛选项)
obj1 = re.compile(r"2026必看热片.*?<ul>(?P<ul>.*?)</ul>", re.S)
obj2 = re.compile(r"<a href='(?P<href>.*?)'", re.S)
obj3 = re.compile(r'◎片　　名(?P<movie>.*?)<br />.*?<td '
                  r'style="WORD-WRAP: break-word" bgcolor="#fdfddf"><a href="(?P<download>.*?)">', re.S)
# .*? 非贪婪匹配，避免吞进不想管的内容  .匹配任意一个字符(配合re.S匹配换行)  *重复0次或多次
# (?P<ul>.*?)命名分组 取的时候可以直接用group('ul')   普通分组(.*?) 取的时候用group(1)、group(2)

resoult1 = obj1.finditer(response.text)
# findall():返回一个列表，里面是所有匹配到的字符串
# finditer()：返回一个迭代器，每个元素是匹配对象（match object）
# findall 如果有分组，只返回分组里的内容，拿不到完整匹配
# finditer 返回的是匹配对象，可以用 .group()、.group('ul') 灵活取值
# 数据量大的时候迭代器更省内存

child_href_list = []

for it in resoult1:
    ul = it.group('ul')

    # 提取子页面链接：
    resoult2 = obj2.finditer(ul)
    for itt in resoult2: # 在’2026必看影片‘页面下点击具体影片会跳转到子页面，所以需要
        # 拼接子页面的url地址：域名 + 子页面地址
        child_href = domain + itt.group('href').strip('/')
        child_href_list.append(child_href) # 把子页面链接保存起来

# 提取子页面内容
for href in child_href_list:
    child_response = requests.get(href, headers=headers)
    child_response.encoding='gb2312'
    resoult3 = obj3.search(child_response.text)
    print(resoult3.group('movie'))
    print(resoult3.group('download'))
    # break 测试用