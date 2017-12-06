#include <Pilgrim.h>
 // за еденицу времени взята 1 минута
double modelTime = 60*24*362*2; // время моделирования 2 года
double TCity = 24*60/100; // 100 заказов в день в город
double TCafe = 24*60/200; // 200 заказов в кафе в день
double TProduct = 60*24*7; // каждые 7 дней закупают продукты
double TDeliver = 30; // 30 минут на доставку
double TCook = 5; // 5 минут разогреть пиццу
double TCash = 60*24; // Каждый день сдаётся касса
double TDeliverCash = 60*24; // Каждый день курьер сдаёт выручку
 
forward
{
 int fw;
 double summ;
 
 modbeg("Бизнес-проесс пиццерии", 131, modelTime, (long)time(NULL), none, 123, none, none, 2);

 actor("Клиент с наличной оплатой и доставкой",  101, 1, norm, TCity, TCity/3, zero, 105);
 actor("Клиент с безналичной оплатой и доставкой",  102, none, norm, 2*TCity, 2*TCity/3, zero, 105);
 actor("Клиент в кафе с наличной оплатой",  103, 2, norm, TCafe, TCafe/3, zero, 106);
 actor("Клиент в кафе с безналичной оплатой",  104, none, norm, 2*TCafe, 2*TCafe/3, zero, 106);
 actor("Требование менеджера купить продукты",  117, none, norm, TProduct, TProduct/3, zero, 118);
 actor("Требоване менеджера сдать кассу", 126, none, norm, TCash, TCash/3, zero, 128);
 actor("Требоване менеджера сдать кассу", 127, none, norm, TDeliverCash, TDeliverCash/3, zero, 129);

 assign ( 120, add, 100000000.00);	 		// Назначили фонд Клиентов
 assign ( 121, add, 0.00);				// Назначили фонд Кассы
 assign ( 122, add, 0.00); 				// Начальный фонд Банковского счёта компании
 assign ( 123, add, 0.00);				// Назначили фонд Курьера
 assign ( 124, add, 0.00);				// Назначили фонд поставщиков
 sknot  (121);						// отслеживаем счета
 sknot  (122);
 sknot  (123);
 network(dummy, standard)

 {
  top(105): 
        queue("Очередь у курьера", none, 107);
             place;
 
  top(106): 
        queue("Очередь в кафе", none, 108);
             place;
 
  top(107):
			 if( t->pr == 1 ){
				fw = 109;
			 } else {
				 fw = 110;
			 }
			serve("Доставка курьером", 7, none, norm, TDeliver, TDeliver/3, zero, fw);
            place;
 
  top(108):
			if( t->pr == 2 ){
				fw = 111;
			 } else {
				 fw = 112;
			 }
        serve("Разогревание пиццы", 3, none, norm, TCook, TCook/3, zero, fw);
             place;
 
  top(109):
             pay("Плата курьеру наличным расчётом", 123, 350, 120, none, 120, 113);
             place; //
 
  top(110):
             pay("Плата курьеру безналичным расчётом", 122, 350, 120, none, 120, 114);
             place;
 
  top(111):
             pay("Плата в кассу наличным расчётом", 121, 300, 120, none, 120, 115);
             place;//
 
  top(112):
             pay("Плата в кассу безналичным расчётом", 122, 300, 120, none, 120, 116);
             place;

  top(128):
             pay("Сдача кассы", 120, 15000, 121, none, 121, 130);
             place;

  top(129):
             pay("Сдача выручки курьера", 120, 15000, 123, none, 123, 131);
             place;

  top(118): 
        pay("Плата поставщикам за продукты", 124, 50000, 122, none, 122, 119);
             place;
 
  top(113): 
        term("Оплата курьеру наличкой выполнена");
             place;
 
  top(114): 
        term("Оплата курьеру безналом выполнена");
             place;
 
  top(115): 
        term("Оплата в кассу наличкой выполнена");
             place;
 
  top(116): 
        term("Оплата в кассу безналом выполнена");
             place;
 
  top(119): 
        term("Оплата продуктов выполнена");
             place;

  top(130): 
        term("Касса сдана");
             place;

  top(131): 
        term("Курьер выручку сдал");
             place;

//----------------------------
//			 детализация счетов
//----------------------------
	top(120):send("Клиенты",  t->k1, t->summ, t->dpr, 125);
              place;
	top(121):send("Касса",  t->k1, t->summ, t->dpr, 125);
              place;
	top(122):send("Счёт компании",  t->k1, t->summ, t->dpr, 125);
              place;
	top(123):send("Курьер", t->k1, t->summ,t->dpr, 125);
              place;
	top(124):send("Поставщик", t->k1, t->summ,t->dpr, 125);
              place;
	top(125):direct("Бухгалтерия",  t->updown);
              place;

  fault(123);
 }
 modend("pilgrim.doc", 1, 30, page);
 return 0;
}
