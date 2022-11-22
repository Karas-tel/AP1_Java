#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""
STR="PATTERNS FLAGS FILES"

declare -a file=(
" grep_tests\/file_1 "
" grep_tests\/file_2 "
" grep_tests\/file_3 "
" grep_tests\/file_4 "
" grep_tests\/file_1 grep_tests\/file_2 "
" grep_tests\/file_1 grep_tests\/file_3 "
" grep_tests\/file_1 grep_tests\/file_4 "
" grep_tests\/file_1 grep_tests\/file_2 grep_tests\/file_4 "
" grep_tests\/file_1 grep_tests\/file_3 grep_tests\/file_4 "
" grep_tests\/file_1 grep_tests\/file_2 grep_tests\/file_3 grep_tests\/file_4 "
" grep_tests\/file_2 grep_tests\/file_4 "
" grep_tests\/file_3 grep_tests\/file_4 "
" grep_tests\/file_2 grep_tests\/file_3 grep_tests\/file_4 "
)

declare -a pattern=(
" -e return "
" -e '^int'"
" -e 'sizeof(char)'"
" -e '\"'"
" -f grep_tests\/pattern.txt"
)

testing()
{
    str=$(echo $STR | sed "s/FLAGS/$flags/g;s/FILES/$files/g;s/PATTERNS/$patterns/g")
    ./s21_grep $str > s21_grep_test.log
    grep $str > grep_test.log
    DIFF="$(diff s21_grep_test.log grep_test.log)"
    (( COUNTER++ ))
 
    if [ "$DIFF" == "" ]
    then
      (( SUCCESS++ ))
      echo "$FAIL $SUCCESS $COUNTER success grep $str"
    else
      (( FAIL++ ))
      echo "$FAIL $SUCCESS $COUNTER fail grep $str"
    fi
    rm s21_grep_test.log grep_test.log
}

getfiles()
{
    for files in "${file[@]}"
    do
        testing
    done
}

for flag1 in i v c l n h s o
do
    for patterns in "${pattern[@]}"
    do
        flags="-$flag1"
        getfiles 
    done
done

for flag1 in i v c l n h s o
do
    for flag2 in i v c l n h s o
    do
        if [ $flag1 != $flag2 ]
        then
            for patterns in "${pattern[@]}"
            do
                flags="-$flag1$flag2"
                getfiles 
            done
        fi
    done
done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
