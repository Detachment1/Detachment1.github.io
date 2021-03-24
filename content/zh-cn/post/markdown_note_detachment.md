+++
date = 2021-03-23T17:01:50+08:00
title = "Markdown 笔记"
description = "Record some markdown syntax"
slug = ""
authors = ["Detachment"]
tags = ["技术"]
categories = ["笔记"]
externalLink = ""
series = []
+++
## 基础语法
| Markdown | output |
| :-------- | :-----|
| # Heading level 1 |<h1>Heading level 1</h1>|
| # Heading level 2 |<h2>Heading level 2</h2>|
| # Heading level 3 |<h3>Heading level 3</h3>|
| # Heading level 4 |<h4>Heading level 4</h4>|
| # Heading level 5 |<h5>Heading level 5</h5>|
| # Heading level 6 |<h6>Heading level 6</h6>|
| # Heading level 7 |<h7>Heading level 7</h7>|
| I just love \*\*bold text\*\*. |I just love **bold text**.|
| Italicized text is the \*cat's meow\*. | Italicized text is the *cat's meow*. |
| \[GitHub Account](https://github.com/Detachment1 "My GitHub Account") | [My GitHub Account](https://github.com/Detachment1 "My GitHub Account") |

## 表格
```
| Left         | Right         |
| :------------| :-------------|
| Left Content | Right Content |
```
| Left         | Right         |
| :------------| :-------------|
| Left Content | Right Content |

## 块
~~~
> this is a block 
>> this is a subblock
~~~
> this is a block
>> this is a subblock

## 任务列表
~~~
- [x] @mentions, #refs, [links](), **formatting**, and <del>tags</del> supported
- [x] list syntax required (any unordered or ordered list supported)
- [x] this is a complete item
- [ ] this is an incomplete item
~~~
- [x] @mentions, #refs, [links](), **formatting**, and <del>tags</del> supported
- [x] list syntax required (any unordered or ordered list supported)
- [x] this is a complete item
- [ ] this is an incomplete item

## 图片
```
![GitHub Logo](../../../images/try.png)
```

![GitHub Logo](../../../images/try.png)

## 代码高亮 (github pages 风格)
```
```javascript
function fancyAlert(arg) {
  if(arg) {
    $.facebox({div:'#foo'})
  }
}
```
```javascript
function fancyAlert(arg) {
  if(arg) {
    $.facebox({div:'#foo'})
  }
}
```

