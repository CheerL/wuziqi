# 五子棋

## 玩法说明

按提示操作进入游戏, 在游戏中, 输入坐标落子, 先字母后数字，如a1

按z键悔棋，按ESC可以退出游戏.

在当获胜或按ESC后, 可以选择重新开始或者退出游戏

***

## 模式说明

该五子棋程序支持多种游戏模式

* 人人对战

>当选择人人对战, 两玩家可以交替游戏直至一方胜利

* 人机对战

>当选择人机对战, 玩家可以自由选择执黑或者执白

* 机机对战（AI测试模式）

>当选择机机对战, 可以控制电脑下棋的间隔时间
>
>按
>
>		ESC
>
>结束机机对战
>
>按
>
>		Enter(回车键)
>
>暂停游戏，暂停后按任何键可以回到游戏

***

## 功能说明

该五子棋程序支持以下功能

* 指定开局

>在开局时，除了人机对战且电脑执黑的情况外, 均可输入
>
>		z + i/d + 数字
>
>来指定26种标准开局中的某一种. 其中数字从1到13，i为斜指开局，d为直指开局，共26种开局.
>
>若不指定开局，可按回车跳过

* 三手互换

>当指定开局后, 可输入
>
>		hh
>
>进行三手互换, 即交换黑白方, 若不互换，可以按回车键跳过

* 悔棋

>按
>
>		z
>
>键悔棋, 可以悔棋无数步直至游戏最开始.

* 行棋记录

>所有行棋记录会以文件名为
>
>		qipu + 时间 (如qipu 2016-12-24 15-15-52)
>
>的txt格式的文件保存, 可以在开始时选择加载游戏, 输入文件名以读取棋谱

* 行棋记录的回放

>读取棋谱后会进入回放模式（复盘）默认复盘至最后一步. 
>
>可以按左键或上键倒退，按右键或者下键前进.
>
>当想结束回放，可以按
>
>		ESC
>
>退出回放模式并从当前位置开始游戏

* 禁手

>按五子棋标准规则禁手

***