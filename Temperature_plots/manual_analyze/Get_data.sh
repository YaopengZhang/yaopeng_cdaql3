#!/bin/bash

# myData -b "2023-10-01 $time_start" -e "2023-10-01 $time_end" hchv30:00:000:VMon  > test.txt
# myData -b "2023-10-01 $time_start" -e "2023-10-01 $time_end" hcnps_intlk_cz_t_back_1  > ./data/chart-1.txt

previous_date=$(cat "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/date.txt")
IFS="-" read -ra date_parts <<< "$previous_date"
year="${date_parts[0]}"
month="${date_parts[1]}"
day="${date_parts[2]}"
echo "$previous_date"
echo "Year: $year"
echo "Month: $month"
echo "Day: $day"

time_start="03:00:00"
time_end="16:00:00"

/home/cdaq/bin/myData -b "$previous_date $time_start" -e "$previous_date $time_end" hcnps_intlk_chiller_CZ_read_chiller_temp > /home/cdaq/yaopeng/Temperature_plots/manual_analyze/data/chart-CZ.txt
/home/cdaq/bin/myData -b "$previous_date $time_start" -e "$previous_date $time_end" hcnps_intlk_chiller_EZ_read_chiller_temp > /home/cdaq/yaopeng/Temperature_plots/manual_analyze/data/chart-EZ.txt
/home/cdaq/bin/myData -b "$previous_date $time_start" -e "$previous_date $time_end" hchv30:00:000:VMon > /home/cdaq/yaopeng/Temperature_plots/manual_analyze/data/chart-HV.txt
/home/cdaq/bin/myData -b "$previous_date $time_start" -e "$previous_date $time_end" ibcm1 > /home/cdaq/yaopeng/Temperature_plots/manual_analyze/data/chart-Beam.txt

for num in {1..56}
do
    echo "---------------------------------------------------"
    echo "Getting data for hcnps_intlk_cz_t_back_${num}"
    var1="hcnps_intlk_cz_t_back_${num}"
    /home/cdaq/bin/myData -b "$previous_date $time_start" -e "$previous_date $time_end" ${var1} > /home/cdaq/yaopeng/Temperature_plots/manual_analyze/data/chart-${num}.txt
    new_num=$((num + 56))
    echo "Getting data for hcnps_intlk_cz_t_front_${num}"
    var2="hcnps_intlk_cz_t_front_${num}"
    /home/cdaq/bin/myData -b "$previous_date $time_start" -e "$previous_date $time_end" ${var2} > /home/cdaq/yaopeng/Temperature_plots/manual_analyze/data/chart-${new_num}.txt
done
