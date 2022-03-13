---
title: "Java笔记"
date: 2022-03-13T20:25:52+08:00
lastmod: 2022-03-13T20:25:52+08:00
draft: false
keywords: ["Java"]
description: ""
tags: ["技术", "Java"]
categories: ["笔记"]
author: "Detachment"

# You can also close(false) or open(true) something for this content.
# P.S. comment can only be closed
comment: false
toc: false
autoCollapseToc: false
postMetaInFooter: false
hiddenFromHomePage: false
# You can also define another contentCopyright. e.g. contentCopyright: "This is another copyright."
contentCopyright: false
reward: false
mathjax: false
mathjaxEnableSingleDollar: false
mathjaxEnableAutoNumber: false

# You unlisted posts you might want not want the header or footer to show
hideHeaderAndFooter: false

# You can enable or disable out-of-date content warning for individual post.
# Comment this out to use the global config.
#enableOutdatedInfoWarning: false

flowchartDiagrams:
  enable: false
  options: ""

sequenceDiagrams: 
  enable: false
  options: ""

---
# Java 基础
## @overide
1. @overide 可以当注释用,方便阅读 
2. 编译器可以验证@Override下面的方法名是否是父类中所有的,如果没有则报错（如果没写@Override而下面的方法名又写错了，这时编译器是可以通过的，因为它以为这个方法是子类中自己增加的方法）
## 字符串
[String str=new String("a")和String str = "a"有什么区别 - 知乎](https://zhuanlan.zhihu.com/p/86521846)

