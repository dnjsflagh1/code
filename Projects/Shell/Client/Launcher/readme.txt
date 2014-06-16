-------------------------------------------------目录文件结构-------------------------------------------------
wxLauncher.sln            工程文件
launcher.vcproj           launcher项目
wxSkin.vcproj             皮肤库项目
wxSkin_example.vcproj     皮肤库演示项目
App.ico                   项目图标

sample                    示例项目源文件目录
wxSkin                    皮肤库源文件目录
launcher                  launcher项目源文件目录                
release                   release输出目录                   
debug                     debug输出目录

------------------------------------------------ 工程说明 ---------------------------------------------------
wxSkin组织方式：
皮肤由 .png图片和结构说明(坐标、别名等信息)的xml组成， 将皮肤图片文件和结构说明xml文件导入zip格式压缩包，例如
skin.zip
|
|-------- main.xml             // 主窗体皮肤结构
|-------- frame.png
|-------- btn_ok.png
|-------- btn_ok_act.png
|-------- btn_cancel.png
|-------- btn_cancel_act.png
|-------- about.xml            // about窗体皮肤结构
|-------- *.png                // 理论上可以添加任意多个png文件             
|
|

类设计：
wxSkinFrame         复杂窗体
复杂窗体要求比较严格，需要将皮肤切割如图
-----------------------------------------
|--+--------------------------------+---|
|  |                                |   |
|  |                                |   |
|  |                                |   |
|  |                                |   |
|--+--------------------------------+---|
|  |                                |   |
|---------------------------------------|
 窗体被切割成9块，我们必须将这九块图片防止到皮肤压缩包中，并以规范命名。
 并提供最大化、最小化、关闭等按钮贴图。详情参考launcher.xml.除此之外，还可以命名窗体Title.


wxSkinSimpleFrame   简单窗体
简单窗体窗体皮肤是一整张，不需要切割。不能指定窗体Title需要在做皮肤的时候做好。
窗体可以任意添加按钮，窗体的内容部分需要在皮肤配置xml中指定。详情参考launcher.xml.


--------------------------------------------- 配置文件 -------------------------------------------------------
launcher.ini 本地配置文件
[WEB]
forum=http://shz.kx1d.com/bbs/
official=http://shz.kx1d.com/
FAQ=http://shz.kx1d.com/faq.php
services=http://www.kx1d.com/service/index.shtml
register=http://passport.kx1d.com/member/register?gourl=http://www.kx1d.com/
news=http://shz.kx1d.com/php/newslist.php
download=http://shz.kx1d.com/download.html
pay=http://www.kx1d.com/pay/index.shtml
[SYSTEM]
language=中文简体
part=华东1区
server=苦海无涯
version=2

http://192.168.1.181/updateversion.xml 更新服务器文件
<MMO>
<game name="SHZ" version="1">
<!-- exe/dll/dir/rar/dat -->
<dir name="common" local=""/>
<dir name="common\testgame.mmo" local=""/>
<dir name="bin" local=""/>
<exe name="Client_double.exe" local="bin" version="" url="http://192.168.1.181/Client.exe"/>
<exe name="Client.exe" local="bin" version="0.0.0.6991" url=""/>
<dll name="d3dx9_31.dll" local="bin" version="" url=""/>
<dll name="d3dx9_33.dll" local="bin" version="" url=""/>
<zip name="library.zip" local="bin" version="" url=""/>
</game>
<game name="SHZ" version="2">
<!-- exe/dll/dir/rar/dat -->
<exe name="shzTest.rar" local="bin" version="" url="ftp://192.168.1.181/update/2/shzTest.rar"/>
<exe name="Client_double.exe" local="bin" version="" url="ftp://192.168.1.181/update/2/Client_double.exe"/>
<exe name="calc1.exe" local="bin" version="" url="ftp://192.168.1.181/update/2/calc1.exe"/>
<exe name="calc.exe" local="bin" version="" url="ftp://192.168.1.181/update/2/calc.exe"/>
<dat name="profile.dat" local="common" version="" url="ftp://192.168.1.181/update/2/profile.dat"/>
</game>
</MMO>


ServerList.xml  本地服务器列表
<?xml version="1.0" encoding="UTF-8"?>
<!-- 0 热，1 满， 2 荐， 3 新， 4 闲 -->
<MMO>
  <area name="华东电信">    
    <server name="东归幻境" address="shzgame00.kx1d.com" state="0"/>
    <server name="蛮荒狼虏" address="shzgame01.kx1d.com" state="0"/>
    <server name="野道麒麟" address="shzgame02.kx1d.com" state="0"/>
    <server name="寒夜狼虏" address="shzgame03.kx1d.com" state="0"/>
    <server name="血宗密令" address="shzgame04.kx1d.com" state="0"/>      
  </area>
  <area name="华南电信">
    <server name="开天辟地" address="shzgame00.kx1d.com" state="0"/>
    <server name="女娲补天" address="shzgame01.kx1d.com" state="0"/>
    <server name="命运之轮" address="shzgame02.kx1d.com" state="0"/>
    <server name="王都密室" address="shzgame03.kx1d.com" state="0"/>
    <server name="昆仑吞云" address="shzgame04.kx1d.com" state="0"/>      
  </area>  
  <area name="华西电信">
    <server name="天魔屠戮" address="shzgame00.kx1d.com" state="0"/>
    <server name="百鬼之祭" address="shzgame01.kx1d.com" state="0"/>
    <server name="浴血荒原" address="shzgame02.kx1d.com" state="0"/>
    <server name="雷泽魔障" address="shzgame03.kx1d.com" state="0"/>
    <server name="刑天猛志" address="shzgame04.kx1d.com" state="0"/>
    <server name="夸父逐日" address="shzgame05.kx1d.com" state="0"/>      
  </area>    
  <area name="华北网通">
    <server name="天魔屠戮" address="shzgame00.kx1d.com" state="0"/>
    <server name="百鬼之祭" address="shzgame01.kx1d.com" state="0"/>
    <server name="浴血荒原" address="shzgame02.kx1d.com" state="0"/>
    <server name="雷泽魔障" address="shzgame03.kx1d.com" state="0"/>
    <server name="刑天猛志" address="shzgame04.kx1d.com" state="0"/>
    <server name="夸父逐日" address="shzgame05.kx1d.com" state="0"/>      
  </area>      
</MMO>