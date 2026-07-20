# 初识爬虫
# 完成时间：2026-7-16
# 练习内容：学习爬虫基本知识，能看懂HTML文档内容

import requests

# 设计一个字典变量，把爬虫伪装成浏览器,避免418等情况
headers = {"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
"(KHTML, like Gecko) Chrome""/150.0.0.0 Safari/537.36 Edg/150.0.0.0"}
# 浏览器网页-右键“检查”-网络-刷新-点击任意请求-展开请求标头-复制User-Agent：后信息

response = requests.get('https://movie.douban.com/top250', headers=headers)
print(response) # 未加headers时得到htpp状态码：418 （客户端错误）(也可以通过.status_code属性查看)
print(response.text) # 得到浏览器页面html源码

"""
网页三大要素：HTML（定义网页结构和信息）、JavaScript（定义用户和网页的交互逻辑）、CSS（定义网页样式）
爬虫主要是爬取网站数据信息，主要与HTML打交道
eg:(缩进表层级关系)
<!DOCTYPE HTML>
<html>
    <body> 文档主体内容
        <h1>这是一个标题（1级标题）</h1>    数字代表是几级标题，标题文本被起始和闭合文本包围
        <p>这是一段文字</p>    文本也被起始和闭合标签包围，换行需要两行使用p标签（<br>在文本段落中强制换行）   
    <body>
</html>
每个被尖括号包围的都是一个HTML标签，开头的<!DOCTYPE HTML>告知浏览器文件类型是HTML
<html>为起始标签 </html>为闭合标签 这两个标签连同中间的内容可以被看成是一个HTML元素
<html>标签是HTML文档的根，所有的其他元素都要放到这个元素里面（起始标签和闭合标签之间）

<b>&</b>:加粗  <i>&</i>:斜体  <u>&</u>:下划线  <img:src="图片路径":加图片(width设置宽度，height设置高度)
<a href="目标要跳转的URL地址"(target="_self":指定链接页面的打开方式 _self指定在当前窗口打开链接 _blank在新窗口打开)>超链接的名称</a>

<div>&</div> <span>&</span> 都是容器，本身不含内容 一般让其他元素被这两个标签包围，作为子元素，便于重复的命令接收
div是块级元素。独占自己的一块，一行最多一个 span是内联元素，不会独占一块，一行可以有多个span元素
<span style="background-color:red">文本段落</span>  设置文本段落为红色字体

<ol>&</ol>:定义有序列表 列表里每项都是有顺序的，可以用数字依次表示 列表里每项元素用<li>&</li>标签
<ul>&</ul>:定义无序列表 每项元素依旧用<li>&</li>标签

<table (border="1" 默认表格无边框，若想加边框可以加上对应的值)>&</table>:定义表格标签，内部通常嵌套一些和表格相关的元素  
<thead>&</thead>:表示表格头部 <tbody>&</tbody>:表示表格主体
在<thead>&</thead>中间放上 <tr>&</tr>:定义表格行 再在每一行中间放上<td>&</td>:表示一项项数据

(class="content")可以被运用到所有元素上，定义元素的类的名称 类可以帮助我们分组，比如一个网页上可以有多个文本段落，就可以通过
class="content"和class=“review”来区分哪些文本段落是文章，哪些文本段落是用户评论
<!----> 在两个--之间写注释
"""

