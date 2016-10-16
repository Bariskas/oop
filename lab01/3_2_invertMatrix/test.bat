set PROGRAM="%~1"

rem проверяем работу программы с несуществующим файлом
%PROGRAM% nonexistent.txt> %TEMP%/test_non_exist_file_open.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\test_non_exist_file_open.txt expected_test_non_exist_file_open_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с обычной матрицей
%PROGRAM% simple_matrix.txt > %TEMP%/test_simple_matrix.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\test_simple_matrix.txt expected_test_simple_matrix_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с вырожденной матрицей
%PROGRAM% matrix_with_null_determinant.txt > %TEMP%/test_matrix_with_null_determinant.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\test_matrix_with_null_determinant.txt expected_test_matrix_with_null_determinant_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с недостающим количеством элементов в строке
%PROGRAM% 2_elem_in_row_matrix.txt > %TEMP%/test_2_element_in_row_matrix.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\test_2_element_in_row_matrix.txt expected_test_2_element_in_row_matrix_result.txt
if ERRORLEVEL 1 goto err

rem проверяем работу программы с недостающим количеством строк
%PROGRAM% 2_row_in_matrix.txt > %TEMP%/test_2_row_in_matrix.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\test_2_row_in_matrix.txt expected_test_2_row_in_matrix_result.txt
if ERRORLEVEL 1 goto err

:succ
echo Program testing successed
exit 0

:err
echo Program testing failed
exit 1