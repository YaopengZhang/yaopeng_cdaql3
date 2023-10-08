#!/usr/bin/env python
import time,subprocess

# hL1ACCP:     10 16  4*32 + 16 = 144
# hTRIG5:      11 14  5*32 + 14 = 174
# hTRIG6:      11 15  5*32 + 15 = 175

def getScalars_hms():
    zvals_hms=[]
    pzvals_hms=[]
    chan_hms=[]
    
    lines = subprocess.check_output(["getscalers","hcvme05"])
    for line in lines.splitlines():
        info = line.split()
        info[0] = info[0].replace(':', '')
        if info[0].isdigit():
            chan_hms.append(int (info[0])+1)
            info_data=info[1].split("(")
            info_data[1]=info_data[1].replace(')','')
            data = int(info_data[0])+int(info_data[1])*65536*65536
            zvals_hms.append(float(data))

    pzvals_hms.append(zvals_hms[144]) # hL1ACCP
    pzvals_hms.append(zvals_hms[174]) # hTRIG5
    pzvals_hms.append(zvals_hms[175]) # hTRIG6
    return pzvals_hms

def main():
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
            ps[i] = -1.
        elif ps[i] == 0:
            ps[i] = 1.
        else:
            ps[i] = 2**(ps[i]-1.)+1.
        print(ps[i])

    zvals_hms = getScalars_hms()
    time.sleep(5)
    zvals_hms2 = getScalars_hms()

    print(zvals_hms2[0]-zvals_hms[0])
    print(zvals_hms2[1]-zvals_hms[1])
    print(zvals_hms2[2]-zvals_hms[2])
    hmsT5 = 0.
    hmsT6 = 0.
    if ps[4] == -1:
        hmsT5 = 0.
        print(hmsT5)
    else:
        hmsT5 = (zvals_hms2[0]-zvals_hms[0])/(zvals_hms2[1]-zvals_hms[1])*ps[4]
    if ps[5] == -1:
        hmsT6 = 0.
        print(hmsT6)
    else:
        hmsT6 = (zvals_hms2[0]-zvals_hms[0])/(zvals_hms2[2]-zvals_hms[2])*ps[5]


    


if __name__=='__main__': main()