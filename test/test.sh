#!/bin/bash

# Test script for testing call_cost_calculator.
# Orhan Mehmedov
# http://mehmed.info
# License: GPL v3
# https://www.gnu.org/licenses/gpl.html

#!/bin/bash 

BIN=call_cost_calculator
BINDIR=../source/bin

RED='\033[1;31m'
NC='\033[0m' # No Color
GREEN='\033[0;32m'

#Take latest and greates version built:
cp $BINDIR/$BIN ./

if [ $? -ne 0 ]; then
	echo "Can not find latest build! Exiting test."
	exit 1
fi

clear

RES="0"

# 1 test case ID and description
# 2 subscriber info / call calculation context
# 3 call start date/tim
# 4 call end date/time
# 5 number called
# 6 expected result

TEST_IS_OK=1

function testcase
{
	header="$1"
	ctxfile="$2"
	callstart="$3"
	callend="$4"
	callnum="$5"
	expres="$6"
	
	echo $1 $2 $3 $4 $5 $6

	RES=$(./$BIN frontend=NO subscriber_account="${ctxfile}" call_start_date_time="${callstart}" call_end_date_time="${callend}" number_called="${callnum}")
	RETURNED=$?
	
	if [ $RETURNED -ne 0 ]; then
		printf "${RED}Returned status is not 0! (returned $RETURNED)$RES${NC}\n"
		TEST_IS_OK=0
	elif [[ $RES != ${expres} ]]; then
		printf "${RED}Failed: expected ${expres}, returned $RES${NC}\n"
		TEST_IS_OK=0
	else
		printf "${GREEN}SUCCESFULL!${NC}\n"
	fi
}

# 10 min x 0.95 + 0.33 = 9.83...
testcase "Test Case N1: Normal week call for 10 minutes" "./test_case_1.txt" "2016-06-06 10:10:00" "2016-06-06 10:20:00" "1234567890" "9.83"

# 10 min - 5 min = 5 x 0.95 + 0.33 = 5.08
testcase "Test Case N2: Normal weekend call for 10 minutes" "./test_case_2.txt" "2016-06-11 10:10:00" "2016-06-11 10:20:00" "1234567890" "5.08"

# 10 min free = 0.33 only
testcase "Test Case N3: Free minutes week call for 10 minutes" "./test_case_3.txt" "2016-06-06 10:10:00" "2016-06-06 10:20:00" "0664567890" "0.33"

# 10 min free = 0.33 only
testcase "Test Case N4: Free minutes weekend call for 10 minutes" "./test_case_4.txt" "2016-06-04 10:10:00" "2016-06-04 10:20:00" "0664567890" "0.33"

# 10 min 5 must be charged = 5 x 0.5 + 0.33 = 2.83
testcase "Test Case N5: Weekday home operator call but days since credit over after 5 min" "./test_case_5.txt" "2016-06-06 10:10:00" "2016-06-06 10:20:00" "0664567890" "2.83"

# 10 min 5 must be charged = 5 x 0.5 + 0.33 = 2.83
testcase "Test Case N6: Weekday home operator call but 5 free left" "./test_case_6.txt" "2016-06-08 10:10:00" "2016-06-08 10:20:00" "0664567890" "2.83"

# 10 min weekend free = 5 min -> 5 - 2 = 3 free weekend first 5 min free left => to be chraged 10-3 = 7 x 0.95 + 0.33 = 6.98
testcase "Test Case N7: Weekday normal call but in 2 min starts weekend" "./test_case_7.txt" "2016-06-03 23:58:00" "2016-06-04 00:08:00" "1234567890" "6.98"

# 10 min weekend free = 5 min -> only 2 min free => 10 - 2 = 8 x 0.95 + 0.33 = 7.93
testcase "Test Case N8: Weekend normal call but in 2 min weekend over" "./test_case_8.txt" "2016-06-05 23:58:00" "2016-06-06 00:08:00" "1234567890" "7.93"

# 10 min weekend free = 5 min -> only 2 min free => then 5 minutes used form free minutes -> 10 - (5+2) = 3 x 0.5 + 0.33 = 1.83
testcase "Test Case N9: Weekend home operator (with 5 minutes left) call but in 2 min weekend over" "./test_case_9.txt" "2016-06-05 23:58:00" "2016-06-06 00:08:00" "0664567890" "1.83"

# 10 min weekend free = 5 min -> only 2 min free => then 5 minutes used form free minutes -> 10 - (5+2) = 3 x 0.5 + 0.33 = 1.83
testcase "Test Case N10: Weekend home operator call but in 2 min weekend over then after 5 min credit time over (still has free minutes)" "./test_case_10.txt" "2016-06-05 23:58:00" "2016-06-06 00:08:00" "0664567890" "1.83"

# 10 min workweek for 1 min (free minutes), then 5 min first call at weekend then last 5 min charged = 5 x 0.5 + 0.33 = 2.83
testcase "Test Case N11: Workweek home operator call but in 1 min weekend starts and during first 5 (4) min - the time since credit over" "./test_case_11.txt" "2016-06-10 23:59:00" "2016-06-11 00:09:00" "0664567890" "2.83"

# 10 min 2 min free + 3 min weekend call (call alerady on going for 2 min) + 5 min free minutes = 0.33
testcase "Test Case N12: Workweek home operator call (7 min left) but in 2 min weekend starts than use free minutes again" "./test_case_12.txt" "2016-06-10 23:58:00" "2016-06-11 00:08:00" "0664567890" "0.33"

# 10 min 2 min free + 1 charged + 2 min free (weekend first 5 min - 3) - rest 5+1 min charged  = 6 x 0.5 + 0.33 = 
testcase "Test Case N13: Workweek home operator call (2 min left) but in 3 min weekend starts" "./test_case_13.txt" "2016-06-10 23:57:00" "2016-06-11 00:07:00" "0664567890" "3.33"

# 10 min x 0.95 + 0.33 = 9.83
testcase "Test Case N14: Test normal call for 10 min with time prior to 1970 - use 15 April 1966" "./test_case_14.txt" "1966-04-15 10:10:00" "1966-04-15 10:20:00" "1234567890" "9.83"

# 10 min x 0.95 + 0.33 = 9.83
testcase "Test Case N15: Test normal call for 10 min transition between 1969-1970" "./test_case_15.txt" "1969-12-31 23:55:00" "1970-01-01 00:05:00" "1234567890" "9.83"

if [ $TEST_IS_OK -eq 1 ]; then
	printf "\n${GREEN}ALL TESTS SUCCEEDED!${NC}\n"
else
	printf "${RED}THERE AT LEAST ONE TEST FAILED!${NC}\n"
fi

