#ifndef MICROVIEWCUSTOMWIDGETS_H
#define MICROVIEWCUSTOMWIDGETS_H

#include "MicroView.h"

class MicroViewProgressBar: public
 MicroViewWidget {
public:
  MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max);
  MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty);

  void draw();
  void drawFace();
  uint8_t getLabelX();
  uint8_t getLabelY();
  uint8_t getWidgetX();
  uint8_t getWidgetY();
  
  uint8_t getThickness();
private:
  uint8_t totalTicks, style, thickness;
  int16_t prevValue;
};


#endif


