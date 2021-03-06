/************************************************************************
**
** $Revision: $
**
** $Log: $
**
************************************************************************/

#ifndef COMDD_INCLUDED

#ifdef building_DD

 #ifdef x16_BIT
  #define SHARE
  #define NO_COMscope
  #pragma message ("building 16 bit (OS/2 1.x) version")
 #else
  #ifdef SHARE
   #define NO_COMscope
   #define MAX_DEVICE      4
   #pragma message ("building Personal COMi without COMscope")
  #endif
  #ifdef SHARE_COMscope
   #define SHARE
   #define NO_ADV_UARTS
   #define MAX_DEVICE      4
   #pragma message ("building Personal COMi with COMscope")
  #endif
 #endif

 #ifdef DigiBoard
  #define MAX_DEVICE      16
  #define OEM
  #define MAX_PCI_ADAPTERS 0
  #pragma message ("building DigiBoard version")
 #else
  #ifdef Comtrol
   #define OEM
   #define MAX_PCI_ADAPTERS 0
   #pragma message ("building Comtrol version")
  #else
   #ifdef Quatech
    #define OEM
    #define MAX_PCI_ADAPTERS 0
    #pragma message ("building Quatech version")
   #else
    #ifdef ConnecTech
     #define OEM
     #define MAX_PCI_ADAPTERS 1
     #define OEM_PCI_VENDOR PCI_VENDOR_CONNECTECH
     #pragma message ("building Connect Tech DFLEX version")
    #else
     #ifdef Globetek
      #define OEM
      #define MAX_PCI_ADAPTERS 1
      #define OEM_PCI_VENDOR PCI_VENDOR_GLOBETEK
      #pragma message ("building Globetek version")
     #else
      #ifdef Sealevel_Retail
       #define OEM_GA
       #define NO_COMscope
       #define MAX_PCI_ADAPTERS 1
       #define OEM_PCI_VENDOR PCI_VENDOR_SEALEVEL
       #pragma message ("building Sealevel Systems retail version")
      #else
       #ifdef Sealevel
        #define OEM
        #define MAX_PCI_ADAPTERS 1
        #define OEM_PCI_VENDOR PCI_VENDOR_SEALEVEL
        #pragma message ("building Sealevel Systems OEM version")
       #else
        #ifdef Neotech
         #define OEM
         #define NoISAsupport
         #define MAX_PCI_ADAPTERS 0
         #pragma message ("building Neotech version")
        #else
         #ifdef Moxa
          #define OEM
          #define MAX_PCI_ADAPTERS 1
          #define OEM_PCI_VENDOR PCI_VENDOR_MOXA
          #pragma message ("building Moxa version")
         #else
          #ifdef Boca
           #define OEM
           #define MAX_PCI_ADAPTERS 0
           #pragma message ("building Boca Research version")
          #else
           #ifndef SHARE
            #define PAGE_SUPPORT
           #endif
          #endif
         #endif
        #endif
       #endif
      #endif
     #endif
    #endif
   #endif
  #endif
 #endif

 #ifndef MAX_DEVICE
  #define MAX_DEVICE      8
 #endif
 #ifdef OEM
  #ifndef SHARE
   #define SHARE
  #endif
  #ifndef NO_COMscope
   #define NO_COMscope
  #endif
 #endif

 #ifdef DEMO
  #pragma message ("building evaluation version")
 #endif

 #if MAX_DEVICE == 8
  #pragma message ("MAX_DEVICE = 8")
 #elif MAX_DEVICE == 16
  #pragma message ("MAX_DEVICE = 16")
 #elif MAX_DEVICE == 4
  #pragma message ("MAX_DEVICE = 4")
 #endif

#endif // building_DD

#ifndef MAX_PCI_ADAPTERS
#define MAX_PCI_ADAPTERS 4
#endif

#ifndef CCHMAXPATH
#define CCHMAXPATH 256
#endif

typedef USHORT WORD;

typedef USHORT sBOOL;
typedef ULONG DWORD;
typedef WORD FLAG;

#define FOUND_TOKEN TRUE
#define SKIP_EOL TRUE
#define TO_EOL FALSE

#define MAX_BUFFER 0x8001

#define F1_ENABLE_DTR              '\x01'
#define F1_ENABLE_DTR_INPUT_HS     '\x02'
#define F1_DTR_MASK                '\x03'
#define F1_ENABLE_DSR_INPUT_HS     '\x40'
#define F1_ENABLE_DCD_OUTPUT_HS    '\x20'
#define F1_ENABLE_DSR_OUTPUT_HS    '\x10'
#define F1_ENABLE_CTS_OUTPUT_HS    '\x08'

#define F1_DEFAULT                  F1_ENABLE_DTR

#define F2_ENABLE_RTS                   '\x40'
#define F2_ENABLE_RTS_INPUT_HS          '\x80'
#define F2_ENABLE_RTS_TOG_ON_XMIT       '\xc0'
#define F2_RTS_MASK                     '\xc0'

#define F2_ENABLE_FULL_DUPLEX           '\x20'

#define F2_ENABLE_BREAK_REPL            '\x10'
#define F2_ENABLE_NULL_STRIP            '\x08'
#define F2_ENABLE_ERROR_REPL            '\x04'

#define F2_ENABLE_RCV_XON_XOFF_FLOW     '\x02'
#define F2_ENABLE_XMIT_XON_XOFF_FLOW    '\x01'

#define F2_DEFAULT                      F2_ENABLE_RTS

#define F3_USE_TX_BUFFER                '\x80'
#define F3_RECEIVE_TRIG_MASK            '\x60'
#define F3_1_CHARACTER_FIFO             '\x00'
#define F3_4_CHARACTER_FIFO             '\x20'
#define F3_8_CHARACTER_FIFO             '\x40'
#define F3_14_CHARACTER_FIFO            '\x60'
#define F3_HDW_BUFFER_MASK              '\x18'
#define F3_HDW_BUFFER_DISABLE           '\x08'
#define F3_HDW_BUFFER_ENABLE            '\x10'
#define F3_HDW_BUFFER_APO               '\x18'
#define F3_FIFO_MASK                    '\xf8'
#define F3_WAIT_NORM                    '\x02'
#define F3_WAIT_NONE                    '\x06'
#define F3_WAIT_SOMETHING               '\x04'
#define F3_RTO_MASK                     '\x06'
#define F3_INFINITE_WRT_TIMEOUT         '\x01'
#define F3_DEFAULT (F3_USE_TX_BUFFER | F3_14_CHARACTER_FIFO | F3_HDW_BUFFER_ENABLE | F3_WAIT_NORM)

#define DEF_WRITE_TIMEOUT             6000
#define DEF_READ_TIMEOUT              6000
#define DEF_LINE_CHARACTERISTICS      '\x03'
#define DEF_DATA_LEN_MASK             '\xff'

#define ALGO_POLL                     0x0000
#define ALGO_SELECT                   0x0001
#define ALGO_HYBRID                   0x0002

#define ALGO_VECT_POLL               0
#define ALGO_VECT_ID_IS_BITS_ON      2
#define ALGO_VECT_DigiBoard_ID       4
#define ALGO_VECT_TEST_ZERO          6
#define ALGO_VECT_TEST_FF            8
#define ALGO_VECT_ID_IS_BITS_OFF    10

#define LOAD_FLAG1_SCRATCH_IS_INT_ID      0x0001 // these must match CFG_FLAG1 bits
#define LOAD_FLAG1_DIGIBOARD08_INT_ID     0x0002
#define LOAD_FLAG1_DIGIBOARD16_INT_ID     0x0004
#define LOAD_FLAG1_TIB_UART               0x0008
#define LOAD_FLAG1_INT_ID_LOAD_MASK       0x800f

#define LOAD_FLAG1_ENABLE_ALL_OUT2        0x0400
#define LOAD_FLAG1_ADVANCED_CFG           0x0800
#define LOAD_FLAG1_INT_ID_REQ             0x8000
#define LOAD_FLAG1_VERBOSE                0x4000
#define LOAD_FLAG1_PRINT_LOCAL            0x2000
#define LOAD_FLAG1_NO_IRRITATION          0x1000

#define CFG_FLAG1_FORCE_4X_TEST          0x0001
//#define CFG_FLAG1_SCRATCH_IS_INT_ID      0x0001
//define CFG_FLAG1_DIGIBOARD08_INT_ID     0x0002
//#define CFG_FLAG1_DIGIBOARD16_INT_ID     0x0004
#define CFG_FLAG1_TIB_UART               0x0008
//#define CFG_FLAG1_INT_ID_LOAD_MASK       0x000f

#define CFG_FLAG1_NORMALIZE_BAUD           0x0010
//#define CFG_FLAG1_USE_HDW_HS             0x0020

#define CFG_FLAG1_COMSCOPE               0x0040
#define CFG_FLAG1_EXPLICIT_BAUD_DIVISOR  0x0080
#define CFG_FLAG1_EXT_MODEM_CTL          0x0100
#define CFG_FLAG1_EXT_ENABLED            0x0200
#define CFG_FLAG1_NO_BREAK_REPORT        0x0400
#define CFG_FLAG1_NO_MODEM_INT           0x0800
#define CFG_FLAG1_TESTS_DISABLE          0x1000
#define CFG_FLAG1_FOREIGN_UART           0x2000
#define CFG_FLAG1_MULTI_INT              0x4000
#define CFG_FLAG1_EXCLUSIVE_ACCESS       0x8000


#define CFG_FLAG2_HDW_TX_XON_HS          0x0100   // these must match FIFO_FLG bits
#define CFG_FLAG2_HDW_RX_XON_HS          0x0200
//#define CFG_FLAG2_HDW_XON_MASK           0x0330
#define CFG_FLAG2_HDW_CTS_HS             0x0400
#define CFG_FLAG2_HDW_RTS_HS             0x0800
//#define CFG_FLAG2_HDW_CTS_RTS_MASK       0x0cc0
//#define CFG_FLAG2_HDW_TX_XON_WAS         0x0010
//#define CFG_FLAG2_HDW_RX_XON_WAS         0x0020
//#define CFG_FLAG2_HDW_CTS_WAS            0x0040
//#define CFG_FLAG2_HDW_RTS_WAS            0x0080
//#define CFG_FLAG2_HDW_WAS_MASK           0x00f0
#define CFG_FLAG2_ALLOW16750RTSCTL       0x0001
#define CFG_FLAG2_ACTIVATE_OUT1          0x0002

#define CFG_FLAG2_EXPLICIT_TX_LOAD       0x4000
#define CFG_FLAG2_LOW_16750_TRIG         0x8000
#define CFG_FLAG2_NO_DCB_UPDATE          0x2000
#define CFG_FLAG2_FIFO_MASK              0xe000

#define SYS_DB_ENABLED                  0x0008
//#define SYS_DB_INT_ENTERED              0x0002
#define SYS_DB_NO_EVAL_LIMIT            0x2000
#define SYS_DB_NO_EVAL_MESSAGE          0x4000
//#define SYS_DB_SPURIOUS_OCCURRED        0x0001

/*
** miscellanious controls, command line option
*/
#define MISC_CTL_16_BIT_ADDRESSES      0x8000

#define LINE_ST_PARITY_ERROR    '\x04'
#define LINE_ST_OVERRUN_ERROR   '\x02'
#define LINE_ST_FRAMING_ERROR   '\x08'
#define LINE_CTL_PARITY_0       '\x38'
#define LINE_CTL_PARITY_1       '\x28'
#define LINE_CTL_ODD_PARITY     '\x08'
#define LINE_CTL_EVEN_PARITY    '\x18'

#define LINE_CTL_WORD_LEN_MASK  '\x07'
#define LINE_CTL_WL5            '\x00'
#define LINE_CTL_WL6            '\x01'
#define LINE_CTL_WL7            '\x02'
#define LINE_CTL_WL8            '\x03'
#define LINE_CTL_SB1            '\x00'
#define LINE_CTL_SB1_5          '\x04'
#define LINE_CTL_SB2            '\x04'

#define LINE_CTL_SEND_BREAK     '\x40'

#define MDM_CTL_RTS_ACTIVATE    '\x02'
#define MDM_CTL_DTR_ACTIVATE    '\x01'
#define MDM_CTL_OUT1_ACTIVATE   '\x04'

#define MDM_ST_DELTA_CTS        '\x01'
#define MDM_ST_DELTA_DSR        '\x02'
#define MDM_ST_DELTA_TRI        '\x04'
#define MDM_ST_DELTA_DCD        '\x08'
#define MDM_ST_CTS              '\x10'
#define MDM_ST_DSR              '\x20'
#define MDM_ST_TRI              '\x40'
#define MDM_ST_DCD              '\x80'

typedef struct _stConfigParms
  {
  WORD wConfigFlags1;
  WORD wConfigFlags2;
  WORD wCOMscopeBuffLen;
  WORD wIObaseAddress;
  WORD wReadBufferLength;
  WORD wWrtBufferLength;
  WORD wTxFIFOload;
  WORD wFlags1;
  WORD wFlags2;
  WORD wFlags3;
  WORD wWrtTimeout;
  WORD wRdTimeout;
  ULONG ulBaudRate;
  WORD wIntIDregister;
  BYTE byMaxWritePktCount;
  BYTE byMaxReadPktCount;
  BYTE byInterruptLevel;
  BYTE byLineCharacteristics;
  BYTE byErrorChar;
  BYTE byBreakChar;
  BYTE byXonChar;
  BYTE byXoffChar;
  WORD wXonHysteresis;
  WORD wXoffThreshold;
  }COMDCB;

typedef struct
  {
  DWORD  hAdapter;
  DWORD  hLDev;
  DWORD  hSysName;
  }RMDEF;

/*
** Device Driver OEM type "byLoadOEMtype"
**
** used to tell Device Driver what type of OEM adapter is being expected, if any
**
** used only during initialization
*/
#define HDWTYPE_NONE        0
#define HDWTYPE_ONE         1
#define HDWTYPE_TWO         2
#define HDWTYPE_THREE       3
#define HDWTYPE_FOUR        4
#define HDWTYPE_FIVE        5
#define HDWTYPE_SIX         6
#define HDWTYPE_SEVEN       7
#define HDWTYPE_EIGHT       8
#define HDWTYPE_PCI         9

#define HDWTYPE_CONNECTECH  0x63
#define HDWTYPE_DIGIBOARD   0x64

/*
** Device Driver OEM types "byDDOEMtype"
**
** used to tell CONFIG what type of OEM adapter is being used, if any
*/
#define OEM_OTHER            0
#define OEM_SEALEVEL         1
#define OEM_COMTROL          2
#define OEM_DIGIBOARD08      3
#define OEM_QUATECH          4
#define OEM_DIGIBOARD16      5
#define OEM_NEOTECH          6
#define OEM_CONNECTECH       7
#define OEM_GLOBETEK         8
#define OEM_BOCA             9
#define OEM_SEALEVEL_RET    10
#define OEM_MOXA            11

#define BUSTYPE_EISA    1   // matches MACH_x in RMhelp.h
#define BUSTYPE_MCA     2
#define BUSTYPE_PCMCIA  3
#define BUSTYPE_ISA     4
#define BUSTYPE_PCI     5

#ifdef building_DD

 #ifndef DD_level
#define DD_level 2
 #endif


typedef struct _stDevHead
  {
  void _far *pNextHeader;
  WORD DevAttributes;
  WORD StrategyOffset;
  WORD IDCoffset;
  BYTE abyDeviceName[8];
  WORD wProtectCS;
  WORD wProtectDS;
  WORD wRealCS;
  WORD wRealDS;
#if DD_level > 2
  DWORD dwDevCaps;
#endif
  }DEVHEAD;

#endif // building_DD

typedef struct _stDCBheader
  {
  char abyPortName[8];
  sBOOL bHeaderIsInitialized;
  WORD oNextDCBheader;
  WORD wOptionFlags1;
  WORD wOptionFlags2;
  COMDCB stComDCB;
  }DCBHEAD;

#define COMi_OPT1_PDR_SUPPORT 0x0001

typedef struct
  {
  WORD wXonThreshold;
  WORD wXoffThreshold;
  BYTE byMaxWritePackets;
  BYTE byMaxReadPackest;
  }DDTHRESHOLDS;

typedef struct
  {
  WORD wFIFOsize;
  WORD wTxFIFOload;
  WORD wFIFOflags;
  ULONG ulReserved;
  }FIFOINF;

typedef struct
  {
  WORD wTxFIFOload;
  WORD wFIFOflags;
  ULONG ulReserved;
  }FIFODEF;

#ifdef allow_16650_HDW_Xon_HS
#define FIFO_FLG_HDW_TX_XON_HS           0x0100  // these must match CFG_FLAG2 bits
#define FIFO_FLG_HDW_RX_XON_HS           0x0200
#define FIFO_FLG_HDW_HS_MASK             0x0f00
#else
#define FIFO_FLG_HDW_HS_MASK             0x0c00
#endif
#define FIFO_FLG_HDW_CTS_HS              0x0400
#define FIFO_FLG_HDW_RTS_HS              0x0800
#define FIFO_FLG_EXPLICIT_TX_LOAD        0x4000
#define FIFO_FLG_LOW_16750_TRIG          0x8000
#define FIFO_FLG_NO_DCB_UPDATE           0x2000
#define FIFO_FLG_NO_HDW_HS_SUPPORT       0x1000
#define FIFO_FLG_FUNC_MASK               0xf000
#define FIFO_FLG_TYPE_MASK               0x000f // used to mask device flags2 UART type bits
#define FIFO_FLG_TYPE_16650              0x0001 //DEV_FLAG2_16650_UART
#define FIFO_FLG_TYPE_16750              0x0002 //DEV_FLAG2_16750_UART
#define FIFO_FLG_TYPE_16654              0x0004 //DEV_FLAG2_16654_UART
#define FIFO_FLG_TYPE_TI16550C           0x0008 //DEV_FLAG2_TI16550C_UART

#define FIFO_FLG_DEF_HDW_HS              0x1000 // used only by CONFIG DLL with wDeviceFlags2

#define OEMHLP_CATEGORY          0x80
#define OEMHLP_FUNC_PCI          0x0b
#define OEMHLP_GET_PCI_BIOS_INFO 0x00
#define OEMHLP_PCI_DEVICE        0x01
#define OEMHLP_PCI_CLASSCODE     0x02
#define OEMHLP_PCI_GET_DATA      0x03
#define OEMHLP_PCI_SET_DATA      0x04

#define PCICFG_IRQ_REG          0x003c
#define PCICFG_MSK_IRQ_PIN      0xff00
#define PCICFG_MSK_IRQ_LINE     0x00ff

#define PCICFG_VEN_DEV_REG         0x00
#define PCICFG_BASEADDR_REG        0x10
#define PCICFG_MSK_IS_IO_SPACE     0x01

#define PCI_CLASSCODE_GENERIC_SERIAL 0x070000
#define PCI_CLASSCODE_SERIAL_16450   0x070001
#define PCI_CLASSCODE_SERIAL_16550   0x070002
#define PCI_CLASSCODE_SERIAL_16650   0x070003
#define PCI_CLASSCODE_SERIAL_16750   0x070004
#define PCI_CLASSCODE_SERIAL_16850   0x070005
#define PCI_CLASSCODE_SERIAL_16950   0x070006
#define PCI_CLASSCODE_MOXA           0x070080
#define PCI_CLASSCODE_MULTIPORT      0x070200
#define PCI_CLASSCODE_GENERIC_MODEM  0x070300
#define PCI_CLASSCODE_16450_MODEM    0x070301
#define PCI_CLASSCODE_16550_MODEM    0x070302
#define PCI_CLASSCODE_16650_MODEM    0x070303
#define PCI_CLASSCODE_16750_MODEM    0x070304
#define PCI_CLASSCODE_16850_MODEM    0x070305
#define PCI_CLASSCODE_16950_MODEM    0x070306
#define PCI_CLASSCODE_OTHER          0x078000


#define PCI_VENDOR_3COM         0x12b9
#define PCI_DEVICE_3COM_MODEM   0x1008  // Sportster PCI modem

#define PCI_VENDOR_GLOBETEK     0x151a
#define PCI_DEVICE_GT_1002      0x1002
#define PCI_DEVICE_GT_1004      0x1004
#define PCI_DEVICE_GT_1008      0x1008

#define PCI_VENDOR_SUNIX        0x1409
#define PCI_DEVICE_SU_4055A     0x7168  // 4 port 16750 64 byte FIFOs, 8X clock

#define PCI_VENDOR_MOXA         0x1393
#define PCI_DEVICE_MX_C104H     0x1040
#define PCI_DEVICE_MX_C168H     0x1680

#define PCI_VENDOR_SEALEVEL     0x135e
#define PCI_DEVICE_SL_7101      0x7101   // one port ultra
#define PCI_DEVICE_SL_7102      0x7102   // 1 Port
#define PCI_DEVICE_SL_7103      0x7103   // 1 Port
#define PCI_DEVICE_SL_7104      0x7104   // 1 Port
#define PCI_DEVICE_SL_7105      0x7105   // 1 Port
#define PCI_DEVICE_SL_7201      0x7201   // two port ultra
#define PCI_DEVICE_SL_7202      0x7202   // two port
#define PCI_DEVICE_SL_7203      0x7203   // 2 Port
#define PCI_DEVICE_SL_7401      0x7401   // four port ultra
#define PCI_DEVICE_SL_7402      0x7402   // four port
#define PCI_DEVICE_SL_7404      0x7404   // four port - RS-485/422
#define PCI_DEVICE_SL_7405      0x7405   // 4 Port
#define PCI_DEVICE_SL_7801      0x7801   // eight port
#define PCI_DEVICE_SL_7901      0x7901   // 2 Ports
#define PCI_DEVICE_SL_7903      0x7903   // 2 Ports
#define PCI_DEVICE_SL_7904      0x7904   // 4 Ports
#define PCI_DEVICE_SL_7905      0x7905   // 8 Ports

#define PCI_VENDOR_CONNECTECH   0x11B0
#define PCI_DEVICE_BH_V960      0x0001
#define PCI_DEVICE_BH_V961      0x0002
#define PCI_DEVICE_BH_V962      0x0004
#define PCI_DEVICE_BH_V292      0x0010

typedef struct
  {
  BYTE xSubFunc;
  WORD wDeviceID;
  WORD wVendorID;
  BYTE xIndex;
  }PCIP_DEVICE;

typedef struct
  {
  BYTE xSubFunc;
  ULONG ulClassCode;
  BYTE xIndex;
  }PCIP_CLASSCODE;

typedef struct
  {
  BYTE xSubFunc;
  BYTE xBusNum;
  BYTE xDevFuncNum;
  BYTE xConfigReg;
  BYTE xSize;
//  ULONG ulData;
  }PCIP_CONFIG;

typedef struct
  {
  BYTE xReturnCode;
  BYTE xHdwMechanism;
  BYTE xMajorVersion;
  BYTE xMinorVersion;
  BYTE xLastBus;
  }PCID_BIOSINFO;

typedef struct
  {
  BYTE xReturnCode;
  BYTE xBusNum;
  BYTE xDevFuncNum;
  }PCID_DEVICE;

typedef struct
  {
  BYTE xReturnCode;
  ULONG ulData;
  }PCID_CONFIG;

typedef struct
  {
  BYTE xDevFuncNum;
  BYTE xBusNum;
  BYTE xIndex;
  BYTE xIRQ;
  SHORT usVendorID;
  SHORT usDeviceID;
  ULONG ulClassCode;
  USHORT usBaseAddress0;
  USHORT usBaseAddress1;
  USHORT usBaseAddress2;
  USHORT usBaseAddress3;
  USHORT usBaseAddress4;
  USHORT usBaseAddress5;
  }PCIADPT;

typedef struct
  {
  WORD wAddress;
  BYTE byInterrupt;
  }MCAPORT;

#define ADP_MISC_DATA_SIZE 27 // this must be adjusted when any changes are made to
                              // the structure below for downward compatibility.
typedef struct _stConfigurationHeader
  {
  WORD wDeviceCount;
  WORD wDCBcount;
  WORD wDelayCount;
  ULONG ulCFGheadDummy;
  BYTE byAdapterType;
  BYTE byInterruptLevel;
  WORD wOEMentryVector;
  WORD wOEMexitVector;
  WORD wIntAlgorithim;
  WORD wLoadFlags;
  WORD wIntIDregister;
  sBOOL bHeaderIsAvailable;
  sBOOL bHeaderIsInitialized;
  WORD oNextCFGheader;
  WORD oFirstDCBheader;
  WORD wPCIvendor;
  WORD wPCIdevice;
  BYTE byPCIslot;
  union
    {
    WORD awData[ADP_MISC_DATA_SIZE / 2];
    BYTE abyData[ADP_MISC_DATA_SIZE];
    }MISC;
  }CFGHEAD;

#define INI_MISC_DATA_SIZE 30 // this must be adjusted when any changes are made to
                              // the structure below for downward compatibility.
typedef struct
  {
  ULONG ulSignature;
  WORD wFlags;
  WORD wCFGheaderCount;
  WORD oFirstCFGheader;
  WORD oCOMscopeIniOffset;
  BYTE byNextPCIslot;
  BYTE byOEMtype;
  union
    {
    WORD awData[INI_MISC_DATA_SIZE / 2];
    BYTE abyData[INI_MISC_DATA_SIZE];
    }MISC;
  }CFGINFO;

typedef struct
  {
  WORD wDevBlkOffset;
  WORD wBlockLen;
  WORD wLID;
  WORD wBaseAddress;
  WORD wDeviceNumber;
  WORD bNameTaken;
  BYTE fFlags;
  BYTE byInterruptLevel;
  WORD dummy;
  }LIDTAB;

typedef struct
  {
  WORD wDeviceBlockLength;
  BYTE byRevision;
  BYTE bySecondaryID;
  WORD wLogicalID;
  WORD wDeviceID;
  WORD wExclusivePortPairCount;
  WORD wCommonPortPairCount;
  WORD wDataArea;
  }DEVBLK;

typedef struct
  {
  DWORD IDCaccessRM;
  WORD IDCaccessRDS;
  DWORD IDCaccessPM;
  WORD IDCaccessPDS;
  }ADDENTRY;


#define LID_ALREADY_OWNED  1
#define LID_DOES_NOT_EXIST 2
#define LID_AVAILABLE      8

#define PORT_USER_DISABLED     0xffff
#define PORT_LID_ALREADY_OWNED 0xfffe
#define PORT_OWNED_BY_OTHER_DD 0xfffd
#define PORT_ADDRESS_INVALID   0xfffc
#define PORT_ADDRESS_TAKEN     0xfffb

#define NO_INI_FILE            0xffff
#define FILE_ACCESS_ERROR      0xc000
#define NO_DEFINED_DEVICES     0x8000

#define DRIVER_ATTACHED    0
#define DRIVER_NOT_FOUND   1
#define NO_IDC_ENTRY       2

#define ASYNC_DEVICE_ID    6

//#define NO_ERROR                 0
#define ERROR_LID_ALREADY_OWNED  1
#define ERROR_LID_DOES_NOT_EXIST 2
#define ERROR_LID_NOT_YOUR_LID   4

#define MIN_INT_LEVEL 2
#define MAX_INT_LEVEL 15

#define MIN_BASE_ADDRESS 0x0000
#define MAX_BASE_ADDRESS 0xffff

#define DISP_HEX    0
#define DISP_DEC    1
#define DISP_BIN    2
#define DISP_CHEX   3
#define DISP_AHEX   4

#define MIN_WRITE_PKT_QUEUE         1
#define MIN_READ_PKT_QUEUE          1
#define MAX_WRITE_PKT_QUEUE         255
#define MAX_READ_PKT_QUEUE          255
#define DEF_WRITE_PKT_QUEUE         6
#define DEF_READ_PKT_QUEUE          6

#define MAX_RTS_OFF_DELAY           32
#define MIN_RTS_OFF_DELAY           2
#define DEF_RTS_OFF_DELAY           3

#define MIN_READ_BUFF_LEN       0x400
#define MAX_READ_BUFF_LEN       0x10000
#define DEF_READ_BUFF_LEN       0x1000
#define MIN_COMscope_BUFF_LEN   0x400
#define MAX_COMscope_BUFF_LEN   0x8000
#define DEF_COMscope_BUFF_LEN   0x1000
#define MAX_WRITE_BUFF_LEN      0x4000
#define MIN_WRITE_BUFF_LEN      0x80
#define DEF_WRITE_BUFF_LEN      0x100

#define DEF_CLOCK_RATE    32

#define DEF_BAUD          9600
#define DEF_BAUD_DIVISOR  12

#define ERR_FILE_OPEN     0x9000
#define ERR_FILE_READ     0xa000
#define ERR_BAD_OEM       0xb000
#define ERR_FILE_WRITE    0xc000
#define ERR_FILE_CORRUPT  0xd000
#define BAD_INI_SIGNATURE 0xe000
#define ERR_MEMORY_ALLOC  0xf000
#define RC_ITEM_NOT_FOUND 0xf800
#define RC_ITEM_FOUND     0xfc00

#define INI_FILE_SIGNATURE 0x19841835

#define MAX_CFG_LOAD   16
#define MAX_CFG_DEVICE 16

/*
** COMscope buffer marker definitions
*/
#define CS_CHAR_MASK          0x00ff
#define CS_FUNC_MASK          0xff00

#define CS_WRITE              0x8000
#define CS_WRITE_IMM          0x8100
#define CS_WRITE_REQ          0x8200
#define CS_WRITE_CMPLT        0x8300
#define CS_MODEM_OUT          0x8400
#define CS_DEVIOCTL           0x8500
#define CS_OPEN_ONE           0x8600
#define CS_OPEN_TWO           0x8700
#define CS_CLOSE_ONE          0x8800
#define CS_CLOSE_TWO          0x8900
#define CS_BREAK_TX           0x8a00

#define CS_READ_REQUEST       0x3c00
#define CS_READ_COMPLETE      0x3d00
#define CS_WRITE_REQUEST      0x3e00
#define CS_WRITE_COMPLETE     0x3f00


#define MAX_WRITE_DISPLAY_EVENTS 11
//#define CS_WRITE_TIME         0x2000

#define CS_READ               0x4000
#define CS_READ_IMM           0x4100
#define CS_READ_REQ           0x4200
#define CS_READ_CMPLT         0x4300
#define CS_MODEM_IN           0x4400
#define CS_READ_BUFF_OVERFLOW 0x4500
#define CS_HDW_ERROR          0x4600
#define CS_BREAK_RX           0x4700

#define MAX_READ_DISPLAY_EVENTS 8
//#define CS_READ_TIME          0x2100

//#define CS_TIME_TAG           0xe000

#define CS_PACKET_DATA        0xff00
/*
**  COMscope function definitions
*/
#define CSFUNC_RESET_BUFFERS             0x0001
#define CSFUNC_TRACE_INPUT_STREAM        0x0002
#define CSFUNC_TRACE_OUTPUT_STREAM       0x0004
#define CSFUNC_TRACE_IMM_STREAM          0x0008
#define CSFUNC_TRACE_MODEM_IN_SIGNALS    0x0010
#define CSFUNC_TRACE_MODEM_OUT_SIGNALS   0x0020
#define CSFUNC_TRACE_MODEM_SIGNALS_MASK  0x0030
#define CSFUNC_TRACE_DEVIOCTL            0x0040
#define CSFUNC_TRACE_ERRORS              0x0080
#define CSFUNC_TRACE_OPEN                0x0100
#define CSFUNC_TRACE_CLOSE               0x0200
#define CSFUNC_TRACE_READ                0x0400
#define CSFUNC_TRACE_WRITE               0x0800
#define CSFUNC_TRACE_STREAMS_MASK        0x4ffe
#define CSFUNC_TRACE_RX_BUFF_LEVEL       0x1000
#define CSFUNC_TRIG_OUTPUT_STREAM        0x2000
#define CSFUNC_TRACE_INCLUDE_PACKET      0x4000
//#define CSFUNC_TRIP_INPUT_STREAM         0x4000
//#define CSFUNC_TRIP_OUTPUT_STREAM        0x8000
//#define CSFUNC_TRIG_MASK                 0xe000

typedef struct _stExtentionParams
  {
  WORD wSignature;
  WORD wCommand;
  WORD wModifier;
  WORD wDataCount;
  }EXTPARM;

typedef struct _stExtentionDataHeader
  {
  WORD wReturnCode;
  WORD wByteCount;
  WORD wData;
  }EXTDATA;

#define HIGH_16750_TRIGGER 0x8000

#define MAX_DD_PATH  512

#define EXT_CMD_GET_MEMORY            0
#define EXT_CMD_GET_DCB               1
#define EXT_CMD_GET_PATH              2
#define EXT_CMD_GET_MEMORY_SIZE       3
#define EXT_CMD_GET_VARIABLES_SIZE    4
#define EXT_CMD_GET_LOAD_NUMBER       5
#define EXT_CMD_GET_CONFIG_FLAGS      6
#define EXT_CMD_GET_SIGNATURE         7
#define EXT_CMD_GET_OEM_TYPE          8
#define EXT_CMD_OPEN_PAGER            9
#define EXT_CMD_GET_MAX_DEVICE_COUNT  10
#define EXT_CMD_TRIG_READ             11
#define EXT_CMD_TRIG_WRITE            12
#define EXT_CMD_ROLL_COUNT            13
#define EXT_CMD_GET_PAGER_COUNTS      14
#define EXT_CMD_RESET_RX_HIGH         15
//#define EXT_CMD_RESET_TX_HIGH         16

#define EXT_RSP_SUCCESS             0x0f00

#define EXT_BAD_SIGNATURE           0xf000
#define EXT_ERROR_NO_TX_FIFO_TRIG   0x0ff8
#define EXT_ERROR_NO_FIFOs          0x0ff9
#define EXT_ERROR_BAD_TARGET        0x0ffa
#define EXT_ERROR_BAD_LENGTH        0x0ffb
#define EXT_ERROR_BAD_PATH          0x0ffc
#define EXT_ERROR_BAD_COMMAND       0x0ffd
#define EXT_ERROR_BAD_MODIFIER      0x0ffe
#define EXT_ERROR_BAD_MEMORY_TARGET 0x0fff

#define COMDD_INCLUDED

#endif //COMDD_INCLUDED
