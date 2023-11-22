#!/bin/bash

# myData -b "2023-10-01 00:00:00" -e "2023-10-01 23:59:59" hchv30:00:000:VMon  > test.txt
# myData -b "2023-10-01 00:00:00" -e "2023-10-01 23:59:59" hcnps_intlk_cz_t_back_1  > ./data/chart-1.txt

previous_date=$(cat "/home/cdaq/yaopeng/Temperature_plots/date.txt")
IFS="-" read -ra date_parts <<< "$previous_date"
year="${date_parts[0]}"
month="${date_parts[1]}"
day="${date_parts[2]}"
echo "$previous_date"
echo "Year: $year"
echo "Month: $month"
echo "Day: $day"

/home/cdaq/bin/myData -b "$previous_date 00:00:00" -e "$previous_date 23:59:59" ibcm1 > /home/cdaq/yaopeng/Temperature_plots/data/chart-Beam.txt
/home/cdaq/bin/myData -b "$previous_date 00:00:00" -e "$previous_date 23:59:59" hcnps_intlk_chiller_CZ_read_chiller_temp > /home/cdaq/yaopeng/Temperature_plots/data/chart-CZ.txt
/home/cdaq/bin/myData -b "$previous_date 00:00:00" -e "$previous_date 23:59:59" hcnps_intlk_chiller_EZ_read_chiller_temp > /home/cdaq/yaopeng/Temperature_plots/data/chart-EZ.txt
/home/cdaq/bin/myData -b "$previous_date 00:00:00" -e "$previous_date 23:59:59" hchv30:00:000:VMon > /home/cdaq/yaopeng/Temperature_plots/data/chart-HV.txt

for num in {1..56}
# for num in {1..2}
do
    echo "---------------------------------------------------"
    echo "Getting data for hcnps_intlk_cz_t_back_${num}"
    var1="hcnps_intlk_cz_t_back_${num}"
    /home/cdaq/bin/myData -b "$previous_date 00:00:00" -e "$previous_date 23:59:59" ${var1} > /home/cdaq/yaopeng/Temperature_plots/data/chart-${num}.txt
    new_num=$((num + 56))
    echo "Getting data for hcnps_intlk_cz_t_front_${num}"
    var2="hcnps_intlk_cz_t_front_${num}"
    /home/cdaq/bin/myData -b "$previous_date 00:00:00" -e "$previous_date 23:59:59" ${var2} > /home/cdaq/yaopeng/Temperature_plots/data/chart-${new_num}.txt
done
