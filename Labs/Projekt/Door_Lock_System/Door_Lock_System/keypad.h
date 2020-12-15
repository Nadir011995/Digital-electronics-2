
#ifndef KEYPAD_H_
#define KEYPAD_H_

// Declarations of the variables

int correct; // Correct Password or not for the 1st person
int correct_1; // Correct Password or not for the 2nd person 
int correct_2; // Correct Password or not for the 3rd person 
int count_1; // Count_1 is actually a flag to check whether any key was pressed or not 
int count; // Count for total number of keys for password 
char pass[4]; // Array where the entered keys will be stored here 
int password[4]; // Password for Mr. Al-Wattar (Person 2) 
int password_1[4]; // Password for Mr. Thomas (Person 2)
int password_2[4]; // Password for Mr. Shala (Person 3)
int position; // Initial position on display
int time_check; // Checking time in TIMER0_OVF_vect
int countdown; // Countdown for closing door
int countdown_1; // Countdown for entering the password
int countdown_2; // For freezing the display
int countdown_flag; // Door is opened






void keypad();

void Check_password();

void Check_password_1();

void Check_password_2();

void reset();

void entry_denied();

void entry_accepted();


#endif /* KEYPAD_H_ */