//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int lcd_key2     = 0;
int adc_key_in  = 0;
unsigned int period[5] = {0, 0, 1, 0, 1};
unsigned int period_loc  = 0;
const int backlight_pin = 10;
const int switch_pin = 13;
int low_time = 1000; //time in milliseconds
int high_time = 9000;
int break_flag = 0;
unsigned long start_time;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  // For V1.1 us this threshold
  if (adc_key_in < 650)   return btnSELECT;
  if (adc_key_in < 825)  return btnRIGHT;
  if (adc_key_in < 875)  return btnLEFT;
  if (adc_key_in < 925)  return btnDOWN;
  if (adc_key_in < 975)  return btnUP;

  return btnNONE;  // when all others fail, return this...
}

void setup()
{;
  lcd.begin(16, 2);              // start the library
  pinMode(switch_pin, OUTPUT);
}

void loop()
{

  
  if (break_flag == 1)
  {
    break_flag = 0;
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Mode switch...");
    while (1)
    {
      lcd_key = read_LCD_buttons();
      if (lcd_key == btnNONE)
      {
        break;
      }
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("Sel=confirm");

  for (int i = 0; i < sizeof(period) / sizeof(int) - 1; i++)
  {
    lcd.setCursor(0 + i, 1);
    lcd.print(period[i]);
  }

  lcd.setCursor(4, 1);
  lcd.print("    ");
  lcd.setCursor(4, 1);

  switch (period[4])
  {
    case 0:
      {
        lcd.print("ms");
        break;
      }
    case 1:
      {
        lcd.print("s");
        break;
      }
    case 2:
      {
        lcd.print("min");
        break;
      }
  }

  lcd_key = read_LCD_buttons();
  lcd.setCursor(period_loc, 1);

  lcd.blink();
  start_time = millis();
  while (millis() - start_time < 250);
  lcd.noBlink();

  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT:
      {
        period_loc++;
        break;
      }
    case btnLEFT:
      {
        period_loc--;
        break;
      }
    case btnUP:
      {
        period[period_loc]++;
        break;
      }
    case btnDOWN:
      {
        period[period_loc]--;
        break;
      }
    case btnSELECT:
      {
        if (break_flag == 0)
        {
          gen_pulses();
        }
        break;
      }
    case btnNONE:
      {
        break;
      }
  }

  if (period_loc > sizeof(period) / sizeof(int) - 1)
  {
    period_loc = 0;
  }

  for (int i = 0; i < sizeof(period) / sizeof(int) - 1; i++)
  {
    if (period[i] > 9)
    {
      period[i] = 0;
    }
  }

  if (period[4] > 2)
  {
    period[4] = 0;
  }

}

void gen_pulses()
{

  break_flag = 0;
  
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("Mode switch...");

  while (1)
  {
    lcd_key = read_LCD_buttons();
    if (lcd_key == btnNONE)
    {
      break;
    }
  }


  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("Running...");

  // now format the period into something we can use

  int period_use = period[3] * pow(10, 0) + period[2] * pow(10, 1) + period[1] * pow(10, 2) + period[0] * pow(10, 3);
  switch (period[4])
  {
    case 0:
      {
        break;
      }
    case 1:
      {
        // working in seconds, convert from ms to s
        period_use *= 1000;
        break;
      }
    case 2:
      {
        // working in minutes, convert from ms to minutes
        period_use *= 60000;
        break;
      }
  }
  period_use -= low_time;

  while (1)
  {
    lcd_key = read_LCD_buttons();
    if (lcd_key == btnSELECT)
    {
      break_flag = 1;
      return;
    }

    start_time = millis();
    digitalWrite(switch_pin, HIGH);
    while (millis() - start_time < period_use)
    {
      lcd_key = read_LCD_buttons();
      if (lcd_key == btnSELECT)
      {
        break_flag = 1;
        return;
      }
    }

    start_time = millis();
    digitalWrite(switch_pin, LOW);
    while (millis() - start_time < low_time)
    {
      lcd_key = read_LCD_buttons();
      if (lcd_key == btnSELECT)
      {
        break_flag = 1;
        return;
      }
    }
  }




}

