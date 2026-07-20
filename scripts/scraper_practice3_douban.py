# 爬虫爬取豆瓣电影前250部
# 完成时间：2026-7-18
# 练习内容：写一个爬虫来获取豆瓣电影前250部电影名字，过滤其他无关信息

import requests
from bs4 import BeautifulSoup
headers = {"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
"(KHTML, like Gecko) Chrome""/150.0.0.0 Safari/537.36 Edg/150.0.0.0"}
"""
response = requests.get("https://movie.douban.com/top250", headers=headers)
html = response.text
Soup = BeautifulSoup(html, "html.parser")

# 通过检查网页可知所有标题都是一个span元素，并且close值都是title
all_title=Soup.find_all("span",attrs={'class':"title"})
for title in all_title:
    title_string=title.string # 此时发现除了我们想要的中文标题还有 /原版标题
    if '/' not in title_string: # 忽略原版标题
        print(title_string)
# 此时发现我们想要的是前250值，但是只提取到了第一页也就是前25的值，在浏览器中切换至第二页发现链接中多了‘？start=25’
# 切换至第三页发现‘？start=50’ 所以需要重新设计循环
"""

for start_num in range(0,250,25):
    response = requests.get(f"https://movie.douban.com/top250?start={start_num}", headers=headers) # 更新链接
    html = response.text
    Soup = BeautifulSoup(html, "html.parser")
    all_title = Soup.find_all("span", attrs={"class": "title"})
    for title in all_title:
        title_string = title.string  # 此时发现除了我们想要的中文标题还有 /原版标题
        if '/' not in title_string:  # 忽略原版标题
            print(title_string)