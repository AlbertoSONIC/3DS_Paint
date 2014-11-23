#ifndef MENU_H
#define MENU_H

void menu();
void printAbout();
void printBottomMenu();
void printSettings();
void printTopMenu();

void paint();
void variableReset();
void renderBottomUi();
void printBottomBackgnd();
void printBottomIcon();
void printDrawing();
void renderDrawing();
void printTop();
void printWarning();

void screenRender();
void screenRefresh();
void clearBottom();
void clearTop();

extern int mode;


#endif
