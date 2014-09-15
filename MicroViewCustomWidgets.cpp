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
 MicroViewProgressBarBase::MicroViewProgressBarBase(uint8_t newx, uint8_t newy, int16_t min, int16_t max):
 MicroViewWidget(newx, newy, min, max) {
  style=WIDGETSTYLE0;
  totalTicks=30;
  printLabel=true;

  Serial.println("24");

  preInit();
  initWidget(); 
  postInit();
}

/** \brief MicroViewProgressBar class initialisation with style. 
 * 
 * 	Initialise the MicroViewProgressBar widget with style WIDGETSTYLE0 or WIDGETSTYLE1 or WIDGETSTYLE2 (like 0, but vertical) 
 *  or WIDGETSTYLE3 (like 1, but vertical). 
 */

 MicroViewProgressBarBase::MicroViewProgressBarBase(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty):
 MicroViewWidget(newx, newy, min, max) {

  style = sty;
  printLabel=true;
  switch(sty){
    case WIDGETSTYLE1:
    totalTicks=60;
    break;
    case WIDGETSTYLE2:
    totalTicks=20;
    break;
    case WIDGETSTYLE3:
    totalTicks=40;
    break;
    // If already 0 or invalid, just make sure it's 0.
    case WIDGETSTYLE0:
    default:
    style=WIDGETSTYLE0;
    totalTicks=30;
    break;
  }

  Serial.println("60");
Serial.println(printLabel);

  preInit();
  initWidget(); 
  postInit();
}


void MicroViewProgressBarBase::initWidget(){
  if (!initialized){
    thickness=DEFAULT_THICKNESS;
    printLabel=true;
    initialized = true;
  }


}

void MicroViewProgressBarBase::preInit(){
  prevValue=getMinValue();
  needFirstDraw=true;

}

void MicroViewProgressBarBase::postInit(){
  drawFace();
  draw(); 
}


uint8_t MicroViewProgressBarBase::getLabelX() {
  if (style == 0 || style == 1){
    return getX();
  }

  // else it's vertical
  return getX();
}

uint8_t MicroViewProgressBarBase::getLabelY() {
  return getY(); 
}

uint8_t MicroViewProgressBarBase::getWidgetX() {
  if (style == 0 || style == 1){
    return getX();
  }

  // else it's vertical
  return getX()+3;
}

uint8_t MicroViewProgressBarBase::getWidgetY() {
  return getY(); 
}

uint8_t MicroViewProgressBarBase::getThickness() {
  return thickness;
}




/** \brief Draw widget face.
 * 
 * 	Draw image/diagram representing the widget's face.
 */
 void MicroViewProgressBarBase::drawFace() {
  uint8_t offsetX, offsetY, endOffset;
  offsetX=getWidgetX();
  offsetY=getWidgetY();

  switch(style){
    // HORIZONTAL
    case WIDGETSTYLE0:
    case WIDGETSTYLE1:
    endOffset = offsetX + totalTicks + 1;
      // Draw sides
    uView.lineV(offsetX, offsetY, getThickness());
    uView.lineV(offsetX+endOffset, offsetY, getThickness());
      // Draw top/bottom
    for (uint8_t i=offsetX; i<=endOffset; i++) {
      uView.pixel(i, offsetY+getThickness());
      uView.pixel(i, offsetY);
    }
    break;
    // VERTICAL 
    case WIDGETSTYLE2:
    case WIDGETSTYLE3:

    endOffset = offsetY + totalTicks + 2;
    uView.lineH(offsetX, offsetY, getThickness());
    uView.lineH(offsetX, offsetY+endOffset, getThickness());

    for (uint8_t i=offsetY; i<=endOffset; i++) {
      uView.pixel(offsetX+getThickness(), i);
      uView.pixel(offsetX, i);
    }
    break;
  }

}

/** \brief Draw widget value.
 * 
 * 	Convert the current value of the widget and draw the ticker representing the value.
 */
 void MicroViewProgressBarBase::draw() {
  uint8_t offsetX, offsetY, endOffset;
  uint8_t tickPosition=0;
  char strBuffer[7];
  char formatStr[] = "%1d";

  formatStr[1] = '0' + getMaxValLen();	// Set the field width for the value range

  offsetX=getWidgetX();
  offsetY=getWidgetY();

  // Draw previous pointer in XOR mode to erase it
  switch(style){
    // HORIZONTAL
    case WIDGETSTYLE0:
    case WIDGETSTYLE1:
    tickPosition = (((float)(uint16_t)(prevValue-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue())) * totalTicks) ;
    endOffset = offsetX + totalTicks + 2;

    for(uint8_t i =offsetX+1; i <= tickPosition; i++){
      uView.lineV(i,offsetY+1, getThickness()-1, WHITE, XOR);
    }
    break;
     // VERTICAL 
    case WIDGETSTYLE2:
    case WIDGETSTYLE3:
    tickPosition = ((float)(uint16_t)(getMaxValue()-prevValue)/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks + 1;
    endOffset = offsetY + totalTicks + 2;

    for(uint8_t i = endOffset-1; i >= tickPosition; i--){
      uView.lineH(offsetX+1,i,getThickness()-1, WHITE, XOR);
    }
    break;
  }


  if (needFirstDraw) {
    sprintf(strBuffer, formatStr, prevValue);	// print with fixed width so that blank space will cover larger value
    needFirstDraw=false;
  }
  else {
    // Draw previous pointer in XOR mode to erase it
    switch(style){
    // HORIZONTAL
      case WIDGETSTYLE0:
      case WIDGETSTYLE1:  
      tickPosition = (((float)(uint16_t)(getValue()-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks);

      for(uint8_t i =offsetX+1; i <= tickPosition; i++){
        //uView.lineV(i, offsetY+1, getThickness()-2, WHITE, XOR);
        uView.lineV(i,offsetY+1, getThickness()-1,WHITE,XOR);
      }
      break;

      // VERTICAL 
      case WIDGETSTYLE2:
      case WIDGETSTYLE3:
      tickPosition = ((float)(uint16_t)(getMaxValue()-getValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks + 1;
      for(uint8_t i = endOffset-1; i >= tickPosition; i--){
        uView.lineH(offsetX+1,i,getThickness()-1, WHITE, XOR);
      }
      break;
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
    uView.setCursor(getLabelX()+getThickness() + 4, offsetY);
    break;
  }

  if (isPrintLabel()){
    uView.print(strBuffer);
  }
}

void MicroViewProgressBarBase::setPrintLabel(boolean print){
  printLabel = print;
}

boolean MicroViewProgressBarBase::isPrintLabel(){
  return printLabel;
}



// -------------------------------------------------------------------------------------
// ProgressBar Widget - end
// -------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------
// Fixed Size ProgressBar Widget - start
// -------------------------------------------------------------------------------------

 /** \brief MicroViewProgressBar class initialisation. 
 * 
 *  Initialise the MicroViewProgressBar widget with default style.
 */
 MicroViewProgressBar::MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max):
 MicroViewProgressBarBase(newx, newy, min, max,WIDGETSTYLE0) {
  thickness = DEFAULT_THICKNESS;
 }


 /** \brief MicroViewProgressBar class initialisation with style. 
 * 
 *  Initialise the MicroViewProgressBar widget with style WIDGETSTYLE0 or WIDGETSTYLE1 or WIDGETSTYLE2 (like 0, but vertical) 
 *  or WIDGETSTYLE3 (like 1, but vertical). 
 */

 MicroViewProgressBar::MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty):
 MicroViewProgressBarBase(newx, newy, min, max, sty) {
  thickness = DEFAULT_THICKNESS;
}


/** \brief MicroViewProgressBar class initialisation with style and thickness 
 * 
 *  Initialise the MicroViewProgressBar widget with style WIDGETSTYLE0 or WIDGETSTYLE1 or WIDGETSTYLE2 (like 0, but vertical) 
 *  or WIDGETSTYLE3 (like 1, but vertical). 
 */

 MicroViewProgressBar::MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty, int16_t thick):
 MicroViewProgressBarBase(newx, newy, min, max, sty) {
  thickness = thick;
}

void MicroViewProgressBar::initWidget(){
  if (!initialized){
    initialized= true;
    printLabel=true;
  }
}

// -------------------------------------------------------------------------------------
// Fixed Size ProgressBar Widget - end
// -------------------------------------------------------------------------------------













