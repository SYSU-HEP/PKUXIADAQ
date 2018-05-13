<!-- README.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 6月 18 13:37:42 2016 (+0800)
;; Last-Updated: 日 5月 13 16:17:00 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 65
;; URL: http://wuhongyi.cn -->

# README

程序下载请访问
https://github.com/wuhongyi/PKUXIADAQ

网页版说明书请访问
http://wuhongyi.cn/PKUXIADAQ/

**本说明书仅适用于 XIA LLC Pixie16**

本程序由北京大学实验核物理组开发。

技术指导:
- 李智焕
- 谭辉(XIA LLC)

软件主要开发者:
- 吴鸿毅(wuhongyi@qq.com)
- 李晶(lijinger02@126.com)

说明书主要撰写者:
- 王翔
- 罗迪雯
- 吴鸿毅



本程序的开发得到以下单位的支持：
- XIA LLC
- 中国科学院近代物理研究所(IMP)
- 中国原子能科学研究院(CIAE)
- 香港大学(HKU)
- 山东大学(威海)(SDU)
- ...

----


本程序适用于 XIA Pixie16 系列采集卡，支持100/250/500MHz采集卡(具体支持型号可查看图形软件中的File->About)，最大支持8个机箱同步运行，即1600+路信号同时采集。**本程序包要求使用 CERN ROOT6 版本。要求采用 1920x1080 及以上分辨率显示屏**。

本程序的设计兼容 100/250/500 MHz 采集卡的混合使用，只需在 cfgPixie16.txt 添加各类采样率采集卡的固件位置即可，程序在线能够自动识别采集卡类型并加载相应的固件。当前我们只有100/250MHz 14bit的采集卡，因此默认可运行该类型的采集卡，如要支持其它类型，请联系 XIA LLC 获取对应固件或者联系吴鸿毅(wuhongyi@qq.com)。


- 对本获取程序有任何的意见及建议(功能添加及改进)，欢迎给吴鸿毅(wuhongyi@qq.com)发邮件。
- 我们将会尽快完善软件的中英文使用说明书，当前基本都是通过操作演示来讲解软件的使用为主。


用户使用程序包中包含以下文件夹:

- Decode(将原始二进制数据转为ROOT)
- docs(使用说明书，网页版，pdf版。暂未完成)
- firmware(固件)
- GUI(图形软件)
- MakeEvent(事件重构程序，可选)
- NOGUI(非图形软件。升级中，暂时不可用)
- OnlineStattics(在线监视程序)
- parset(参数设置文件)
- README(说明书md版)
- PlxSdk(Plx9054驱动，由PlxSdk.tar.gz得到)
- software(pixie16驱动API)
- firmware/firmware.md(历史各版本固件说明)
- TestTool(开发者测试工具，用户不需要)



<!-- README.md ends here -->