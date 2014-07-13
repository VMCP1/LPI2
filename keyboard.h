 
#ifndef KEYBOARD_H
#define KEYBOARD_H

void KeyboardConfig();

/*
 * Return
 * 
 * 'U'->Up
 * 'D'->Down
 * 'L'->Left
 * 'R'->Right
 * 'O'->Ok
 * 'Z'->No Key Pressed
 */
char KeyboardGetKey();

#endif
