/** \brief Draw widget value.
 * 
 * 	Convert the current value of the widget and draw the ticker representing the value.
 */
#include <MicroView.h>
#include "MicroViewCustomWidgets.h"

// -------------------------------------------------------------------------------------
// ProgressBar Widget - start
// -------------------------------------------------------------------------------------

/** \brief MicroViewProgressBar class initialisation. 
 * 
 * 	Initialise the MicroViewProgressBar widget with default style.
 */
MicroViewProgressBar::MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max):
MicroViewWidget(newx, newy, min, max) {
  style=0;
  totalTicks=30;
  prevValue=getMinValue();
  needFirstDraw=true;
  drawFace();
  draw();
}

/** \brief MicroViewProgressBar class initialisation with style. 
 * 
 * 	Initialise the MicroViewProgressBar widget with style WIDGETSTYLE0 or WIDGETSTYLE1 or WIDGETSTYLE2 (like 0, but vertical) or WIDGETSTYLE3 (like 1, but vertical). If this list gets any longer, it might be better as a switch/case statement.
 */

MicroViewProgressBar::MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty):
MicroViewWidget(newx, newy, min, max) {

  switch(sty){
  case WIDGETSTYLE1: 
    style=1;
    totalTicks=60;
    break;
  case WIDGETSTYLE2: 
    style=2;
    totalTicks=20;
    break;
  case WIDGETSTYLE3: 
    style=3;
    totalTicks=40;
    break;
  default: 
    style=0;
    totalTicks=30;
    break;
  }

  prevValue=getMinValue();
  needFirstDraw=true;
  drawFace();
  draw();
}

uint8_t MicroViewProgressBar::getLabelX() {
  if (style == 0 || style == 1){
    return getX();
  }

  // else it's vertical
  return getX();
}

uint8_t MicroViewProgressBar::getLabelY() {
  return getY(); 
}

uint8_t MicroViewProgressBar::getWidgetX() {
  if (style == 0 || style == 1){
    return getX();
  }

  // else it's vertical
  return getX()+3;
}

uint8_t MicroViewProgressBar::getWidgetY() {
  return getY(); 
}

uint8_t MicroViewProgressBar::getThickness() {
  return 8;
}




/** \brief Draw widget face.
 * 
 * 	Draw image/diagram representing the widget's face.
 */
void MicroViewProgressBar::drawFace() {
  uint8_t offsetX, offsetY, endOffset;
  offsetX=getWidgetX();
  offsetY=getWidgetY();

  //Horizontal styles, style 0 or 1
  if (style==0 || style==1) {
    endOffset = offsetX + totalTicks + 1;
    // Draw sides
    uView.lineV(offsetX, offsetY, getThickness());
    uView.lineV(offsetX+endOffset, offsetY, getThickness());
    // Draw top/bottom
    for (uint8_t i=offsetX; i<=endOffset; i++) {
      uView.pixel(i, offsetY+getThickness());
      uView.pixel(i, offsetY);
    }
  }
  //Vertical styles, style 2 or 3
  else {
    endOffset = offsetY + totalTicks + 2;
    uView.lineH(offsetX, offsetY, getThickness());
    uView.lineH(offsetX, offsetY+endOffset, getThickness());

    for (uint8_t i=offsetY; i<=endOffset; i++) {
      uView.pixel(offsetX+getThickness(), i);
      uView.pixel(offsetX, i);
    }
  }
}

/** \brief Draw widget value.
 * 
 * 	Convert the current value of the widget and draw the ticker representing the value.
 */
void MicroViewProgressBar::draw() {
  uint8_t offsetX, offsetY, endOffset;
  uint8_t tickPosition=0;
  char strBuffer[7];
  char formatStr[] = "%1d";

  formatStr[1] = '0' + getMaxValLen();	// Set the field width for the value range

  offsetX=getWidgetX();
  offsetY=getWidgetY();

  // Draw previous pointer in XOR mode to erase it
  if (style==0 || style==1){		//Horizontal
    tickPosition = (((float)(uint16_t)(prevValue-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue())) * totalTicks) ;
    endOffset = offsetX + totalTicks + 2;

    for(uint8_t i =offsetX+1; i <= tickPosition; i++){
      uView.lineV(i,offsetY+1, getThickness()-1, WHITE, XOR);
    }

  }
  else {					//Vertical
    tickPosition = ((float)(uint16_t)(getMaxValue()-prevValue)/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks + 1;
    endOffset = offsetY + totalTicks + 2;

    for(uint8_t i = endOffset-1; i >= tickPosition; i--){
      uView.lineH(offsetX+1,i,getThickness()-1, WHITE, XOR);
    }

  }

  if (needFirstDraw) {
    sprintf(strBuffer, formatStr, prevValue);	// print with fixed width so that blank space will cover larger value
    needFirstDraw=false;
  }
  else {
    // Draw current pointer
    if (style==0 || style==1){		//Horizontal
      tickPosition = (((float)(uint16_t)(getValue()-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks);

      for(uint8_t i =offsetX+1; i <= tickPosition; i++){
        //uView.lineV(i, offsetY+1, getThickness()-2, WHITE, XOR);
        uView.lineV(i,offsetY+1, getThickness()-1,WHITE,XOR);
      }
    }
    else {            //Vertical
      tickPosition = ((float)(uint16_t)(getMaxValue()-getValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks + 1;
      for(uint8_t i = endOffset-1; i >= tickPosition; i--){
        uView.lineH(offsetX+1,i,getThickness()-1, WHITE, XOR);
      }
    }

    sprintf(strBuffer, formatStr, getValue());	// print with fixed width so that blank space will cover larger value
    prevValue=getValue();
  }

  // Draw value
  switch(style){
  case 0:
    //uView.setCursor(getLabelX()+totalTicks+4, offsetY+1);
    uView.setCursor(getLabelX()+totalTicks+4, getLabelY() + 1);
    break;
  case 1:
    uView.setCursor(getLabelX(), offsetY+10);
    break;
  case 2:
    uView.setCursor(getLabelX()+1, offsetY+totalTicks+4);
    break;  
  default:
    uView.setCursor(getLabelX()+9, offsetY);
    break;
  }

  uView.print(strBuffer);
}

// -------------------------------------------------------------------------------------
// ProgressBar Widget - end
// -------------------------------------------------------------------------------------










