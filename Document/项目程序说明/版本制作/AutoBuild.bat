@echo off
@echo 一键做版本....

::变量定义
set devenvFilePath=D:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE
set slnFilePath=E:\work\MGCode\Build
set projectFilePath=E:\work\MGCode\Projects

::进入Bat文件所在的路径
cd /d %~dp0


@echo 编译MGUtility DEBUG....
D:
cd %devenvFilePath%
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::Clean
devenv /clean Debug "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGMisc\MGMisc.vcproj" /projectconfig Debug
devenv /clean Debug "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGDB\MGDB.vcproj" /projectconfig Debug
devenv /clean Debug "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGThread\MGThread.vcproj" /projectconfig Debug
devenv /clean Debug "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGMemory\MGMemory.vcproj" /projectconfig Debug
devenv /clean Debug "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGMath\MGMath.vcproj" /projectconfig Debug
devenv /clean Debug "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGFile\MGFile.vcproj" /projectconfig Debug
devenv /clean Debug "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGLua\MGLua.vcproj" /projectconfig Debug
devenv /clean Debug "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGNet\MGNet.vcproj" /projectconfig Debug
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::Build
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Debug /project "%projectFilePath%\Utility\MGDB\MGDB.vcproj" /projectconfig Debug
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Debug /project "%projectFilePath%\Utility\MGMisc\MGMisc.vcproj" /projectconfig Debug
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Debug /project "%projectFilePath%\Utility\MGThread\MGThread.vcproj" /projectconfig Debug
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Debug /project "%projectFilePath%\Utility\MGMemory\MGMemory.vcproj" /projectconfig Debug
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Debug /project "%projectFilePath%\Utility\MGMath\MGMath.vcproj" /projectconfig Debug
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Debug /project "%projectFilePath%\Utility\MGFile\MGFile.vcproj" /projectconfig Debug
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Debug /project "%projectFilePath%\Utility\MGLua\MGLua.vcproj" /projectconfig Debug
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Debug /project "%projectFilePath%\Utility\MGNet\MGNet.vcproj" /projectconfig Debug
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

@echo 编译MGUtility DEBUG成功!....

@echo 编译MGUtility RELEASE....
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::Clean
devenv /clean Release "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGMisc\MGMisc.vcproj" /projectconfig Release
devenv /clean Release "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGDB\MGDB.vcproj" /projectconfig Release
devenv /clean Release "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGThread\MGThread.vcproj" /projectconfig Release
devenv /clean Release "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGMemory\MGMemory.vcproj" /projectconfig Release
devenv /clean Release "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGMath\MGMath.vcproj" /projectconfig Release
devenv /clean Release "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGFile\MGFile.vcproj" /projectconfig Release
devenv /clean Release "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGLua\MGLua.vcproj" /projectconfig Release
devenv /clean Release "%slnFilePath%\Utility\MGUtility.sln" /project "%projectFilePath%\Utility\MGNet\MGNet.vcproj" /projectconfig Release
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::Build
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Release /project "%projectFilePath%\Utility\MGDB\MGDB.vcproj" /projectconfig Release
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Release /project "%projectFilePath%\Utility\MGMisc\MGMisc.vcproj" /projectconfig Release
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Release /project "%projectFilePath%\Utility\MGThread\MGThread.vcproj" /projectconfig Release
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Release /project "%projectFilePath%\Utility\MGMemory\MGMemory.vcproj" /projectconfig Release
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Release /project "%projectFilePath%\Utility\MGMath\MGMath.vcproj" /projectconfig Release
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Release /project "%projectFilePath%\Utility\MGFile\MGFile.vcproj" /projectconfig Release
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Release /project "%projectFilePath%\Utility\MGLua\MGLua.vcproj" /projectconfig Release
devenv "%slnFilePath%\Utility\MGUtility.sln" /build Release /project "%projectFilePath%\Utility\MGNet\MGNet.vcproj" /projectconfig Release
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

pause