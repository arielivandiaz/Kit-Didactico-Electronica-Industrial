/*
 * Autor: Ariel Ivan Diaz
 * Documentación: https://github.com/arielivandiaz/Kit-Didactico-Electronica-Industrial
 * Año: 2019
 */
 
#include <SoftwareSerial.h>

#define inputSize  10
#define outputSize  10

int outputPin = 0;

int inputResult = 0;
int outputResult = 0;

int outputWrite = 0;

int inputFloat =  0;
int outputFloat =  0;

int inputArray[inputSize] = {0};
int OutputArray[outputSize] = {0};

SoftwareSerial mySerial(1, 2); // RX, TX

/************* *******************/

void setup()
{
  mySerial.begin(9600);

  pinMode(outputPin, OUTPUT);  // sets the pin as output
}

/************* *******************/
void loop()
{

  //Leer entradas ADC
  int inputValue = analogRead(A2);
  int outputValue = analogRead(A3);


  //Filtro potenciometro
  for (int  i = 0; i < inputSize - 1; i++) {
    inputArray[i] = inputArray[i + 1];
  }
  inputArray[inputSize - 1] = inputValue;

  inputResult = 0;
  for (int  i = 0; i < inputSize; i++) {
    inputResult += inputArray[i];
    inputFloat +=  map(inputArray[i], 0, 1023, 0, 100);

  }
  inputResult /= inputSize;
  inputFloat /= inputSize;


  //Filtro entrada
  for (int  i = 0; i < outputSize - 1; i++) {
    OutputArray[i] = OutputArray[i + 1];
  }
  OutputArray[outputSize - 1] = outputValue;

  outputResult = 0;
  outputFloat =  0;
  for (int  i = 0; i < outputSize; i++) {
    outputResult += OutputArray[i];
    outputFloat +=  map(OutputArray[i], 0, 1023, 0, 100);
  }
  outputResult /= outputSize;
  outputFloat /= outputSize ;


  if (inputFloat > 100) inputFloat = 100;
  if (outputFloat > 100) outputFloat = 100;

  //Escribir salida analogica
  outputWrite = outputResult / 4 ;  
  analogWrite(outputPin, outputWrite);

  //Comunicación serial
  mySerial.print(inputFloat);
  mySerial.print('\t');
  mySerial.print(outputFloat  );
  mySerial.println('\t');


  delay(2);

}
