---
title: "Leetcode_Detachment"
date: 2021-05-31T15:16:23+08:00
lastmod: 2021-05-31T15:16:23+08:00
draft: false
keywords: []
description: ""
tags: ["技术", "Leetcode"]
categories: []
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

<!--more-->
## P42 接雨水问题
* ## Leetcode问题链接   
  [Leetcode trapping-rain-water](https://leetcode-cn.com/problems/trapping-rain-water/ "Leetcode trapping-rain-water")
* ## 解法
1. ### 双指针  
   时间复杂度 $O(n)$，空间复杂度$O(1)$  
   对于每一个位置来说，考虑这个位置在一个单位宽度的范围竖直方向是否可以接到雨水以及有多少单位的雨水。如果该位置左边最高的高度记为$leftMax$，右边最高的高度记为$rightMax$，如果该位置同时小于$leftMax$和$rightMax$，则这个位置可以接到雨水，反之则接不到。可以接到雨水时，能接到多少单位雨水取决于$min(leftMax, rightMax)$  
   当我们从左往右处理到$left$下标时，左边的最大值$leftMax$对它而言是可信的，但$rightMax$对它而言是不可信的，右边同理。但是在从左往右处理的时候，如果此时$leftMax<rightMax$，则该位置的接到的水的数量只取决于$leftMax$，而此时$leftMax$是可信的，因此这种情况从左向右处理，反之从右向左处理。
   ```java
   public int trap(int[] height) {
        // Double pointer
        int left = 0;
        int right = height.length - 1;
        int leftMax = 0;
        int rightMax = 0;
        int res = 0;
        while (left <= right){
            if (leftMax <= rightMax){
                leftMax = Math.max(leftMax, height[left]);
                res += leftMax - height[left];
                left += 1;
            }
            else {
                rightMax = Math.max(rightMax, height[right]);
                res += rightMax - height[right];
                right -= 1;
            }
        }
        return res;
    }
   ```
2. ### 单调栈
   时间复杂度 $O(n)$，空间复杂度$O(n)$  
   以高度单调递减的方式将索引储存在栈里面，当遇到高于栈顶的值时，开始接水，接水量考虑 $left$，$bottom$，$right$三个柱子，计算这三个柱子包含的水量（是一个面积），然后将 $bottom$ 出栈，由于计算接水量的前提是遍历到的柱子高度大于栈顶柱子高度，因此弹出 $bottom$ 后，栈顶柱子的高度就是新的 $bottom$
   ```java
   public int trap(int[] height) {
        // Monotonous stack
        LinkedList<Integer> stack = new LinkedList<>();
        int res = 0;
        for (int i = 0; i < height.length; i++){
            while (!stack.isEmpty() && (height[i] > height[stack.peek()])){
                int bottom = stack.pop();
                if (stack.isEmpty()){
                    break;
                }
                int left = stack.peek();
                res += (i - left - 1) * (Math.min(height[i], height[left]) - height[bottom]);
            }
            stack.push(i);
        }
        return res;
    }
   ```
3. ### 动态规划
   时间复杂度 $O(n)$，空间复杂度$O(n)$