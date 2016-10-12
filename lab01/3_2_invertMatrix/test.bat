set PROGRAM="%~1"

rem проверяем работу программы с несуществующим файлом
%PROGRAM% nonexistent.txt> %TEMP%/test_non_exist_file_open.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\test_non_exist_file_open.txt expected_test_non_exist_file_open_result.txt
if ERRORLEVEL 1 goto err

:succ
echo Program testing successed
exit 0

:err
echo Program testing failed
exit 1