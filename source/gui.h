#ifndef GUI_H
#define GUI_H

void guiTopPaint();
void guiTopMenu();
void guiBottomPaint(int color, int cTable[8][3], int posxy[320][240]);
void guiBottomMenu();
void guiClock();
void guiPopup(char* title, char* line1, char* line2, char* line3, char* button1, char* button2, bool closeonly);
void guiDebug(int mode, int state, int color, int rendered, int printFPS, int posX, int posY);


#endif
