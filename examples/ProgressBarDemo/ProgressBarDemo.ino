/*
Author: Esmit Perez <https://github.com/esmitperez/>
 
 MicroView Custom Widgets Demo
 
 */

#include <MicroView.h>
#include <MicroViewCustomWidgets.h>


MicroViewWidget *progress[8];   // declaring an array of 4 MicroViewWidget


void setup() {
  Serial.begin(9600);


  uView.begin();    // init and start MicroView

  uView.flipHorizontal(true);
  uView.flipVertical(true);
  // horizontal
  progress[0] = new MicroViewProgressBar(0,0,0,150,WIDGETSTYLE0); 
  progress[1] = new MicroViewConfigurableProgressBar(0,30,0, 150,WIDGETSTYLE0,4);
  // Vertical
  progress[2] = new MicroViewProgressBar(0,0,0, 150, WIDGETSTYLE1); 
  progress[3] = new MicroViewConfigurableProgressBar(0,30,0, 150, WIDGETSTYLE1,4);  

  // horizontal
  progress[4] = new MicroViewProgressBar(0,0,0,150,WIDGETSTYLE2); 
  progress[5] = new MicroViewConfigurableProgressBar(30,0,0, 150,WIDGETSTYLE2,4);
  // Vertical
  progress[6] = new MicroViewProgressBar(0,0,0, 150, WIDGETSTYLE3); 
  progress[7] = new MicroViewConfigurableProgressBar(30,0,0, 150, WIDGETSTYLE3,4);  

  uView.clear(PAGE);  // erase the memory buffer, when next uView.display() is called, the OLED will be cleared.

}


void loop() {
  for (int s=0; s<8; s++){
    drawSet(s);
    s++;
  }
}

void drawSet(uint8_t s){

  ((MicroViewWidget *) progress[s])->reDraw();
  ((MicroViewWidget *) progress[s+1])->reDraw();

  for (int i=0;i<=150;i++) {
    progress[s]->setValue(i);  
    progress[s+1]->setValue(i);
    delay(5);
    uView.display();
  }

  for(int i=150; i>=0;i--) {
    progress[s]->setValue(i);  
    progress[s+1]->setValue(i);
    delay(5);
    uView.display();
  }

  uView.clear(PAGE);  
  delay(200);
}
