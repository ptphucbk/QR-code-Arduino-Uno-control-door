
#include <avr/pgmspace.h>
#include <UTFT.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

static const unsigned char gen_poly[29] PROGMEM = {
  0x00,0xa8,0xdf,0xc8,0x68,0xe0,0xea,0x6c,0xb4,0x6e,0xbe,0xc3,0x93,0xcd,0x1b,0xe8,0xc9,0x15,0x2b,0xf5,0x57,0x2a,0xc3,0xd4,0x77,0xf2,0x25,0x09,0x7b};
static const unsigned char g0log[256] PROGMEM = {
  0xff,0x00,0x01,0x19,0x02,0x32,0x1a,0xc6,0x03,0xdf,0x33,0xee,0x1b,0x68,0xc7,0x4b,
  0x04,0x64,0xe0,0x0e,0x34,0x8d,0xef,0x81,0x1c,0xc1,0x69,0xf8,0xc8,0x08,0x4c,0x71,
  0x05,0x8a,0x65,0x2f,0xe1,0x24,0x0f,0x21,0x35,0x93,0x8e,0xda,0xf0,0x12,0x82,0x45,
  0x1d,0xb5,0xc2,0x7d,0x6a,0x27,0xf9,0xb9,0xc9,0x9a,0x09,0x78,0x4d,0xe4,0x72,0xa6,
  0x06,0xbf,0x8b,0x62,0x66,0xdd,0x30,0xfd,0xe2,0x98,0x25,0xb3,0x10,0x91,0x22,0x88,
  0x36,0xd0,0x94,0xce,0x8f,0x96,0xdb,0xbd,0xf1,0xd2,0x13,0x5c,0x83,0x38,0x46,0x40,
  0x1e,0x42,0xb6,0xa3,0xc3,0x48,0x7e,0x6e,0x6b,0x3a,0x28,0x54,0xfa,0x85,0xba,0x3d,
  0xca,0x5e,0x9b,0x9f,0x0a,0x15,0x79,0x2b,0x4e,0xd4,0xe5,0xac,0x73,0xf3,0xa7,0x57,
  0x07,0x70,0xc0,0xf7,0x8c,0x80,0x63,0x0d,0x67,0x4a,0xde,0xed,0x31,0xc5,0xfe,0x18,
  0xe3,0xa5,0x99,0x77,0x26,0xb8,0xb4,0x7c,0x11,0x44,0x92,0xd9,0x23,0x20,0x89,0x2e,
  0x37,0x3f,0xd1,0x5b,0x95,0xbc,0xcf,0xcd,0x90,0x87,0x97,0xb2,0xdc,0xfc,0xbe,0x61,
  0xf2,0x56,0xd3,0xab,0x14,0x2a,0x5d,0x9e,0x84,0x3c,0x39,0x53,0x47,0x6d,0x41,0xa2,
  0x1f,0x2d,0x43,0xd8,0xb7,0x7b,0xa4,0x76,0xc4,0x17,0x49,0xec,0x7f,0x0c,0x6f,0xf6,
  0x6c,0xa1,0x3b,0x52,0x29,0x9d,0x55,0xaa,0xfb,0x60,0x86,0xb1,0xbb,0xcc,0x3e,0x5a,
  0xcb,0x59,0x5f,0xb0,0x9c,0xa9,0xa0,0x51,0x0b,0xf5,0x16,0xeb,0x7a,0x75,0x2c,0xd7,
  0x4f,0xae,0xd5,0xe9,0xe6,0xe7,0xad,0xe8,0x74,0xd6,0xf4,0xea,0xa8,0x50,0x58,0xaf,
};

// Integer

static const unsigned char g0exp[256] PROGMEM = {
  0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1d,0x3a,0x74,0xe8,0xcd,0x87,0x13,0x26,
  0x4c,0x98,0x2d,0x5a,0xb4,0x75,0xea,0xc9,0x8f,0x03,0x06,0x0c,0x18,0x30,0x60,0xc0,
  0x9d,0x27,0x4e,0x9c,0x25,0x4a,0x94,0x35,0x6a,0xd4,0xb5,0x77,0xee,0xc1,0x9f,0x23,
  0x46,0x8c,0x05,0x0a,0x14,0x28,0x50,0xa0,0x5d,0xba,0x69,0xd2,0xb9,0x6f,0xde,0xa1,
  0x5f,0xbe,0x61,0xc2,0x99,0x2f,0x5e,0xbc,0x65,0xca,0x89,0x0f,0x1e,0x3c,0x78,0xf0,
  0xfd,0xe7,0xd3,0xbb,0x6b,0xd6,0xb1,0x7f,0xfe,0xe1,0xdf,0xa3,0x5b,0xb6,0x71,0xe2,
  0xd9,0xaf,0x43,0x86,0x11,0x22,0x44,0x88,0x0d,0x1a,0x34,0x68,0xd0,0xbd,0x67,0xce,
  0x81,0x1f,0x3e,0x7c,0xf8,0xed,0xc7,0x93,0x3b,0x76,0xec,0xc5,0x97,0x33,0x66,0xcc,
  0x85,0x17,0x2e,0x5c,0xb8,0x6d,0xda,0xa9,0x4f,0x9e,0x21,0x42,0x84,0x15,0x2a,0x54,
  0xa8,0x4d,0x9a,0x29,0x52,0xa4,0x55,0xaa,0x49,0x92,0x39,0x72,0xe4,0xd5,0xb7,0x73,
  0xe6,0xd1,0xbf,0x63,0xc6,0x91,0x3f,0x7e,0xfc,0xe5,0xd7,0xb3,0x7b,0xf6,0xf1,0xff,
  0xe3,0xdb,0xab,0x4b,0x96,0x31,0x62,0xc4,0x95,0x37,0x6e,0xdc,0xa5,0x57,0xae,0x41,
  0x82,0x19,0x32,0x64,0xc8,0x8d,0x07,0x0e,0x1c,0x38,0x70,0xe0,0xdd,0xa7,0x53,0xa6,
  0x51,0xa2,0x59,0xb2,0x79,0xf2,0xf9,0xef,0xc3,0x9b,0x2b,0x56,0xac,0x45,0x8a,0x09,
  0x12,0x24,0x48,0x90,0x3d,0x7a,0xf4,0xf5,0xf7,0xf3,0xfb,0xeb,0xcb,0x8b,0x0b,0x16,
  0x2c,0x58,0xb0,0x7d,0xfa,0xe9,0xcf,0x83,0x1b,0x36,0x6c,0xd8,0xad,0x47,0x8e,0x00,
};

SoftwareSerial BTSerial(11, 12); // RX | TX
UTFT myGLCD(ITDB24D,19,18,17,16);   // Remember to change the model parameter to suit your display module!

String account;
String password;
int i = 0;
int j = 0;
int x=24, y=24, flip = 1;
int direction = -1;
String confirm;
String command;
char lastChar;
String newAccount;

int numberAccount = 3;
int control = -1;
unsigned long time;
int led = 13;

void setup(){
  randomSeed(analogRead(0));
  pinMode(13,OUTPUT);
  myGLCD.InitLCD();
  myGLCD.clrScr();
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
}

void loop(){

  if (control == -1){
    password = "";
    myGLCD.fillScr(255,255,255);
    i = 0;
    j = 0;
    x=24;
    y=24;
    flip = 1;
    direction = -1;
    command = "";
    confirm = "";
    char lastChar;
    control = 0;
    account = "";
    time = millis()/1000;
  }

  // Login

  if (control == 0){
    // Time out
    if(millis()/1000 - time > 30){
      control = -1;
    }
    if(account.length() < 20){
      if (BTSerial.available()){
        char passChar = BTSerial.read();
        account = account + String(passChar);
      }
    }
    else {
      control = 1;
    }
  }

  // Check account  

  if(control == 1){
    if (checkAccount(account) <= numberAccount){
      if (checkAccount(account) == 1){
        BTSerial.write('1'); // Account Admin
      }
      else{
        BTSerial.write('2'); // Account user
      }
      control = 2;
    }
    else{
      BTSerial.write('0');  // Wrong Account
      control = -1;
    }
    time = millis()/1000;
  }

  // Receive command

  if(control == 2){
    // Time out
    if(millis()/1000 - time > 30){
      control = -1;
      lastChar = ' ';
    }
    if(lastChar != '#'){
      if (BTSerial.available()){
        lastChar = BTSerial.read();
        command = command + String(lastChar);
      }
    }
    else{
      control = 3;
    }
  }

  if(control == 3){
    if(checkAccount(account) == 1){
      if(command.substring(0,command.length()-1).equals("a")){
        lastChar = 'a'; // Add account
        control = 7;
      }
      if(command.substring(0,command.length()-1).equals("d")){
        BTSerial.print('$');
        for(int del=20;del<numberAccount*20;del++){
          char temp = EEPROM.read(640+del);
          delay(10);
          BTSerial.print(String(temp));
        }
        //        BTSerial.print(allAccount);
        lastChar = 'd'; // Delete Account
        control = 7;
      }
      if(command.substring(0,command.length()-1).equals("l")){
        control = -1; // Log out
      }
    } 
    if(command.substring(0,command.length()-1).equals("e")){
      control = 7;
      lastChar = 'e';  // Edit Account
    }

    if(command.substring(0,command.length()-1).equals("s")){
      control = 4; // Scan QR code
      lastChar = ' ';
    }
    command = "";
    time = millis()/1000;
  }

  // Display Account

  if(control == 4){
    int randLength = random(5,8);
    for(int l=0;l<randLength;l++){
      password = password + String(random(0,10));
    }
    //  password = "13111991";
    add_mode_count(password);
    complete();
    //    mask_matrix();

    myGLCD.fillScr(255,255,255);

    myGLCD.setColor(0, 0, 0);
    myGLCD.drawPixel(160, 120);

    for(i=55; i< 280; i++){
      for (j=10; j<235; j++){
        if (EEPROM.read(((j-10)/9)*25+(i-55)/9) == '1'){
          myGLCD.drawPixel(i, j);
        }
      }
    }
    control = 5;
    time = millis()/1000;
  }

  // Receive password
  // Return to the beginning if not send pass in 30s

  if(control == 5){
    if(millis()/1000 - time > 30){
      control = -1;
      account = "";
      lastChar = ' ';
    }
    if(lastChar != '#'){
      if (BTSerial.available()){
        lastChar = BTSerial.read();
        confirm = confirm + String(lastChar);
      }
    }
    else{
      control = 6;
    }
  }

  // If account is authenticated then turn on the LED

  if(control == 6){
    if(confirm.substring(0,confirm.length()-1).equals(password)){
      BTSerial.write('3');
      digitalWrite(led,HIGH);
      delay(3000);
      digitalWrite(led,LOW);
    }
    else{
      BTSerial.write('4');
    }
    control = -1;
    account = "";
    lastChar = ' ';
  }

  // Receive account to edit, add, delete

  if(control == 7){
    // Time out
    if(millis()/1000 - time > 30){
      control = -1;
      account = "";
      newAccount = "";
    }
    if(newAccount.length() < 20){
      if (BTSerial.available()){
        char passChar = BTSerial.read();
        newAccount = newAccount + String(passChar);
      }
    }
    else {
      control = 8;
    }
  }

  // Add, Edit, Delete

  if(control == 8){
    if(!newAccount.equals("####################")){
      if(lastChar == 'a'){    // add account
        addAccount(newAccount);
        BTSerial.write('r');  // success
      }
      if(lastChar == 'e'){    // add account
        editAccount(checkAccount(account) - 1,newAccount);
        BTSerial.write('r');  // success
      }
      if(lastChar == 'd'){    // delete account
        deleteAccount(checkAccount(newAccount) - 1);
        BTSerial.write('%');  // success
      }
    }
    newAccount = "";
    control = -1;
    lastChar = ' ';
  }
}

String binary_string(String str){
  int number = str.toInt();
  String bin = String(number,BIN);
  return bin;
}

void add_mode_count(String password){
  int i = 0;
  String add_zero;
  int input;
  int length = 0;

  fill_matrix("0001");
  length += 4;
  String character_count = binary_string(String(password.length()));
  // Tao Character Count Indicator
  while (character_count.length() < 10) {
    character_count = '0' + character_count;
  }
  fill_matrix(character_count);
  length += 10;
  i = password.length() / 3;

  while (i > 0) {

    add_zero = binary_string(password.substring(0, 3));
    password = password.substring(3, password.length());

    while (add_zero.length() < 10) {
      add_zero = '0' + add_zero;
    }
    fill_matrix(add_zero);
    length += 10;
    i--;
  }
  if (password.length() != 0) {
    if (password.length() == 2) {
      add_zero = binary_string(password);
      while (add_zero.length() < 7) {
        add_zero = '0' + add_zero;
      }
      fill_matrix(add_zero);
      length += 7;
    }
    if (password.length() == 1) {
      add_zero = binary_string(password);
      while (add_zero.length() < 4) {
        add_zero = '0' + add_zero;
      }
      fill_matrix(add_zero);
      length += 4;
    }
  }
  // Add a Terminator of 0s if Necessary
  // Add More 0s to Make the Length a Multiple of 8
  // Add Pad Bytes if the String is Still too Short

  if (length <= 16 * 8 - 4) {
    fill_matrix("0000");
    length += 4;
  } 
  else {
    while (length < 16 * 8) {
      fill_matrix("0");
      length += 1;
    }
  }
  while ((length % 8) != 0) {
    fill_matrix("0");
    length += 1;
  }
  while (length < 16 * 8) {
    fill_matrix("1110110000010001");
    length += 16;
  }
  if (length > 16 * 8) {
    length = 128;
    x=12;
    y=16;
  }
}

void complete(){
  int i = 0, j = 0;
  int x_c=24, y_c=24;
  int yy;
  int flop = 1;
  int orientation = -1;

  unsigned char coefficients[44];
  unsigned char divisor[29];
  while(i < 16){

    String str = "";

    int index=0;

    while (index<8) {
      if ( x_c >= 0 && x_c < 25) {
        if (flop==0) {
          flop=1;
        }
        else {
          flop=0;
        }
        yy = y_c - flop;
        if (check_coordinate(x_c, yy) == 1) {
          //          print(x_c);print(" ");println(yy);
          if (EEPROM.read(x_c*25 + yy) == '0') {
            str = str + "0";
          }
          else
          {
            str = str + "1";
          }
          index++;
        }
        if (flop == 1) {
          x_c += orientation;
        }
      }
      else {
        orientation = -orientation;
        x_c += orientation;
        y_c -= 2;
      }
    }

    byte myNum = 0x00;
    String y = "00000000";
    while(!str.equals(y)){
      myNum++;
      y = String(myNum,BIN);
      while(y.length() < 8){
        y = '0' + y;
      }  
    }
    coefficients[i] = myNum;
    i++;
  }
  for (i = 16; i < 44; i++) {
    coefficients[i] = 0x00;
  }
  i=0;
  j=0;
  while (j < 16){
    for (i=0; i<29; i++){
      divisor[i] = pgm_read_byte(&gen_poly[i]);
      divisor[i] = (divisor[i] + pgm_read_byte(&g0log[coefficients[j]]))%0xff;
      divisor[i] = pgm_read_byte(&g0exp[divisor[i]]);
    }
    for (i=0; i < 29; i++){
      coefficients[i+j] = coefficients[i+j]^divisor[i];
    }
    j++;
  }
  i = 16;
  while(i<44){
    String buffer = String(coefficients[i],BIN);
    while((buffer.length() % 8) != 0){
      buffer = '0' + buffer;
    }
    if (i != 43) {
      fill_matrix(buffer);
    }
    else {
      fill_matrix(buffer.substring(0, 6));
      if (buffer.substring(7, 8).equals("0")) {
        EEPROM.write(225,'0');
      }
      else {
        EEPROM.write(225,'1');
      }
    }
    i++;
  }
  for (x = 10; x<17; x++) {
    EEPROM.write(x*25,'0');
  }
}

int check_coordinate(int x, int y){
  if (x >=0 && x <=8 && y >=0 && y <= 8){
    return 0;
  }
  else if (x >=17 && x <= 24 && y >=0 && y <= 8){
    return 0;
  }
  else if (y >=17 && y <= 24 && x >=0 && x <= 8){
    return 0;
  }
  else if (x == 6 && y >= 9 && y <= 16){
    return 0;
  }
  else if (x >= 9 && x <= 16 && y == 6){
    return 0;
  }
  else if (x >= 16 && x <= 20 && y >= 16 && y <= 20){
    return 0;
  }
  else return 1;
}

void fill_matrix(String str) {
  int yy;
  int i=0;

  while (i<str.length ()) {
    if ( x >= 0 && x < 25) {
      if (flip==0) {
        flip=1;
      }
      else {
        flip=0;
      }
      yy = y - flip;
      if (check_coordinate(x, yy) == 1) {
        if (str.substring(i, i+1).equals("0")) {
          EEPROM.write(x*25+yy, '0');
        }
        else
        {
          EEPROM.write(x*25+yy, '1');
        }
        i++;
      }
      if (flip == 1) {
        x += direction;
      }
    }
    else {
      direction = -direction;
      x += direction;
      y -= 2;
    }
  }
}

void mask_matrix(){
  int x=0, y=0;
  for (x=0;x<25;x++){
    for (y=0;y<25;y++){
      if ((x+y+1)%2 == 0 && check_coordinate(x, y) == 1){
        if (EEPROM.read(x*25+y) == '0'){
          EEPROM.write(x*25+y, '1');
        }
        else {
          EEPROM.write(x*25+y, '0');
        }
      }
    }
  }
}

void writeString(int address, String str){
  int i=0;
  for(i=0;i<str.length();i++){
    if(str.substring(i,i+1).equals("0")){
      EEPROM.write(i + address, '0');  
    }
    else {
      EEPROM.write(i + address, '1');
    }

  }
}

boolean addAccount(String account){
  numberAccount += 1;
  if (numberAccount < 18){
    writeStringPass(640 + numberAccount*20 - 20,account);
    return true;
  }
  else {
    numberAccount -= 1;
    return false;
  }
}

boolean editAccount(int stt, String newAccount){
  writeStringPass(640 + stt*20, newAccount);
  return true;
}

boolean deleteAccount(int stt){
  if (stt != numberAccount - 1 && stt != 0){
    for (int i=0;i<20;i++){
      EEPROM.write(640+stt*20 + i,EEPROM.read(640 + (numberAccount-1)*20 + i));
    }
  }
  writeStringPass(640 + (numberAccount-1)*20, "####################");
  numberAccount -= 1;
  return true;
}

void writeStringPass(int address, String str){
  int i=0;
  for(i=0;i<str.length();i++){
    EEPROM.write(address, str.charAt(i));
    address++;
  }
}

int checkAccount(String account){
  String acc;
  char singleChar;
  int accountChecked=0;
  while(accountChecked < numberAccount + 1 && !account.equals(acc)){
    acc = "";
    for(int add = 640 + accountChecked*20; add < 640 + accountChecked*20 + 20; add++){
      singleChar = EEPROM.read(add);
      acc = acc + String(singleChar);
    }
    accountChecked += 1;
  }
  return accountChecked;
}
