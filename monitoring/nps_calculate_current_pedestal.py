#!/usr/bin/env python
import time,sys,os,argparse,atexit,subprocess
import ROOT
from ROOT import TH2D,TH2I,gStyle,gPad,TPaveText,TCanvas, TF1
from ROOT import TArrow,TBox,TLine,TDatime,TText,TGFrame
from ROOT import gClient,TGMainFrame,TGVerticalFrame,TGWindow
from ROOT import TGHorizontalFrame,TGLayoutHints
from ROOT import TRootEmbeddedCanvas,TApplication
from ROOT import gROOT, TCanvas

XVALS,YVALS=[],[]
START=0
NCHAN=1080
# NCHAN=241
Pedestals=[0.0]*NCHAN

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

    lines = subprocess.check_output(["getscalers","nps-vme1"])
    icount=0
    icount_=0
    for line in lines.splitlines():
        icount_+=1 
        if icount_<243: continue
        if icount>=240: 
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
    for line in lines2.splitlines():
        icount2_+=1 
        if icount2_<243: continue
        if icount2>=240: 
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
    for line in lines3.splitlines():
        icount3_+=1 
        if icount3_<259: continue
        if icount3>=240: 
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
    for line in lines4.splitlines():
        icount4_+=1 
        if icount4_<243: continue
        if icount4>=240: 
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
    for line in lines5.splitlines():
        icount5_+=1 
        if icount5_<131: continue
        if icount5>=120: 
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
    return [pzvals,time_clock]


def calcRates(rates,rates2,time_diff):
    total,maximum=0.0,0.0
    for ii in range(len(XVALS)):
        zz,zz2,tt=rates[ii],rates2[ii],time_diff[ii]
        total+=(zz2-zz)/tt/5.12e7
        if (zz2-zz)/tt/5.12e7>maximum: maximum=(zz2-zz)/tt/5.12e7
    return [total,maximum]

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
    ttime=TPaveText(11,-1.5,20,-2.5)
    tchan=TPaveText(0,0,0.9,1)
    setupPaveTexts([tt1,ttM,ttime,tchan])
    ttM.SetTextColor(2)
    
    ttt=TText()
    ttt.SetTextColor(1)
    ttt.SetTextSize(0.02)
    ttt.DrawText(25,-2.5,'Script maintained by Yaopeng Zhang <yaopeng@jlab.org>')

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
    for xx in [ttM,tt1,ttime]: xx.Draw()
    cc2.cd()
    tchan.Draw('NDC')
    cc.cd()

    xmin,xmax=xax.GetXmin(),xax.GetXmax()
    ymin,ymax=yax.GetXmin(),yax.GetXmax()
   
    gPad.SetEditable(0)

    Cycles=0

    while True:
        Cycles+=1
        print(Cycles)

        [zvals,time1] = getScalars()
        time.sleep(20)
        [zvals2,time2] = getScalars()
        t_diff = []
        for ii in range(len(zvals)):
            t_diff.append((time2[ii]-time1[ii])/60.0)
            if t_diff[ii]<0.1: t_diff[ii] = 1.
            hh.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),(zvals2[ii]-zvals[ii])/t_diff[ii]/5.12e7)
            hi.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),(zvals2[ii]-zvals[ii])/t_diff[ii]/5.12e7)
            Pedestals[ii] += (zvals2[ii]-zvals[ii])/t_diff[ii]/5.12e10 # output pedestals in mA
            
        if Cycles==10:
            file = open('Pedestals.txt','w')
            for ii in range(len(zvals)):
                file.write(str(Pedestals[ii]/Cycles)+'\n')
            file.write(str(Cycles)+'\n')
            file.close()

        for xx in [ttime,ttM,tt1]: xx.Clear()
        [total,maximum]=calcRates(zvals,zvals2,t_diff)
        tt1.AddText('Total:  %.2f mA'%((total)/1000))
        ttM.AddText('MAX SINGLE Current = %.2f #muA'%(maximum))
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


