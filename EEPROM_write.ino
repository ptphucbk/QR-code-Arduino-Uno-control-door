// We use the first 625 bytes of EEPROM to save the QR code and the rest of EEPROM from byte number 640 we save our 
// database of accounts. Each account has the format: username#password### (length 20)
// This code is for writing account to EEPROM

#include <EEPROM.h>

char matrix[25][25] = {
{'1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
{'1', '0', '1', '1', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '1', '1', '0', '1'},
{'1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '1', '1', '0', '1'},
{'1', '0', '1', '1', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '1', '1', '0', '1'},
{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '0', '1', '1', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0'},
{'1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0'},
{'1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0'},
{'1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '0', '0'},
{'1', '0', '1', '1', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
};

//String str = "00010000001001000111101101111011010111010001000011101100000100011110110000010001111011000001000111101100000100011110110000010001010010101101011001111010010110100010111001100101101010001100100100101011111110101111101101111010000100101110011001001001010110001010101110010101001011001011110100110101011000001010011001011101101010001011010101011010110001010000000";

void setup()
{
  Serial.begin(9600);
  
  String admin = "Phuc%08101991#######";
  String user1 = "Duong%1234##########";
  String user2 = "Thang%HaThang#######";
  int address = 640;
  address = writeString(address,admin);
  address = writeString(address,user1);
  address = writeString(address,user2);
  
  
  for (int i = 0; i < 25; i++){
    for (int j = 0; j < 25; j++){
      EEPROM.write(i*25 + j, matrix[i][j]);
    }
  }
//  writeString(650, str);
//  fill_data();
//  mask_matrix();
}

void loop()
{

}

int writeString(int address, String str){
  int i=0;
  for(i=0;i<str.length();i++){
      EEPROM.write(address, str.charAt(i));
      address++;
      Serial.print(str.charAt(i));
  }
  Serial.println();
  return address;
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

void fill_data(){

  int x = 24;
  int yy;
  int y = 24;
  int direction = -1;
  int i=650,j=0;

  while(y > 0){
    while( x >= 0 && x < 25){
      for(j=0; j<2; j++){
        yy = y - j;
        if (check_coordinate(x,yy)){
//          if (str.substring(i,i+1).equals("0")){
            if (EEPROM.read(i) == '0'){
            EEPROM.write(x*25 + yy, '0');
          }
          else
          {
            EEPROM.write(x*25 + yy, '1');
          }
          i++;
        }
      }
      x += direction;
    }
    direction = -direction;
    x += direction;
    y -= 2;
  }

  for(x = 9; x<17; x++){
//    if (str.substring(i,i+1).equals("0")){
      if (EEPROM.read(i) == '0'){
      EEPROM.write(x*25, '0');
    }
    else
    {
      EEPROM.write(x*25, '1');
    }
    i++;
  }
}

void mask_matrix(){
  int x=0, y=0;
  for (x=0;x<25;x++){
    for (y=0;y<25;y++){
      if ((x+y)%2 == 0 && check_coordinate(x, y) == 1){
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

























