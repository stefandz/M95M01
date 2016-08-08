/*******************************************************************************

 M95M01 SPI EEPROM library
 -------------------------
 
 M95M01_test.ino - M95M01 test sketch
 
 Code written by Stefan Dzisiewski-Smith.
 
 This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 
 Unported License (CC BY-SA 3.0) http://creativecommons.org/licenses/by-sa/3.0/
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

*******************************************************************************/

#include "M95M01.h"

const uint8_t CS = 2; // connect EEPROM CS pin to D2 on Arduino
const uint32_t unaligned_array_length = 881; // prime number to avoid page alignment
const uint32_t aligned_array_length = 512; // page aligned - must be < unaligned_array_length

uint32_t i;
uint32_t j;

uint8_t readback[unaligned_array_length];  
uint8_t test_array[unaligned_array_length];

void setup() {

  M95M01.begin(CS, 2000000); // I have limited this to a 2MHz clock speed, but feel free to increase

  Serial.begin(115200);

  while(!Serial); // wait for Serial service to start on Leonardo  
}

void loop() {

  Serial.println(F("Starting full address write and read test:")); 
  Serial.println();

/************* ZEROS *************/

  Serial.print(F("Populating zeros array..."));

  for(i=0; i<aligned_array_length; i++){
    test_array[i] = 0;
  }

  Serial.println(F("done."));
  Serial.println();

  Serial.println(F("zeros:"));

  for(i=0; i<M95M01.num_bytes/aligned_array_length; i++){
      
    Serial.print(F("."));
    
    M95M01.write_array(i*aligned_array_length, test_array, aligned_array_length);
    M95M01.read_array(i*aligned_array_length, readback, aligned_array_length);

    for(j=0; j<aligned_array_length; j++){
      if(readback[j]!=0){
        Serial.print(F("zero readback error at 0x"));
        Serial.println(j+(i*aligned_array_length), HEX);
      }
    }   
    if(i%64 == 63){
      Serial.println();
    }
  }    

  Serial.println(F("done.")); 
  Serial.println(); 

/********* ALIGNED ARRAY *********/

  Serial.print(F("Populating randomised array..."));

  randomSeed(analogRead(0));

  for(i=0; i<aligned_array_length; i++){
    test_array[i] = random(0, 255);
  }

  Serial.println(F("done."));
  Serial.println(F("First 16 values:"));
  for(i=0; i<16; i++){
    Serial.print(test_array[i]);
    if(i<15){
      Serial.print(F(", "));
    }
  }
  Serial.println();
  Serial.println();  

  Serial.println(F("page-aligned array:"));

  for(i=0; i<M95M01.num_bytes/aligned_array_length; i++){
      
    Serial.print(F("."));
    
    M95M01.write_array(i*aligned_array_length, test_array, aligned_array_length);
    M95M01.read_array(i*aligned_array_length, readback, aligned_array_length);

    for(j=0; j<aligned_array_length; j++){
      if(readback[j]!=test_array[j]){
        Serial.print(F("page-aligned array readback error at 0x"));
        Serial.println(j+(i*aligned_array_length), HEX);
      }
    }   
    if(i%64 == 63){
      Serial.println();
    }
  }    

  Serial.println(F("done.")); 
  Serial.println(); 

/*************  END  *************/   

/******* NON-ALIGNED-ARRAY *******/ 

  Serial.print(F("Repopulating randomised array..."));

  randomSeed(analogRead(0));

  for(i=0; i<unaligned_array_length; i++){
    test_array[i] = random(0, 255);
  }

  Serial.println(F("done."));
  Serial.println(F("First 16 values:"));
  for(i=0; i<16; i++){
    Serial.print(test_array[i]);
    if(i<15){
      Serial.print(F(", "));
    }
  }
  Serial.println();
  Serial.println();

  Serial.println(F("non-aligned array:"));  

  for(i=0; i<1+(M95M01.num_bytes/unaligned_array_length); i++){ 
    Serial.print(F("."));
    M95M01.write_array(i*unaligned_array_length, test_array, unaligned_array_length);
    M95M01.read_array(i*unaligned_array_length, readback, unaligned_array_length);

    for(j=0; j<unaligned_array_length; j++){
      if(readback[j]!=test_array[j]){
        Serial.print(F("non-aligned array readback error at 0x"));
        Serial.println(j+(i*unaligned_array_length), HEX);
      }
    } 
    if(i%64 == 63){
      Serial.println();
    }    
  }
  Serial.println(F("done."));
  Serial.println();
  Serial.println(F("Send any serial char to repeat."));
/*************  END  *************/ 

  while(!Serial.available()){

  }
  while(Serial.available()){
    Serial.read(); // chew up the chars so they don't retrigger us
  }

}