// Offline.h --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 7月 29 20:40:09 2016 (+0800)
// Last-Updated: 三 10月  5 14:28:47 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 29
// URL: http://wuhongyi.github.io 

#ifndef _OFFLINE_H_
#define _OFFLINE_H_

#include "TGWindow.h"
#include "TGFrame.h"
#include "TGDoubleSlider.h"
#include "TGraph.h"
#include "TMultiGraph.h"

#include "TGNumberEntry.h"
#include "TGLabel.h"
#include "TGTextEntry.h"
#include "TRootEmbeddedCanvas.h"
#include "TString.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TGStatusBar.h"
#include "TGApplication.h"
#include "TObject.h"
#include "TH1.h"

class Detector;
class Offline : public TGTransientFrame
{
public:
  Offline(const TGWindow *p, const TGWindow *main,Detector *det, TGTextEntry *filepath, TGTextEntry	*filename);
  virtual ~Offline();

  virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t);//process message queue

  void MakeFold1Panel(TGCompositeFrame *TabPanel);
  void MakeFold2Panel(TGCompositeFrame *TabPanel);
  void MakeFold3Panel(TGCompositeFrame *TabPanel);

private:
  Pixel_t color;
  Detector *detector;
  TObject *selected;
  TGTextEntry *filepathtext;
  TGTextEntry *filenametext;
  
  TCanvas *adjustCanvas;
  TGStatusBar* sbfold3;
  TGDoubleHSlider *dslider;

  TMultiGraph *offlinemultigraph;
  TGraph *rawdata,*threshdata,*cfddata,*sfilterdata,*ffilterdata;
  unsigned short *RcdTrace;//
  double *doublesample;
  double *doublethresh;
  double *doublercdtrace;
  double *doublefastfilter;//
  double *doublecfd;//
  double *doubleslowfilter;//

  char offlinefilename[256];
  int modNumber, chanNumber,fileRunNum;//the par used to offline
  TGNumberEntry	*offlinefilerunnum;//int
  TGNumberEntry	*offlinemodnum;//int
  TGNumberEntry	*offlinechnum;//int
  TGNumberEntry* offlinefilterrange;
  void OfflineChangeValues(int mod,int ch);
  void OfflineLoadValues(int mod,int ch);
  unsigned int GetModuleEvents(char *FileName);//return events
  void GetEventsInfo(char *FileName, unsigned int *EventInformation);
  unsigned int *OfflineEventInformation;
  unsigned int OfflineModuleEventsCount;
  unsigned int OfflineCurrentCount;
  
  unsigned int OfflinefRange;
  // 0-fastlength 1-fastgap  2-slowlength  3-slowgap  4-preamptau  5-cfddelay  6-cfdscale 7-threshold
  TGNumberEntryField *offlinefilters[8];
  /* TGNumberEntry	*offlinepreamptau;//double */
  /* TGNumberEntry	*offlinecfddelay;//double */
  /* TGNumberEntry	*offlinecfdscale;//double */

  TGTextEntry* OfflineFileStatus;
  TGTextEntry* OfflineCurrentCountText;
  TGTextButton* OfflineReadFileButton;
  TGTextButton* OfflineLoadButton;
  TGTextButton* OfflineApplyButton;
  TGTextButton* OfflineDrawButton;

  enum Commands
    {
      ADJUSTPARSLIDER,
      OFFLINERUNNUM,
      OFFLINERUNNUM2,
      OFFLINERUNNUM3,
      OFFLINEMODNUM,
      OFFLINEMODNUM2,
      OFFLINEMODNUM3,
      OFFLINECHNUM,
      OFFLINEREAD,
      OFFLINEREAD2,
      OFFLINEREAD3,
      OFFLINELOAD,
      OFFLINEAPPLY,
      OFFLINEDRAW,
      OFFLINEDRAW2,
      OFFLINEDRAW3,
      OFFLINEFASTLENGTH,
      OFFLINEFASTGAP,
      OFFLINESLOWLENGTH,
      OFFLINESLOWGAP,
      OFFLINEPREAMPTAU,
      OFFLINECFDDELAY,
      OFFLINECFDSCALE,
      OFFLINETHRESH,
      OFFLINEFILTERRANGE
    };

  // Fold2
  TCanvas *canvas2;
  TGNumberEntry	*offlinefilerunnum2;
  TGNumberEntry	*offlinemodnum2;
  TGTextButton* OfflineReadFileButton2;
  TGTextEntry* OfflineFileStatus2;
  TGTextButton* OfflineDrawButton2;
  TMultiGraph *offlinemultigraph2[16];

  char offlinefilename2[256];
  int fileRunNum2,modNumber2;
  unsigned int OfflineModuleEventsCount2;
  unsigned int *OfflineEventInformation2;
  unsigned int OfflineCurrentCount2[16];
  
  TGraph *rawdata2[16],*threshdata2[16],*cfddata2[16],*sfilterdata2[16],*ffilterdata2[16];
  unsigned short *RcdTrace2[16];//
  double *doublesample2[16];
  double *doublethresh2[16];
  double *doublercdtrace2[16];
  double *doublefastfilter2[16];//
  double *doublecfd2[16];//
  double *doubleslowfilter2[16];//

  // Fold3
  TCanvas *canvas3;
  TGNumberEntry	*offlinefilerunnum3;
  TGNumberEntry	*offlinemodnum3;
  TGTextButton* OfflineReadFileButton3;
  TGTextEntry* OfflineFileStatus3;
  TGTextButton* OfflineDrawButton3;  
  TH1D *offlineth1d3[16];
  
  char offlinefilename3[256];
  int fileRunNum3,modNumber3;
  unsigned int OfflineModuleEventsCount3;
  unsigned int *OfflineEventInformation3;

  
  // function
  void Panel1Draw();
  void Panel2Draw();
  void Panel3Draw();
  void Panel1ReadFile();
  void Panel2ReadFile();
  void Panel3ReadFile();

  
};

#endif /* _OFFLINE_H_ */
// 
// Offline.h ends here
