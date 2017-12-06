#include            <Simulate.h>
//---------------------------------------------------------------------------------------
//                                                              
//    Глобальные переменные системы моделирования Actor Pilgrim     
//                                                              
//---------------------------------------------------------------------------------------
extern long         rbstatus1;             // Для хранения состояния селекторной кнопки 1
extern long         rbstatus2;             // Для хранения состояния селекторной кнопки 2
extern long         rbstatus3;             // Для хранения состояния селекторной кнопки 3
extern long         rbstatus4;             // Для хранения состояния селекторной кнопки 4
extern long         rbstatus5;             // Для хранения состояния селекторной кнопки 5
extern long         rbstatus6;             // Для хранения состояния селекторной кнопки 6
extern FILE         *stream;               // Файл с параметрами пространства          
extern WNDCLASS     wcl;                   // Структуры определения класса окна        
extern TBBUTTON     tbButtons[NUMBUTTONS]; // Характеристики кнопок        
extern HWND         tbwnd;                 // Дескриптор панели инструментов           
extern MYDLL        funcwindow;            // Объявление функции из DLL                
extern MSG          msg;                   // Буферы для хранения сообщений Windows    
extern char         buf[1024];             // Буфер для файла                          
extern char         modname[16];           // Название модели                          
extern char         szWimName[];           // Имя класса окна          
extern char         str[3000];             // Буфер для строки вывода                  
extern LPTSTR       szFileName;            // Имя файла ГЕО-картографии
extern char         geoMapName[256];       // Имя map-файла ГЕО-картографии
extern char         geoTreangle[256];      // Имя set-файла для привязки карты
extern char         newSpaceFile[256];     // Имя нового SPACE-файла для привязки карты
extern char         geoSpaName[256];       // Имя SPACE-файла для практической работы с картой
extern char         geoPoint1[80];         // Информация о Пункте1 для привязки карты
extern char         geoPoint2[80];         // Информация о Пункте2 для привязки карты
extern double       latPoint1;             // Широта  Пункта1 для привязки карты
extern double       lonPoint1;             // Долгота Пункта1 для привязки карты
extern long         xPoint1;               // Координата X Пункта1 для привязки карты
extern long         yPoint1;               // Координата Y Пункта1 для привязки карты
extern double       latPoint2;             // Широта  Пункта2 для привязки карты
extern double       lonPoint2;             // Долгота Пункта2 для привязки карты
extern long         xPoint2;               // Координата X Пункта2 для привязки карты
extern long         yPoint2;               // Координата Y Пункта2 для привязки карты
extern long         maxX, maxY;            // Размеры экрана                           
extern long         wX, wY;                // Текущие координаты вывода                
extern long         stop0;                 // Признак выполнения модели                
extern long         stop1;                 // Признак приостановки                     
extern long         stop2;                 // Признак отладки/трассировки              
extern long         stop3;                 // Установить масштаб времени               
extern long         sound;                 // Включить/Выключить музыку                
extern long         nastroit;              // Признак разрешения настройки F-окна
extern long         percent;               // Процент выполнения модели                
extern long         queFlag;               // Флаг показа графика очереди              
extern long         floFlag;               // Флаг показа графика очереди              
extern long         geoFlag;               // Флаг показа пространства модели          
extern long         useFlag;               // Флаг открытого функционального окна      
extern long         sKnot;                 // Наблюдаемый узел                         
extern long         numbTreangPoint;       // Номер пункта треангуляции
extern OPENFILENAME ofn;
extern char         szDirName[256];
extern char         szFile[256];
extern char         szFileTitle[256];
extern UINT         i;
extern UINT         cbString;
extern char         chReplace;             // Разделитель строк для szFilter           
extern char         szFilter[256];
extern HFILE        hf;
extern HFONT        hOldf;                 // Старый шрифт                             
extern HFONT        hNewf;                 // Новый шрифт                              
extern DWORD        tid;                   // Идентификатор потока                     
extern HDC          memdc;                 // DC виртуального окна                     
extern HBITMAP      hbit;                  // Растр - виртуальное окно                 
extern HBRUSH       hbrush;                // Рабочая кисть                            
extern HBRUSH       hOldbrush;             // Дескриптор прежней кисти                 
extern HBRUSH       hHollowbrush;          // Прозрачная кисть                         
extern HBRUSH       hWhitebrush;           // Белая кисть                              
extern HBRUSH       hBlackbrush;           // Черная кисть                             
extern HBRUSH       hRedbrush;             // Красная кисть                            
extern HBRUSH       hGreenbrush;           // Зеленая кисть                            
extern HBRUSH       hBluebrush;            // Синяя кисть                              
extern HBRUSH       hYelloybrush;          // Жёлтая кисть                             
extern HBRUSH       hMagentabrush;         // Фиолетовая кисть                         
extern HBRUSH       hCyanbrush;            // Бирюзовая кисть
extern HPEN         hDarkOrangepen;        // Тёмно-оранжевое перо
extern HPEN         hBrownpen;             // Коричневое перо
extern HPEN         hOldpen;               // Дескриптор прежнего пера                 
extern HPEN         hWhitepen;             // Белая кисть                              
extern HPEN         hBlackpen;             // Черная кисть                             
extern HPEN         hRedpen;               // Красное перо                             
extern HPEN         hRedpenDOT;            // Красный пунктир
extern HPEN         hGreenpen;             // Зеленое перо                             
extern HPEN         hBluepen;              // Синее перо                               
extern HPEN         hYelloypen;            // Жёлтое перо                              
extern HPEN         hMagentapen;           // Фиолетовое перо                          
extern HPEN         hCyanpen;              // Бирюзовое перо                           
extern HANDLE       hThread;               // Дескриптор потока                        
extern HANDLE       hEvent1;               // Дескриптор события "Приостановить"       
extern HINSTANCE    hInst;                 // Дескриптор текущего экземпляря приложения
extern HINSTANCE    gLibMyDLL;             // Экземпляр библиотеки MyDLL               
extern HWND         hwnd;                  // Дескриптор главного окна приложения      
extern HWND         ghwnd;                 // Дескриптор окна ГЕО-приложения
extern void         *pointer;              // Настраиваемый указатель                  
extern long         xLp;                   // X левого  края прямоугольника индикатора 
extern long         xRp;                   // X правого края прямоугольника индикатора 
extern long         yHp;                   // Y верхнего края прямоугольника индикатора
extern long         yLp;                   // Y правого края прямоугольника индикатора 
extern long         memnofree;             // Признак присутствия kcb, acb, ecb, rcb   
extern long         timeScore;             // Масштабируемая задержка в милисекундах   
extern double       floatScore1;           // Установленное значение масштаба времени  
extern double       floatScore2;           // Вновь введенное значение масштаба        
extern double       rn;                    // ПСЧ                                      
extern double       timer;                 // Мoдeльный тaймep                         
extern double       tmax;                  // Вpeмя мoдeлиpoвaния                      
extern double       timeOld;               // Засечка таймера в индикаторе             
extern long         naOld;                 // Засечка событий в индикаторе             
extern double       teral;                 // Нижний   уровень  потока                 
extern double       terab;                 // Начальный уровень потока                 
extern double       terah;                 // Верхний  уровень  потока                 
extern double       zemm;                  // Вычисляемый радиус Земли                 
extern double       lat[nvil];             // Массив широт                             
extern double       lon[nvil];             // Массив долгот                            
extern long         pos[nvil];             // Массив "порядковый номер пункта"         
extern double       qurvq[simgr];          // График процесса в очереди                
extern double       qurvt[simgr];          // График процесса в терминаторе            
extern long         longTrace;             // Целочисленный параметр трассировки       
extern double       doubleTrace;           // Параметр трассировки с плавающей точкой  
extern char         command[81];           // Команда трассировки для отладки                     
extern char         commKnotFrom[81];      // Команда трассировки "узел-производитель"                      
extern char         commActorNumb[81];     // Команда трассировки "уникальный номер актора"                      
extern char         commEventNumb[81];     // Команда трассировки "порядковый номер события"                      
extern char         commVirtualTime[81];   // Команда трассировки "виртуальное время моделирования"                      
extern char         commKnotTo[81];        // Команда трассировки "узел-потребитель"                      
extern long         knotFrom;              // "узел-производитель"                      
extern long         actorNumb;             // "уникальный номер актора"                      
extern __int64      eventNumb;             // "порядковый номер события"                      
extern double       virtualTime;           // "виртуальное время моделирования"                      
extern long         knotTo;                // "узел-потребитель"                      
extern long         actorPass;             // "маршрут текущего актора"                      
extern char         comscore[81];          // Строка для приема масштаба               
extern char         comwork[81];           // Для измерений длин текстов               
extern long         tNumb;                 // Порядковый номер актора               
extern long         ix;                    // Пpeдпocлeднee ПСЧ                        
extern long         iy;                    // Нoвoe ПСЧ                                
extern __int64      nd;                    // Кoличecтвo диcпeтчepизaций в "Simula"    
extern long         nut;                   // Идентификатор актора                  
extern long         ne;                    // Длинa coбытийнoгo cпиcкa                 
extern bool         go;                    // Удaчный вxoд в узeл                      
extern bool         start;                 // Нaчaлo paбoты simula  		            
extern bool         finish;                // Зaвepшeниe мoдeлиpoвaния                 
extern char         strname[22];           // Точка старта                             
extern struct       kcb *addr[pool];       // Мaccив укaзaтeлeй узлoв           
extern struct       kcb *epkf;             // Цепочка укaзaтeлeй узлoв                 
extern struct       kcb *epkl;             // Цепочка укaзaтeлeй узлoв                 
extern struct       ecb *de;               // Начало мусора                            
extern struct       acb *dt;               // Начало мусора                            
extern struct       rcb *dr;               // Начало мусора                            
extern struct       acb *t;                // Адрес  пpoдвигaeмoгo актора           
extern struct       ecb *e;                // Адрес  вновь oбpaзoвaннoгo ecb           
extern struct       ecb *fe;               // Нaчaлo coбытийнoгo cпиcкa                
extern struct       ecb *le;               // Кoнeц cпиcкa ecb                         
extern struct       ecb *iec;              // Укaзaтeль cкaниpуemoгo coбытия           
extern struct       ecb *fee;              // *          упpaвлeниe                    
extern struct       ecb *lee;              // *           cпиcкoм                      
extern struct       acb *fte;              // *            пaмяти                      
extern struct       acb *lte;              // *           свободных                    
extern struct       rcb *fre;              // *             ecb                        
extern struct       rcb *lre;              // *          acb и rcb                     
extern struct       ecb *w;                // Сплaниpoвaннoe coбытиe                   
extern struct       fwcb *s;               // Блок управления функциональным окном     
extern struct       scb *space;            // Указатель на "точку" пространства        
extern struct       scb *spbeg;            // Начало списка "точек" пространства       
extern struct       scb *sptec;            // Предпоследняя "точек" пространства       
extern struct       scb *spend;            // Последняя     "точка" пространства       
extern long         quen;                  // Очередь для которой строится график      
extern long         tern;                  // Терминатор, для которого строится график 
extern long         spacetype;             // Тип пространства                         
extern long         vil;                   // Всего пунктов                            
extern long         nepk;                  // Контролируемый вход в прибор             
extern long         next;                  // Знaчeниe simula                          
extern long         kec;                   // Скaнep пoиcкa coбытия в цeпoчкe ecb      
extern long         nee;                   // Число свободных ecb                      
extern long         nte;                   // Число свободных acb                      
extern long         nre;                   // Число свободных rcb                      
extern long         maxn;                  // Мaкcим.число узлов общего назначения     
extern long         nue;                   // Мaкс.нoмep coбытия                       
extern long         nur;                   // Мaкc.нomep rcb                           
extern long         che;                   // Пpизнaк тecтиpoвaния                     
extern long         error;                 // Фaтaльнaя oшибкa                         
extern long         nk;                    // Чиcлo узлoв мoдeли                       
extern long         cx;                    // Широта  цeнтpa peгиoнa                   
extern long         cy;                    // Долгота центра peгиoнa                   
extern long         grnq;                  // Номер точки графика для очереди          
extern long         grnt;                  // Номер точки графика для терминатора      
extern long         dsproc;                // Процесс с контролем простр.динамики      
extern long         presise;               // Кол-во знаков после десятичной точки     
extern long         npoints;               // Кол-во населенных пунктов                
extern long         globali;               // Текущий номер точки SPACE                
extern double       northpoint;            // Северный пункт  - fi2
extern double       southpoint;            // Южный пункт     - fi1
extern double       westpoint;             // Западный пункт  - lambda1
extern double       eastpoint;             // Восточный пункт - lambda2
extern long         northsp;               // Номер Северного  пункта
extern long         southsp;               // Номер Южного     пункта
extern long         westsp;                // Номер Западного  пункта
extern long         eastsp;                // Номер Восточного пункта
extern long         windicator;            // Рабочая для индикатора
extern long         xLg;                   // X-левая   прямоугольника, охватывающего график
extern long         xRg;                   // X-правая  прямоугольника, охватывающего график
extern long         yLg;                   // Y-верхняя прямоугольника, охватывающего график
extern long         yHg;                   // Y-нижняя  прямоугольника, охватывающего график
extern long         xmax;                  // Ширина прямоугольника, охватывающего карту
extern long         ymax;                  // Высота прямоугольника, охватывающего карту
extern long         l1;                    // Большой радиус развертки на экране
extern long         l2;                    // Малый радиус развертки на экране
extern long         startpoint;            // Пункт старта
extern long         finishpoint;           // Пункт финиша
extern double       psi;                   // Угол конической развертки
extern double       xsmesh;                // Смещение X диапазона xmax
extern double       ysmesh;                // Смещение Y диапазона ymax
extern long         xmouse;                // Текущая x-координата мыши (пиксел)
extern long         ymouse;                // Текущая y-координата мыши (пиксел)
extern long         xmapmouse;             // Текущая x-координата мыши на карте (пиксел)
extern long         ymapmouse;             // Текущая y-координата мыши на карте (пиксел)
extern long         xscreen;               // Ширина экрана (пиксел)
extern long         yscreen;               // Высота экрана (пиксел)
extern char         xcoord[80];            // Текущая x-координата мыши (строка)
extern char         ycoord[80];            // Текущая y-координата мыши (строка)
extern char         latcoord[80];          // Текущая ГЕО-широта мыши (строка)
extern char         loncoord[80];          // Текущая ГЕО-долгота мыши (строка)
extern BITMAP       bm;                    // Растр ГЕО-карты 
extern long         vertpos;               // Вертикальная позиция линейки прокрутки
extern long         horzpos;               // Горизонтальная позиция линейки прокрутки
extern long         flagSpaceFile;         // Флаг записи в SPASE-файл
extern long         saveNpoints;           // Сохранение кол-ва населенных пунктов
extern double       l0map;                 // Большой радиус развертки ГЕО-карты
extern double       lmmap;                 // Малый радиус развертки ГЕО-карты
extern double       psimap;                // Угол конической развертки ГЕО-карты
extern double       wmap;                  // Ширина растра
extern double       hmap;                  // Высота растра
extern double       beta1;                 // Левая  составляющая углового расстояния
extern double       beta2;                 // Правая составляющая углового расстояния
extern double       gamma1;                // Смещение по долготе влево
extern double       gamma2;                // Смещение по долготе вправо
extern double       lambda0;               // Долгота крайнего западного меридиана
extern double       lambdam;               // Долгота крайнего западного меридиана
extern double       l1map;                 // Радиус развертки точки-привязки 1
extern double       l2map;                 // Радиус развертки точки-привязки 2
extern double       delat;                 // Пиксельное расстояние между точками по широте  
extern double       fi0map;                // Широта крайней южной параллели
extern double       fimmap;                // Широта крайней северной параллели
extern double       epsilon;               // Погрешность определения радиуса lmmap
extern double       tpicrad;               // Коэффициент пересчета пиксели->радианы
extern double       fimouse;               // Широта курсора мыши
extern double       lambdamouse;           // Долгота курсора мыши
extern double       betamouse;             // Рабочий угол курсора мыши
extern double       delon;                 // Угловое расстояние по долготе
extern double       lmmapold;              // Предшествующее значение lmmap
extern HBITMAP      hBitmap;               // Дескриптор битовой матрицы (изображения)
extern HPALETTE     hPalette;              // Дескриптор палитры битовой матрицы
extern long         *journal;              // Системный журнал перемещений - нужен только в теле программы
extern double       antpathAB;             // Нейтральный отрезок пути
extern double       antpathA;              // Отрезок пути A
extern double       antpathB;              // Отрезок пути B
