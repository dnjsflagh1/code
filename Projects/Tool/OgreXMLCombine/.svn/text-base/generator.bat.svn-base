set inputDir=CombineInput

set outputDir=CombineOutput

set animName=crash

@echo on

if "%1" == "" goto end

if not exist %inputDir% md %inputDir%

if not exist %outputDir% md %outPutDir%

:start

if %errorlevel% equ 1 goto end

cd %inputDir%

for /f "delims=" %%i in ('dir /b /a-d /s "*.mesh"') do (
	..\\MyXMLConverter %%i
)

cd..

OgreXMLCombine_d %1 %inputDir% %outputDir% %animName%

cd %outputDir%

..\\MyXMLConverter %1.skeleton.xml
..\\MyXMLConverter %1.mesh.xml

cd..

:end
