#ifndef CONTROLLER_H
#define CONTROLLER_H

#define CTRL_LEFT 1
#define CTRL_RIGHT 2
#define CTRL_QUIT 3

int controller_connected(int controller);
void controller_update();
int key_down(int controller, int key);

#endif