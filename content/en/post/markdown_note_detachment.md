+++ 
draft = false
date = 2021-03-23T17:02:46+08:00
title = "Markdown Note"
description = "Record some markdown syntax"
authors = ["Detachment"]
tags = ["tech"]
categories = ["note"]
externalLink = ""
series = []
+++
## Basic Syntax
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

## Table
```
| Left         | Right         |
| :------------| :-------------|
| Left Content | Right Content |
```
| Left         | Right         |
| :------------| :-------------|
| Left Content | Right Content |

## Block
~~~
> this is a block 
>> this is a subblock
~~~
> this is a block
>> this is a subblock

## Task List
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

## Image
```
![GitHub Logo](../../../images/try.png)
```

![GitHub Logo](../../../images/try.png)

## Code Hilight (github pages style)
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