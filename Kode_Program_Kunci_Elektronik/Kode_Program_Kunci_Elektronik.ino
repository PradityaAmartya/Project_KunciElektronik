//Proyek #36: Kunci Elektronik dengan Password                  
#include <LiquidCrystal.h>
#include <Password.h> 
#include <Keypad.h> //library
//buat obyek password library, diisi dengan array char angka
Password password = Password( "123456" ); //angka kode PIN 
//buat obyek lcd library
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
int x = 0; //variabel looping
int a = 0; // variabel untuk kontrol tulisan LCD
int led = 13; //pin solenoid (disini diasumsikan led)
//definisikan jumlah kolom dan baris keypad 3 x 4
const byte JmlBaris = 4; // 4 baris
const byte JmlKolom = 3; // 3 kolom
//inisiasi untuk keypad atau definisikan keymap
char keys[JmlBaris][ JmlKolom] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };//matriks 4x3 menunjukkan keypad mana yang ditekan
//hubungkan pin baris keypad dengan pin arduino
  byte PinBaris [JmlBaris] = { 3, 2, 1, 0};
//hubungkan pin kolom keypad dengan pin arduino
  byte PinKolom[JmlKolom] = { 4, 5, 6 };  
//buat obyek keypad library
Keypad syahwil = Keypad( makeKeymap(keys), PinBaris,   PinKolom, JmlBaris, JmlKolom );

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); //memulai LCD
  lcd.setCursor(0,0); //set tempat kursor/teks
  lcd.print("Power On...");//print tulisan dlm tanda petik
  lcd.setCursor(0,1); //set tempat kursor/teks
  lcd.print("...by TT3C...");
  delay(500);
  lcd.clear();
  syahwil.addEventListener(keypadEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(led, OUTPUT);
   if (a==0) { //state awal
     lcd.setCursor(0, 0); //set tempat kursor
     lcd.print("Pintu Elektronik!");
     lcd.setCursor(0, 1); //set tempat kursor
     lcd.print("Masukan Kode....");
     lcd.noDisplay();
     delay(250);
     lcd.display();
     delay(250);
}
  syahwil.getKey(); //membaca keypad
}
void keypadEvent(KeypadEvent eKey){ 
  switch (syahwil.getState()){
    case PRESSED: //saat ditekan
      if (a == 0){ 
         lcd.clear();
         a = 1;
      }
      lcd.setCursor(0, 0);
      lcd.print("Kode :          ");
      lcd.setCursor(x, 1);
switch (eKey){ //uji kondisi eKey
case '*': 
  checkPassword();
  password.reset(); 
  break; //saat * ditekan, melakukan pengecekan password
case '#': 
  password.reset(); 
  lcd.setCursor(0, 0); 
  lcd.clear();
  x=0; 
  a=0;
  break; //saat # ditekan, hapus password yg ditekan
default:
  password.append(eKey); //default untuk selain * dan #
  lcd.print("*"); //print tanda *
  x++;}
}
}
void checkPassword(){ //prosedur untuk mengecek password benar atau salah
if (password.evaluate()){ //jika password cocok
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" KODE DITERIMA");
  lcd.setCursor(0, 1);
  lcd.print(" Silahkan Masuk!");
  digitalWrite(led, HIGH); //aktikan solenoid 2 detik
  delay(2000);
  digitalWrite(led, LOW); //off kan selenoid
  x = 0;
  a = 0; 
 } else {
     lcd.clear();
     lcd.setCursor(0, 0); //jika password salah
     lcd.print("  KODE DITOLAK ");
     lcd.setCursor(0, 1); //kalo password salah
     lcd.print("================");
//teks lcd berkedip sebanyak 5 kali
  for(int i=0; i < 5; i++) { 
    lcd.noDisplay();// tampilan teks off
    delay(250);
    lcd.display();// tampilan teks on
    delay(250);
    x=0;
    a=0;
}
}
}
