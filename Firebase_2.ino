//firebase-arduino-master kütüphanesini kullanılacak.https://github.com/FirebaseExtended/firebase-arduino indirme linki. 
//Olusturdugumuz firebase linkinin Fingerprint adresi kutuphanedeki src dosyasından FirebaseHttpClient adlı metindeki ile değiştirecek.
// fingerprint adresinin yanında yer alan tarih güncellenmelidir.
// ArduinoJson-5.13.1 kütüphanesi kullanmalıdır. Daha yeni sürümler hata vermektedir.
// Esp8266 modüllerinden kullanılıyorsa 2.4.1 versiyonu kullanılmalıdır.
// Bu proje nodemcu esp8266 kullanılaak yapılmıştır.

//D0=16   D1=5  D2=4   D3=0  D4=2  D5=14  D6=12  D7=13   D8=15    RX=3  TX=1   With Nodemcu
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <FirebaseArduino.h>

// Finger     CF:6C:F8:33:A3:FB:42:4A:49:0A:E7:72:24:53:1A:11:A2:C1:34:0D
// Set these to run example.
#define FIREBASE_HOST "library-6dc10-default-rtdb.firebaseio.com"  //Firebase url 
#define FIREBASE_AUTH "1VuWj18jKSdX9b4uDbdrPQUVZysM1n4Y2Esxqr9E"    //Firebase güvenliği
#define WIFI_SSID "BATTAL"        //Wifi Adı
#define WIFI_PASSWORD "7D297Cd2d3fB4"   //Wifi şifresi

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
  Serial.begin(115200);


  pinMode(GiristrigPin, OUTPUT);
  pinMode(GirisechoPin,INPUT);
  pinMode(CikistrigPin, OUTPUT);
  pinMode(CikisecgoPin,INPUT);
 
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
void loop(){

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
  digitalWrite(GiristrigPin, LOW);   
  delayMicroseconds(10);          
  digitalWrite(GiristrigPin, HIGH);    
  delayMicroseconds(10);
  digitalWrite(GiristrigPin, LOW);    
  Girissure = pulseIn(GirisechoPin, HIGH); 
  Girisuzaklik= (Girissure /29.1)/2;         

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
  digitalWrite(GiristrigPin, LOW);   
  delayMicroseconds(10);         
  digitalWrite(GiristrigPin, HIGH);   
  delayMicroseconds(10);
  digitalWrite(GiristrigPin, LOW);    
  Girissure = pulseIn(GirisechoPin, HIGH); 
  Girisuzaklik= (Girissure /29.1)/2;          

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




// Firebase Veri Aktarılması

int val_1 = insanSayisi;
int val_2 = girenSayisi; 
int val_3 = cikanSayisi;

    //Toplam İnsan sayısı
  Firebase.setFloat("val_1", insanSayisi);
  if (Firebase.failed()) {
      Serial.print("setting /Toplam İnsan failed:");
      Serial.println(Firebase.error());  
  }
 
      //Giren İnsan sayısı
  Firebase.setFloat("val_2", girenSayisi);
  if (Firebase.failed()) {
      Serial.print("setting /Giren İnsan failed:");
      Serial.println(Firebase.error());  
  }

        //Çıkan İnsan sayısı
  Firebase.setFloat("val_3", cikanSayisi);
  if (Firebase.failed()) {
      Serial.print("setting /Çıkan İnsanfailed:");
      Serial.println(Firebase.error());  
  }




}
