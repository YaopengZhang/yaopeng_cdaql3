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

    lines = subprocess.check_output(["getscalers","nps-vme1"])
    icount=0
    for line in lines.splitlines():
        if icount==242: break
        icount+=1 
        #print line
        info = line.split()
        info[0] = info[0].replace(':', '')
        if info[0].isdigit():
            chan.append(int (info[0])+1)
            info[1] = info[1].rpartition('(')[0]
            zvals.append(float(info[1]))

    lines2 = subprocess.check_output(["getscalers","nps-vme2"])
    icount2=0
    for line in lines2.splitlines():
        if icount2==242: break
        icount2+=1 
        #print line
        info = line.split()
        info[0] = info[0].replace(':', '')
        if info[0].isdigit():
            chan.append(int (info[0])+1)
            info[1] = info[1].rpartition('(')[0]
            zvals.append(float(info[1]))

    lines3 = subprocess.check_output(["getscalers","nps-vme3"])
    icount3=0
    for line in lines3.splitlines():
        if icount3==242: break
        icount3+=1 
        #print line
        info = line.split()
        info[0] = info[0].replace(':', '')
        if info[0].isdigit():
            chan.append(int (info[0])+1)
            info[1] = info[1].rpartition('(')[0]
            zvals.append(float(info[1]))

    lines4 = subprocess.check_output(["getscalers","nps-vme4"])
    icount4=0
    for line in lines4.splitlines():
        if icount4==242: break
        icount4+=1 
        #print line
        info = line.split()
        info[0] = info[0].replace(':', '')
        if info[0].isdigit():
            chan.append(int (info[0])+1)
            info[1] = info[1].rpartition('(')[0]
            zvals.append(float(info[1]))

    lines5 = subprocess.check_output(["getscalers","nps-vme5"])
    icount5=0
    for line in lines5.splitlines():
        if icount5==122: break
        icount5+=1 
        #print line
        info = line.split()
        info[0] = info[0].replace(':', '')
        if info[0].isdigit():
            chan.append(int (info[0])+1)
            info[1] = info[1].rpartition('(')[0]
            zvals.append(float(info[1]))

    ix,iy=1,1
    for ii in range (len(zvals)):
        if ii>=START:
            if ii==START+NCHAN: break
            XVALS.append(ix)
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
    return pzvals


def calcRates(rates,rates2):
    total,maximum=0.0,0.0
    for ii in range(len(XVALS)):
        xx,zz,zz2=XVALS[ii],rates[ii],rates2[ii]
        total+=(zz2-zz)/10
        if (zz2-zz)/10>maximum: maximum=(zz2-zz)/10
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
        xx=1
        for ix in range(30):
            hh.GetXaxis().SetBinLabel(ix+1,'%d'%(xx))
            xx+=1
        yy=1
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
mf.Resize(1200,800)# resize to get proper frame placement
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
    
    tt=TText()
    tt.SetTextColor(1)
    tt.SetTextAngle(90)
    tt.SetTextSize(0.045)
    tt.DrawText(34.5,36,'Hz')
    tt.SetTextAngle(0)
    tt.SetTextColor(2)
    tt.DrawTextNDC(0.3,0.905,'NPS CAL FADC SCALERS')


    cc.cd()
    for xx in [ttM,tt1,ttime]: xx.Draw()
    cc2.cd()
    tchan.Draw('NDC')
    cc.cd()

    xmin,xmax=xax.GetXmin(),xax.GetXmax()
    ymin,ymax=yax.GetXmin(),yax.GetXmax()
   
    gPad.SetEditable(0)

    while True:

        zvals = getScalars()
        time.sleep(10)
        zvals2 = getScalars()
        for ii in range(len(zvals)):
            hh.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),(zvals2[ii]-zvals[ii])/10.0)
            hi.SetBinContent(xax.FindBin(XVALS[ii]),yax.FindBin(YVALS[ii]),(zvals2[ii]-zvals[ii])/10.0)
    
        for xx in [ttime,ttM,tt1]: xx.Clear()
        [total,maximum]=calcRates(zvals,zvals2)
        tt1.AddText('Total:  %.1f kHz'%((total)/1000))
        ttM.AddText('MAX SINGLE CRYSTAL = %.0f Hz'%(maximum))
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


