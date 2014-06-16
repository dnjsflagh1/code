@echo off
@echo һ�����汾....

::��������
set devenvFilePath=D:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE
set slnFilePath=E:\work\MGCode\Build
set projectFilePath=E:\work\MGCode\Projects

::����Bat�ļ����ڵ�·��
cd /d %~dp0


@echo ����MGUtility DEBUG....
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

@echo ����MGUtility DEBUG�ɹ�!....

@echo ����MGUtility RELEASE....
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