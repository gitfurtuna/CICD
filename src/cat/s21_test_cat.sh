#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="s21_cat.txt"
echo "" > log.txt

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.log
          cat $TEST1 > cat.log
          DIFF_RES="$(diff -s s21_cat.log cat.log)"
          if [ "$DIFF_RES" == "Files s21_cat.log and cat.log are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.log cat.log
done

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $TEST_FILE"
          # echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.log
          cat $TEST1 > cat.log
          DIFF_RES="$(diff -s s21_cat.log cat.log)"
          if [ "$DIFF_RES" == "Files s21_cat.log and cat.log are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.log cat.log
        fi
  done
done

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
      for var3 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="$var $var2 $var3 $TEST_FILE"
          # echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.log
          cat $TEST1 > cat.log
          DIFF_RES="$(diff -s s21_cat.log cat.log)"
          if [ "$DIFF_RES" == "Files s21_cat.log and cat.log are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.log cat.log

        fi
      done
  done
done

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
      for var3 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
      do
          for var4 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              TEST1="$var $var2 $var3 $var4 $TEST_FILE"
              # echo "$TEST1"
              ./s21_cat $TEST1 > s21_cat.log
              cat $TEST1 > cat.log
              DIFF_RES="$(diff -s s21_cat.log cat.log)"
              if [ "$DIFF_RES" == "Files s21_cat.log and cat.log are identical" ]
                then
                  (( COUNTER_SUCCESS++ ))
                else
                  echo "$TEST1" >> log.txt
                  (( COUNTER_FAIL++ ))
              fi
              rm s21_cat.log cat.log

            fi
          done
      done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

if [ $COUNTER_FAIL -ne 0 ]
then 
  exit 1
fi
