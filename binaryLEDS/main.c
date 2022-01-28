
#include <LPC17xx.h>
#include <stdbool.h>
#include <stdio.h>

#define Part 4

// Helper function to initialize the LEDs
void initLEDs (void) {
	LPC_GPIO2 -> FIODIR |= (1u << 6);
	LPC_GPIO2 -> FIODIR |= (1u << 5);
	LPC_GPIO2 -> FIODIR |= (1u << 4);
	LPC_GPIO2 -> FIODIR |= (1u << 3);
	LPC_GPIO2 -> FIODIR |= (1u << 2);
	LPC_GPIO1 -> FIODIR |= (1u << 31);
	LPC_GPIO1 -> FIODIR |= (1u << 29);
	LPC_GPIO1 -> FIODIR |= (1u << 28);
}

int part1(void) {
	initLEDs(); // Initialize the LEDs
	while (true) {
		// If P2.10 = 0: the pushbutton is pushed (active low)
		if (!((LPC_GPIO2 -> FIOPIN)&(1 << 10))) {
			LPC_GPIO2 -> FIOSET |= (1u << 6); // Turn leftmost LED on
		}
		else {
			LPC_GPIO2 -> FIOCLR |= (1u << 6); // Turn leftmost LED off
		}
	}
}

int part2(void) {
	int input = 0; // Initialize input variable to pause execution after a Joystick change
	while (true) {
		printf("Enter any number & press ctrl+j once you have changed the Joystick position: ");
		scanf("%d", &input); // Pause execution until user input
		// If P1.23 = 0 & P1.20 = 0 (active low)
		if (!((LPC_GPIO1 -> FIOPIN)&(1u << 23)) && !((LPC_GPIO1 -> FIOPIN)&(1u << 20))) { 
			printf("Joystick IS pressed in the NORTH direction\n");
		}
		// If P1.23 = 0 & P1.20 = 1 (active low)
		else if (!((LPC_GPIO1 -> FIOPIN)&(1u << 23)) && ((LPC_GPIO1 -> FIOPIN)&(1u << 20))) {
			printf("Joystick IS NOT pressed in the NORTH direction\n");
		}
		// If P1.25 = 0 & P1.20 = 0 (active low)
		else if (!((LPC_GPIO1 -> FIOPIN)&(1u << 25)) && !((LPC_GPIO1 -> FIOPIN)&(1u << 20))) {
			printf("Joystick IS pressed in the SOUTH direction\n");
		}
		// If P1.25 = 0 & P1.20 = 1 (active low)
		else if (!((LPC_GPIO1 -> FIOPIN)&(1u << 25)) && ((LPC_GPIO1 -> FIOPIN)&(1u << 20))) {
			printf("Joystick IS NOT pressed in the SOUTH direction\n");
		}
		// If P1.24 = 0 & P1.20 = 0 (active low)
		else if (!((LPC_GPIO1 -> FIOPIN)&(1u << 24)) && !((LPC_GPIO1 -> FIOPIN)&(1u << 20))) {
			printf("Joystick IS pressed in the EAST direction\n");
		}
		// If P1.24 = 0 & P1.20 = 1 (active low)
		else if (!((LPC_GPIO1 -> FIOPIN)&(1u << 24)) && ((LPC_GPIO1 -> FIOPIN)&(1u << 20))) {
			printf("Joystick IS NOT pressed in the EAST direction\n");
		}
		// If P1.26 = 0 & P1.20 = 0 (active low)
		else if (!((LPC_GPIO1 -> FIOPIN)&(1u << 26)) && !((LPC_GPIO1 -> FIOPIN)&(1u << 20))) {
			printf("Joystick IS pressed in the WEST direction\n");
		}
		// If P1.26 = 0 & P1.20 = 1 (active low)
		else if (!((LPC_GPIO1 -> FIOPIN)&(1u << 26)) && ((LPC_GPIO1 -> FIOPIN)&(1u << 20))) {
			printf("Joystick IS NOT pressed in the WEST direction\n");
		}
		// If P1.20 = 1 (active low)
		else if (((LPC_GPIO1 -> FIOPIN)&(1u << 20))) {
			printf("Joystick IS NOT pressed\n");
		}
		// If P1.20 = 0 (active low)
		else if (!((LPC_GPIO1 -> FIOPIN)&(1u << 20))) {
			printf("Joystick IS pressed\n");
		}
	}
}

int part3 (void) {
	initLEDs(); // Initialize LEDs
	int binary[8]; // Initialize array to hold binary digits
	while (true) {
		int input = -1; // Initialize input variable as -1 so if user enters a letter, error message will still appear
		int i = 0; // Initialize counter variable
		printf("Enter a number between 0 - 255 to display on the LEDs: ");
		scanf("%d", &input); // Pause execution until user input
		// If input is invalid, re-enter value
		if (input < 0 || input > 255) {
			printf("Number is not between 0 - 255 ... try again\n");
		}
		else {
			// Clear binary array of values from previous conversion
			for (int j = 0; j < 8; j++) {
				binary[j] = 0;
			}
			// While input != 0
			while (input != 0) {
				binary[i] = input%2; // Store remainder of modulo 2 into the binary array
				input = input/2; // Divide input by 2 (integer division)
				i++; // Increment the counter
			}
			// first binary digit is 1
			if (binary[0] == 1) {
				LPC_GPIO1 -> FIOSET |= (1u << 28); // Turn ON first LED from right
			}
			else {
				LPC_GPIO1 -> FIOCLR |= (1u << 28); // Turn OFF first LED from right
			}
			// second binary digit is 1
			if (binary[1] == 1) {
				LPC_GPIO1 -> FIOSET |= (1u << 29); // Turn ON second LED from right
			}
			else {
				LPC_GPIO1 -> FIOCLR |= (1u << 29); // Turn OFF second LED from right
			}
			// third binary digit is 1
			if (binary[2] == 1) {
				LPC_GPIO1 -> FIOSET |= (1u << 31); // Turn ON third LED from right
			}
			else {
				LPC_GPIO1 -> FIOCLR |= (1u << 31); // Turn OFF third LED from right
			}
			// fourth binary digit is 1
			if (binary[3] == 1) {
				LPC_GPIO2 -> FIOSET |= (1u << 2); // Turn ON fourth LED from right
			}
			else {
				LPC_GPIO2 -> FIOCLR |= (1u << 2); // Turn OFF fourth LED from right
			}
			// fifth binary digit is 1
			if (binary[4] == 1) {
				LPC_GPIO2 -> FIOSET |= (1u << 3); // Turn ON fifth LED from right
			}
			else {
				LPC_GPIO2 -> FIOCLR |= (1u << 3); // Turn OFF fifth LED from right
			}
			// sixth binary digit is 1
			if (binary[5] == 1) {
				LPC_GPIO2 -> FIOSET |= (1u << 4); // Turn ON sixth LED from right
			}
			else {
				LPC_GPIO2 -> FIOCLR |= (1u << 4); // Turn OFF sixth LED from right
			}
			// seventh binary digit is 1
			if (binary[6] == 1) {
				LPC_GPIO2 -> FIOSET |= (1u << 5); // Turn ON seventh LED from right
			}
			else {
				LPC_GPIO2 -> FIOCLR |= (1u << 5); // Turn OFF seventh LED from right
			}
			// eighth binary digit is 1
			if (binary[7] == 1) {
				LPC_GPIO2 -> FIOSET |= (1u << 6); // Turn ON eighth LED from right
			}
			else {
				LPC_GPIO2 -> FIOCLR |= (1u << 6); // Turn OFF eighth LED from right
			}
		}
	}
}

int part4 (void) {
	LPC_SC -> PCONP |= (1 << 12); // Power the ADC
	LPC_PINCON -> PINSEL1 &= ~(3 << 18); // Clear bits 18 & 19
	LPC_PINCON -> PINSEL1 |= (1 << 18); // Set bits 18 & 19 to 01 = AD0.2
	LPC_ADC -> ADCR = (1 << 2) | // Select AD0.2
										(4 << 8) | // Clock = 5MHz = 25MHz/(4+1)
										(1 << 21); // Enable ADC
	float digital = 0; // Digital FLOAT to print after conversion
	while (true) {
		LPC_ADC -> ADCR |= (1u << 24); // Set bit 24 of ADCR register to start conversion
		// Wait for bit 31 of ADGDR to indicate conversion complete
		while (!((LPC_ADC -> ADGDR)&(1u << 31)));
		digital = ((LPC_ADC -> ADGDR >> 4)&0xFFF); // Shift value by 4 places and mask the 12 bits
		printf("%f\n", digital*(3.5/4095)); // Scale and print the result
	}
}

int main (void) {
	#if Part == 1
	part1();
	#elif Part == 2
	part2();
	#elif Part == 3
	part3();
	#elif Part == 4
	part4();
	#endif
}
