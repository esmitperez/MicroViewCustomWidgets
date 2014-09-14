#ifndef MICROVIEWCUSTOMWIDGETS_H

#define MICROVIEWCUSTOMWIDGETS_H
#define DEFAULT_THICKNESS 8

#include "MicroView.h"


class MicroViewProgressBarBase: public
MicroViewWidget {
public:
  MicroViewProgressBarBase(uint8_t newx, uint8_t newy, int16_t min, int16_t max);
  MicroViewProgressBarBase(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty);
  void draw();
  void drawFace();
  uint8_t getLabelX();
  uint8_t getLabelY();
  uint8_t getWidgetX();
  uint8_t getWidgetY();
  
  uint8_t getThickness();

private:
  uint8_t totalTicks, style;
  int16_t prevValue;

protected:
  uint8_t thickness;
  boolean printLabel;
  boolean initialized;
  void preInit();
  void postInit();
  virtual void initWidget();
};


class MicroViewConfigurableProgressBar: public
MicroViewProgressBarBase {
public:
  MicroViewConfigurableProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max);
  MicroViewConfigurableProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty);
  MicroViewConfigurableProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty, int16_t thickness);
  MicroViewConfigurableProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty, int16_t thickness, boolean printLabel);

protected:
virtual void initWidget();
};

class MicroViewProgressBar: public
MicroViewConfigurableProgressBar {
public:
  MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max);
  MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty);
  MicroViewProgressBar(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty, boolean printLabel);

protected:
  virtual void initWidget();
};



#endif


