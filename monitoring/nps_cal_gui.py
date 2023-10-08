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

# nps-vme1  253 = 15*16+13
# nps-vme2  253 = 15*16+13
# nps-vme3  269 = 16*16+13  (slot 20 scintillators)
# nps-vme4  253 = 15*16+13
# nps-vme4  141 = 8*16+13

def getScalars():
    zvals=[]
    XVALS[:] = []
    YVALS[:] = []
    chan=[]
    pchan=[]
    pzvals=[]
    time_clock=[]

    try:
        lines = subprocess.check_output(["getscalers","nps-vme1"])
        icount=0
        for line in lines.splitlines():
            icount+=1 
            if icount>=243: 
                if icount==496: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,240):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
                data = int(info_data[0])+int(info_data[1])*65536*65536
                zvals.append(float(data))

        lines2 = subprocess.check_output(["getscalers","nps-vme2"])
        icount2=0
        for line in lines2.splitlines():
            icount2+=1 
            if icount2>=243:
                if icount2==496: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,240):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
                data = int(info_data[0])+int(info_data[1])*65536*65536
                zvals.append(float(data))

        lines3 = subprocess.check_output(["getscalers","nps-vme3"])
        icount3=0
        for line in lines3.splitlines():
            icount3+=1 
            if icount3>=243:
                if icount3==528: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,240):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
                data = int(info_data[0])+int(info_data[1])*65536*65536
                zvals.append(float(data))

        lines4 = subprocess.check_output(["getscalers","nps-vme4"])
        icount4=0
        for line in lines4.splitlines():
            icount4+=1 
            if icount4>=243:
                if icount4==496: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,240):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
                data = int(info_data[0])+int(info_data[1])*65536*65536
                zvals.append(float(data))

        lines5 = subprocess.check_output(["getscalers","nps-vme5"])
        icount5=0
        for line in lines5.splitlines():
            icount5+=1 
            if icount5>=123:
                if icount5==272: 
                    info_time = line.split()
                    info_time[0] = info_time[0].replace(':', '')
                    if info[0].isdigit():
                        TT = info_time[1].split("(")
                        TT[1] = TT[1].replace(')','')
                        for i in range(0,120):
                            time_clock.append(float(int(TT[0])+int(TT[1])*65536*65536))
                continue
            #print line
            info = line.split()
            info[0] = info[0].replace(':', '')
            if info[0].isdigit():
                chan.append(int (info[0])+1)
                info_data=info[1].split("(")
                info_data[1]=info_data[1].replace(')','')
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
    except subprocess.CalledProcessError as e:
        return [None, None]

def getScalars_hms():
    zvals_hms=[]
    pzvals_hms=[]
    chan_hms=[]
    
    try:
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
    except subprocess.CalledProcessError as e:
        return None

def calcRates(rates,rates2,time_diff):
    total,maximum=0.0,0.0
    for ii in range(len(XVALS)):
        xx,zz,zz2,tt=XVALS[ii],rates[ii],rates2[ii],time_diff[ii]
        total+=(zz2-zz)/tt
        if (zz2-zz)/tt>maximum: maximum=(zz2-zz)/tt
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
mf.SetWindowName('NPS CAL FADC SCALERS')
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
    
    tt_hmsT5=TPaveText(0.05,0.95,0.22,1.0,'NDC')
    tt_hmsT6=TPaveText(0.05,0.90,0.22,0.95,'NDC')
    tt1=TPaveText(0.67,0.90,0.84,0.95,'NDC')
    ttM=TPaveText(0.65,0.95,0.95,1,'NDC')
    ttime=TPaveText(11,-1.5,20,-2.5)
    tchan=TPaveText(0,0,0.9,1)
    setupPaveTexts([tt1,ttM,tt_hmsT5,tt_hmsT6,ttime,tchan])
    ttM.SetTextColor(2)

    ttt=TText()
    ttt.SetTextColor(1)
    ttt.SetTextSize(0.02)
    ttt.DrawText(25,-2.5,'Script maintained by Yaopeng Zhang <yaopeng@jlab.org>')
    
    tt=TText()
    tt.SetTextColor(1)
    tt.SetTextAngle(90)
    tt.SetTextSize(0.045)
    tt.DrawText(34.5,36,'kHz')
    tt.SetTextAngle(0)
    tt.SetTextColor(2)
    tt.DrawTextNDC(0.3,0.905,'NPS CAL FADC SCALERS')


    cc.cd()
    for xx in [ttM,tt1,tt_hmsT5,tt_hmsT6,ttime]: xx.Draw()
    cc2.cd()
    tchan.Draw('NDC')
    cc.cd()

    xmin,xmax=xax.GetXmin(),xax.GetXmax()
    ymin,ymax=yax.GetXmin(),yax.GetXmax()
   
    gPad.SetEditable(0)

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

        [zvals,time1] = getScalars()
        zvals_hms = getScalars_hms()
        time.sleep(5)
        [zvals2,time2] = getScalars()
        zvals_hms2 = getScalars_hms()
        if zvals is None or zvals_hms is None or zvals2 is None or zvals_hms2 is None:
            continue

        t_diff = []
        for ii in range(len(zvals)):
            t_diff.append((time2[ii]-time1[ii])/60.0)
            if t_diff[ii]<0.1: t_diff[ii] = 1.
            hh.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),(zvals2[ii]-zvals[ii])/t_diff[ii]/1000.)
            hi.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),(zvals2[ii]-zvals[ii])/t_diff[ii]/1000.)
    
        for xx in [ttime,ttM,tt1,tt_hmsT5,tt_hmsT6]: xx.Clear()
        [total,maximum]=calcRates(zvals,zvals2,t_diff)
        tt1.AddText('Total:  %.1f kHz'%((total)/1000))
        ttM.AddText('MAX SINGLE CRYSTAL = %.0f Hz'%(maximum))
        if ps[4] == -1:
            hmsT5 = 0.
        elif (zvals_hms2[1]-zvals_hms[1])>0:
            hmsT5 = (zvals_hms2[0]-zvals_hms[0])/(zvals_hms2[1]-zvals_hms[1])*ps[4]
        else:
            hmsT5 = 0.
        if ps[5] == -1:
            hmsT6 = 0.
        elif (zvals_hms2[2]-zvals_hms[2])>0:
            hmsT6 = (zvals_hms2[0]-zvals_hms[0])/(zvals_hms2[2]-zvals_hms[2])*ps[5]
        else:
            hmsT6 = 0.
        tt_hmsT5.AddText('hL1ACCP/hTRIG5(after ps) = %.3f %%'%(hmsT5*100.))
        tt_hmsT6.AddText('hL1ACCP/hTRIG6(after ps) = %.3f %%'%(hmsT6*100.))
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
        # cc.SaveAs("screenshots/test.pdf")

        time.sleep(1)
   

if __name__=='__main__': main()


