---
title: "炸弹实验笔记"
date: 2021-04-05T14:48:02+08:00
lastmod: 2021-04-05T14:48:02+08:00
draft: false
keywords: ["CS:APP"]
description: ""
tags: ["技术", "CS:APP", "CS:APP炸弹实验"]
categories: ["笔记"]
author: ""

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
## 实验网站
* http://csapp.cs.cmu.edu/3e/labs.html
* 下载Self-Study Handout
## 实验准备
* ### 实验要求
压缩包中包含两个文件：bomb 和 cbomb.c  
bomb文件为可执行文件，cbomb.c文件为main函数部分的c语言文件，其余函数文件未给出  
运行bomb文件后，依次输入六个字符串，需要通过反编译bomb文件猜测正确的六个字符串，若有字符串不符合要求则炸弹会“爆炸”
* ### 调试相关命令行操作
>`./bomb`运行bomb  
`objdump -d bomb > bomb.s` 反编译可执行文件并保存在bomb.s文件中  
`gdb bomb` gdb调试bomb文件  
`break * 0x12345` 在0x12345位置出添加断点  
`delete 1` 删除断点1  
`layout regs` 显示寄存器界面  
`run` 运行  
`stepi` 执行一条指令  
`print /x *(long *) 0x345678` 以十六进制方式输出0x345678位置的8字节长度数字  
`print /x $rax` 以十六进制方式输出%rax寄存器的内容  
`finish` 运行到当前函数返回  
`kill` 停止程序（未退出调试，可重新run）  
`quit` 退出调试  
## 实验分析
* ### 第一个字符串  
```x86asm
0000000000400ee0 <phase_1>:
  400ee0:	48 83 ec 08          	sub    $0x8,%rsp
  400ee4:	be 00 24 40 00       	mov    $0x402400,%esi
  400ee9:	e8 4a 04 00 00       	callq  401338 <strings_not_equal>
  400eee:	85 c0                	test   %eax,%eax
  400ef0:	74 05                	je     400ef7 <phase_1+0x17>
  400ef2:	e8 43 05 00 00       	callq  40143a <explode_bomb>
  400ef7:	48 83 c4 08          	add    $0x8,%rsp
  400efb:	c3                   	retq 
```
`callq  401338 <strings_not_equal>` 调用函数比较两个字符串是否相等，相等则`%eax`为0  
`strings_not_equal`函数：
```x86asm
0000000000401338 <strings_not_equal>:
  401338:	41 54                	push   %r12
  40133a:	55                   	push   %rbp
  40133b:	53                   	push   %rbx
  40133c:	48 89 fb             	mov    %rdi,%rbx
  40133f:	48 89 f5             	mov    %rsi,%rbp
  401342:	e8 d4 ff ff ff       	callq  40131b <string_length>
  401347:	41 89 c4             	mov    %eax,%r12d
  40134a:	48 89 ef             	mov    %rbp,%rdi
  40134d:	e8 c9 ff ff ff       	callq  40131b <string_length>
  401352:	ba 01 00 00 00       	mov    $0x1,%edx
  401357:	41 39 c4             	cmp    %eax,%r12d
  40135a:	75 3f                	jne    40139b <strings_not_equal+0x63>
  40135c:	0f b6 03             	movzbl (%rbx),%eax
  40135f:	84 c0                	test   %al,%al
  401361:	74 25                	je     401388 <strings_not_equal+0x50>
  401363:	3a 45 00             	cmp    0x0(%rbp),%al
  401366:	74 0a                	je     401372 <strings_not_equal+0x3a>
  401368:	eb 25                	jmp    40138f <strings_not_equal+0x57>
  40136a:	3a 45 00             	cmp    0x0(%rbp),%al
  40136d:	0f 1f 00             	nopl   (%rax)
  401370:	75 24                	jne    401396 <strings_not_equal+0x5e>
  401372:	48 83 c3 01          	add    $0x1,%rbx
  401376:	48 83 c5 01          	add    $0x1,%rbp
  40137a:	0f b6 03             	movzbl (%rbx),%eax
  40137d:	84 c0                	test   %al,%al
  40137f:	75 e9                	jne    40136a <strings_not_equal+0x32>
  401381:	ba 00 00 00 00       	mov    $0x0,%edx
  401386:	eb 13                	jmp    40139b <strings_not_equal+0x63>
  401388:	ba 00 00 00 00       	mov    $0x0,%edx
  40138d:	eb 0c                	jmp    40139b <strings_not_equal+0x63>
  40138f:	ba 01 00 00 00       	mov    $0x1,%edx
  401394:	eb 05                	jmp    40139b <strings_not_equal+0x63>
  401396:	ba 01 00 00 00       	mov    $0x1,%edx
  40139b:	89 d0                	mov    %edx,%eax
  40139d:	5b                   	pop    %rbx
  40139e:	5d                   	pop    %rbp
  40139f:	41 5c                	pop    %r12
  4013a1:	c3                   	retq   
```
```x86asm
401338:	41 54                	push   %r12
40133a:	55                   	push   %rbp
40133b:	53                   	push   %rbx
40133c:	48 89 fb             	mov    %rdi,%rbx
40133f:	48 89 f5             	mov    %rsi,%rbp
401342:	e8 d4 ff ff ff       	callq  40131b <string_length>
401347:	41 89 c4             	mov    %eax,%r12d
40134a:	48 89 ef             	mov    %rbp,%rdi
40134d:	e8 c9 ff ff ff       	callq  40131b <string_length>
401352:	ba 01 00 00 00       	mov    $0x1,%edx
401357:	41 39 c4             	cmp    %eax,%r12d
40135a:	75 3f                	jne    40139b <strings_not_equal+0x63>
```
以上代码比较两个字符串长度是否相等  
```x86asm
40135c:	0f b6 03             	movzbl (%rbx),%eax
40135f:	84 c0                	test   %al,%al
401361:	74 25                	je     401388 <strings_not_equal+0x50>
401363:	3a 45 00             	cmp    0x0(%rbp),%al
401366:	74 0a                	je     401372 <strings_not_equal+0x3a>
401368:	eb 25                	jmp    40138f <strings_not_equal+0x57>
40136a:	3a 45 00             	cmp    0x0(%rbp),%al
40136d:	0f 1f 00             	nopl   (%rax)
401370:	75 24                	jne    401396 <strings_not_equal+0x5e>
401372:	48 83 c3 01          	add    $0x1,%rbx
401376:	48 83 c5 01          	add    $0x1,%rbp
40137a:	0f b6 03             	movzbl (%rbx),%eax
40137d:	84 c0                	test   %al,%al
40137f:	75 e9                	jne    40136a <strings_not_equal+0x32>
```
以上代码依次比较两个字符串各个位是否相同，从这一段代码可以看到，用于比较的两个字符串地址分别存储在`%rbx`和`%rbp`  
在`strings_not_equal`函数开头：
```x86asm
40133c:	48 89 fb             	mov    %rdi,%rbx
40133f:	48 89 f5             	mov    %rsi,%rbp
```
可以看到这两个字符串地址分别从`%rdi`和`%rsi`传递到`strings_not_equal`中  
从`phase_1`函数中可以看到，`%rdi`中保存的是用户输入的字符串地址，`%rsi`中保存的是`0x402400`，输出`0x402400`位置保存的字符串即为第一个需要输入的字符串。
* ### 第二个字符串
```x86asm
0000000000400efc <phase_2>:
  400efc:	55                   	push   %rbp
  400efd:	53                   	push   %rbx
  400efe:	48 83 ec 28          	sub    $0x28,%rsp
  400f02:	48 89 e6             	mov    %rsp,%rsi
  400f05:	e8 52 05 00 00       	callq  40145c <read_six_numbers>
  400f0a:	83 3c 24 01          	cmpl   $0x1,(%rsp)
  400f0e:	74 20                	je     400f30 <phase_2+0x34>
  400f10:	e8 25 05 00 00       	callq  40143a <explode_bomb>
  400f15:	eb 19                	jmp    400f30 <phase_2+0x34>
  400f17:	8b 43 fc             	mov    -0x4(%rbx),%eax
  400f1a:	01 c0                	add    %eax,%eax
  400f1c:	39 03                	cmp    %eax,(%rbx)
  400f1e:	74 05                	je     400f25 <phase_2+0x29>
  400f20:	e8 15 05 00 00       	callq  40143a <explode_bomb>
  400f25:	48 83 c3 04          	add    $0x4,%rbx
  400f29:	48 39 eb             	cmp    %rbp,%rbx
  400f2c:	75 e9                	jne    400f17 <phase_2+0x1b>
  400f2e:	eb 0c                	jmp    400f3c <phase_2+0x40>
  400f30:	48 8d 5c 24 04       	lea    0x4(%rsp),%rbx
  400f35:	48 8d 6c 24 18       	lea    0x18(%rsp),%rbp
  400f3a:	eb db                	jmp    400f17 <phase_2+0x1b>
  400f3c:	48 83 c4 28          	add    $0x28,%rsp
  400f40:	5b                   	pop    %rbx
  400f41:	5d                   	pop    %rbp
  400f42:	c3                   	retq   
```
调用`read_six_numbers`函数，该函数将输入的字符串转化为数字，如果输入字符串小于6或者输入字符串不是数字，均会“爆炸”。通过gdb调试可以发现转化后的数字会保存在栈上，栈顶为最后一个字符。  
`400f0a:	83 3c 24 01          	cmpl   $0x1,(%rsp)`说明第一个字符为1  
后面的部分依次比较后一个数字是否等于前一个数字的二倍，若不相等则“爆炸”
* ### 第三个字符串
```x86asm
0000000000400f43 <phase_3>:
  400f43:	48 83 ec 18          	sub    $0x18,%rsp
  400f47:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  400f4c:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  400f51:	be cf 25 40 00       	mov    $0x4025cf,%esi
  400f56:	b8 00 00 00 00       	mov    $0x0,%eax
  400f5b:	e8 90 fc ff ff       	callq  400bf0 <__isoc99_sscanf@plt>
  400f60:	83 f8 01             	cmp    $0x1,%eax
  400f63:	7f 05                	jg     400f6a <phase_3+0x27>
  400f65:	e8 d0 04 00 00       	callq  40143a <explode_bomb>
  400f6a:	83 7c 24 08 07       	cmpl   $0x7,0x8(%rsp)
  400f6f:	77 3c                	ja     400fad <phase_3+0x6a>
  400f71:	8b 44 24 08          	mov    0x8(%rsp),%eax
  400f75:	ff 24 c5 70 24 40 00 	jmpq   *0x402470(,%rax,8)
  400f7c:	b8 cf 00 00 00       	mov    $0xcf,%eax
  400f81:	eb 3b                	jmp    400fbe <phase_3+0x7b>
  400f83:	b8 c3 02 00 00       	mov    $0x2c3,%eax
  400f88:	eb 34                	jmp    400fbe <phase_3+0x7b>
  400f8a:	b8 00 01 00 00       	mov    $0x100,%eax
  400f8f:	eb 2d                	jmp    400fbe <phase_3+0x7b>
  400f91:	b8 85 01 00 00       	mov    $0x185,%eax
  400f96:	eb 26                	jmp    400fbe <phase_3+0x7b>
  400f98:	b8 ce 00 00 00       	mov    $0xce,%eax
  400f9d:	eb 1f                	jmp    400fbe <phase_3+0x7b>
  400f9f:	b8 aa 02 00 00       	mov    $0x2aa,%eax
  400fa4:	eb 18                	jmp    400fbe <phase_3+0x7b>
  400fa6:	b8 47 01 00 00       	mov    $0x147,%eax
  400fab:	eb 11                	jmp    400fbe <phase_3+0x7b>
  400fad:	e8 88 04 00 00       	callq  40143a <explode_bomb>
  400fb2:	b8 00 00 00 00       	mov    $0x0,%eax
  400fb7:	eb 05                	jmp    400fbe <phase_3+0x7b>
  400fb9:	b8 37 01 00 00       	mov    $0x137,%eax
  400fbe:	3b 44 24 0c          	cmp    0xc(%rsp),%eax
  400fc2:	74 05                	je     400fc9 <phase_3+0x86>
  400fc4:	e8 71 04 00 00       	callq  40143a <explode_bomb>
  400fc9:	48 83 c4 18          	add    $0x18,%rsp
  400fcd:	c3                   	retq   
```
`callq  400bf0 <__isoc99_sscanf@plt>`调用scanf函数，匹配成功的数量返回在`%eax`中
```x86asm
400f60:	83 f8 01             	cmp    $0x1,%eax
400f63:	7f 05                	jg     400f6a <phase_3+0x27>
400f65:	e8 d0 04 00 00       	callq  40143a <explode_bomb>
```
从上面代码可以看到，匹配成功数量应该大于1，因此最少输入两个字符串，通过 gdb调试可以得到应该输入至少两个整数字符，且`0x8(%rsp)`和`0xc(%rsp)`分别保存这第一个数和第二个数  
后面的代码首先要求第一个数小于等于7，然后根据第一个输入的数的值跳到对应分支，给`%eax`赋给相应的值，最后将`0xc(%rsp)`和`%eax`比较，如果不相等则“爆炸”，因此，有多个数字对满足要求：
| 第一个数 | 第二个数（十进制）|第二个数（十六进制）|
| :-------| :----------------| :----------------|
| 0       | 207              | 0xcf               |
| 1       | 311              | 0x137              |
| 2       | 707              | 0x2c3              |
| 3       | 256              | 0x100              |
| 4       | 389              | 0x185              |
| 5       | 206              | 0xce               |
| 6       | 682              | 0x2aa              |
| 7       | 327              | 0x147              |
* ### 第四个字符串
```x86asm
000000000040100c <phase_4>:
  40100c:	48 83 ec 18          	sub    $0x18,%rsp
  401010:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  401015:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  40101a:	be cf 25 40 00       	mov    $0x4025cf,%esi
  40101f:	b8 00 00 00 00       	mov    $0x0,%eax
  401024:	e8 c7 fb ff ff       	callq  400bf0 <__isoc99_sscanf@plt>
  401029:	83 f8 02             	cmp    $0x2,%eax
  40102c:	75 07                	jne    401035 <phase_4+0x29>
  40102e:	83 7c 24 08 0e       	cmpl   $0xe,0x8(%rsp)
  401033:	76 05                	jbe    40103a <phase_4+0x2e>
  401035:	e8 00 04 00 00       	callq  40143a <explode_bomb>
  40103a:	ba 0e 00 00 00       	mov    $0xe,%edx
  40103f:	be 00 00 00 00       	mov    $0x0,%esi
  401044:	8b 7c 24 08          	mov    0x8(%rsp),%edi
  401048:	e8 81 ff ff ff       	callq  400fce <func4>
  40104d:	85 c0                	test   %eax,%eax
  40104f:	75 07                	jne    401058 <phase_4+0x4c>
  401051:	83 7c 24 0c 00       	cmpl   $0x0,0xc(%rsp)
  401056:	74 05                	je     40105d <phase_4+0x51>
  401058:	e8 dd 03 00 00       	callq  40143a <explode_bomb>
  40105d:	48 83 c4 18          	add    $0x18,%rsp
  401061:	c3                   	retq 
```
```x86asm
401024:	e8 c7 fb ff ff       	callq  400bf0 <__isoc99_sscanf@plt>
401029:	83 f8 02             	cmp    $0x2,%eax
```
从上面的代码可以看到要求输入字符串为两个
```x86asm
40102e:	83 7c 24 08 0e       	cmpl   $0xe,0x8(%rsp)
401033:	76 05                	jbe    40103a <phase_4+0x2e>
```
从上面的代码可以看出，第一个数字要求小于等于14  
`callq  400fce <func4>`调用函数`func4`
```x86asm
0000000000400fce <func4>:
  400fce:	48 83 ec 08          	sub    $0x8,%rsp
  400fd2:	89 d0                	mov    %edx,%eax
  400fd4:	29 f0                	sub    %esi,%eax
  400fd6:	89 c1                	mov    %eax,%ecx
  400fd8:	c1 e9 1f             	shr    $0x1f,%ecx
  400fdb:	01 c8                	add    %ecx,%eax
  400fdd:	d1 f8                	sar    %eax 
  400fdf:	8d 0c 30             	lea    (%rax,%rsi,1),%ecx
  400fe2:	39 f9                	cmp    %edi,%ecx
  400fe4:	7e 0c                	jle    400ff2 <func4+0x24>
  400fe6:	8d 51 ff             	lea    -0x1(%rcx),%edx
  400fe9:	e8 e0 ff ff ff       	callq  400fce <func4>
  400fee:	01 c0                	add    %eax,%eax
  400ff0:	eb 15                	jmp    401007 <func4+0x39>
  400ff2:	b8 00 00 00 00       	mov    $0x0,%eax
  400ff7:	39 f9                	cmp    %edi,%ecx
  400ff9:	7d 0c                	jge    401007 <func4+0x39>
  400ffb:	8d 71 01             	lea    0x1(%rcx),%esi
  400ffe:	e8 cb ff ff ff       	callq  400fce <func4>
  401003:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  401007:	48 83 c4 08          	add    $0x8,%rsp
  40100b:	c3                   	retq  
```
```x86asm
40104d:	85 c0                	test   %eax,%eax
40104f:	75 07                	jne    401058 <phase_4+0x4c>
```
从上面的代码可以得出，fun4返回值保存在`%eax`中，且要求返回值为0，否则会“爆炸”  

将`func4`翻译为c语言：
```c
int func4(int ax, int si, int edi)
{
    //初始值：
    //dx=14, si=0, edi=第一个数
    ax = ax - si;
    ax = ax + (ax >> 31);
    ax = ax >> 1;
    int cx = ax + si;
    if (cx <= edi)
    {
        ax = 0;
        if (cx >= edi)
        {
            return ax;
        }
        else
        {
            si = cx + 1;
            return 2 * func4(ax, si, edi) + 1;
        }
    }
    else
    {
        ax = cx - 1;
        return 2 * func4(ax, si, edi);
    }
}
```
从以上代码中可以看到有三个返回分支：  
`return 2 * func4(ax, si, edi) + 1;`无法返回0  
`return ax;`必定返回0  
因此如果要求`func4`返回0，则在递归过程中，递归数的叶节点为`return ax;`且不经过`return 2 * func4(ax, si, edi) + 1;`分支
因此第一个数可以是7，3，1，0
```x86asm
401051:	83 7c 24 0c 00       	cmpl   $0x0,0xc(%rsp)
401056:	74 05                	je     40105d <phase_4+0x51>
401058:	e8 dd 03 00 00       	callq  40143a <explode_bomb>
```
从上面代码可以看到，第二个数应该为0
* ### 第五个字符串
```x86asm
0000000000401062 <phase_5>:
  401062:	53                   	push   %rbx
  401063:	48 83 ec 20          	sub    $0x20,%rsp
  401067:	48 89 fb             	mov    %rdi,%rbx
  40106a:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401071:	00 00 
  401073:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  401078:	31 c0                	xor    %eax,%eax
  40107a:	e8 9c 02 00 00       	callq  40131b <string_length>
  40107f:	83 f8 06             	cmp    $0x6,%eax
  401082:	74 4e                	je     4010d2 <phase_5+0x70>
  401084:	e8 b1 03 00 00       	callq  40143a <explode_bomb>
  401089:	eb 47                	jmp    4010d2 <phase_5+0x70>
  40108b:	0f b6 0c 03          	movzbl (%rbx,%rax,1),%ecx
  40108f:	88 0c 24             	mov    %cl,(%rsp)
  401092:	48 8b 14 24          	mov    (%rsp),%rdx
  401096:	83 e2 0f             	and    $0xf,%edx
  401099:	0f b6 92 b0 24 40 00 	movzbl 0x4024b0(%rdx),%edx
  4010a0:	88 54 04 10          	mov    %dl,0x10(%rsp,%rax,1)
  4010a4:	48 83 c0 01          	add    $0x1,%rax
  4010a8:	48 83 f8 06          	cmp    $0x6,%rax
  4010ac:	75 dd                	jne    40108b <phase_5+0x29>
  4010ae:	c6 44 24 16 00       	movb   $0x0,0x16(%rsp)
  4010b3:	be 5e 24 40 00       	mov    $0x40245e,%esi
  4010b8:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  4010bd:	e8 76 02 00 00       	callq  401338 <strings_not_equal>
  4010c2:	85 c0                	test   %eax,%eax
  4010c4:	74 13                	je     4010d9 <phase_5+0x77>
  4010c6:	e8 6f 03 00 00       	callq  40143a <explode_bomb>
  4010cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4010d0:	eb 07                	jmp    4010d9 <phase_5+0x77>
  4010d2:	b8 00 00 00 00       	mov    $0x0,%eax
  4010d7:	eb b2                	jmp    40108b <phase_5+0x29>
  4010d9:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  4010de:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4010e5:	00 00 
  4010e7:	74 05                	je     4010ee <phase_5+0x8c>
  4010e9:	e8 42 fa ff ff       	callq  400b30 <__stack_chk_fail@plt>
  4010ee:	48 83 c4 20          	add    $0x20,%rsp
  4010f2:	5b                   	pop    %rbx
  4010f3:	c3                   	retq  

```
```x86asm
40107a:	e8 9c 02 00 00       	callq  40131b <string_length>
40107f:	83 f8 06             	cmp    $0x6,%eax
401082:	74 4e                	je     4010d2 <phase_5+0x70>
401084:	e8 b1 03 00 00       	callq  40143a <explode_bomb>
```
从上面的代码可以看到，需要输入6个字符（不输入空格）
```x86asm
40108b:	0f b6 0c 03          	movzbl (%rbx,%rax,1),%ecx
40108f:	88 0c 24             	mov    %cl,(%rsp)
401092:	48 8b 14 24          	mov    (%rsp),%rdx
401096:	83 e2 0f             	and    $0xf,%edx
401099:	0f b6 92 b0 24 40 00 	movzbl 0x4024b0(%rdx),%edx
4010a0:	88 54 04 10          	mov    %dl,0x10(%rsp,%rax,1)
4010a4:	48 83 c0 01          	add    $0x1,%rax
4010a8:	48 83 f8 06          	cmp    $0x6,%rax
4010ac:	75 dd                	jne    40108b <phase_5+0x29>
```
上面的代码把输入的字符取Ascii码低四位（可能的范围是0~F），然后根据`movzbl 0x4024b0(%rdx),%edx`从内存中对应地址取得对应的值，组成新的字符串存入内存：
| 低四位 | 对应新字符（十六进制）|
| :-------| :----------------| 
| 0       | 0x6d              |
| 1       | 0x61              |
| 2       | 0x64              |
| 3       | 0x75              |
| 4       | 0x69              |
| 5       | 0x65              |
| 6       | 0x72              |
| 7       | 0x73              |
| 8       | 0x6e              |
| 9       | 0x66              |
| a       | 0x6f              |
| b       | 0x74              |
| c       | 0x76              |
| d       | 0x62              |
| e       | 0x79              |
| f       | 0x6c              |
```x86asm
4010b3:	be 5e 24 40 00       	mov    $0x40245e,%esi
4010b8:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
4010bd:	e8 76 02 00 00       	callq  401338 <strings_not_equal>
4010c2:	85 c0                	test   %eax,%eax
```
由上面的代码可知，新生成字符串与内存0x4025e处字符串进行比较  
`pring * (long *) 0x4025e` 得到的字符串为`0x737265796c66`，查询上表得到需要输入的字符串的第四位为：`9fe567`（注意反向），查询ASCII码得到其中一个结果为：`ionefg`
### 第六个字符串
```x86asm
00000000004010f4 <phase_6>:
  4010f4:	41 56                	push   %r14
  4010f6:	41 55                	push   %r13
  4010f8:	41 54                	push   %r12
  4010fa:	55                   	push   %rbp
  4010fb:	53                   	push   %rbx
  4010fc:	48 83 ec 50          	sub    $0x50,%rsp
  401100:	49 89 e5             	mov    %rsp,%r13
  401103:	48 89 e6             	mov    %rsp,%rsi
  401106:	e8 51 03 00 00       	callq  40145c <read_six_numbers>
  40110b:	49 89 e6             	mov    %rsp,%r14
  40110e:	41 bc 00 00 00 00    	mov    $0x0,%r12d
  401114:	4c 89 ed             	mov    %r13,%rbp
  401117:	41 8b 45 00          	mov    0x0(%r13),%eax
  40111b:	83 e8 01             	sub    $0x1,%eax
  40111e:	83 f8 05             	cmp    $0x5,%eax
  401121:	76 05                	jbe    401128 <phase_6+0x34>
  401123:	e8 12 03 00 00       	callq  40143a <explode_bomb>
  401128:	41 83 c4 01          	add    $0x1,%r12d
  40112c:	41 83 fc 06          	cmp    $0x6,%r12d
  401130:	74 21                	je     401153 <phase_6+0x5f>
  401132:	44 89 e3             	mov    %r12d,%ebx
  401135:	48 63 c3             	movslq %ebx,%rax
  401138:	8b 04 84             	mov    (%rsp,%rax,4),%eax
  40113b:	39 45 00             	cmp    %eax,0x0(%rbp)
  40113e:	75 05                	jne    401145 <phase_6+0x51>
  401140:	e8 f5 02 00 00       	callq  40143a <explode_bomb>
  401145:	83 c3 01             	add    $0x1,%ebx
  401148:	83 fb 05             	cmp    $0x5,%ebx
  40114b:	7e e8                	jle    401135 <phase_6+0x41>
  40114d:	49 83 c5 04          	add    $0x4,%r13
  401151:	eb c1                	jmp    401114 <phase_6+0x20>
  401153:	48 8d 74 24 18       	lea    0x18(%rsp),%rsi
  401158:	4c 89 f0             	mov    %r14,%rax
  40115b:	b9 07 00 00 00       	mov    $0x7,%ecx
  401160:	89 ca                	mov    %ecx,%edx
  401162:	2b 10                	sub    (%rax),%edx
  401164:	89 10                	mov    %edx,(%rax)
  401166:	48 83 c0 04          	add    $0x4,%rax
  40116a:	48 39 f0             	cmp    %rsi,%rax
  40116d:	75 f1                	jne    401160 <phase_6+0x6c>
  40116f:	be 00 00 00 00       	mov    $0x0,%esi
  401174:	eb 21                	jmp    401197 <phase_6+0xa3>
  401176:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  40117a:	83 c0 01             	add    $0x1,%eax
  40117d:	39 c8                	cmp    %ecx,%eax
  40117f:	75 f5                	jne    401176 <phase_6+0x82>
  401181:	eb 05                	jmp    401188 <phase_6+0x94>
  401183:	ba d0 32 60 00       	mov    $0x6032d0,%edx
  401188:	48 89 54 74 20       	mov    %rdx,0x20(%rsp,%rsi,2)
  40118d:	48 83 c6 04          	add    $0x4,%rsi
  401191:	48 83 fe 18          	cmp    $0x18,%rsi
  401195:	74 14                	je     4011ab <phase_6+0xb7>
  401197:	8b 0c 34             	mov    (%rsp,%rsi,1),%ecx
  40119a:	83 f9 01             	cmp    $0x1,%ecx
  40119d:	7e e4                	jle    401183 <phase_6+0x8f>
  40119f:	b8 01 00 00 00       	mov    $0x1,%eax
  4011a4:	ba d0 32 60 00       	mov    $0x6032d0,%edx
  4011a9:	eb cb                	jmp    401176 <phase_6+0x82>//根据六个数字重新排列六个数，并将地址按顺序存入栈 
  4011ab:	48 8b 5c 24 20       	mov    0x20(%rsp),%rbx
  4011b0:	48 8d 44 24 28       	lea    0x28(%rsp),%rax
  4011b5:	48 8d 74 24 50       	lea    0x50(%rsp),%rsi
  4011ba:	48 89 d9             	mov    %rbx,%rcx
  4011bd:	48 8b 10             	mov    (%rax),%rdx
  4011c0:	48 89 51 08          	mov    %rdx,0x8(%rcx)
  4011c4:	48 83 c0 08          	add    $0x8,%rax
  4011c8:	48 39 f0             	cmp    %rsi,%rax
  4011cb:	74 05                	je     4011d2 <phase_6+0xde>
  4011cd:	48 89 d1             	mov    %rdx,%rcx
  4011d0:	eb eb                	jmp    4011bd <phase_6+0xc9>
  4011d2:	48 c7 42 08 00 00 00 	movq   $0x0,0x8(%rdx)
  4011d9:	00 
  4011da:	bd 05 00 00 00       	mov    $0x5,%ebp
  4011df:	48 8b 43 08          	mov    0x8(%rbx),%rax
  4011e3:	8b 00                	mov    (%rax),%eax
  4011e5:	39 03                	cmp    %eax,(%rbx)
  4011e7:	7d 05                	jge    4011ee <phase_6+0xfa>
  4011e9:	e8 4c 02 00 00       	callq  40143a <explode_bomb>
  4011ee:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
  4011f2:	83 ed 01             	sub    $0x1,%ebp
  4011f5:	75 e8                	jne    4011df <phase_6+0xeb>
  4011f7:	48 83 c4 50          	add    $0x50,%rsp
  4011fb:	5b                   	pop    %rbx
  4011fc:	5d                   	pop    %rbp
  4011fd:	41 5c                	pop    %r12
  4011ff:	41 5d                	pop    %r13
  401201:	41 5e                	pop    %r14
  401203:	c3                   	retq   
```
`callq  40145c <read_six_numbers>`读取六个数字
```x86asm
40110b:	49 89 e6             	mov    %rsp,%r14
40110e:	41 bc 00 00 00 00    	mov    $0x0,%r12d
401114:	4c 89 ed             	mov    %r13,%rbp
401117:	41 8b 45 00          	mov    0x0(%r13),%eax
40111b:	83 e8 01             	sub    $0x1,%eax
40111e:	83 f8 05             	cmp    $0x5,%eax
401121:	76 05                	jbe    401128 <phase_6+0x34>
401123:	e8 12 03 00 00       	callq  40143a <explode_bomb>
```
以上代码要求六个数减一均小于等于5，因此可能的范围是1~6（注意减一可能会溢出，因此要大于1）
```x86asm
401128:	41 83 c4 01          	add    $0x1,%r12d
40112c:	41 83 fc 06          	cmp    $0x6,%r12d
401130:	74 21                	je     401153 <phase_6+0x5f>
401132:	44 89 e3             	mov    %r12d,%ebx
401135:	48 63 c3             	movslq %ebx,%rax
401138:	8b 04 84             	mov    (%rsp,%rax,4),%eax
40113b:	39 45 00             	cmp    %eax,0x0(%rbp)
40113e:	75 05                	jne    401145 <phase_6+0x51>
401140:	e8 f5 02 00 00       	callq  40143a <explode_bomb>
401145:	83 c3 01             	add    $0x1,%ebx
401148:	83 fb 05             	cmp    $0x5,%ebx
40114b:	7e e8                	jle    401135 <phase_6+0x41>
40114d:	49 83 c5 04          	add    $0x4,%r13
401151:	eb c1                	jmp    401114 <phase_6+0x20>
```
以上代码要求六个数互不相等，因此这六个数是1，2，3，4，5，下面的代码决定这六个数的顺序
```x86asm
401153:	48 8d 74 24 18       	lea    0x18(%rsp),%rsi
401158:	4c 89 f0             	mov    %r14,%rax
40115b:	b9 07 00 00 00       	mov    $0x7,%ecx
401160:	89 ca                	mov    %ecx,%edx
401162:	2b 10                	sub    (%rax),%edx
401164:	89 10                	mov    %edx,(%rax)
401166:	48 83 c0 04          	add    $0x4,%rax
40116a:	48 39 f0             	cmp    %rsi,%rax
40116d:	75 f1                	jne    401160 <phase_6+0x6c>
```
以上代码将每一个数字用7减得到新的数字重新存储  
内存中保存了一个链表:
```x86asm
0x6032d0 : 0x10000014c
0x6032d8 : 0x6032e0
0x6032e0 : 0x2000000a8
0x6032e8 : 0x6032f0
0x6032f0 : 0x30000039c
0x6032f8 : 0x603300
0x603300 : 0x4000002b3
0x603308 : 0x603310
0x603310 : 0x5000001dd
0x603318 : 0x603320
0x603320 : 0x6000001bb
```
```x86asm
40116f:	be 00 00 00 00       	mov    $0x0,%esi
401174:	eb 21                	jmp    401197 <phase_6+0xa3>
401176:	48 8b 52 08          	mov    0x8(%rdx),%rdx
40117a:	83 c0 01             	add    $0x1,%eax
40117d:	39 c8                	cmp    %ecx,%eax
40117f:	75 f5                	jne    401176 <phase_6+0x82>
401181:	eb 05                	jmp    401188 <phase_6+0x94>
401183:	ba d0 32 60 00       	mov    $0x6032d0,%edx
401188:	48 89 54 74 20       	mov    %rdx,0x20(%rsp,%rsi,2)
40118d:	48 83 c6 04          	add    $0x4,%rsi
401191:	48 83 fe 18          	cmp    $0x18,%rsi
401195:	74 14                	je     4011ab <phase_6+0xb7>
401197:	8b 0c 34             	mov    (%rsp,%rsi,1),%ecx
40119a:	83 f9 01             	cmp    $0x1,%ecx
40119d:	7e e4                	jle    401183 <phase_6+0x8f>
40119f:	b8 01 00 00 00       	mov    $0x1,%eax
4011a4:	ba d0 32 60 00       	mov    $0x6032d0,%edx
4011a9:	eb cb                	jmp    401176 <phase_6+0x82>
```
以上代码根据输入的数字从链表中取出数据存入内存
例如：
>如果第一个数字是4，那么从链表的根节点：0x6032d0 向后调用三次，得到的地址为0x603300（代表的新数字为14c（只取低4个字节））  

因此，以上操作相当于根据输入数字的顺序，对链表中的数字进行排序
```x86asm
4011ab:	48 8b 5c 24 20       	mov    0x20(%rsp),%rbx
4011b0:	48 8d 44 24 28       	lea    0x28(%rsp),%rax
4011b5:	48 8d 74 24 50       	lea    0x50(%rsp),%rsi
4011ba:	48 89 d9             	mov    %rbx,%rcx
4011bd:	48 8b 10             	mov    (%rax),%rdx
4011c0:	48 89 51 08          	mov    %rdx,0x8(%rcx)
4011c4:	48 83 c0 08          	add    $0x8,%rax
4011c8:	48 39 f0             	cmp    %rsi,%rax
4011cb:	74 05                	je     4011d2 <phase_6+0xde>
4011cd:	48 89 d1             	mov    %rdx,%rcx
4011d0:	eb eb                	jmp    4011bd <phase_6+0xc9>
4011d2:	48 c7 42 08 00 00 00 	movq   $0x0,0x8(%rdx)
4011d9:	00 
4011da:	bd 05 00 00 00       	mov    $0x5,%ebp
4011df:	48 8b 43 08          	mov    0x8(%rbx),%rax
4011e3:	8b 00                	mov    (%rax),%eax
4011e5:	39 03                	cmp    %eax,(%rbx)
4011e7:	7d 05                	jge    4011ee <phase_6+0xfa>
4011e9:	e8 4c 02 00 00       	callq  40143a <explode_bomb>
4011ee:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
4011f2:	83 ed 01             	sub    $0x1,%ebp
4011f5:	75 e8                	jne    4011df <phase_6+0xeb>
```
以上代码用来判断链表中数字是否按照由大到小的顺序排列，如果不是降序排列，则“爆炸”，因此将链表按降序排列需要的字符串为：`345612`，而由于前面将每一个数字用7减得到新的数字重新存储，因此输入的字符串应为：`432165`
## 实验结果
```x86asm
Border relations with Canada have never been better.
1 2 4 8 16 32
0 207
7 0
ionefg
432165
```
