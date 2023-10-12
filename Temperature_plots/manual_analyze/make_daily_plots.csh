#!/bin/csh

# source /u/apps/root/6.08.00/setroot_CUE.csh

# root -l -b -q /home/cdaq/yaopeng/Temperature_plots/manual_analyze/Analyze.C

# sleep 5

set previous_date=`cat /home/cdaq/yaopeng/Temperature_plots/manual_analyze/date.txt`

/site/ace/certified/apps/bin/logentry \
-cert /home/cdaq/.elogcert \
-t "NPS Temperature plots for ${previous_date}" \
-e yaopeng \
-l HCLOG \
-a "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/plots_hclog/temp_average_2D.pdf" \
-a "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/plots_hclog/temp_std_2D.pdf" \
-a "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/plots_hclog/temp_front_1D_array.pdf" \
-a "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/plots_hclog/temp_back_1D_array.pdf" \
-a "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/plots_hclog/temp_front_1D.pdf" \
-a "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/plots_hclog/temp_back_1D.pdf" \
-a "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/plots_hclog/temp_chiller_readout.pdf" \
-a "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/plots_hclog/Beam_status.pdf" \
-a "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/plots_hclog/HV_status.pdf" \
-b "/home/cdaq/yaopeng/Temperature_plots/manual_analyze/log_content.txt" \

# set current_date=`date +"%Y-%m-%d"`
# echo "$current_date" > /home/cdaq/yaopeng/Temperature_plots/manual_analyze/date.txt