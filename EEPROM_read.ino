// This code is used to read EEPROM

//#include <UTFT.h>
#include <EEPROM.h>

//UTFT        myGLCD(ITDB24D,19,18,17,16);   // Remember to change the model parameter to suit your display module!
//UTouch      myTouch(15,10,14,9,8);

boolean login = false;
int numberAccount = 4;

void setup()
{ 
  Serial.begin(9600);
  // Initial setup
  //  myGLCD.InitLCD();
  //  myGLCD.clrScr();
}

void loop()
{
  if(!login){

    //    myGLCD.fillScr(255,255,255);
    //
    //    myGLCD.setColor(0, 0, 0);
    //    myGLCD.drawPixel(160, 120);
    //
    //    for(i=55; i< 280; i++){
    //      for (j=10; j<235; j++){
    //        if (EEPROM.read(((j-10)/9)*25+(i-55)/9) == '1'){
    //          myGLCD.drawPixel(i, j);
    //        }
    //      }
    //    }

    String allAccounts = "hahaha";
    for(int i=0;i<numberAccount*20;i++){
      char temp = EEPROM.read(640+i);
      allAccounts = allAccounts + String(temp);
//      Serial.write(EEPROM.read(640+i));
    }
    Serial.print(allAccounts);
//    String account = "Phuc%08101991#######";
//    if (checkAccount(account)){
//      Serial.print("Success");
//    }else{
//      Serial.print("Failed");
//    }

    login = true;
  }
}

//boolean checkAccount(int address, String account){
//  String acc;
//  char singleChar;
//  for(int add = address; add < address + 20; add++){
//    singleChar = EEPROM.read(add);
//    acc = acc + String(singleChar);
////    Serial.write(EEPROM.read(address));
//  }
//  Serial.println(acc);
//  if (account.equals(acc)){
//    return true;
//  }else {
//    return false;
//  }
//}

int checkAccount(String account){
  String acc;
  char singleChar;
  int accountChecked=0;
  while(accountChecked < numberAccount + 1 && !account.equals(acc)){
    acc = "";
    for(int add = 640 + accountChecked*20; add < 640 + accountChecked*20 + 20; add++){
      singleChar = EEPROM.read(add);
//      Serial.print(singleChar);
      acc = acc + String(singleChar);
    }
    Serial.println(acc);
    accountChecked += 1;
  }
  Serial.println(accountChecked);
  return accountChecked;
}




























