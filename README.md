# GMAS
**Geoganlle Multi-Agent System Path Planning Program 
description**
last update: 2019/6/5 16:02:32 
## 简述 ##
本程序实现了基于A*算法的多智能体路径规划算法，用于处理多任务路径规划问题。

**主要思想：**

**合作**：智能体在决策前先其他智能体交换数据信息

**竞争**：以全局最优解的思路处理路径冲突

## 程序说明 ##
本程序分为三个子程序，Generate，GMAS，QMAS
### Generate ###
**路径**：GMAS\Generate

**功能**：数据生成程序，随机生成地图和任务数据，用于多智能体路径规划的数据输入。可以批量生成不同参数下的测试用例。
### GMAS ###
**路径**：GMAS\GMAS

**功能**：核心算法程序

主函数可以调用以下函数完成具体功能
>void test1();//单智能体路径规划
>
>void test2();//多智能体路径规划
>
>void test3();//静态多智能体路径规划批量测试
>
>void test4();///动态多智能体路径规划批量测试
### QMAS ###
**路径**：GMAS\QMAS

**功能**：提供输入输出的可视化操作界面
## 操作说明 ##
###运行环境###
> C++11（**必须**）
>
> windows 10 1809(非必须)
>
> vistual studio 2019（低版本请参考错误与警告信息进行配置）
> 
> qt 5.12.2 msvc-2017-64 (低版本不兼容)

###操作步骤###

1. 用 visual studio 打开 GMAS\QMAS\QMAS.vcxproj 文件（或者用 qt creater 打开 GMAS\QMAS\QMAS.pro文件）
2. 配置运行环境，点击运行。
3. 选择从文件输入或者手动输入的方式输入地图和任务信息
4. 选择静态规划或者动态规划
5. 查看运行结果，点击单步运行或单阶段运行查看每个时刻智能体的位置
6. 点击退出按钮或右上角X按钮退出程序

###编辑说明###
Generate可以调整地图尺寸，障碍物密集程序，智能体个数，批量处理个数等参数生成输入数据

GMAS中的runmas1和runmas2分别用于生成静态多智能体路径规划程序和动态多智能体路径规划程序，在可运行程序（GMAS.exe）生成后，请将其分别重命名GMAS1.exe和GMAS2.exe，然后拷贝到GMAS\cached 目录下用于为可视化程序（QMAS）提供算法服务

QMAS仅提供输入输出逻辑，其中与GMAS核心程序（GMAS1.exe和GMAS2.exe）的交互通过文件实现，文件目录为GMAS\cached