QR-code-Arduino-Uno-control-door
==========================================================================================================================

We implement QR code on Arduino Uno and an app on Android to control a door (open/close) under GNU license

Arduino Uno encodes QR code (size 25*25 Error Correction Level H with modified mask 0) and display it on LCD TFT 2.4"
(http://www.geeetech.com/wiki/index.php/2.4%22TFT_LCD) using UTFT library (http://www.henningkarlsen.com/electronics/library.php?id=52)

Arduino communicates with Android phone by an app. We modified zxing library (https://code.google.com/p/zxing/) to 
decode our QR code. You can find our Android project here (https://mega.co.nz/#!wdwGWAYJ!AKUjEAaSn8iitt9UYr0DdH-IEOUDSXa_jsY8iz-mVnA)

The steps of our system as follow:

- Open app on Android phone
- Log in by an account (ex: Username : Phuc, Password : 08101991)
- After logging in, you can request Arduino to generate a random QR code or edit the account.
- If you request Arduino to generate and display QR code, you can scan it and send the result back to Arduino, then
Arduino will check if the result is correct or not. If correct it will turn on a LED.
- You also can manage all accounts saved in EEPROM by delete and add funtions 

In the future we will replace Uno by Mega so that we can use the touching screen of LCD and add more functions to our system.

Demo video : http://www.youtube.com/watch?v=de_rx1Wt1DE

Our group: 
            Leader: Phan Tuan Phuc (ptphucbk@gmail.com)
            Member: Nguyen Dai Duong
                    Ha Duc Thang
