#include <Pilgrim.h>
 
double modelTime = 730; // время моделирования 2 года
double TCity = 1/70; // 70 заказов в день в город
double TCafe = 1/130; // 130 заказов в кафе в день
double TProduct = 7; // каждые 7 дней закупают продукты
double TDeliver = 1/24/4; // 15 минут на доставку
double TCook = 1/24/20; // 3 минуты разогреть пиццу
 
forward
{
 int fw;
 double summ;
 
 modbeg("Бизнес-проесс пиццерии", 127, modelTime, (long)time(NULL), none, 122, none, none, 2);

 actor("Клиент с наличной оплатой и доставкой",  101, 1, norm, TCity, TCity/3, zero, 105);
 actor("Клиент с безналичной оплатой и доставкой",  102, 2, norm, TCity, TCity/3, zero, 105);
 actor("Клиент в кафе с наличной оплатой",  103, 3, norm, TCafe, TCafe/3, zero, 106);
 actor("Клиент в кафе с безналичной оплатой",  104, 4, norm, TCafe, TCafe/3, zero, 106);
 actor("Требование менеджера купить продукты",  117, none, norm, TProduct, TProduct/3, zero, 118);

 assign ( 120, add, 1000000000.00); 	// Назначили фонд Клиентов       
 assign ( 122, add, 0.00); 				// Начальный фонд Банковского счёта        
 assign ( 121, add, 0.00);				// Назначили фонд Кассы
 assign ( 123, add, 0.00);				// Назначили фонд Курьера
 sknot  (122);					// Состояние расчетного счета

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
			serve("Доставка курьером", 1, none, norm, TDeliver, TDeliver/3, zero, fw);
            place;
 
  top(108):
			if( t->pr == 3 ){
				fw = 111;
			 } else {
				 fw = 112;
			 }
        serve("Разогревание пиццы", 2, none, norm, TCook, TCook/3, zero, fw);
             place;
 
  top(109):
             pay("Плата курьеру наличным расчётом", 123, 350, 120, none, 123, 113);
             place;
 
  top(110):
             pay("Плата курьеру безналичным расчётом", 122, 350, 120, none, 122, 114);
             place;
 
  top(111):
             pay("Плата в кассу наличным расчётом", 121, 300, 120, none, 121, 115);
             place;
 
  top(112):
             pay("Плата в кассу безналичным расчётом", 122, 300, 120, none, 122, 116);
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
 
  top(118): 
        pay("Плата поставщикам за продукты", 124, 15000, 122, none, 124, 119);
             place;
 
  top(119): 
        term("Оплата продуктов выполнена");
             place;

//////////////////////////////////////////////////////////
// Второй слой - слой переводов денег
//////////////////////////////////////////////////////////

  top(120): 
        if( t->pr == 1 )
             {
              fw = 123;
			  summ = 350;
             }
            else
             if( t->pr == 2 )
             {
              fw=122;
			  summ = 350;
             }
            else
             if( t->pr == 3 )
             {
              fw = 122;
			  summ = 300;
             }
            else
             {
              fw = 122;
			  summ = 300;
             }
             send("Клиенты", fw, summ, none, 125);
             place;
 
  top(121): 
             send("Кафе", 122, 7000, none, 125);
             place;
 
  top(122): 
             send("Банковский счёт", 124, 15000, none, 125);
             place;
 
  top(123): 
             send("Курьер", 122, 3000, none, 125);
             place;
 
  top(124): 
        send("Поставщик", 122, 0, none, 125);
             place;
 
  top(125): 
        direct("Бухгалтерия", t->updown);
             place;
 
  fault(123);
 }
 modend("pilgrim.doc", 1, 30, page);
 return 0;
}
