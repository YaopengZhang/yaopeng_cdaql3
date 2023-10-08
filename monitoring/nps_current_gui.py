#!/usr/bin/env python
import time,sys,os,argparse,atexit,subprocess
import ROOT
from ROOT import TH2D,TH2I,gStyle,gPad,TPaveText,TCanvas, TF1
from ROOT import TArrow,TBox,TLine,TDatime,TText,TGFrame
from ROOT import gClient,TGMainFrame,TGVerticalFrame,TGWindow
from ROOT import TGHorizontalFrame,TGLayoutHints
from ROOT import TRootEmbeddedCanvas,TApplication
from ROOT import gROOT, TCanvas

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

def calcRates(rates,rates2,time_diff):
    global Gain_Flag
    gain_factor=1.
    if Gain_Flag==1: gain_factor=12.
    total,maximum=0.0,0.0
    for ii in range(len(XVALS)):
        zz,zz2,tt=rates[ii],rates2[ii],time_diff[ii]
        zz_diff=zz2-zz
        total+=((zz_diff)/tt/5.12e7-Pedestals[ii])/gain_factor
        if (((zz_diff)/tt/5.12e7-Pedestals[ii])/gain_factor)>maximum: maximum=(((zz_diff)/tt/5.12e7-Pedestals[ii])/gain_factor)
    return [total,maximum]

# def calcRates(rates,rates2,time_diff):
#     total,maximum=0.0,0.0
#     for ii in range(len(XVALS)):
#         zz,zz2,tt=rates[ii],rates2[ii],time_diff[ii]
#         total+=(zz2-zz)/tt/5.12e10
#         if (zz2-zz)/tt/5.12e10>maximum: maximum=(zz2-zz)/tt/5.12e10
#     return [total,maximum]

def setupHists(hhh):
    for hh in hhh:
        hh.SetStats(0)
        hh.GetXaxis().CenterLabels()
        hh.GetXaxis().SetNdivisions(30,0)
        hh.GetYaxis().CenterLabels()
        hh.GetYaxis().SetNdivisions(36,0)
        hh.GetYaxis().SetTickLength(0)
        hh.GetXaxis().SetTickLength(0)
        hh.GetYaxis().SetTitleOffset(0.5)
        hh.GetXaxis().SetTitleOffset(0.5)
        hh.SetMinimum(0.1)
        xx=0
        for ix in range(30):
            hh.GetXaxis().SetBinLabel(ix+1,'%d'%(29-xx))
            xx+=1
        yy=0
        for iy in range(36):
            hh.GetYaxis().SetBinLabel(iy+1,'%d'%(yy))
            yy+=1

def makeTime():
    datime=TDatime()
    return '%d/%d/%d %.2d:%.2d:%.2d'%(datime.GetDay(),
             datime.GetMonth(),
             datime.GetYear(),
             datime.GetHour(),
             datime.GetMinute(),
             datime.GetSecond())

def setupPaveTexts(pts):
    for pt in pts:
        pt.SetTextColor(1)
        pt.SetTextAngle(0)
        pt.SetFillColor(0)
        pt.SetBorderSize(0)
        pt.SetLineWidth(0)


#mf=ROOT.TGMainFrame(gClient.GetRoot(),1500,475)
mf=ROOT.TGMainFrame(0,1300,925)
gvf=TGVerticalFrame(mf,1300,925)
rec=TRootEmbeddedCanvas("ccc",gvf,1200,800)
rec2=TRootEmbeddedCanvas("ccc2",gvf,1200,25)
gvf.AddFrame(rec,TGLayoutHints(ROOT.kLHintsExpandX|ROOT.kLHintsTop))
gvf.AddFrame(rec2,TGLayoutHints(ROOT.kLHintsExpandX|ROOT.kLHintsBottom))
mf.AddFrame(gvf,TGLayoutHints(ROOT.kLHintsExpandX))
cc=rec.GetCanvas()
cc2=rec2.GetCanvas()
mf.SetEditable(0)
mf.SetWindowName('NPS CAL Anode Currents')
mf.MapSubwindows()
mf.Resize(1600,800)# resize to get proper frame placement
mf.MapWindow()
mf.SetCleanup(ROOT.kDeepCleanup)

def __atexit__():
    del cc2
    del cc
    del rec
    del rec2
    del gvf
    del mf

def main():

    cc.cd()
    cc.SetBorderMode(0)
    cc.SetFixedAspectRatio(1)
    cc.FeedbackMode(1)
    
    gStyle.SetOptStat(0)
    gStyle.SetGridStyle(1)
    gStyle.SetGridColor(11)
    hh=TH2D('hh',';X;Y',30,1,31,36,1,37)
    hi=TH2I('hi',';X;Y',30,1,31,36,1,37)
    setupHists([hh,hi])
    xax,yax=hh.GetXaxis(),hh.GetYaxis()
    hh.Draw('COLZ')
    hi.Draw('TEXTSAME')

    gPad.SetLogz()
    gPad.SetGrid(1,1)
    gPad.SetLeftMargin(0.05)
    gPad.SetRightMargin(0.12)
    
    tt1=TPaveText(0.05,0.94,0.22,1.0,'NDC')
    ttM=TPaveText(0.65,0.94,0.95,1,'NDC')
    tt_warning=TPaveText(0.65,0.91,0.95,0.94,'NDC')
    ttime=TPaveText(11,-1.5,20,-2.5)
    tchan=TPaveText(0,0,0.9,1)
    setupPaveTexts([tt1,ttM,tt_warning,ttime,tchan])
    ttM.SetTextColor(2)
    tt_warning.SetTextColor(2)
    
    ttt=TText()
    ttt.SetTextColor(1)
    ttt.SetTextSize(0.02)
    ttt.DrawText(25,-2.5,'Script maintained by Yaopeng Zhang <yaopeng@jlab.org>')
    if LV_Flag==1:ttt.DrawText(1,-2.5,'Subtracting pedestals read from <Pedestals_LV_ON.txt>')
    else: ttt.DrawText(0,-2.5,'Subtracting pedestals read from <Pedestals_LV_OFF.txt>')

    tt=TText()
    tt.SetTextSize(0.045)
    tt.SetTextColor(2)
    tt.DrawTextNDC(0.35,0.905,'NPS CAL Anode Currents')

    latex = ROOT.TLatex()
    latex.SetTextColor(1)
    latex.SetTextAngle(90)
    latex.SetTextSize(0.045)
    latex.DrawLatex(34.5,32,r'$\bm{\mu} A $')

    cc.cd()
    for xx in [ttM,tt_warning,tt1,ttime]: xx.Draw()
    cc2.cd()
    tchan.Draw('NDC')
    cc.cd()

    xmin,xmax=xax.GetXmin(),xax.GetXmax()
    ymin,ymax=yax.GetXmin(),yax.GetXmax()
   
    gPad.SetEditable(0)

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

        for ii in range(len(zvals)):
            t_diff.append((time2[ii]-time1[ii])/60.0)
            if t_diff[ii]<0.1: t_diff[ii] = 1.
            Current_Value = ((zvals2[ii]-zvals[ii])/t_diff[ii]/5.12e7-Pedestals[ii])/gain_factor
            if Current_Value<0: Current_Value=0

            t_diff_fast.append((time_fast2[ii]-time_fast1[ii])*256*30*1e-9)
            if t_diff_fast[ii]<0.1: t_diff_fast[ii] = 1.
            Current_Value_fast = ((zvals2[ii]-zvals[ii])/t_diff_fast[ii]/5.12e7-Pedestals[ii])/gain_factor
            if Current_Value_fast<0: Current_Value_fast=0

            hh.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),Current_Value)
            hi.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),Current_Value)
            # hh.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),(zvals2[ii]-zvals[ii])/t_diff[ii]/5.12e10)
            # hi.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),(zvals2[ii]-zvals[ii])/t_diff[ii]/5.12e10)
            # if ii==0: file.write(str((zvals2[ii]-zvals[ii])/t_diff[ii]/5.12e10)+'\n')
        # print('%.2f   %.2f'%(t_diff_fast[0],t_diff[ii]))
        # file.close()

        for xx in [ttime,ttM,tt_warning,tt1]: xx.Clear()
        [total,maximum]=calcRates(zvals,zvals2,t_diff)
        tt1.AddText('Total:  %.2f mA'%((total)/1000))
        ttM.AddText('MAX SINGLE Current = %.2f #muA'%(maximum))
        tt_warning.AddText('( Should < 30 #muA )')
        ttime.AddText(makeTime())
         
        if not gPad: sys.exit()

        #if gPad.GetEvent()==11:
         #   xy=pix2xy(gPad)
            #ee=ECAL.findChannelXY(xy[0],xy[1])
            #if ee:
         #   tchan.Clear()
            #tchan.AddText(printChannel(ee))
          #  cc2.Modified()
          #  cc2.Update()
        #elif gPad.GetEvent()==12:
         #   tchan.Clear()
          #  cc2.Modified()
           # cc2.Update()
    
   
        cc.Modified()
        cc.Update()

        time.sleep(1)
   

if __name__=='__main__': main()


