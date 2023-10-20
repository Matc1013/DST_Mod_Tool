@echo off

pushd %1 & for %%i in (.) do set dir_name=%%~ni

set source_dir=%cd%

cd ..
rmdir /s /q "%dir_name%_build"
mkdir "%dir_name%_build"

call cmake -S "%source_dir%" -B "%dir_name%_build" 
call cmake --open "%dir_name%_build"

