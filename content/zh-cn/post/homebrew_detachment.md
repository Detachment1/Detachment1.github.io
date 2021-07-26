+++
date = 2021-06-19T10:58:00+08:00
title = "Homebrew 语句"
description = "Record some homebrew words"
slug = ""
authors = ["Detachment"]
tags = ["技术"]
categories = ["笔记"]
externalLink = ""
series = []
+++
* 安装 Homebrew
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
* 添加到环境变量的路径

```bash
/opt/homebrew/bin
```

* 替换中科大镜像源
```bash
cd "$(brew --repo)"
git remote set-url origin https://mirrors.ustc.edu.cn/brew.git
```
* 修改为默认源
```bash
cd "$(brew --repo)"
git remote set-url origin https://github.com/Homebrew/brew.git
```