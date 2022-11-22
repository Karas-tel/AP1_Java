#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""
STR="FLAGS FILES"

declare -a file=(
" cat_tests\/file_1 "
" cat_tests\/file_2 "
" cat_tests\/file_3 "
" cat_tests\/file_4 "
)

declare -a flag=(
" -b "
" -e "
" -n "
" -s "
" -t "
" -be "
" -en "
" -ns "
" -st "
" -tb "
" -bn "
" -es "
" -nt "
" -sb "
" -te "
# " --number-nonblank"
# " -E "
# " --number "
# " --squeeze-blank "
# " -T "
)

testing()
{
    str=$(echo $STR | sed "s/FLAGS/$flags/g;s/FILES/$files/g")
    ./s21_cat $str > s21_cat_test.log
    cat $str > cat_test.log
    DIFF="$(diff s21_cat_test.log cat_test.log)"
    (( COUNTER++ ))
 
    if [ "$DIFF" == "" ]
    then
      (( SUCCESS++ ))
      echo "$FAIL $SUCCESS $COUNTER success cat $str"
    else
      (( FAIL++ ))
      echo "$FAIL $SUCCESS $COUNTER fail cat $str"
    fi
    rm s21_cat_test.log cat_test.log
}

getfiles()
{
    for files in "${file[@]}"
    do
        testing
    done
}

for flags in "${flag[@]}"
do
    getfiles 
done


echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
