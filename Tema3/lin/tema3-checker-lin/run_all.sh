#!/bin/bash

first_test=1
last_test=33
script=run_test

# Call init to set up testing environment
./_test/"$script" init

for i in $(seq $first_test $last_test); do
    ./_test/"$script" $i
done | tee results.txt

cat results.txt | grep '\[.*\]$' | awk -F '[] /[]+' '
BEGIN {
    sum=0
}

{
	sum += $(NF-2);
}

END {
    printf "\n%66s  [%02d/90]\n", "Total:", sum;
}'

# Cleanup testing environment
./_test/"$script" cleanup
rm -f results.txt
