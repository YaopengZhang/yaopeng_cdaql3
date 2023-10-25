#!/usr/bin/env python
import time,subprocess


def getScalars():
    zvals=[]
    pzvals=[]
    chan=[]
    overflow=[]
    try:
        lines = subprocess.check_output(["./getscalers","hcvme05"])
        for line in lines.splitlines():
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                temp  = info[1].rpartition('(')[0]
                temp2 =  info[1].rpartition('(')[2]
                temp3 =  temp2.rpartition(')')[0]
                overflow.append(int(temp3))
                zvals.append(float(temp))
        
        pzvals.append(zvals[223])   # 6000000 Hz clock
        pzvals.append(zvals[217])
        pzvals.append(zvals[170])
        pzvals.append(zvals[171])
        pzvals.append(zvals[172])
        pzvals.append(zvals[174])   #hTRIG5
        pzvals.append(zvals[175])   #hTRIG6
        pzvals.append(zvals[144])   #hL1ACCP
        return [pzvals,overflow]
    except subprocess.CalledProcessError as e:
        return [None,None]


def makeTime():
    datime=TDatime()
    return '%d/%d/%d %.2d:%.2d:%.2d'%(datime.GetDay(),
             datime.GetMonth(),
             datime.GetYear(),
             datime.GetHour(),
             datime.GetMinute(),
             datime.GetSecond())



def main():


    timeCul = 0
    timeCulCh = 0
    chargeCul = 0
    FracTime = 0
    aveI = 0
    TRIG5Cul = 0
    TRIG6Cul = 0
    L1ACCPCul = 0
    RunStatus = 0
    while True:
        with open('/net/cdaqfs1/cdaqfs-coda-home/coda/coda/config_files/HMS/default.flags', 'r') as file:
            lines_hms = file.readlines()
        ps=[]
        for line in lines_hms:
            if line.startswith(';'):
                continue
            parameter_dict = {}
            parts = line.split(',')
            for part in parts:
                if '=' in part:
                    param_name, param_value = part.split('=')
                    parameter_dict[param_name] = param_value
            ps1_value = parameter_dict.get('ps1')
            ps2_value = parameter_dict.get('ps2')
            ps3_value = parameter_dict.get('ps3')
            ps4_value = parameter_dict.get('ps4')
            ps5_value = parameter_dict.get('ps5')
            ps6_value = parameter_dict.get('ps6')

        ps.append(int(ps1_value))
        ps.append(int(ps2_value))
        ps.append(int(ps3_value))
        ps.append(int(ps4_value))
        ps.append(int(ps5_value))
        ps.append(int(ps6_value))

        for i in range(6):
            if ps[i] == -1:
                ps[i] = -1
            elif ps[i] == 0:
                ps[i] = 1.
            else:
                ps[i] = 2**(ps[i]-1.)+1.
            # print(ps[i])
        
        [zvals,overflow1] = getScalars()
        time.sleep(5)
        [zvals2,overflow2] = getScalars()
        if zvals is None or zvals2 is None:
            continue
        
        diff = zvals2[0]-zvals[0]
        RunStatus = subprocess.check_output(["caget","-t","hcCOINRunInProgress" ])

        if diff>0 and int(RunStatus)==1:
          time1 = (zvals2[0]-zvals[0])/1000000. # 1/60 second
          current = ((zvals2[1]-zvals[1])/time1+1605.)/9570.
          t1rate=  (zvals2[2]-zvals[2])/time1/1000.
          t2rate=  (zvals2[3]-zvals[3])/time1/1000.
          t3rate=  (zvals2[4]-zvals[4])/time1/1000.
          TRIG5= zvals2[5]-zvals[5]
          TRIG6= zvals2[6]-zvals[6]
          L1ACCP= zvals2[7]-zvals[7]
          charge = 0
          timeCul = timeCul + time1/60. # second
          if current>2. : 
              charge = current*time1
              chargeCul = chargeCul + charge/1000.
              timeCulCh = timeCulCh + time1/60.
              TRIG5Cul = TRIG5Cul + TRIG5
              TRIG6Cul = TRIG6Cul + TRIG6
              L1ACCPCul = L1ACCPCul + L1ACCP
          if timeCulCh>0 :  aveI=chargeCul/(timeCulCh*60)*1000
          if timeCul>0 : FracTime= timeCulCh/timeCul*100
          with open('ChargeCount_output.txt', 'w') as file:
            output_string = 'Total Time: {0:7.2f} min\nBeam on time(current>2uA): {1:7.2f} min\nTime fraction: {2:5.1f} %\nTotal Charge(current>2uA): {3:7.2f} mC\nAverage I(current>2uA): {4:7.2f} uA\n'.format(timeCul,timeCulCh,FracTime,chargeCul,aveI)
            file.write(output_string)
            if ps[4] != -1 and TRIG5Cul>0:
                output_string = '\n<b>TI Live Time (current>2uA)</b> \nhL1ACCP/hTRIG5(after ps): {0:7.2f} % \n'.format(L1ACCPCul*1./(TRIG5Cul*1.)*100.*ps[4])
                file.write(output_string)
            if ps[5] != -1 and TRIG6Cul>0:
                output_string = '\n<b>TI Live Time (current>2uA)</b> \nhL1ACCP/hTRIG6(after ps): {0:7.2f} % \n'.format(L1ACCPCul*1./(TRIG6Cul*1.)*100.*ps[5])
                file.write(output_string)
        else :
          if int(RunStatus)==0:
            timeCul = 0
            chargeCul = 0
            timeCulCh = 0
            TRIG5Cul = 0
            TRIG6Cul = 0
            L1ACCPCul = 0

if __name__=='__main__': main()


