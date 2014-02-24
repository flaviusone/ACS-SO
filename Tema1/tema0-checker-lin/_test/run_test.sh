#!/bin/bash

#
# Tema0 Test Suite
#
# 2012, Operating Systems
#

# ----------------- General declarations and util functions ------------------ #

INPUT_DIR=_test/inputs
REF_DIR=_test/ref
OUT_DIR=_test/outputs
EXEC_NAME=./tema0
DF=-BEbw
max_points=90
# Enable/disable exiting when program fails.
EXIT_IF_FAIL=0
# Enable/disable debug (1/0).
DEBUG_=0

DEBUG()
{
	if test "x$DEBUG_" = "x1"; then
		$@ 1>&2
	fi
}

print_header()
{
	header="${1}"
	header_len=${#header}
	printf "\n"
	if [ $header_len -lt 71 ]; then
		padding=$(((71 - $header_len) / 2))
		for ((i = 0; i < $padding; i++)); do
			printf " "
		done
	fi
	printf "= %s =\n\n" "${header}"
}

test_do_fail()
{
	printf "failed  [ 0/%02d]\n" "$max_points"
	if test "x$EXIT_IF_FAIL" = "x1"; then
		exit 1
	fi
}

test_do_pass()
{
	printf "passed  [%02d/%02d]\n" "$points" "$max_points"
}

# Compares to files and prints the first 10
# lines if the files differ
function compare()
{
	diff $DF $1 $2 > __result
	ret=$?
	if [ $ret != 0 ] ; then
		echo "$1 vs $2:"
		cat __result | head -n 10
	fi
	rm -f __result
	return $ret
}

basic_test()
{
	$@
	res=$?
    printf "%02d) %s" "$test_index" "$description"

    for ((i = 0; i < 56 - ${#description}; i++)); do
        printf "."
    done

    if test $res -eq 0; then
        test_do_pass "$points"
    else
        test_do_fail "$points"
    fi
}

# ---------------------------------------------------------------------------- #

# ----------------- Init and cleanup tests ----------------------------------- #

init_test()
{
	input_f=$INPUT_DIR"/test"$test_index".in"
	ref_f=$REF_DIR"/test"$test_index".ref"
	out_f=$OUT_DIR"/test"$test_index".out"
}

cleanup_test()
{
	rm -f $out_f
}

init_world()
{
	print_header "Testing - HashTable"
	mkdir -p $OUT_DIR
}

cleanup_world()
{
	rm -rf $OUT_DIR &> /dev/null
}

# ---------------------------------------------------------------------------- #

# ----------------- Test Suite ----------------------------------------------- #

test_add()
{
	init_test
	$EXEC_NAME 256 $input_f > $out_f
	basic_test compare $out_f $ref_f
	cleanup_test
}

test_remove()
{
	init_test
	$EXEC_NAME 256 $input_f > $out_f
	basic_test compare $out_f $ref_f
	cleanup_test
}

test_remove_clear()
{
	init_test
	$EXEC_NAME 256 $input_f > $out_f
	basic_test compare $out_f $ref_f
	cleanup_test
}

test_stdin_read()
{
	init_test
	$EXEC_NAME 256 < $input_f > $out_f
	basic_test compare $out_f $ref_f
	cleanup_test
}

test_double()
{
	init_test
	$EXEC_NAME 256 $input_f > $out_f
	basic_test compare $out_f $ref_f
	cleanup_test
}

test_halve_redirects()
{
	init_test
	FILE1="hash.out"
	REF_FILE1=$REF_DIR"/hash.ref"
	FILE2="buckets.out"
	REF_FILE2=$REF_DIR"/buckets.ref"

	$EXEC_NAME 1024 $input_f > $out_f
	args="compare $FILE1 $REF_FILE1 && compare $FILE2 $REF_FILE2 &&
		compare $out_f $ref_f"
	basic_test eval $args

	rm $FILE1 $FILE2
	cleanup_test
}

test_stress1()
{
	init_test
	$EXEC_NAME 512 $input_f > $out_f
	basic_test compare $out_f $ref_f
	cleanup_test
}

test_stress2()
{
	init_test
	$EXEC_NAME 16384 $input_f > $out_f
	basic_test compare $out_f $ref_f
	cleanup_test
}

test_stress3()
{
	init_test
	$EXEC_NAME 16384 $input_f > $out_f
	basic_test compare $out_f $ref_f
	cleanup_test
}

test_fun_array=(											\
	test_add "Test add"									10	\
	test_remove "Test remove"							10	\
	test_remove_clear "Test remove and clear"			10	\
	test_stdin_read "Test read from stdin"				10	\
	test_double "Test double"							10	\
	test_halve_redirects "Test halve redirects"			10	\
	test_stress1 "Test stress 1"						10	\
	test_stress2 "Test stress 2"						10	\
	test_stress3 "Test stress 3"						10	\
	)

# ---------------------------------------------------------------------------- #

# ----------------- Run test ------------------------------------------------- #

if test $# -ne 1; then
	echo "Usage: $0 test_number | init | cleanup" 1>&2
	exit 1
fi

test_index=$1

if test $test_index == "init"; then
	init_world
	exit 0
fi

if test $test_index == "cleanup"; then
	cleanup_world
	exit 0
fi

arr_index=$((($test_index - 1) * 3))
last_test=$((${#test_fun_array[@]} / 3))
description=${test_fun_array[$(($arr_index + 1))]}
points=${test_fun_array[$(($arr_index + 2))]}

if test "$test_index" -gt "$last_test" -o "$arr_index" -lt 0; then
	>--->---echo "Error: Test index is out range (1 < test_index <=
	>$last_test)." 1>&2
	>--->---exit 1
fi

# Run proper function
${test_fun_array[$(($arr_index))]}

exit 0
