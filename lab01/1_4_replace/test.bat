set PROGRAM="%~1"

rem проверяем работу программы с неверным количеством аргументов
%PROGRAM% empty.txt %TEMP%\empty.txt testSearch > %TEMP%/run_program_with_wrong_count_arguments_result.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\run_program_with_wrong_count_arguments_result.txt expected_run_program_with_wrong_count_arguments_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с пустой заменяемой строкой
%PROGRAM% empty.txt %TEMP%\empty.txt "" testSearch > %TEMP%/run_program_with_empty_string_to_replace.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\run_program_with_empty_string_to_replace.txt expected_run_program_with_empty_string_to_replace.txt
if ERRORLEVEL 1 goto err

rem проверка работы программы несуществующего файла
%PROGRAM% nonexistent.txt %TEMP%\multi_line.txt testSearch testReplace > %TEMP%/nonexistent_file_copy_result.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\nonexistent_file_copy_result.txt expected_nonexistent_file_copy_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с пустым файлом
%PROGRAM% empty.txt %TEMP%\empty.txt testSearch testReplace
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt empty.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с данными внутри текста
%PROGRAM% simple_test_text.txt %TEMP%\simple_test_text_result.txt testSearch testReplace
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\simple_test_text_result.txt expected_simple_test_text_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с данными в начале и конце строки
%PROGRAM% test_text_begin_end_placement.txt %TEMP%\test_text_begin_end_placement_result.txt testSearch testReplace
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\test_text_begin_end_placement_result.txt expected_test_text_begin_end_placement_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с многократным вхождением
%PROGRAM% test_text_repeated_search_text_in_a_row.txt %TEMP%\test_text_repeated_search_text_in_a_row_result.txt testtest testtesttest
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\test_text_repeated_search_text_in_a_row_result.txt expected_test_text_repeated_search_text_in_a_row_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с пустыми строками
%PROGRAM% test_text_with_empty_rows.txt %TEMP%\test_text_with_empty_rows_result.txt testSearch testReplace
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\test_text_with_empty_rows_result.txt expected_test_text_with_empty_rows_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу с открытием запущенного файла
%PROGRAM% test_text_with_empty_rows.txt %PROGRAM% testSearch testReplace > %TEMP%/wrong_flush_result.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing successed
exit 0

:err
echo Program testing failed
exit 1