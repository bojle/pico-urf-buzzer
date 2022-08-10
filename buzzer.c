#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include <PicoTM1637.h>

#define NO_LEADING_ZEROS 0

const uint buzzer_pin = 15;
const uint trig_pin = 16;
const uint echo_pin = 17;
const uint clk_pin = 18;
const uint dio_pin = 19;
const uint led_pin = PICO_DEFAULT_LED_PIN;

void init() {
	stdio_init_all();
	gpio_init(buzzer_pin);
	gpio_init(trig_pin);
	gpio_init(echo_pin);
	gpio_init(led_pin);
	gpio_set_dir(buzzer_pin, GPIO_OUT);
	gpio_set_dir(trig_pin, GPIO_OUT);
	gpio_set_dir(echo_pin, GPIO_IN);
	gpio_set_dir(led_pin, GPIO_OUT);
    TM1637_init(clk_pin, dio_pin);
    TM1637_clear();
    TM1637_set_brightness(3); // appropriate brightness
}

double get_distance() {
	gpio_put(trig_pin, 0);
	sleep_us(5);

	gpio_put(trig_pin, 1);
	sleep_us(10);
	gpio_put(trig_pin, 0);

	absolute_time_t start, stop;	
	while (gpio_get(echo_pin) == 0) {
		start = get_absolute_time();	
	}
	while (gpio_get(echo_pin) == 1) {
		stop = get_absolute_time();
	}
	int diff = absolute_time_diff_us(start, stop);
	printf("Difference: %d\n", diff);
	double distance = diff / 58.f;
	return distance;	
}

void print_debug() {
	printf("Buzzer pin: %d\n", gpio_get(buzzer_pin));
}

void beep_once() {
	gpio_put(buzzer_pin, 1);
	sleep_ms(200);
	gpio_put(buzzer_pin, 0);
}

void beep_twice() {
	gpio_put(buzzer_pin, 1);
	sleep_ms(200);
	gpio_put(buzzer_pin, 0);
	sleep_ms(20);
	gpio_put(buzzer_pin, 1);
	sleep_ms(200);
	gpio_put(buzzer_pin, 0);
}

void long_beep() {
	gpio_put(buzzer_pin, 1);
	sleep_ms(800);
	gpio_put(buzzer_pin, 0);
}

int main() {
	init();
	gpio_put(led_pin, 1);

	double distance;
	while (1) {
		distance = get_distance();
		if (distance <= 15) {
			long_beep();
		}
		else if (distance <= 20) {
			beep_twice();
		}
		else if (distance <= 30) {
			beep_once();
		}
		else {
			gpio_put(buzzer_pin, 0);
		}
		printf("Distance: %f\n", distance);
		print_debug();
		sleep_ms(500);
	}
}
