#include <COMMON.H>
#include <UTILITY.H>
#include "menu.h"

#define UM_INIT 4055

typedef struct
    {
    SHORT cx;
    SHORT cy;
    }CHCELL;

MRESULT EXPENTRY fnwpSelectPortDlg(HWND hwnd,USHORT msg,MPARAM mp1,MPARAM mp2);

void Paint(void);
void ErrorNotify(char szMessage[]);
void PrintString(char szMessage[],ULONG ulPos);
BOOL RecoverProfile(HINI hProfile);
BOOL CopyProfile(HINI hProfile,HINI hDestProfile);

BOOL TerminatePort(void);
BOOL InitializePort(void);
BOOL RemovePort(void);
BOOL InstallPort(void);
BOOL SetupPort(void);
ULONG QueryPort(char achBuffer[],ULONG cbBuffSize);
BOOL EnumeratePorts(char achBuffer[],ULONG cbBuffSize);

BOOL WndSize(HWND hwnd,MPARAM mp2);
VOID CreatePS(HWND hwnd);

MRESULT EXPENTRY fnwpClient(HWND hwnd,USHORT msg,MPARAM mp1,MPARAM mp2);
VOID PaintWindow( HWND hwnd, COLOR clr );
VOID ClientPaint(HWND hwnd);
VOID ClearScreen(void);

LONG lXScr;
LONG lcxVSc;
LONG lcxBrdr;
WORD wForeground;
WORD wBackground;
USHORT usWndWidth;
USHORT usWndDepth;
CHCELL  stCell;

ULONG ulWindowWidth;
ULONG ulWindowHeight;

char szDriverIniPath[CCHMAXPATH];

CHAR szErrorMessage[81];
char szMessage[200];
char szPortName[20];
char szPortDesc[256];

HDC hdcPs;

CHAR szEXEtitle[] = "Serial PDR Test";
HAB habAnchorBlock;
HFILE hCom = 0;
HWND hwndFrame;
HWND hwndClient;
ERRORID eidError;

char achBuffer[4096];

char szModuleName[CCHMAXPATH] = "p:\\DebugResults\\SPL_DEB.PDR";

ULONG ulItemCount;
HMODULE hMod;

//SERIALDATA stPortData;

typedef struct
  {
  char *pszPortName;
  char *pszPortDesc;
  }PORTDESC;

PORTDESC stPorts[100];

ULONG ulPortCount;

void  main(int argc,char *argv[])
  {
  HMQ hmqQueue;
  QMSG qmsgMessage;
  ULONG flCreate;
  LONG lIndex;

  if (argc >= 2)
    {
    for (lIndex = 1;lIndex < argc;lIndex++)
      {
      if ((argv[lIndex][0] == '/') || (argv[lIndex][0] == '-'))
        {
        switch (argv[lIndex][1] & 0xdf)
          {
          case 'L':
            strcpy(szModuleName,&argv[lIndex][2]);
            break;
	        case 'P':
            strcpy(szPortName,&argv[lIndex][2]);
            break;
          }
        }
      }
    }

  if (DosLoadModule(0,0,szModuleName,&hMod) != NO_ERROR)
    hMod = 0;

  habAnchorBlock = WinInitialize(0);        /* Initialize PM                 */

  hmqQueue   = WinCreateMsgQueue(habAnchorBlock,0);   /* Create application msg queue */

  WinRegisterClass(habAnchorBlock,
                  "ICOMMAIN",
            (PFNWP)fnwpClient,
                   CS_SIZEREDRAW,
                   10);

  flCreate =  (FCF_STANDARD ^ FCF_SHELLPOSITION);

  hwndFrame = WinCreateStdWindow(HWND_DESKTOP,
                                 WS_VISIBLE,
                                &flCreate,
                                "ICOMMAIN",
                                 0,
                                (WS_VISIBLE | WS_CLIPCHILDREN),
                                 0,
                                IDM_SERIAL,
                                &hwndClient);

  if (hwndFrame == 0)
    {
    eidError = WinGetLastError(habAnchorBlock);
    return;
    }

  WinSetWindowText(hwndFrame,szEXEtitle);
  /*
  ** Set up globals used for sizing
  */

  lXScr   = WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN);
  lcxVSc  = WinQuerySysValue(HWND_DESKTOP,SV_CXVSCROLL);
  lcxBrdr = WinQuerySysValue(HWND_DESKTOP,SV_CXSIZEBORDER);

  while( WinGetMsg(habAnchorBlock,&qmsgMessage,(HWND)0,0,0))
    WinDispatchMsg(habAnchorBlock,&qmsgMessage);

  if (hMod != 0)
    DosFreeModule(hMod);
  WinDestroyWindow(hwndFrame);
  WinDestroyMsgQueue(hmqQueue);
  WinTerminate(habAnchorBlock);
//  DosExit(1,0);
  }

MRESULT EXPENTRY fnwpClient(HWND hwnd,USHORT msg,MPARAM mp1,MPARAM mp2)
  {
  RECTL   rcl;
  USHORT   Command;
  ULONG *pulPtr;

  switch(msg)
    {
    case WM_CREATE:
      stCell.cy = 12;
      stCell.cx = 8;
      hdcPs = WinOpenWindowDC(hwnd);

      /****************************************************************/
      /* Set the size and position of the frame window by making the  */
      /* client area width and height integral numbers of AVIO cell   */
      /* units.  Calculate the frame window values necessary to       */
      /* achieve this.                                                */
      /****************************************************************/

      rcl.yBottom = 0L;
      rcl.xLeft   = 0L;
      rcl.yTop    = 20 * stCell.cy;
      rcl.xRight  = 40 * stCell.cx;

      WinCalcFrameRect(WinQueryWindow(hwnd,QW_PARENT),&rcl,FALSE);

      WinSetWindowPos(WinQueryWindow(hwnd,QW_PARENT),
                      0,
                      7 * stCell.cx,
                      2 * stCell.cy,
              (SHORT)(rcl.xRight - rcl.xLeft),
              (SHORT)(rcl.yTop - rcl.yBottom),
                      SWP_MOVE | SWP_SIZE);

      WinPostMsg(hwnd,UM_INIT,0L,0L);
      break;
    case WM_ACTIVATE:
      if(LOUSHORT(LONGFROMMP(mp1)))
        WinSetFocus(HWND_DESKTOP,hwnd);
      break;
    case UM_INIT:
      if (szPortName[0] != 0)
        WinSetWindowText(hwndFrame,szPortName);
      else
        MenuItemEnable(hwndFrame,IDM_PROCESS,FALSE);
      WinShowWindow(hwndFrame,TRUE);
      WinQueryWindowRect(hwndClient,&rcl);
      ulWindowWidth = rcl.xRight;
      ulWindowHeight = rcl.yTop;
      ClearScreen();
      break;
    case WM_PAINT:
      Paint();
      break;
    case WM_SIZE:
      WndSize(hwnd,mp2);
      ClearScreen();
      return WinDefWindowProc(hwnd,msg,mp1,mp2);
    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1))
        {
        case IDM_SELECT:
          if (WinDlgBox(HWND_DESKTOP,
                        hwnd,
                 (PFNWP)fnwpSelectPortDlg,
                (USHORT)NULL,
                        PS_DLG,
                        NULL))
            WinSetWindowText(hwndFrame,szPortDesc);
          break;
        case IDM_RECOVER_USER_INI:
          RecoverProfile(HINI_USERPROFILE);
          break;
        case IDM_RECOVER_SYS_INI:
          RecoverProfile(HINI_SYSTEMPROFILE);
          break;
        case IDM_EXIT:
          WinPostMsg(hwnd,WM_QUIT,0L,0L);
          break;
        case IDM_SETUP:
          SetupPort();
          break;
        case IDM_REMOVE:
          RemovePort();
          break;
        case IDM_INSTALL:
          InstallPort();
          break;
        case IDM_INIT:
          InitializePort();
          break;
        case IDM_TERM:
          TerminatePort();
//          TerminatePort(szPortName);
          break;
        case IDM_QUERY:
          ulItemCount = QueryPort(achBuffer,4096);
          break;
        default:
          return WinDefWindowProc(hwnd,msg,mp1,mp2);
        }
      break;
    case WM_CLOSE:
      WinPostMsg(hwnd,WM_QUIT,0L,0L);  /* Cause termination     */
      break;
    default:
      return WinDefWindowProc(hwnd,msg,mp1,mp2);
    }
  return(FALSE);
  }

BOOL SetupPort(void)
  {
//APIRET EXPENTRY SplPdSetPort(HAB hab,PSZ pszPortName,PULONG flModified)
  PFN pfnProcess;
  BOOL bModified = FALSE;
  APIRET rc;

  sprintf(szMessage,"Configuring %s",szPortName);
  PrintString(szMessage,3);
  if (hMod != 0)
    {
    if (DosQueryProcAddr(hMod,0,"SPLPDSETPORT",&pfnProcess) == NO_ERROR)
      rc = pfnProcess(habAnchorBlock,szPortName,&bModified);
    else
      {
      ErrorNotify("Error Getting SETPORT Address");
      return(FALSE);
      }
    }
  else
    {
    sprintf(szMessage,"Error Loading Module %s",szModuleName);
    ErrorNotify(szMessage);
    return(FALSE);
    }
  if (rc != NO_ERROR)
    {
    sprintf(szMessage,"Error Setting-up Port - rc = %X",rc);
    ErrorNotify(szMessage);
    return(FALSE);
    }
  if (bModified)
    sprintf(szMessage,"Port %s was configured",szPortName);
  else
    sprintf(szMessage,"Port %s was not configured",szPortName);
  PrintString(szMessage,4);
  return(bModified);
  }

ULONG QueryPort(char achBuffer[],ULONG cbBuffSize)
  {
//APIRET APIENTRY SplPdQueryPort(HAB hab,PSZ pszPortName,PVOID pBufIn,ULONG cbBuf,PULONG cItems)
  PFN pfnProcess;
  ULONG ulItemCount = 0;
  APIRET rc;

  sprintf(szMessage,"Querying %s",szPortName);
  PrintString(szMessage,3);
  if (hMod != 0)
    {
    if (DosQueryProcAddr(hMod,0,"SPLPDQUERYPORT",&pfnProcess) == NO_ERROR)
      rc = pfnProcess(habAnchorBlock,szPortName,achBuffer,cbBuffSize,&ulItemCount);
    else
      {
      ErrorNotify("Error Getting QUERYPORT Address");
      return(FALSE);
      }
    }
  else
    {
    sprintf(szMessage,"Error Loading Module %s",szModuleName);
    ErrorNotify(szMessage);
    return(FALSE);
    }
  if (rc != NO_ERROR)
    {
    sprintf(szMessage,"Error Querying Port - rc = %X",rc);
    ErrorNotify(szMessage);
    return(0);
    }
  sprintf(szMessage,"%s -> %s",szPortName,achBuffer);
  PrintString(szMessage,4);
  return(ulItemCount);
  }

ULONG EnumeratePorts(char achBuffer[],ULONG cbBuffSize)
  {
//APIRET APIENTRY SplPdEnumPort(HAB hab,PVOID pBuf,ULONG cbBuf,PULONG pulReturned,PULONG pulTotal,PULONG pcbRequired);
  ULONG ulReturned;
  ULONG ulTotal = 0;
  ULONG cbRequired;
  PFN pfnProcess;
  APIRET rc;

  if (hMod != 0)
    {
    if (DosQueryProcAddr(hMod,0,"SPLPDENUMPORT",&pfnProcess) == NO_ERROR)
      {
      if (pfnProcess(habAnchorBlock,0,0,&ulReturned,&ulTotal,&cbRequired) == ERROR_MORE_DATA)
        if (cbRequired <= cbBuffSize)
          rc = pfnProcess(habAnchorBlock,achBuffer,cbBuffSize,&ulReturned,&ulTotal,&cbRequired);
        else
          ulTotal = 0;
      }
    else
      {
      ErrorNotify("Error Getting ENUMPORT Address");
      return(FALSE);
      }
    }
  else
    {
    sprintf(szMessage,"Error Loading Module %s",szModuleName);
    ErrorNotify(szMessage);
    return(FALSE);
    }
  if (rc != NO_ERROR)
    {
    sprintf(szMessage,"Error Enumerating Port - rc = %X",rc);
    ErrorNotify(szMessage);
    return(0);
    }
  return(ulTotal);
  }

BOOL RemovePort(void)
  {
  PFN pfnProcess;
  APIRET rc;

  sprintf(szMessage,"Removing %s",szPortName);
  PrintString(szMessage,3);
  if (hMod != 0)
    {
    if (DosQueryProcAddr(hMod,0,"SPLPDREMOVEPORT",&pfnProcess) == NO_ERROR)
      rc = pfnProcess(habAnchorBlock,szPortName);
    else
      {
      ErrorNotify("Error Getting REMOVEPORT Address");
      return(FALSE);
      }
    }
  else
    {
    sprintf(szMessage,"Error Loading Module %s",szModuleName);
    ErrorNotify(szMessage);
    return(FALSE);
    }
  if (rc != NO_ERROR)
    {
    sprintf(szMessage,"Error Removing Port - rc = %X",rc);
    ErrorNotify(szMessage);
    return(FALSE);
    }
  sprintf(szMessage,"Port %s Removed",szPortName);
  PrintString(szMessage,4);
  return(TRUE);
  }

BOOL InstallPort(void)
  {
//APIRET APIENTRY SplPdInstallPort(HAB hab,PSZ pszPortName)
  PFN pfnProcess;
  APIRET rc;

  sprintf(szMessage,"Installing %s",szPortName);
  PrintString(szMessage,3);
  if (hMod != 0)
    {
    if (DosQueryProcAddr(hMod,0,"SPLPDINSTALLPORT",&pfnProcess) == NO_ERROR)
      rc = pfnProcess(habAnchorBlock,szPortName);
    else
      {
      ErrorNotify("Error Getting INSTALLPORT Address");
      return(FALSE);
      }
    }
  else
    {
    sprintf(szMessage,"Error Loading Module %s",szModuleName);
    ErrorNotify(szMessage);
    return(FALSE);
    }

  if (rc != NO_ERROR)
    {
    sprintf(szMessage,"Error Installing Port - rc = %X",rc);
    ErrorNotify(szMessage);
    return(FALSE);
    }
  sprintf(szMessage,"Port %s Installed",szPortName);
  PrintString(szMessage,4);
  return(TRUE);
  }

BOOL InitializePort(void)
  {
//APIRET APIENTRY SplPdInitPort(HFILE hCom,PSZ pszPortName)
  PFN pfnProcess;
  APIRET rc;
  HFILE hCom;
  ULONG ulAction;

  sprintf(szMessage,"Initializing %s",szPortName);
  PrintString(szMessage,3);
  if ((rc = DosOpen(szPortName,&hCom,&ulAction,0L,0L,0x0001,0x21c2,0L)) == NO_ERROR)
    {
    if (hMod != 0)
      {
      if (DosQueryProcAddr(hMod,0,"SPLPDINITPORT",&pfnProcess) == NO_ERROR)
        rc = pfnProcess(hCom,szPortName);
      else
        {
        ErrorNotify("Error Getting INITPORT Address");
        return(FALSE);
        }
      }
    else
      {
      sprintf(szMessage,"Error Loading Module %s",szModuleName);
      ErrorNotify(szMessage);
      return(FALSE);
      }
    DosClose(hCom);
    }
  if (rc != NO_ERROR)
    {
    sprintf(szMessage,"Error Initializing Port - rc = %X",rc);
    ErrorNotify(szMessage);
    return(FALSE);
    }
  sprintf(szMessage,"Port %s Initialized",szPortName);
  PrintString(szMessage,4);
  return(TRUE);
  }

BOOL TerminatePort(void)
  {
//APIRET APIENTRY SplPdInitPort(HFILE hCom,PSZ pszPortName)
  PFN pfnProcess;
  APIRET rc;
  HFILE hCom;
  ULONG ulAction;

  sprintf(szMessage,"Terminating %s",szPortName);
  PrintString(szMessage,3);
  if ((rc = DosOpen(szPortName,&hCom,&ulAction,0L,0L,0x0001,0x21c2,0L)) == NO_ERROR)
    {
    if (hMod != 0)
      {
      if (DosQueryProcAddr(hMod,0,"SPLPDTERMPORT",&pfnProcess) == NO_ERROR)
        rc = pfnProcess(hCom,szPortName);
      else
        {
        ErrorNotify("Error Getting TERMPORT Address");
        return(FALSE);
        }
      }
    else
      {
      sprintf(szMessage,"Error Loading Module %s",szModuleName);
      ErrorNotify(szMessage);
      return(FALSE);
      }
    DosClose(hCom);
    }
  if (rc != NO_ERROR)
    {
    sprintf(szMessage,"Error Terminating Port - rc = %X",rc);
    ErrorNotify(szMessage);
    return(FALSE);
    }
  sprintf(szMessage,"Port %s terminated",szPortName);
  PrintString(szMessage,4);
  return(TRUE);
  }

void PrintString(char szMessage[],ULONG ulLine)
  {
  HPS    hps;
  RECTL  rcl;
  POINTL ptl;

  ptl.y = (ulWindowHeight - (ulLine * (stCell.cy + 3)));
  ptl.x = stCell.cx;
  rcl.yBottom = (ptl.y - 3);
  rcl.yTop = (ptl.y + stCell.cy);
  rcl.xLeft = 0;
  rcl.xRight = ulWindowWidth;
  hps = WinGetPS(hwndClient);
  WinFillRect(hps,&rcl,CLR_WHITE);
  GpiCharStringAt(hps,&ptl,strlen(szMessage),szMessage);
  WinReleasePS(hps);
  }

void ErrorNotify(char szMessage[])
  {
  HPS    hps;
  RECTL  rcl;
  POINTL ptl;

  ptl.y = 2;
  ptl.x = stCell.cx;
  rcl.yBottom = 0;
  rcl.yTop = stCell.cy;
  rcl.xLeft = 0;
  rcl.xRight = ulWindowWidth;
  hps = WinGetPS(hwndClient);
  WinFillRect(hps,&rcl,CLR_WHITE);
  GpiCharStringAt(hps,&ptl,strlen(szMessage),szMessage);
  WinReleasePS(hps);
  }

void ClearScreen(void)
  {
  HPS     hps;
  RECTL   rcl;

  WinInvalidateRect(hwndClient,(PRECTL)NULL,FALSE);
  hps = WinBeginPaint(hwndClient,(HPS)0,(PRECTL)&rcl);
  GpiSetColor(hps,CLR_WHITE);
  GpiSetBackColor(hps,CLR_BLUE);
  GpiSetBackMix(hps,BM_OVERPAINT);
  WinFillRect(hps,&rcl,CLR_WHITE);
  WinEndPaint(hps);
  }

void Paint(void)
  {
  HPS     hps;
  RECTL   rcl;

  hps = WinBeginPaint(hwndClient,(HPS)0,(PRECTL)&rcl);
  GpiSetColor(hps,CLR_WHITE);
  GpiSetBackColor(hps,CLR_BLUE);
  GpiSetBackMix(hps,BM_OVERPAINT);
  WinFillRect(hps,&rcl,CLR_WHITE);
  WinEndPaint(hps);
  }


/**************************************************************************/
/* WNDSIZE:                                                               */
/* This function positions the Presentation Space correctly within a      */
/* sized window.  It adjusts the origin when necessary, so that there     */
/* are no gaps between the edge of the Presentation Space and the window  */
/* border.                                                                */
/**************************************************************************/
BOOL WndSize(HWND hwnd,MPARAM mp2)
  {
  RECTL rcl;

  usWndDepth = HIUSHORT(mp2)/ stCell.cy;
  usWndWidth = LOUSHORT(mp2)/ stCell.cx;

  /************************************************************************/
  /* The test below caters for the first instance of WM_SIZE that invokes */
  /* this function BEFORE window creation is complete and the Frame handle*/
  /* has been set.                                                        */
  /************************************************************************/

  hwndFrame = (hwndFrame != (HWND)0) ? hwndFrame : WinQueryWindow(hwnd,QW_PARENT);
  WinQueryWindowRect(hwndClient,&rcl);
  ulWindowWidth = rcl.xRight;
  ulWindowHeight = rcl.yTop;
  WinInvalidateRect(hwnd,(PRECTL)0,FALSE);
  return(TRUE);
  }

MRESULT EXPENTRY fnwpSelectPortDlg(HWND hwnd,USHORT msg,MPARAM mp1,MPARAM mp2)
  {
  int iIndex;
  int iItemSelected;
  BOOL bItemSelected;
  int iCOMindex;
  int iTempIndex;
  int iFirstItem;
  BYTE *pByte;
  ULONG *pulPtr;

  switch (msg)
    {
    case WM_INITDLG:
      CenterDlgBox(hwnd);
      if ((ulPortCount = EnumeratePorts(achBuffer,4096)) != 0)
        {
        pulPtr = (PULONG)achBuffer;
        bItemSelected = FALSE;
        for (iIndex = 0;iIndex < ulPortCount;iIndex++)
          {
          stPorts[iIndex].pszPortName = (char *)*(pulPtr++);
          stPorts[iIndex].pszPortDesc = (char *)*(pulPtr++);
          WinSendDlgItemMsg(hwnd,PS_NAME_LIST,LM_INSERTITEM,MPFROMSHORT(LIT_END),MPFROMP(stPorts[iIndex].pszPortName));
          if (strcmp(szPortName,stPorts[iIndex].pszPortName) == 0)
            {
            bItemSelected = TRUE;
            WinSendDlgItemMsg(hwnd,PS_NAME_LIST,LM_SELECTITEM,MPFROMSHORT(iIndex),MPFROMSHORT(TRUE));
            }
          }
        if (!bItemSelected)
          WinSendDlgItemMsg(hwnd,PS_NAME_LIST,LM_SELECTITEM,MPFROMSHORT(0),MPFROMSHORT(TRUE));
        }
      else
        WinDismissDlg(hwnd,FALSE);
      break;
    case WM_COMMAND:
      switch(SHORT1FROMMP(mp1))
        {
        case DID_OK:
          iItemSelected = (SHORT)WinSendDlgItemMsg(hwnd,PS_NAME_LIST,LM_QUERYSELECTION,0L,0L);
          WinSendDlgItemMsg(hwnd,PS_NAME_LIST,LM_QUERYITEMTEXT,MPFROM2SHORT(iItemSelected,9),MPFROMP(szPortName));
          strcpy(szPortDesc,stPorts[iItemSelected].pszPortDesc);
          sprintf(szMessage,"Port %s Selected",szPortName);
          PrintString(szMessage,1);
          MenuItemEnable(hwndFrame,IDM_PROCESS,TRUE);
          WinDismissDlg(hwnd,TRUE);
          break;
        case DID_CANCEL:
          WinDismissDlg(hwnd,FALSE);
          break;
        default:
          return WinDefDlgProc(hwnd,msg,mp1,mp2);
        }
      break;
    default:
      return(WinDefDlgProc(hwnd,msg,mp1,mp2));
    }
  return(FALSE);
  }

BOOL RecoverProfile(HINI hProfile)
  {
  HINI hDestProfile;
  HINI hSourceProfile;
  APIRET rc;
  char szTempFile[40];
  char *pIniFile;
  PRFPROFILE stProfileNames;

  stProfileNames.cchUserName = 0;
  stProfileNames.cchSysName = 0;
  PrfQueryProfile(habAnchorBlock,&stProfileNames);
  stProfileNames.pszUserName = malloc(stProfileNames.cchUserName + 1);
  stProfileNames.pszSysName = malloc(stProfileNames.cchSysName + 1);
  PrfQueryProfile(habAnchorBlock,&stProfileNames);
  if (hProfile == HINI_USERPROFILE)
    strcpy(szTempFile,"C:\\OS2\\DLL\\_USER_.INI");
  else
    strcpy(szTempFile,"C:\\OS2\\DLL\\_SYSTEM_.INI");
  if ((hDestProfile = PrfOpenProfile(habAnchorBlock,szTempFile)) != 0)
    {
    if (CopyProfile(hProfile,hDestProfile))
      {
      if (PrfCloseProfile(hDestProfile))
        {
        if (hProfile == HINI_USERPROFILE)
          {
          pIniFile = stProfileNames.pszUserName;
          stProfileNames.pszUserName = szTempFile;
          stProfileNames.cchUserName = sizeof(szTempFile);
          }
        else
          {
          pIniFile = stProfileNames.pszSysName;
          stProfileNames.pszSysName = szTempFile;
          stProfileNames.cchSysName = sizeof(szTempFile);
          }
        if (PrfReset(habAnchorBlock,&stProfileNames))
          {
          DosCopy(szTempFile,pIniFile,DCPY_EXISTING);
          if (hProfile == HINI_USERPROFILE)
            {
            stProfileNames.pszUserName = pIniFile;
            stProfileNames.cchUserName = sizeof(pIniFile);
            }
          else
            {
            stProfileNames.pszSysName = pIniFile;
            stProfileNames.cchSysName = sizeof(pIniFile);
            }
          if (PrfReset(habAnchorBlock,&stProfileNames))
            DosDelete(szTempFile);
          }
        }
      }
    else
      PrfCloseProfile(hDestProfile);
    }
  free(stProfileNames.pszUserName);
  free(stProfileNames.pszSysName);
  PrintString("Profile Recovery Complete",5);
  return(TRUE);
  }

BOOL CopyProfile(HINI hSourceProfile,HINI hDestinationProfile)
  {
  int iAppIndex;
  int iKeyIndex;
  char *pKeyNames;
  char *pAppNames;
  char *pAppName;
  char *pKeyName;
  ULONG ulAppSize;
  ULONG ulDataSize;
  ULONG ulKeySize;
  void *pData;

  PrfQueryProfileSize(hSourceProfile,0L,0L,&ulAppSize);
  if ((pAppNames = malloc(ulAppSize + 1)) == NULL)
    return(FALSE);
  PrfQueryProfileString(hSourceProfile,0L,0L,0L,pAppNames,ulAppSize);
  iAppIndex = 0;
  while (iAppIndex < ulAppSize)
    {
    pAppName = &pAppNames[iAppIndex];
    PrfQueryProfileSize(hSourceProfile,pAppName,0L,&ulKeySize);
    if ((pKeyNames = malloc(ulKeySize + 1)) == NULL)
      {
      free (pAppNames);
      return(FALSE);
      }
    PrfQueryProfileString(hSourceProfile,pAppName,0L,0L,pKeyNames,ulKeySize);
    iKeyIndex = 0;
    while (iKeyIndex < ulKeySize)
      {
      pKeyName = &pKeyNames[iKeyIndex];
      PrfQueryProfileSize(hSourceProfile,pAppName,pKeyName,&ulDataSize);
      if ((pData = malloc(ulDataSize + 1)) != NULL)
        {
        PrfQueryProfileData(hSourceProfile,pAppName,pKeyName,pData,&ulDataSize);
        PrfWriteProfileData(hDestinationProfile,pAppName,pKeyName,pData,ulDataSize);
        free(pData);
        }
      while(pKeyNames[iKeyIndex++] != 0);
      if (pKeyNames[iKeyIndex] == 0)
        break;;
      }
    free(pKeyNames);
    while(pAppNames[iAppIndex++] != 0);
    if (pAppNames[iAppIndex] == 0)
      break;;
    }
  free(pAppNames);
  return(TRUE);
  }



