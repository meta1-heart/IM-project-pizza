#include            <Simulate.h>
//---------------------------------------------------------------------------------------
//                                                              
//    ���������� ���������� ������� ������������� Actor Pilgrim     
//                                                              
//---------------------------------------------------------------------------------------
extern long         rbstatus1;             // ��� �������� ��������� ����������� ������ 1
extern long         rbstatus2;             // ��� �������� ��������� ����������� ������ 2
extern long         rbstatus3;             // ��� �������� ��������� ����������� ������ 3
extern long         rbstatus4;             // ��� �������� ��������� ����������� ������ 4
extern long         rbstatus5;             // ��� �������� ��������� ����������� ������ 5
extern long         rbstatus6;             // ��� �������� ��������� ����������� ������ 6
extern FILE         *stream;               // ���� � ����������� ������������          
extern WNDCLASS     wcl;                   // ��������� ����������� ������ ����        
extern TBBUTTON     tbButtons[NUMBUTTONS]; // �������������� ������        
extern HWND         tbwnd;                 // ���������� ������ ������������           
extern MYDLL        funcwindow;            // ���������� ������� �� DLL                
extern MSG          msg;                   // ������ ��� �������� ��������� Windows    
extern char         buf[1024];             // ����� ��� �����                          
extern char         modname[16];           // �������� ������                          
extern char         szWimName[];           // ��� ������ ����          
extern char         str[3000];             // ����� ��� ������ ������                  
extern LPTSTR       szFileName;            // ��� ����� ���-�����������
extern char         geoMapName[256];       // ��� map-����� ���-�����������
extern char         geoTreangle[256];      // ��� set-����� ��� �������� �����
extern char         newSpaceFile[256];     // ��� ������ SPACE-����� ��� �������� �����
extern char         geoSpaName[256];       // ��� SPACE-����� ��� ������������ ������ � ������
extern char         geoPoint1[80];         // ���������� � ������1 ��� �������� �����
extern char         geoPoint2[80];         // ���������� � ������2 ��� �������� �����
extern double       latPoint1;             // ������  ������1 ��� �������� �����
extern double       lonPoint1;             // ������� ������1 ��� �������� �����
extern long         xPoint1;               // ���������� X ������1 ��� �������� �����
extern long         yPoint1;               // ���������� Y ������1 ��� �������� �����
extern double       latPoint2;             // ������  ������2 ��� �������� �����
extern double       lonPoint2;             // ������� ������2 ��� �������� �����
extern long         xPoint2;               // ���������� X ������2 ��� �������� �����
extern long         yPoint2;               // ���������� Y ������2 ��� �������� �����
extern long         maxX, maxY;            // ������� ������                           
extern long         wX, wY;                // ������� ���������� ������                
extern long         stop0;                 // ������� ���������� ������                
extern long         stop1;                 // ������� ������������                     
extern long         stop2;                 // ������� �������/�����������              
extern long         stop3;                 // ���������� ������� �������               
extern long         sound;                 // ��������/��������� ������                
extern long         nastroit;              // ������� ���������� ��������� F-����
extern long         percent;               // ������� ���������� ������                
extern long         queFlag;               // ���� ������ ������� �������              
extern long         floFlag;               // ���� ������ ������� �������              
extern long         geoFlag;               // ���� ������ ������������ ������          
extern long         useFlag;               // ���� ��������� ��������������� ����      
extern long         sKnot;                 // ����������� ����                         
extern long         numbTreangPoint;       // ����� ������ ������������
extern OPENFILENAME ofn;
extern char         szDirName[256];
extern char         szFile[256];
extern char         szFileTitle[256];
extern UINT         i;
extern UINT         cbString;
extern char         chReplace;             // ����������� ����� ��� szFilter           
extern char         szFilter[256];
extern HFILE        hf;
extern HFONT        hOldf;                 // ������ �����                             
extern HFONT        hNewf;                 // ����� �����                              
extern DWORD        tid;                   // ������������� ������                     
extern HDC          memdc;                 // DC ������������ ����                     
extern HBITMAP      hbit;                  // ����� - ����������� ����                 
extern HBRUSH       hbrush;                // ������� �����                            
extern HBRUSH       hOldbrush;             // ���������� ������� �����                 
extern HBRUSH       hHollowbrush;          // ���������� �����                         
extern HBRUSH       hWhitebrush;           // ����� �����                              
extern HBRUSH       hBlackbrush;           // ������ �����                             
extern HBRUSH       hRedbrush;             // ������� �����                            
extern HBRUSH       hGreenbrush;           // ������� �����                            
extern HBRUSH       hBluebrush;            // ����� �����                              
extern HBRUSH       hYelloybrush;          // Ƹ���� �����                             
extern HBRUSH       hMagentabrush;         // ���������� �����                         
extern HBRUSH       hCyanbrush;            // ��������� �����
extern HPEN         hDarkOrangepen;        // Ҹ���-��������� ����
extern HPEN         hBrownpen;             // ���������� ����
extern HPEN         hOldpen;               // ���������� �������� ����                 
extern HPEN         hWhitepen;             // ����� �����                              
extern HPEN         hBlackpen;             // ������ �����                             
extern HPEN         hRedpen;               // ������� ����                             
extern HPEN         hRedpenDOT;            // ������� �������
extern HPEN         hGreenpen;             // ������� ����                             
extern HPEN         hBluepen;              // ����� ����                               
extern HPEN         hYelloypen;            // Ƹ���� ����                              
extern HPEN         hMagentapen;           // ���������� ����                          
extern HPEN         hCyanpen;              // ��������� ����                           
extern HANDLE       hThread;               // ���������� ������                        
extern HANDLE       hEvent1;               // ���������� ������� "�������������"       
extern HINSTANCE    hInst;                 // ���������� �������� ���������� ����������
extern HINSTANCE    gLibMyDLL;             // ��������� ���������� MyDLL               
extern HWND         hwnd;                  // ���������� �������� ���� ����������      
extern HWND         ghwnd;                 // ���������� ���� ���-����������
extern void         *pointer;              // ������������� ���������                  
extern long         xLp;                   // X ������  ���� �������������� ���������� 
extern long         xRp;                   // X ������� ���� �������������� ���������� 
extern long         yHp;                   // Y �������� ���� �������������� ����������
extern long         yLp;                   // Y ������� ���� �������������� ���������� 
extern long         memnofree;             // ������� ����������� kcb, acb, ecb, rcb   
extern long         timeScore;             // �������������� �������� � ������������   
extern double       floatScore1;           // ������������� �������� �������� �������  
extern double       floatScore2;           // ����� ��������� �������� ��������        
extern double       rn;                    // ���                                      
extern double       timer;                 // �o�e����� �a��ep                         
extern double       tmax;                  // �pe�� �o�e��po�a���                      
extern double       timeOld;               // ������� ������� � ����������             
extern long         naOld;                 // ������� ������� � ����������             
extern double       teral;                 // ������   �������  ������                 
extern double       terab;                 // ��������� ������� ������                 
extern double       terah;                 // �������  �������  ������                 
extern double       zemm;                  // ����������� ������ �����                 
extern double       lat[nvil];             // ������ �����                             
extern double       lon[nvil];             // ������ ������                            
extern long         pos[nvil];             // ������ "���������� ����� ������"         
extern double       qurvq[simgr];          // ������ �������� � �������                
extern double       qurvt[simgr];          // ������ �������� � �����������            
extern long         longTrace;             // ������������� �������� �����������       
extern double       doubleTrace;           // �������� ����������� � ��������� ������  
extern char         command[81];           // ������� ����������� ��� �������                     
extern char         commKnotFrom[81];      // ������� ����������� "����-�������������"                      
extern char         commActorNumb[81];     // ������� ����������� "���������� ����� ������"                      
extern char         commEventNumb[81];     // ������� ����������� "���������� ����� �������"                      
extern char         commVirtualTime[81];   // ������� ����������� "����������� ����� �������������"                      
extern char         commKnotTo[81];        // ������� ����������� "����-�����������"                      
extern long         knotFrom;              // "����-�������������"                      
extern long         actorNumb;             // "���������� ����� ������"                      
extern __int64      eventNumb;             // "���������� ����� �������"                      
extern double       virtualTime;           // "����������� ����� �������������"                      
extern long         knotTo;                // "����-�����������"                      
extern long         actorPass;             // "������� �������� ������"                      
extern char         comscore[81];          // ������ ��� ������ ��������               
extern char         comwork[81];           // ��� ��������� ���� �������               
extern long         tNumb;                 // ���������� ����� ������               
extern long         ix;                    // �pe��oc�e��ee ���                        
extern long         iy;                    // �o�oe ���                                
extern __int64      nd;                    // �o���ec��o ��c�e��ep��a��� � "Simula"    
extern long         nut;                   // ������������� ������                  
extern long         ne;                    // ����a co������o�o c��c�a                 
extern bool         go;                    // ��a���� �xo� � ��e�                      
extern bool         start;                 // �a�a�o pa�o�� simula  		            
extern bool         finish;                // �a�ep�e��e �o�e��po�a���                 
extern char         strname[22];           // ����� ������                             
extern struct       kcb *addr[pool];       // �acc�� ��a�a�e�e� ���o�           
extern struct       kcb *epkf;             // ������� ��a�a�e�e� ���o�                 
extern struct       kcb *epkl;             // ������� ��a�a�e�e� ���o�                 
extern struct       ecb *de;               // ������ ������                            
extern struct       acb *dt;               // ������ ������                            
extern struct       rcb *dr;               // ������ ������                            
extern struct       acb *t;                // �����  �po����ae�o�o ������           
extern struct       ecb *e;                // �����  ����� o�pa�o�a��o�o ecb           
extern struct       ecb *fe;               // �a�a�o co������o�o c��c�a                
extern struct       ecb *le;               // �o�e� c��c�a ecb                         
extern struct       ecb *iec;              // ��a�a�e�� c�a��p�emo�o co�����           
extern struct       ecb *fee;              // *          ��pa��e��e                    
extern struct       ecb *lee;              // *           c��c�o�                      
extern struct       acb *fte;              // *            �a����                      
extern struct       acb *lte;              // *           ���������                    
extern struct       rcb *fre;              // *             ecb                        
extern struct       rcb *lre;              // *          acb � rcb                     
extern struct       ecb *w;                // ���a��po�a��oe co����e                   
extern struct       fwcb *s;               // ���� ���������� �������������� �����     
extern struct       scb *space;            // ��������� �� "�����" ������������        
extern struct       scb *spbeg;            // ������ ������ "�����" ������������       
extern struct       scb *sptec;            // ������������� "�����" ������������       
extern struct       scb *spend;            // ���������     "�����" ������������       
extern long         quen;                  // ������� ��� ������� �������� ������      
extern long         tern;                  // ����������, ��� �������� �������� ������ 
extern long         spacetype;             // ��� ������������                         
extern long         vil;                   // ����� �������                            
extern long         nepk;                  // �������������� ���� � ������             
extern long         next;                  // ��a�e��e simula                          
extern long         kec;                   // ��a�ep �o�c�a co����� � �e�o��e ecb      
extern long         nee;                   // ����� ��������� ecb                      
extern long         nte;                   // ����� ��������� acb                      
extern long         nre;                   // ����� ��������� rcb                      
extern long         maxn;                  // �a�c��.����� ����� ������ ����������     
extern long         nue;                   // �a��.�o�ep co�����                       
extern long         nur;                   // �a�c.�omep rcb                           
extern long         che;                   // �p���a� �ec��po�a���                     
extern long         error;                 // �a�a���a� o����a                         
extern long         nk;                    // ��c�o ���o� �o�e��                       
extern long         cx;                    // ������  �e��pa pe��o�a                   
extern long         cy;                    // ������� ������ pe��o�a                   
extern long         grnq;                  // ����� ����� ������� ��� �������          
extern long         grnt;                  // ����� ����� ������� ��� �����������      
extern long         dsproc;                // ������� � ��������� ������.��������      
extern long         presise;               // ���-�� ������ ����� ���������� �����     
extern long         npoints;               // ���-�� ���������� �������                
extern long         globali;               // ������� ����� ����� SPACE                
extern double       northpoint;            // �������� �����  - fi2
extern double       southpoint;            // ����� �����     - fi1
extern double       westpoint;             // �������� �����  - lambda1
extern double       eastpoint;             // ��������� ����� - lambda2
extern long         northsp;               // ����� ���������  ������
extern long         southsp;               // ����� ������     ������
extern long         westsp;                // ����� ���������  ������
extern long         eastsp;                // ����� ���������� ������
extern long         windicator;            // ������� ��� ����������
extern long         xLg;                   // X-�����   ��������������, ������������� ������
extern long         xRg;                   // X-������  ��������������, ������������� ������
extern long         yLg;                   // Y-������� ��������������, ������������� ������
extern long         yHg;                   // Y-������  ��������������, ������������� ������
extern long         xmax;                  // ������ ��������������, ������������� �����
extern long         ymax;                  // ������ ��������������, ������������� �����
extern long         l1;                    // ������� ������ ��������� �� ������
extern long         l2;                    // ����� ������ ��������� �� ������
extern long         startpoint;            // ����� ������
extern long         finishpoint;           // ����� ������
extern double       psi;                   // ���� ���������� ���������
extern double       xsmesh;                // �������� X ��������� xmax
extern double       ysmesh;                // �������� Y ��������� ymax
extern long         xmouse;                // ������� x-���������� ���� (������)
extern long         ymouse;                // ������� y-���������� ���� (������)
extern long         xmapmouse;             // ������� x-���������� ���� �� ����� (������)
extern long         ymapmouse;             // ������� y-���������� ���� �� ����� (������)
extern long         xscreen;               // ������ ������ (������)
extern long         yscreen;               // ������ ������ (������)
extern char         xcoord[80];            // ������� x-���������� ���� (������)
extern char         ycoord[80];            // ������� y-���������� ���� (������)
extern char         latcoord[80];          // ������� ���-������ ���� (������)
extern char         loncoord[80];          // ������� ���-������� ���� (������)
extern BITMAP       bm;                    // ����� ���-����� 
extern long         vertpos;               // ������������ ������� ������� ���������
extern long         horzpos;               // �������������� ������� ������� ���������
extern long         flagSpaceFile;         // ���� ������ � SPASE-����
extern long         saveNpoints;           // ���������� ���-�� ���������� �������
extern double       l0map;                 // ������� ������ ��������� ���-�����
extern double       lmmap;                 // ����� ������ ��������� ���-�����
extern double       psimap;                // ���� ���������� ��������� ���-�����
extern double       wmap;                  // ������ ������
extern double       hmap;                  // ������ ������
extern double       beta1;                 // �����  ������������ �������� ����������
extern double       beta2;                 // ������ ������������ �������� ����������
extern double       gamma1;                // �������� �� ������� �����
extern double       gamma2;                // �������� �� ������� ������
extern double       lambda0;               // ������� �������� ��������� ���������
extern double       lambdam;               // ������� �������� ��������� ���������
extern double       l1map;                 // ������ ��������� �����-�������� 1
extern double       l2map;                 // ������ ��������� �����-�������� 2
extern double       delat;                 // ���������� ���������� ����� ������� �� ������  
extern double       fi0map;                // ������ ������� ����� ���������
extern double       fimmap;                // ������ ������� �������� ���������
extern double       epsilon;               // ����������� ����������� ������� lmmap
extern double       tpicrad;               // ����������� ��������� �������->�������
extern double       fimouse;               // ������ ������� ����
extern double       lambdamouse;           // ������� ������� ����
extern double       betamouse;             // ������� ���� ������� ����
extern double       delon;                 // ������� ���������� �� �������
extern double       lmmapold;              // �������������� �������� lmmap
extern HBITMAP      hBitmap;               // ���������� ������� ������� (�����������)
extern HPALETTE     hPalette;              // ���������� ������� ������� �������
extern long         *journal;              // ��������� ������ ����������� - ����� ������ � ���� ���������
extern double       antpathAB;             // ����������� ������� ����
extern double       antpathA;              // ������� ���� A
extern double       antpathB;              // ������� ���� B
