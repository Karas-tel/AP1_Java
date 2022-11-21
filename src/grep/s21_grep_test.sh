#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

declare -a tests=(
"-e return FLAGS FILES"
#"for s21_grep.c s21_grep.h Makefile VAR"
#"for s21_grep.c VAR"
#"-e for -e ^int s21_grep.c s21_grep.h Makefile VAR"
#"-e for -e ^int s21_grep.c VAR"
#"-e regex -e ^print s21_grep.c VAR -f test_ptrn_grep.txt"
#"-e while -e void s21_grep.c Makefile VAR -f test_ptrn_grep.txt"
)

declare -a files=(
" grep_tests\/file_1 "
" grep_tests\/file_2 "
" grep_tests\/file_3 "
" grep_tests\/file_4 "
" "
)

declare -a extra=(
"-n for test_1_grep.txt test_2_grep.txt"
"-n for test_1_grep.txt"
"-n -e ^\} test_1_grep.txt"
"-c -e /\ test_1_grep.txt"
"-ce ^int test_1_grep.txt test_2_grep.txt"
"-e ^int test_1_grep.txt"
"-nivh = test_1_grep.txt test_2_grep.txt"
"-e"
"-ie INT test_5_grep.txt"
"-echar test_1_grep.txt test_2_grep.txt"
"-ne = -e out test_5_grep.txt"
"-iv int test_5_grep.txt"
"-in int test_5_grep.txt"
"-c -l aboba test_1_grep.txt test_5_grep.txt"
"-v test_1_grep.txt -e ank"
"-noe ) test_5_grep.txt"
"-l for test_1_grep.txt test_2_grep.txt"
"-o -e int test_4_grep.txt"
"-e = -e out test_5_grep.txt"
"-noe ing -e as -e the -e not -e is test_6_grep.txt"
"-e ing -e as -e the -e not -e is test_6_grep.txt"
"-c -e . test_1_grep.txt -e '.'"
"-l for no_file.txt test_2_grep.txt"
"-f test_3_grep.txt test_5_grep.txt"
)

testing()
{
    t=$(echo $@ | sed "s/FLAGS/$flags/g;s/FILES/$files/g")
    echo $t
    ./s21_grep $t > s21_grep_test.log
    grep $t > grep_test.log
    # DIFF_RES="$(diff -s s21_grep_test.log grep_test.log)"
    DIFF="$(diff s21_grep_test.log grep_test.log)"
    (( COUNTER++ ))
 
    if [ "$DIFF" == "" ]
    then
      (( SUCCESS++ ))
      echo "$FAIL $SUCCESS $COUNTER success grep $t"
    else
      (( FAIL++ ))
      echo "$FAIL $SUCCESS $COUNTER fail grep $t"
    fi
    rm s21_grep_test.log grep_test.log
}

# специфические тесты
# for i in "${extra[@]}"
# do
#     var="-"
#     testing $i
# done
getfiles()
{
    for file1 in "${files[@]}"
    do
        for file2 in "${files[@]}"
        do
        #     for file3 in "${files[@]}"
        #     do
        #         for file4 in "${files[@]}"
        #         do
                    
                    if [ "$file1" != "$file2" ] #&& [ "$file2" != "$file3" ] && [ "$file1" != "$file3" ] 
                    # && \
                    #    [ $file4 != $file1 ] && [ $file4 != $file2 ] && [ $file4 != $file3 ]
                    then
                        files="$file1 $file2"
                        testing $i
                    fi
                    
        #         done
        #     done
        done
    done
}

for flag1 in i v c l n h s o
do
    for i in "${tests[@]}"
    do
        flags="-$flag1"
        getfiles 
        # testing $i
    done
done

# for flag1 in i v c l n h s o
# do
#     for flag2 in i v c l n h s o
#     do
#         if [ $flag1 != $flag2 ]
#         then
#             for i in "${tests[@]}"
#             do
#                 flags="-$flag1$flag2"
#                 testing $i
#             done
#         fi
#     done
# done

# for flag1 in i v c l n h s o
# do
#     for flag2 in i v c l n h s o
#     do
#         for flag3 in i v c l n h s o
#         do
#             if [ $flag1 != $flag2 ] && [ $flag2 != $flag3 ] && [ $flag1 != $flag3 ]
#             then
#                 for i in "${tests[@]}"
#                 do
#                     flags="-$flag1$flag2$flag3"
#                     testing $i
#                 done
#             fi
#         done
#     done
# done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
