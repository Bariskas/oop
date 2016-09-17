set PROGRAM="%~1"

rem ��������� ����������� ������� �����
%PROGRAM% empty.txt %TEMP%\empty.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt empty.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ����� �� ����� ������
%PROGRAM% single_line.txt %TEMP%\single_line.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\single_line.txt single_line.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ����� �� ���������� �����
%PROGRAM% multi_line.txt %TEMP%\multi_line.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\multi_line.txt multi_line.txt
if ERRORLEVEL 1 goto err

rem �������� ������� ����������� ��������������� �����
%PROGRAM% nonexistent.txt %TEMP%\multi_line.txt > %TEMP%/nonexistent_file_copy_result.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\nonexistent_file_copy_result.txt expected_nonexistent_file_copy_result.txt
if ERRORLEVEL 1 goto err


echo Program testing successed
exit 0

:err
echo Program testing failed
exit 1