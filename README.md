# MicroView Arduino Custom Widget Library

Author: Esmit Perez <https://github.com/esmitperez/>


## Description

Custom Widgets for MicroView.

## Required Libraries

1. [MicroView.h] <https://github.com/geekammo/MicroView-Arduino-Library>

## Installation

1. Change directory to Arduino's main directory
2. cd libraries
3. mkdir MicroViewCustomWidgets
4. cd MicroViewCustomWidgets
5. git clone https://github.com/esmitperez/MicroViewCustomWidgets.git .
6. Start Arduino IDE.
7. MicroViewCustomWidget example is located at, File--->Example--->MicroViewCustomWidgets--->Demo

### Example 1 -  Widgets
<pre><code>
#include &lt;MicroView.h&gt;
#include &lt;MicroViewCustomWidgets.h&gt;


MicroViewWidget *widget;

void setup() {
    uView.begin();
    uView.clear(PAGE);
    widget= new MicroViewProgressBar(0,0,0,100);

void loop() {
    for(int i=0; i&lt;=100;i++) {
        widget->setValue(i);	// give a value to widget
        uView.display();		// display current page buffer
    }
}
</code></pre>


## License
    Esmit Perez - esmit.perez@gmail.com
    Copyright (C) 2014 Esmit Perez

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
