#include "mbed.h"
#include "SevenSegDisplay.h"

// display1 i display2 objekti klase SevenSegDisplay, definiramo pinove displaya
SevenSegDisplay display_home(PA_0, PB_8, PC_0, PA_6, PC_1, PA_5, PB_9); // a, b, c, d, e, f, g
SevenSegDisplay display_away(PA_9, PA_8, PB_10, PB_3, PB_5, PB_0, PA_10); // a, b, c, d, e, f, g

InterruptIn button_home(USER_BUTTON); // Interrupt USER_BUTTON tipkala
InterruptIn button_away(PC_7); // Interrupt pin tipkala

DigitalOut green_led(PA_7); // zelena LED
DigitalOut yellow_led(PC_8); // zuta LED
DigitalOut red_led(PB_6); // crvena LED

PwmOut buzzer(PB_4); // buzzer PWM

//ticker
Ticker ticker;

Timer debounce;

int home_score = 0; // domaci rezultat
int away_score = 0; // gostujuci rezultat

void flash();
void celebrate();
void button_home_pressed();
void button_away_pressed();

void flash() {
    if (home_score>away_score) {
        green_led = !green_led;
        red_led = yellow_led = 0;
    } else if (home_score<away_score) {
        red_led = !red_led;
        green_led = yellow_led = 0;
    } else {
        yellow_led = !yellow_led;
        green_led = red_led = 0;
    }
}

void celebrate() {
    buzzer.period(1.0/500);  // Set the PWM period to 500 Hz
    green_led=yellow_led=red_led=0;
    for(int i=0; i<4; i++) {
        for (float duty_cycle = 0.0; duty_cycle < 1.0; duty_cycle += 0.01) {
            buzzer.write(duty_cycle);  // Set the PWM duty cycle
            display_home.off(); // poziv metode off iz klase, gasi display
            green_led=red_led=yellow_led=1;
            wait(0.005);  // Wait for 5 ms
        }
        for (float duty_cycle = 1.0; duty_cycle > 0.0; duty_cycle -= 0.01) {
            buzzer.write(duty_cycle);  // Set the PWM duty cycle
            display_home.write(home_score); // poziv metode write iz klase, ovisno o rezultatu ispisuje broj na displayu
            green_led=red_led=yellow_led=0;
            wait(0.005);  // Wait for 5 ms
        }
    }
}

void button_home_pressed() {
  if (debounce.read_ms() > 200) {    // koristimo debounce kako bi sprijecili titranje signala tipkala kod pritiska
    if (home_score<9) {
        home_score++;
        celebrate();
    }
    debounce.reset();
  }
}

void button_away_pressed() {
  if (debounce.read_ms() > 200) {    // koristimo debounce kako bi sprijecili titranje signala tipkala kod pritiska
    if (away_score<9) {
        green_led=yellow_led=red_led=0;
        away_score++;
        for (int i=0; i<5; i++)
        {
            if (i%2==0) display_away.off(); // poziv metode off iz klase, gasi display
            else display_away.write(away_score); // poziv metode write iz klase, prikazuje rezultat
            wait(0.3);
            red_led=!red_led;
        }
    }
    debounce.reset();
  }
}

int main() {
  green_led = 0;
  red_led = 0;
  button_home.mode(PullUp);// pull up - definiramo stanje tipkala
  button_away.mode(PullUp);// pull up - definiramo stanje tipkala
  debounce.start();
  button_home.rise(&button_home_pressed); // tipkalo poziva funkciju na rastući brid signala (kad stisnemo tipkalo)
  button_away.rise(&button_away_pressed); // tipkalo poziva funkciju na rastući brid signala (kad stisnemo tipkalo)
  ticker.attach(flash, 0.7);  // ticker objektu pridruzujemo flash funckiju svakih 0.7 sekunde
  while (true) {
    display_home.write(home_score); // poziv metode write iz klase, ovisno o rezultatu ispisuje broj na displayu
    display_away.write(away_score); // poziv metode write iz klase, ovisno o rezultatu ispisuje broj na displayu
  }
}