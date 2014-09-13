

#include <MicroView.h>


#import "MicroViewCustomWidgets.h"



MicroViewWidget *progress[3];		// declaring an array of 4 MicroViewWidget

void setup() {
  uView.begin();		// init and start MicroView
  uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.

  uView.flipHorizontal(true);
  uView.flipVertical(true);

  progress[1] = new MicroViewProgressBar(0,0,0, 50, WIDGETSTYLE0);		// declare widget0 as a Slider at x=0, y=0, min=0, max=100
  //progress[1] = new MicroViewProgressBar(0,15,0, 50, WIDGETSTYLE0);	// declare widget0 as a Slider at x=0, y=10, min=0, max=150
  progress[0] = new MicroViewSlider(0,15,0, 50, WIDGETSTYLE0);	// declare widget0 as a Slider at x=0, y=10, min=0, max=150

    //widget[2] = new MicroViewProgressBar(0,20,0, 255);		// declare widget0 as a Slider at x=0, y=20, min=0, max=50
  //widget[3] = new MicroViewSlider(0,30,0,255);	// declare widget0 as a Slider at x=0, y=30, min=0, max=200

    //progress[0]  -> setThickness(1);
  //progress[2]  -> setThickness(3);
}

void loop1(){
  uView.display();
}

void loop() {
  delay(1200);

  for (int i=0;i<=50;i++) {
    progress[0]->setValue(i);		// set value i to widget0
    //progress[1]->setValue(i);
    progress[1]->setValue(i);

    /*
                widget[1]->setValue(100-i);
     		widget[2]->setValue(i);
     		widget[3]->setValue(100-i);
     */
    delay(50);
    uView.display();
  }

  delay(1200);

  for(int i=50; i>=0;i--) {
    progress[0]->setValue(i);		// set value i to widget0
    //progress[1]->setValue(i);
    progress[1]->setValue(i);

    /*
		widget[1]->setValue(100-i);
     		widget[2]->setValue(i);
     		widget[3]->setValue(100-i);
     */
    delay(50);
    uView.display();
  }

}

