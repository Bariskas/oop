set PROGRAM="%~1"

rem проверяем работу программы с неверным количеством аргументов
%PROGRAM% > %TEMP%/run_program_without_arguments_result.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\run_program_without_arguments_result.txt expected_run_program_without_arguments_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с пустым аргументом
%PROGRAM% 10 "" 45 > %TEMP%/run_program_with_empty_radix_argument_result.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\run_program_with_empty_radix_argument_result.txt expected_run_program_with_empty_argument_result.txt
if ERRORLEVEL 1 goto err
%PROGRAM% 10 16 "" > %TEMP%/run_program_with_empty_value_argument_result.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\run_program_with_empty_value_argument_result.txt expected_run_program_with_empty_argument_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу с обычными данными
%PROGRAM% 10 2 255 > %TEMP%\simple_test_from_10_to_2_255.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\simple_test_from_10_to_2_255.txt expected_simple_test_from_10_to_2_255_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу с максимальным значением unsigned int: 4 294 967 295
%PROGRAM% 10 16 4294967295 > %TEMP%\from_10_to_16_4294967295.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\from_10_to_16_4294967295.txt expected_from_10_to_16_4294967295_result.txt
if ERRORLEVEL 1 goto err
%PROGRAM% 16 10 FFFFFFFF > %TEMP%\from_16_to_10_FFFFFFFF.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\from_16_to_10_FFFFFFFF.txt expected_from_16_to_10_FFFFFFFF_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу с значением большим максимального на 1 unsigned int: 4 294 967 296
%PROGRAM% 10 16 4294967296 > %TEMP%\from_10_to_16_4294967296.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\from_10_to_16_4294967296.txt overflow_result.txt
if ERRORLEVEL 1 goto err
%PROGRAM% 16 10 100000000 > %TEMP%\from_16_to_10_100000000.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\from_16_to_10_100000000.txt overflow_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу с неверной системой счисления
%PROGRAM% 40 16 429496729 > %TEMP%\from_40_to_16_429496729.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\from_40_to_16_429496729.txt wrong_radix_error.txt
if ERRORLEVEL 1 goto err
%PROGRAM% 1 16 429496729 > %TEMP%\from_1_to_16_429496729.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\from_1_to_16_429496729.txt wrong_radix_error.txt
if ERRORLEVEL 1 goto err

:succ
echo Program testing successed
exit 0

:err
echo Program testing failed
exit 1