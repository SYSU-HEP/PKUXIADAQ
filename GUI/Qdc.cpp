#include "Qdc.h"
#include "Global.h"
#include "pixie16app_defs.h"
#include "pixie16app_export.h"
#include <iostream>

using namespace std;

Qdc::Qdc(const TGWindow *p, const TGWindow *main, char *name, int columns, int rows,int NumModules)
  : Table(p,main,columns,rows,name, PRESET_MAX_MODULES)
{
  // numModules=24;
  modNumber=0;
  char n[10];
  cl0->SetText("ch #");
  for(int i=0;i<rows;i++){
    sprintf(n,"%2d",i);
    Labels[i]->SetText(n);
  }
  CLabel[0]->SetText("QDC len0[us]");
  CLabel[0]->SetAlignment(kTextCenterX);
  CLabel[1]->SetText("QDC len1[us]");
  CLabel[1]->SetAlignment(kTextCenterX);
  CLabel[2]->SetText("QDC len2[us]");
  CLabel[2]->SetAlignment(kTextCenterX);
  CLabel[3]->SetText("QDC len3[us]");
  CLabel[3]->SetAlignment(kTextCenterX);
  CLabel[4]->SetText("QDC len4[us]");
  CLabel[4]->SetAlignment(kTextCenterX);
  CLabel[5]->SetText("QDC len5[us]");
  CLabel[5]->SetAlignment(kTextCenterX);
  CLabel[6]->SetText("QDC len6[us]");
  CLabel[6]->SetAlignment(kTextCenterX);
  CLabel[7]->SetText("QDC len7[us]");
  CLabel[7]->SetAlignment(kTextCenterX);
  
  // ***** COPY BUTTON *********
  TGHorizontal3DLine *ln2 = new TGHorizontal3DLine(mn_vert, 200, 2);
  mn_vert->AddFrame(ln2, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 10, 10));
  TGHorizontalFrame *CopyButton = new TGHorizontalFrame(mn_vert, 400, 300);
  mn_vert->AddFrame(CopyButton, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

  TGLabel *Copy = new TGLabel(CopyButton, "Select channel #");

  chanCopy = new TGNumberEntry(CopyButton, 0, 4, MODNUMBER+1000, (TGNumberFormat::EStyle) 0, (TGNumberFormat::EAttribute) 1, (TGNumberFormat::ELimit) 3/*kNELLimitMinMax*/, 0, 3);
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


Qdc::~Qdc()
{

}

Bool_t Qdc::ProcessMessage(Long_t msg, Long_t parm1,Long_t parm2)
{
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
	      //	pol_temp=lstBox[chanNumber-1]->GetSelected();
	      //	gain_temp=lstBoxGain[chanNumber-1]->GetSelected();
	      memset(qlen,0,sizeof(float)*8);
	      for(int i=0;i<8;i++)
		qlen[i]=NumEntry[i+1][chanNumber]->GetNumber();
	      //cout<<pol_temp<<" "<<gain_temp<<" "<<offset_temp<<endl;
	      for(int i=0;i<16;i++)
		{
		  if(i != (chanNumber))
		    {
		      //			lstBox[i]->Select(pol_temp);
		      //		lstBoxGain[i]->Select(gain_temp);
		      for(int j=0;j<8;j++){
			sprintf(tmp,"%1.3f",qlen[j]);
			NumEntry[j+1][i]->SetText(tmp);
		      }
		    }
		}  
		    
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

int Qdc::change_values(Long_t mod)
{
  int retval;
  char varN[32];
  for(int i = 0;i < 16;i++){
    for(int j = 0;j < 8;j++){
      qlen[j] = NumEntry[j+1][i]->GetNumber();
      sprintf(varN,"QDCLen%d",j);
      retval = Pixie16WriteSglChanPar(varN,qlen[j],modNumber,i);
      if(retval<0) {
	ErrorInfo("Qdc.cpp", "change_values(...)", "Pixie16WriteSglChanPar/QDCLen0-7", retval);
	return retval;
      }
      //     cout<<varN<<"\t"<<qlen[j]<<"\t";
    }
    //    cout<<endl;
  }
  return 0;
}

int Qdc::load_info(Long_t mod)
{
  int retval;
  double ChanParData = -1;
  char text[20];

  char varN[8][10] = {"QDCLen0","QDCLen1","QDCLen2","QDCLen3","QDCLen4","QDCLen5","QDCLen6","QDCLen7"};
  for(int i = 0;i < 16;i++){
    for(int j = 0;j < 8;j++){
      retval = Pixie16ReadSglChanPar(varN[j],&ChanParData,modNumber,i);
      if(retval < 0) ErrorInfo("Qdc.cpp", "load_info(...)", "Pixie16ReadSglChanPar/QDCLen0-7", retval);
      sprintf(text,"%1.2f",ChanParData);
      NumEntry[j+1][i]->SetText(text);
    }
  }
  //  cout<< varN[0]<<endl;
  return 0;
}
