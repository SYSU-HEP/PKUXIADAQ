// LogicTrigger.h --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 7月 28 18:18:36 2016 (+0800)
// Last-Updated: 三 10月  5 13:38:42 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 21
// URL: http://wuhongyi.github.io 

#ifndef _LOGICTRIGGER_H_
#define _LOGICTRIGGER_H_

#include "Table.h"
#include "TGComboBox.h"
#include "TGTextEntry.h"

class LogicTrigger : public Table
{
public:
  LogicTrigger(const TGWindow * p, const TGWindow * main, 
	       char *name, int columns = 6,
	       int rows = 16, int NumModules = 5);
  virtual ~LogicTrigger();

  int change_values(Long_t mod);
  int load_info(Long_t mod);
  Bool_t ProcessMessage(Long_t msg, Long_t parm1,Long_t parm2);

  void TGTextEntryAddStyle(TGTextEntry *tgtextentry,char *title, char *tooltip);

  void SetMultipleBit(unsigned int *Data,int Select,int bit0);
  void SetMultipleBit(unsigned int *Data,int Select,int bit1,int bit0);
  void SetMultipleBit(unsigned int *Data,int Select,int bit2,int bit1,int bit0);
  void SetMultipleBit(unsigned int *Data,int Select,int bit3,int bit2,int bit1,int bit0);
    
protected:
  short int modNumber;
  unsigned short chanNumber;
  bool Load_Once;
  TGNumberEntry* chanCopy;

  float exttrigstretch;
  float externdelaylen;
  float ftrigoutdelay;
  float vetostretch;
  float chantrigstretch;

  
  TGComboBox *ChTri_ch0_3;//2 [24]
  TGComboBox *GroupTri0;//2 [17:16]
  TGComboBox *GroupTri0_0;//1 [3:0]
  TGComboBox *GroupTri0_1;//1 [7:4]
  TGComboBox *GroupTri0_2;//1 [11:8]
  
  TGComboBox *ChTri_ch4_7;//2 [25]
  TGComboBox *GroupTri1;//2 [19:18]
  TGComboBox *GroupTri1_0;//1 [15:12]
  TGComboBox *GroupTri1_1;//1 [19:16]
  TGComboBox *GroupTri1_2;//1 [23:20]
  
  TGComboBox *ChTri_ch8_11;//2 [26]
  TGComboBox *GroupTri2;//2 [21:20]
  TGComboBox *GroupTri2_0;//1 [27:24]
  TGComboBox *GroupTri2_1;//1 [31:28]
  TGComboBox *GroupTri2_2;//2 [3:0]

  TGComboBox *ChTri_ch12_15;//2 [27]
  TGComboBox *GroupTri3;//2 [23:22]
  TGComboBox *GroupTri3_0;//2 [7:4]
  TGComboBox *GroupTri3_1;//2 [11:8]
  TGComboBox *GroupTri3_2;//2 [15:12]

  TGComboBox *ChannelTrigger;//2 [31:28]
  TGComboBox *InternalFastTrigger;//0 [3:0]
  TGComboBox *ExternalFastTrigger;//0 [7:4]
  TGComboBox *InternalValidationTrigger;//0 [11:8]
  TGComboBox *GlobalFastTrigger;//0 [25:24]
  TGComboBox *GlobalValidationTrigger;//0 [27:26]
  TGComboBox *ExternalValidationTrigger;//0 [31:28]
};

#endif /* _LOGICTRIGGER_H_ */
// 
// LogicTrigger.h ends here
