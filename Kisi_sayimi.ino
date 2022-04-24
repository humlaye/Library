//D0=16   D1=5  D2=4   D3=0  D4=2  D5=14  D6=12  D7=13   D8=15    RX=3  TX=1  
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include<ThingSpeak.h>
#include<Wire.h>    
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F , 16 , 2);  // SDA=D4   SCL=D3  


//Sensör Pin atama
int GiristrigPin = 15;  //D8
int GirisechoPin = 13;  //D7
int CikistrigPin = 14;  //D5
int CikisecgoPin = 12;  //D6

long Girissure;
long Girisuzaklik;
long Cikissure;
long Cikisuzaklik;

int girenSayisi = 0;
int cikanSayisi = 0;
int insanSayisi = 0;
int gireninsanSayisi=0;
int cikaninsanSayisi=0;
int kapiMesafesi = 50;

bool durum = false;


void setup() {


  pinMode(GiristrigPin, OUTPUT);
  pinMode(GirisechoPin,INPUT);
  pinMode(CikistrigPin, OUTPUT);
  pinMode(CikisecgoPin,INPUT);

Serial.begin(115200);
}

void loop() {
  
 //Girişteki sensör için
  digitalWrite(GiristrigPin, LOW);     //İlk olarak trip pinimizi low durumunda başlatıyoruz.
  delayMicroseconds(10);           //10 Mikrosaniye(saniyenin milyonda biri) beklemesini belirtiyoruz.
  digitalWrite(GiristrigPin, HIGH);    //Daha sonra pinimizin ses dalgası göndermesi için emir veriyoruz.
  delayMicroseconds(10);
  digitalWrite(GiristrigPin, LOW);     //Yeni ses dalgası üretebilmesi için trig pinimizi pasif durumuna getiriyoruz.
  Girissure = pulseIn(GirisechoPin, HIGH);  //Gönderilen ses dalgasının geri dönmesindeki süre ölçülüyor.
  Girisuzaklik= (Girissure /29.1)/2;          //Ölçütüğümüz süre uzaklığa çevriliyor.

  //Çıkıştaki sensör ile
  digitalWrite(CikistrigPin, LOW);    
  delayMicroseconds(10);         
  digitalWrite(CikistrigPin, HIGH);    
  delayMicroseconds(10);
  digitalWrite(CikistrigPin, LOW);     
  Cikissure = pulseIn(CikisecgoPin, HIGH);  
  Cikisuzaklik= (Cikissure /29.1)/2;          


if(1<Girisuzaklik && Girisuzaklik<kapiMesafesi && durum == false ){
while(1){

     //Girişteki sensör için
  digitalWrite(GiristrigPin, LOW);     //İlk olarak trip pinimizi low durumunda başlatıyoruz.
  delayMicroseconds(10);           //10 Mikrosaniye(saniyenin milyonda biri) beklemesini belirtiyoruz.
  digitalWrite(GiristrigPin, HIGH);    //Daha sonra pinimizin ses dalgası göndermesi için emir veriyoruz.
  delayMicroseconds(10);
  digitalWrite(GiristrigPin, LOW);     //Yeni ses dalgası üretebilmesi için trig pinimizi pasif durumuna getiriyoruz.
  Girissure = pulseIn(GirisechoPin, HIGH);  //Gönderilen ses dalgasının geri dönmesindeki süre ölçülüyor.
  Girisuzaklik= (Girissure /29.1)/2;          //Ölçütüğümüz süre uzaklığa çevriliyor.

//Çıkıştakni sensör ile
  digitalWrite(CikistrigPin, LOW);    
  delayMicroseconds(10);         
  digitalWrite(CikistrigPin, HIGH);    
  delayMicroseconds(10);
  digitalWrite(CikistrigPin, LOW);     
  Cikissure = pulseIn(CikisecgoPin, HIGH);  
  Cikisuzaklik= (Cikissure /29.1)/2; 

    if(Girisuzaklik<kapiMesafesi){
     
   // Serial.println("Giriş while "); 
    }
    else{
    if(1<Cikisuzaklik && Cikisuzaklik< kapiMesafesi){
        gireninsanSayisi++;
        delay(100);
    }
  durum = true;
  break;
    }
 }
 }
 
 if(1<Cikisuzaklik && Cikisuzaklik< kapiMesafesi && durum== false ){
while(1){

//Girişteki sensör için
  digitalWrite(GiristrigPin, LOW);     //İlk olarak trip pinimizi low durumunda başlatıyoruz.
  delayMicroseconds(10);           //10 Mikrosaniye(saniyenin milyonda biri) beklemesini belirtiyoruz.
  digitalWrite(GiristrigPin, HIGH);    //Daha sonra pinimizin ses dalgası göndermesi için emir veriyoruz.
  delayMicroseconds(10);
  digitalWrite(GiristrigPin, LOW);     //Yeni ses dalgası üretebilmesi için trig pinimizi pasif durumuna getiriyoruz.
  Girissure = pulseIn(GirisechoPin, HIGH);  //Gönderilen ses dalgasının geri dönmesindeki süre ölçülüyor.
  Girisuzaklik= (Girissure /29.1)/2;          //Ölçütüğümüz süre uzaklığa çevriliyor.

//Çıkıştakni sensör ile
  digitalWrite(CikistrigPin, LOW);    
  delayMicroseconds(10);         
  digitalWrite(CikistrigPin, HIGH);    
  delayMicroseconds(10);
  digitalWrite(CikistrigPin, LOW);     
  Cikissure = pulseIn(CikisecgoPin, HIGH);  
  Cikisuzaklik= (Cikissure /29.1)/2; 

    if(Cikisuzaklik<kapiMesafesi){
    }
    else{
    if(1<Girisuzaklik && Girisuzaklik< kapiMesafesi){
        cikaninsanSayisi++;
        delay(100);
    }
  durum = true;
  break;
    }
 }
 }
  
  
  durum = false;
  

  girenSayisi= girenSayisi + gireninsanSayisi;
  cikanSayisi= cikanSayisi + cikaninsanSayisi;
  insanSayisi= insanSayisi + gireninsanSayisi - cikaninsanSayisi; //Giren İnsan sayısından çıkan insan sayısını çıkarak içerdeki toplam insan sayısını buluruz
  if (insanSayisi<0){
    insanSayisi=0;
  }




  Serial.print("\nGiriş Uzaklik "); 
  Serial.println(Girisuzaklik);         //Giriş sensörü mesafeini verir
//  Serial.println(" CM ");
  Serial.print("Çıkış Uzaklik "); 
  Serial.println(Cikisuzaklik);          //Çıkış sensörü mesafesini verir
//  Serial.println(" CM ");
  Serial.print("İnsan Sayısı :");
  Serial.println(insanSayisi);;         //Toplam insan sayısını verir
//  Serial.print("Giren İnsan Sayısı :");
//  Serial.println(gireninsanSayisi);
  Serial.print("Giren Sayısı :");
  Serial.println(girenSayisi);        //İçeriye giren toplam insan sayısını verir
//  Serial.print("Çıkan İnsan Sayısı :");
//  Serial.println(cikaninsanSayisi);
  Serial.print("Çıkan Sayısı :");
  Serial.println(cikanSayisi);    //Çıkan toplam insan sayısını verir
  delay(50);



  gireninsanSayisi=0;
  cikaninsanSayisi=0;   //Giren ve çıkan insan sayısını her seferinde 0 a eşit olması lazım

 
}
