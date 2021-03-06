#ifndef _INCL_COMM_H_

//typedef unsigned int BITFLD;

#define FROM_CLIENT ".FC"
#define IN_PROCESS ".IP"
#define TO_CLIENT ".TC"

#define UM_REQUEST                    7001
#define UM_RESPONSE                   7002
#define UM_INIT                       7003
#define UM_COM_THREAD                 7004

#define ERROR_SOCKET_ERROR            0x80000000
#define ERROR_API_ERROR               0x40000000
#define ERROR_LIB_NOT_INIT            0xe0000001
#define ERROR_LIB_IN_USE              0xe0000002

#define MESSAGE                       0
#define API_ERROR                     1
#define MSG_ERROR                     2
#define SOCKET_ERROR                  3

#define COM_THREAD_END                1
#define CON_ACCEPTED                  2
#define BUFF_ALLOCATED                3
#define BUFF_RECEIVED                 4

#define BY_ADDR                       0
#define BY_HOST                       1

#define REQ_REGISTER                  0
#define REQ_LOGON                     1
#define REQ_QUERY_SUBSCRIBER          2
#define REQ_QUERY_GROUP               3
#define REQ_QUERY_SERVER              4
#define REQ_QUERY_ACCESS              5
#define REQ_NOTIFY                    6
#define REQ_TIMEOUT                   7

#define RSP_SERVER                    1
#define RSP_ACK_GROUP                 2
#define RSP_NAK_GROUP                 3
#define RSP_ACK_SUBSCRIBER            4
#define RSP_NAK_SUBSCRIBER            5
#define RSP_ACK_NOTIFY                6
#define RSP_NAK_NOTIFY                7
#define RSP_ACK_LOGON                 8
#define RSP_NAK_LOGON                 9
#define RSP_TIMEOUT                   10

#define MSG_ERROR_POST_FAILED         1
#define MSG_ERROR_CONNECTION_CLOSED   2

typedef struct
  {
  char szUserName[40];
  char szPassword[40];
  USHORT fFlags;
  }LOGON;

typedef struct
  {
  USHORT cbSize;
  USHORT fMessageType;
  USHORT cbDataSize;
  USHORT cbMaxDataSize;
  ULONG ulMessageNumber;
  BYTE byReserved[16];
  BYTE byData;
  }MSG;

typedef struct
  {
  char szAddressee[20];
  ULONG fAddrType;
  }COMADDR;

//APIRET (* _System pfnnInitServer)(HWND);
//APIRET (* _System pfnnInitCOM)(HWND, COMADDR *, LOGON *);
//APIRET (* _System pfnnSendMessage)(MSG *);

extern int iLastCOMerror;

#define _INCL_COMM_H_

#endif
