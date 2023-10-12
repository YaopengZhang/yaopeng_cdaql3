#!/usr/bin/env python
import time,subprocess,multiprocessing

# LV_Flag=0 # LV-ON 1; LV-OFF 0
LV_Flag=1 # LV-ON 1; LV-OFF 0 A
# Gain_Flag=0 # Gain=12 1; Gain=1 0
Gain_Flag=1 # Gain=12 1; Gain=1 0
XVALS,YVALS=[],[]
START=0
NCHAN=1080
# NCHAN=241
Pedestals=[]
Curr=[0.0]*NCHAN

# nps-vme1  493 = 15*16*2+13
# nps-vme2  493 = 15*16*2+13
# nps-vme3  525 = 16*16*2+13  (slot 20 scintillators)
# nps-vme4  493 = 15*16*2+13
# nps-vme4  269 = 8*16*2+13

def getScalars():
    zvals=[]
    XVALS[:] = []
    YVALS[:] = []
    chan=[]
    pchan=[]
    pzvals=[]
    time_clock=[]
    time_clock_fast=[]

    try:
        lines = subprocess.check_output(["getscalers","nps-vme1"])
        icount=0
        icount_=0
        T_fast=0
        for line in lines.splitlines():
            icount_+=1 
            if icount_<243: continue
            if icount>=240: 
                if icount_==483: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast = float(int(TT[0])+int(TT[1])*65536*65536)
                if icount_==484: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast += float(int(TT[0])+int(TT[1])*65536*65536)
                        for i in range(0,240):
                            time_clock_fast.append(T_fast)
                if icount_==496: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,240):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            icount+=1 
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
                # data = (int(info_data[1])<<32)|int(info_data[0])
                data = int(info_data[0])+int(info_data[1])*65536*65536
                zvals.append(float(data))

        lines2 = subprocess.check_output(["getscalers","nps-vme2"])
        icount2=0
        icount2_=0
        T_fast2=0
        for line in lines2.splitlines():
            icount2_+=1 
            if icount2_<243: continue
            if icount2>=240: 
                if icount2_==483: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast2 = float(int(TT[0])+int(TT[1])*65536*65536)
                if icount2_==484: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast2 += float(int(TT[0])+int(TT[1])*65536*65536)
                        for i in range(0,240):
                            time_clock_fast.append(T_fast2)
                if icount2_==496: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,240):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            icount2+=1 
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
                # data = (int(info_data[1])<<32)|int(info_data[0])
                data = int(info_data[0])+int(info_data[1])*65536*65536
                zvals.append(float(data))

        lines3 = subprocess.check_output(["getscalers","nps-vme3"])
        icount3=0
        icount3_=0
        T_fast3=0
        for line in lines3.splitlines():
            icount3_+=1 
            if icount3_<259: continue
            if icount3>=240: 
                if icount3_==515: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast3 = float(int(TT[0])+int(TT[1])*65536*65536)
                if icount3_==516: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast3 += float(int(TT[0])+int(TT[1])*65536*65536)
                        for i in range(0,240):
                            time_clock_fast.append(T_fast3)
                if icount3_==528: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,240):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            icount3+=1 
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
                # data = (int(info_data[1])<<32)|int(info_data[0])
                data = int(info_data[0])+int(info_data[1])*65536*65536
                zvals.append(float(data))

        lines4 = subprocess.check_output(["getscalers","nps-vme4"])
        icount4=0
        icount4_=0
        T_fast4=0
        for line in lines4.splitlines():
            icount4_+=1 
            if icount4_<243: continue
            if icount4>=240: 
                if icount4_==483: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast4 = float(int(TT[0])+int(TT[1])*65536*65536)
                if icount4_==484: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast4 += float(int(TT[0])+int(TT[1])*65536*65536)
                        for i in range(0,240):
                            time_clock_fast.append(T_fast4)
                if icount4_==496: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,240):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            icount4+=1 
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
                # data = (int(info_data[1])<<32)|int(info_data[0])
                data = int(info_data[0])+int(info_data[1])*65536*65536
                zvals.append(float(data))

        lines5 = subprocess.check_output(["getscalers","nps-vme5"])
        icount5=0
        icount5_=0
        T_fast5=0
        for line in lines5.splitlines():
            icount5_+=1 
            if icount5_<131: continue
            if icount5>=120:
                if icount5_==259: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast5 = float(int(TT[0])+int(TT[1])*65536*65536)
                if icount5_==260: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        T_fast5 += float(int(TT[0])+int(TT[1])*65536*65536)
                        for i in range(0,240):
                            time_clock_fast.append(T_fast5)
                if icount5_==272: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,120):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            icount5+=1 
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
                # data = (int(info_data[1])<<32)|int(info_data[0])
                data = int(info_data[0])+int(info_data[1])*65536*65536
                zvals.append(float(data))

        ix,iy=1,1
        for ii in range (len(zvals)):
            if ii>=START:
                if ii==START+NCHAN: break
                XVALS.append(31-ix)
                YVALS.append(iy)
                pzvals.append(zvals[ii])
                pchan.append(ii-START+1)
                #print pchan[ii-START],
                #print pzvals[ii-START],
                #print XVALS[ii-START],
                #print YVALS[ii-START]
            
                if pchan[ii-START]==30*iy:
                    ix=0
                    iy+=1
                ix+=1 
        #print 'EndEvent'
        #print len(pzvals),
        #print len(XVALS),
        #print len(YVALS)       
        return [pzvals,time_clock,time_clock_fast]
    except subprocess.CalledProcessError as e:
        return [None, None, None]

def Read_Pedestals():
    global Pedestals
    global LV_Flag
    Pedestals_file_path='Pedestals.txt'
    if LV_Flag==1: Pedestals_file_path='Pedestals_LV_ON.txt'
    else: Pedestals_file_path='Pedestals_LV_OFF.txt'
    with open(Pedestals_file_path,'r') as file_Pedestals:
        count_Pedestals=0
        for line in file_Pedestals:
            count_Pedestals+=1
            if count_Pedestals<=1080: Pedestals.append(float(line)*1000.0)

def execute_caput(variable_name, value):
    command = 'caput "{}" {:.4f}'.format(variable_name, value)
    subprocess.call(command, shell=True)
            

def main():

    Read_Pedestals()

    global Gain_Flag
    gain_factor=1.
    if Gain_Flag==1: gain_factor=12.

    while True:

        [zvals,time1,time_fast1] = getScalars()
        time.sleep(5)
        [zvals2,time2,time_fast2] = getScalars()
        if zvals is None or zvals2 is None:
            continue

        t_diff = []
        t_diff_fast = []

        # file = open('Pedestals_channel_0.txt','a')
        flag = 1
        for ii in range(len(zvals)):
            t_diff.append((time2[ii]-time1[ii])/60.0)
            if t_diff[ii]<0.1:
                t_diff[ii] = 1.
                flag = 0
            if zvals[ii]<1000. or zvals2[ii]<1000.:
                flag = 0
            Current_Value = ((zvals2[ii]-zvals[ii])/t_diff[ii]/5.12e7-Pedestals[ii])/gain_factor
            # if Current_Value<0: Current_Value=0

            t_diff_fast.append((time_fast2[ii]-time_fast1[ii])*256*30*1e-9)
            if t_diff_fast[ii]<0.1: t_diff_fast[ii] = 1.
            Current_Value_fast = ((zvals2[ii]-zvals[ii])/t_diff_fast[ii]/5.12e7-Pedestals[ii])/gain_factor
            # if Current_Value_fast<0: Current_Value_fast=0

            Curr[ii] = Current_Value
            # Curr[ii] = float(ii)*1.0
        if flag==1:
            pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
            # ii from 0-1079
            for i in range(1080):
                variable_name = 'hcnps_anodeCurr:{}'.format(i)
                # execute_caput(variable_name,Curr[i])
                pool.apply_async(execute_caput, (variable_name, Curr[i]))
            pool.close()
            pool.join()
            print("caput all Finished")
   

if __name__=='__main__': main()
