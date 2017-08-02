#include <LiquidCrystal.h>

const int ANALOG_ERROR= 5;
const int BTN_SELECT  = 0;
const int BTN_LEFT    = 1;
const int BTN_UP      = 2;
const int BTN_DOWN    = 3;
const int BTN_RIGHT   = 4;
const int NOT_DEFINED = 5;
const int STEPS       = 400;
const long PRINT_MILLIS_TIME = 1000;

const int PIN_PUL = 3;
const int PIN_DIR = 2;

LiquidCrystal _lcd(8,9,4,5,6,7);
int _last_btn = NOT_DEFINED;
int _last_btn_acction;
int _steps;
int _vueltas;
unsigned long _last_millis_time;
int _l_potencimeter1,_l_potencimeter2;

boolean _dir = HIGH;

void setup() {
  pinMode(PIN_PUL,OUTPUT);
  pinMode(PIN_DIR,OUTPUT);
  
  _lcd.begin(16,2);
  _lcd.setCursor(0,0);
  _lcd.print("V=");
  _lcd.setCursor(4,0);
  _lcd.print("F=");

}

void loop() {
  executeButton();
  int potencimeter1 = map(analogRead(1),0,1023,1,1000);
  if(isPotenciometer1Change(potencimeter1)){ // ejecuta y asgina siempre y cuando ha cambiado un valor
      if(millis() - _last_millis_time > PRINT_MILLIS_TIME){ // ejecuta cuando se ha completado almenos 1 segundo
        //displayData();
      }
  }

  if(_steps > STEPS * _vueltas){ // sirve para cambiar de direccion luego de completar X vueltas/steps
    _dir = !_dir;
    _steps = 0;
  }  
  if(_vueltas != 0){
    digitalWrite(PIN_DIR,_dir);    
    digitalWrite(PIN_PUL,HIGH);
    delayMicroseconds(potencimeter1);
    digitalWrite(PIN_PUL,LOW);
    delayMicroseconds(potencimeter1);
    _steps++;
  }
}

void displayData(){
  _lcd.setCursor(2,0);
  _lcd.print(_vueltas);
  _lcd.setCursor(6,0);
  _lcd.print(_l_potencimeter1*2);
  _last_millis_time = millis();
}

bool isPotenciometer1Change(long analogValue){
  if(analogValue != _l_potencimeter1){
    _l_potencimeter1 = analogValue;
    return true;
  }
  return false;  
}

bool isPotenciometer2Change(long analogValue){
    if(analogValue != _l_potencimeter2){
    _l_potencimeter2 = analogValue;
    return true;
  }
  return false;
}

void executeAction(int value){ // ejecuta acciones para el boton dependiendo de cual presiona
  //displayData(); // independiente de la accion muestra la data
  switch(value){
    case BTN_SELECT:      
      
      break;
    case BTN_LEFT:      
      
      break;
    case BTN_UP:      
      _vueltas++;
      break;
    case BTN_DOWN:
      if(_vueltas != 0) _vueltas--;
      break;
    case BTN_RIGHT:      
      
      break;
    default:      
      
      break;
  }
}

void executeButton(){
  int value = getValorBoton(analogRead(0));
  if(value != _last_btn){ // ha presionado un boton
    if(value != NOT_DEFINED){
      _last_btn_acction = value;
    }else{
      executeAction(_last_btn_acction);
      _last_btn_acction = NOT_DEFINED;
    }
    _last_btn = value;
  }
}


int getValorBoton(int valorAnalogico){
  if(valorAnalogico > (721 - ANALOG_ERROR) && valorAnalogico < (721 + ANALOG_ERROR) )      return BTN_SELECT;
  else if(valorAnalogico > (479 - ANALOG_ERROR) && valorAnalogico < (479 + ANALOG_ERROR) ) return BTN_LEFT;
  else if(valorAnalogico > (132 - ANALOG_ERROR) && valorAnalogico < (132 + ANALOG_ERROR) ) return BTN_UP;
  else if(valorAnalogico > (307 - ANALOG_ERROR) && valorAnalogico < (307 + ANALOG_ERROR) ) return BTN_DOWN;
  else if(valorAnalogico > (0 - ANALOG_ERROR) && valorAnalogico < (0 + ANALOG_ERROR) )     return BTN_RIGHT;
  else                                                                                     return NOT_DEFINED;
}
