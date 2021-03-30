---
title: "CS:APP 笔记"
date: 2021-03-27T10:31:24+08:00
lastmod: 2021-03-27T10:31:24+08:00
draft: false
keywords: []
description: ""
tags: ["技术", "CS:APP"]
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
mathjax: true
mathjaxEnableSingleDollar: true
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

<!--more-->
### c语言相关
* printf() 控制符
  | 控制符        | 含义         |
  | :------------| :-------------|
  | %d | 十进制整型 | 
  | %ld | 输出长整型数据 | 
  | %x | 十六进制整型 | 
  | %u | 无符号整型 | 
  | %c | 一个字符 | 
  | %s | 用来输出字符串 | 
  | %f | 实数，包括单精度和双精度，以小数形式输出。不指定字段宽度，由系统自动指定，整数部分全部输出，小数部分输出 6 位，超过 6 位的四舍五入 | 
  | %.mf | 输出实数时小数点后保留 m 位 | 
  
### Linux相关
* 查看用户名
  `whoami`
* VirtualBox建立了ubuntu系统，设置好共享文件夹之后，在ubuntu中显示没有权限打开文件夹，需要将用户添加到vboxsf组  
  `sudo adduser [username] vboxsf`
* 运行make btest时出错：*bits/libc-header-start.h: No such file or directory*  
  `sudo apt install gcc-multilib`
### 英文单词对照 
* Unary integer operations 一元整数操作
  * 指的是一个操作数的整数操作，例如 **! ~** 
* Binary integer operations 二元整数操作
  * 指的是两个操作数的整数操作，例如 **& ^ | + << >>** 
***
持续更新中...
