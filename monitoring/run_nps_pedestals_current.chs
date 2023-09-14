#!/bin/csh


source /u/apps/root/6.08.00/setroot_CUE.csh
setenv PYTHONPATH $ROOTSYS/lib/
python -i nps_calculate_current_pedestal.py
