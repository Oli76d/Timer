#include <Wire.h>
#include <RTC.h>

static DS3231 RTC;

int typcykl;   //  ty cyklu 18/6 lub 12/12
int  ontime;   //  jak dlugo wlaczone
int  onlight;    // kiedy ma sie wlaczyc
int  offlight;
float swiatla;

void setup() 
{
  Serial.begin(9600);
  RTC.begin();
  
  typcykl = 1 ;    ////// 1 dla 18/6  ////////  2 dla 12/12  ///////  3 dla wlaczone  ///////  4 dla wylaczony  ///////
  onlight = 11;    // o ktorej godzinie ma sie wlanczyc swiatlo 0-23
  
//  RTC.setHourMode(CLOCK_H12);
  RTC.setHourMode(CLOCK_H24);  // zegar 24h
//  RTC.setWeek(7);
//  RTC.setDay(15);
//  RTC.setMonth(12);
//  RTC.setYear(2021); 
//  RTC.setHours(17);                        //  ! ustaw godzine !
//  RTC.setMinutes(58);                      //  ! ustaw minuty  !
//  RTC.setSeconds(00);                      //  ! ustaw sekundy !
//  RTC.setDateTime(__DATE__,__TIME__);      // pobiera ustawienia z systemu
//  RTC.setDate(15,8,2021);                  //  ! ustaw date    !
}

void loop()
{
  delay(2000);
  oswietlenie(); // odnosi sie do napisanych podprogramow/fumkcji ponizej.
  
    ///           wyswietla uzyskane wyniki 
  
  Serial.print("    cykl   ");
       if (typcykl==1)
       {
        Serial.print(" 18 / 6 ");
       }
        else if (typcykl==2)
       {
        Serial.print(" 12 / 12 ");
       }
         else if (typcykl==3)
       {
        Serial.print("wlonczone");
       }
        else 
       {
        Serial.print("wylaczone");
       }
  Serial.print("                od ");
  Serial.print(onlight);
  Serial.print("  do  ");
  Serial.println(offlight);
  Serial.print("  swiatlo  ");
      if (swiatla==1) 
        {
        Serial.print("wlanczone");  
        }
      else {
        Serial.print("wylanczone");
      }
  Serial.print("             dlugosc dnia  ");
  Serial.print(ontime);
  Serial.println(" h");
  Serial.println("---------------------------------------------------------"); 
  Serial.print("                 godzina        "); 
  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.println(RTC.getMinutes());
  Serial.println("---------------------------------------------------------");
  
  
  
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////   F U N K C J E    //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
void oswietlenie() 
{
  cykle();
    if (typcykl==3)
        {
        swiatla = 1;                       ///     light ON
        }
    else if (typcykl==4)
    {
      swiatla = 0;                        ///       light OFF
      onlight=0;
      ontime = 0;
      
    }
    else if (offlight<=onlight)
    {
       if (RTC.getHours()<=onlight || RTC.getHours()>=offlight )
       {
        swiatla = 1;                     ///    light 1 ON
       }

       else if (RTC.getHours()>=onlight || RTC.getHours()<=offlight )
       {
        swiatla = 0;                      /// light off
       }
    }
    
    else if (RTC.getHours()<=onlight || RTC.getHours()>=offlight)
    {
        swiatla = 0;                       /// light off
    }
        
    else if (RTC.getHours()>=onlight || RTC.getHours()<=offlight )
    {
        swiatla = 1;                       ///    light  ON
    }
}
 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void cykle()   //                  cykle oswietlenia
{
  if (typcykl==1)
  {
    ontime = 18;
    offlight = onlight + ontime ;
    if (offlight>23)
    {
     offlight = offlight-24;  
    }
    else{}
  }
  else if (typcykl==2)
  {
    ontime = 12;
    offlight = onlight + ontime ;
     if (offlight>23)
    {
     offlight = offlight-24;  
    }
      else{}
  }
   else if (typcykl==3)
  {  
    ontime = 24 ;
    offlight = onlight + ontime ;
     if (offlight>23)
     {
     offlight = offlight-24;
     }
     else{}
   }
}
