// MultiplicityMask.cpp --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 二 10月  4 20:33:32 2016 (+0800)
// Last-Updated: 三 10月  5 14:38:28 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 5
// URL: http://wuhongyi.github.io 

#include "MultiplicityMask.h"
#include "Detector.h"
#include "pixie16app_export.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MultiplicityMask::MultiplicityMask(const TGWindow *p, const TGWindow * main, char *name, int columns, int rows, int NumModules)
  :Table(p,main,columns,rows,name, PRESET_MAX_MODULES)
{
  modNumber=0;
  char n[10];
  cl0->SetText("ch #");
  for(int i = 0;i < rows;i++){
    sprintf(n,"%2d",i);
    Labels[i]->SetText(n);
  }
  CLabel[0]->SetText("Left");
  CLabel[0]->SetAlignment(kTextCenterX);
  CLabel[1]->SetText("Itself");
  CLabel[1]->SetAlignment(kTextCenterX);
  CLabel[2]->SetText("Right");
  CLabel[2]->SetAlignment(kTextCenterX);
  CLabel[3]->SetText("1st");
  CLabel[3]->SetAlignment(kTextCenterX);
  CLabel[4]->SetText("2nd");
  CLabel[4]->SetAlignment(kTextCenterX);
  CLabel[5]->SetText("3rd");
  CLabel[5]->SetAlignment(kTextCenterX);  
   
  // ***** COPY BUTTON *********
  TGHorizontal3DLine *ln2 = new TGHorizontal3DLine(mn_vert, 200, 2);
  mn_vert->AddFrame(ln2, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 10, 10));
  TGHorizontalFrame *CopyButton = new TGHorizontalFrame(mn_vert, 400, 300);
  mn_vert->AddFrame(CopyButton, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

  TGLabel *Copy = new TGLabel(CopyButton, "Select channel #");

  chanCopy = new TGNumberEntry(CopyButton, 0, 4, MODNUMBER+1000, (TGNumberFormat::EStyle) 0, (TGNumberFormat::EAttribute) 1, (TGNumberFormat::ELimit) 3/*kNELLimitMinMax*/,0, 3);
  chanCopy->SetButtonToNum(0);
  chanCopy->IsEditable();
  chanCopy->SetIntNumber(0);
  CopyButton->AddFrame(Copy, new TGLayoutHints(kLHintsCenterX, 5, 10, 3, 0));
  CopyButton->AddFrame(chanCopy, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 20, 0, 0));

  chanCopy->Associate(this);

  ////////////////////Copy button per se///////////////////
  TGTextButton *copyB = new TGTextButton(CopyButton, "C&opy", COPYBUTTON+1000);
  copyB->Associate(this);
  copyB->SetToolTipText("Copy the setup of the selected channel to all channels of the module", 0);
  CopyButton->AddFrame(copyB, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 20, 0, 0));


  chanNumber = 0;
  MapSubwindows();
  Resize();			// resize to default size

  Load_Once = true;
}

MultiplicityMask::~MultiplicityMask()
{
  cout<<"MultiplicityMask is deleted!"<<endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Bool_t MultiplicityMask::ProcessMessage(Long_t msg,Long_t parm1, Long_t parm2){

  switch (GET_MSG(msg))
    {
    case kC_COMMAND:
      switch (GET_SUBMSG(msg))
	{
	case kCM_BUTTON:
	  switch (parm1)
	    {
	    case (MODNUMBER):
	      if (parm2 == 0)
		{
		  if (modNumber != numModules-1)
		    {
		      ++modNumber;
		      numericMod->SetIntNumber(modNumber);
		      load_info(modNumber);
		    }
		}
	      else
		{
		  if (modNumber != 0)
		    {
		      if (--modNumber == 0)
			modNumber = 0;
		      numericMod->SetIntNumber(modNumber);
		      load_info(modNumber);
		    }
		}
	      break;
	      ////////////////////////////////////////
	    case (MODNUMBER+1000):
	      if (parm2 == 0)
		{
		  if (chanNumber != 15)
		    {
		      ++chanNumber;
		      chanCopy->SetIntNumber(chanNumber);
		    }
		}
	      else
		{
		  if (chanNumber != 0)
		    {
		      if (--chanNumber == 0)
			chanNumber = 0;
		      chanCopy->SetIntNumber(chanNumber);
		    }
		}
	      break;

	      ////////////////////////////////////////
	    case LOAD:
	      {
		Load_Once = true;
		load_info(modNumber);
	      }
	      break;
	    case APPLY:
	      if (Load_Once)
		change_values(modNumber);
	      else
		std::cout << "please load once first !\n";
	      break;
	    case CANCEL:		/// Cancel Button
	      DeleteWindow();
	      break;
	      //////////////////////////////
	    case (COPYBUTTON+1000):
	      // tdelay = NumEntry[1][chanNumber]->GetNumber();
	      // cfrac = NumEntry[2][chanNumber]->GetNumber();
	      // thresh = NumEntry[3][chanNumber]->GetNumber();
	      // for(int i = 0;i < 16;i++)
	      // 	{
	      // 	  if(i != (chanNumber))
	      // 	    {
	      // 	      sprintf(tmp,"%1.3f",tdelay);
	      // 	      NumEntry[1][i]->SetText(tmp);
	      // 	      sprintf(tmp,"%1.3f",cfrac);
	      // 	      NumEntry[2][i]->SetText(tmp);
	      // 	      sprintf(tmp,"%1.3f",thresh);
	      // 	      NumEntry[3][i]->SetText(tmp);
	      // 	    }
	      // 	}  
	      
	      break;
	      
	      /////////////////////////////
	      
	    default:
	      break;
	    }
	  break;
	default:
	  break;
	}
      break;
    default:
      break;
    }
  return kTRUE;
}

int MultiplicityMask::load_info(Long_t mod)
{
  // double ChanParData = -1;
  // int retval;
  // char text[20];

  // for (int i = 0; i < 16; i++)
  //   {
  //     retval = Pixie16ReadSglChanPar((char*)"CFDDelay", &ChanParData, modNumber, i);
  //     if(retval < 0) ErrorInfo("Cfd.cpp", "load_info(...)", "Pixie16ReadSglChanPar/CFDDelay", retval);
  //     sprintf(text, "%1.2f", ChanParData);
  //     NumEntry[1][i]->SetText(text);

  //     retval = Pixie16ReadSglChanPar((char*)"CFDScale", &ChanParData, modNumber, i);
  //     if(retval < 0) ErrorInfo("Cfd.cpp", "load_info(...)", "Pixie16ReadSglChanPar/CFDScale", retval);  
  //     sprintf(text, "%1.2f", ChanParData);
  //     NumEntry[2][i]->SetText(text);

  //     retval = Pixie16ReadSglChanPar((char*)"CFDThresh", &ChanParData, modNumber, i);
  //     if(retval < 0) ErrorInfo("Cfd.cpp", "load_info(...)", "Pixie16ReadSglChanPar/CFDThresh", retval);     
  //     sprintf(text, "%1.2f", ChanParData);
  //     NumEntry[3][i]->SetText(text);
     
  //   }
  //  std::cout << "loading info\n";
  return 1;
}

int MultiplicityMask::change_values(Long_t mod)
{
  // double delay;
  // double frac;
  // double thres;
  // int retval;
  // for (int i = 0; i < 16; i++)
  //   {
  //     delay = NumEntry[1][i]->GetNumber();
  //     retval = Pixie16WriteSglChanPar((char*)"CFDDelay", delay, modNumber, i);
  //     if(retval < 0) ErrorInfo("Cfd.cpp", "change_values(...)", "Pixie16WriteSglChanPar/CFDDelay", retval);
      
  //     frac = NumEntry[2][i]->GetNumber();
  //     retval = Pixie16WriteSglChanPar((char*)"CFDScale", frac, modNumber, i);
  //     if(retval < 0) ErrorInfo("Cfd.cpp", "change_values(...)", "Pixie16WriteSglChanPar/CFDScale", retval);
      
  //     thres = NumEntry[3][i]->GetNumber();
  //     retval = Pixie16WriteSglChanPar((char*)"CFDThresh", thres, modNumber, i);
  //     if(retval < 0) ErrorInfo("Cfd.cpp", "change_values(...)", "Pixie16WriteSglChanPar/CFDThresh", retval);
  //   }
  // std::cout << "change values\n";

  return 1;
}



// 
// MultiplicityMask.cpp ends here
