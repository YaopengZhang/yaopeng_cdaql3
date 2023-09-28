# source /apps/root/PRO/setroot_CUE.csh

# line="480: 804925838(10)"
# info=line.split()
# print(info)

# info_data=info[1].split("(")
# print(info_data)

# info_data[1]=info_data[1].replace(')','')
# print(info_data)
# print(info_data[0])
# print(info_data[1])
# print(info_data[0].isdigit())
# print(info_data[1].isdigit())

# string1=bin(int(info_data[1]))
# string2=bin(int(info_data[0]))
# print(string1)
# print(string2)
# print(int(info_data[1]))
# print(int(info_data[0]))

# data = (int(info_data[1])<<32)|int(info_data[0])
# print(bin(data))
# print(data)
# print(float(data))

# icount=0
# for i in range(0,10):
#     # print(i)
#     icount+=1
# print(icount)

# a=[0.0]*10
# print(a)
# a=[10.0]*10
# file = open('Pedestals.txt','w')
# file.write(str(a[2]/2)+'\n')
# file.write(str(a[5]/2)+'\n')
# file.close()

# with open('Pedestals.txt','r') as file_Pedestals:
#     count_Pedestals=0
#     for line in file_Pedestals:
#         count_Pedestals+=1
#         if count_Pedestals<=1080: print(float(line))

# import subprocess

# for i in range(1080):
#     variable_name = f'nps_{i}'
#     value = 3.14
#     command = f'caput {variable_name} {value:.2f}'
#     subprocess.run(command, shell=True)

# variable_name = 'cvxwrksHost:ai1'
# variable_name = 'cvxwrksHost:ai2'
# variable_name = 'cvxwrksHost:ai3'
# variable_name = 'cvxwrksHost:aiExample'
# variable_name = 'cvxwrksHost:aiExample1'
# variable_name = 'cvxwrksHost:aiExample2'
# variable_name = 'cvxwrksHost:aiExample3'
# variable_name = 'cvxwrksHost:aSubExample'
# variable_name = 'cvxwrksHost:calc1'
# variable_name = 'cvxwrksHost:calc2'
# variable_name = 'cvxwrksHost:calc3'
# variable_name = 'cvxwrksHost:calcExample'
# variable_name = 'cvxwrksHost:calcExample1'
# variable_name = 'cvxwrksHost:calcExample2'
# variable_name = 'cvxwrksHost:calcExample3'
# variable_name = 'cvxwrksHost:compressExample'
# variable_name = 'cvxwrksHost:subExample'
# variable_name = 'cvxwrksHost:xxxExample'
# value = 3.1415
# command = f'caput {variable_name} {value:.2f}'
# subprocess.run(command, shell=True)

# ii=0
# variable_name = f'hcnps_anodeCurr:{ii}'
# Current_Value = 3.1415
# command = f'caput {variable_name} {Current_Value:.2f}'
# subprocess.run(command, shell=True)

# ii=0
# variable_name = 'hcnps_anodeCurr:{}'.format(ii)
# Current_Value = 3.1415
# command = 'caput "{}" {:.2f}'.format(variable_name, Current_Value)
# subprocess.call(command, shell=True)

# for i in range(100): print(i)




import time,sys,os,argparse,atexit,subprocess

# LV_Flag=0 # LV-ON 1; LV-OFF 0
LV_Flag=1 # LV-ON 1; LV-OFF 0 A
# Gain_Flag=0 # Gain=12 1; Gain=1 0
Gain_Flag=1 # Gain=12 1; Gain=1 0
XVALS,YVALS=[],[]
START=0
NCHAN=1080
# NCHAN=241
Pedestals=[]

# nps-vme1  493 = 15*16*2+13
# nps-vme2  493 = 15*16*2+13
# nps-vme3  525 = 16*16*2+13  (slot 20 scintillators)
# nps-vme4  493 = 15*16*2+13
# nps-vme4  269 = 8*16*2+13
# 239 479
# 240 480
# 242 482
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
        Check = subprocess.check_output(["getscalers", "nps-vme1"])
    except subprocess.CalledProcessError as e:
        print("Error running getscalers for nps-vme1:", e)
        return [None, None, None]

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


def main():
    [zvals,time1,time_fast1] = getScalars()
    if zvals is None:
        print("None")
    else:
        print("success")
    
    # while True:
    #     data = getScalars()
    #     if data is None:
    #         continue  

if __name__ == "__main__":
    main()