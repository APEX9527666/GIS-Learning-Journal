# 解析HTML文档
# 完成时间：2026-7-17
# 练习内容：利用BeautifulSoup包解析HTML文档，并根据顽网页情况筛选解析内容

from bs4 import BeautifulSoup
import requests
content = requests.get('https://www.example.com/').text # 发送get请求得到HTML
soup = BeautifulSoup(content, 'html.parser') # 传入至BeautifulSoup的构造函数，'html.parser'指定解析器
# print(soup.p) 打印这个HTML第一个<p>元素 若p里还有其他标签，则把第一个p标签连带里面所有内容都一并返回 （其他元素同理）

# 在浏览器网页"检查"以确定所需数据的元素信息

all_prices = soup.findAll('p', attrs={'class': 'price_color'})
# findAll(a,b)能根据标签、属性等找出所有符合要求的元素
# a： 传入p，表示找p标签
# b： 可选参数attrs={想找的属性:对应的值}

# 循环依次返回各个对象
for price in all_prices:
    print(price.string) # string会把标签包围的文字返回给我们，从而忽略繁杂的HTML标签信息 可通过切片操作进一步修改

# 打印书名标题

# 法一
all_titles = soup.findAll('h3')
for title in all_titles:
    all_links = title.findAll('a')
    for link in all_links:
        print(link.string)

# 法二
all_titles = soup.findAll('h3')
for title in all_titles:
    link = title.find('a') # 当前网页所有h3里面只有一个a元素，所以可用.find找第一个a元素
    # 此处返回的并不是可迭代对象 而直接是第一个对象 故不用第二次循环
    print(link.string)