#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
//definition for the wire connections
#define rs PC0
#define rw PC1
#define en PC2
#define data PORTB
//functions necessary
void lcd_init(); //to initialize lcd.
void lcd_cmd(char cmd_out); //to send command to lcd.
void lcd_data(char data_out); //to send data to lcd.
void lcd_str(const char *str); //to send string, basically stripping each character and sending.
void check();

int main()
{
	//set DDR
	DDRB |= 0XFF; //set port b as output
	DDRC |= (1<<rs)| (1<<rw) | (1<<en);
	lcd_init(); // calls init commands
	check();
	while(1)
	{}
}

//initializes the command
void lcd_init()
{
	
	lcd_cmd(0x38); // Initializing to 2 lines & 5x7 font.
	lcd_cmd(0xE);// Display on, cursor on
	lcd_cmd(0x1);// Clear LCD
	lcd_cmd(0x80);// Set cursor position to top row 0x80
}


void lcd_cmd(char cmd_out)
{
	data = cmd_out; //send the cmd_out to data
	PORTC &= ~(1<<rs);//set rs = 0, data is a cmd
	PORTC &= ~(1<<rw);//rw=0, we are writing
	PORTC |= (1<<en);//en = 1, lets lcd read cmd
	_delay_ms(10);//wait for small delay 10ms
	PORTC &= ~(1<<en);//set en =0, stops reading cmd
	_delay_ms(10);///wait for small delay 10ms
}

void lcd_data(char data_out)
{
	data = data_out;//send the data_out to data
	PORTC |= (1<<rs); // rs = 1 , we are given data not cmd
	PORTC &= ~(1 << rw); //rw = 0, we are writing
	PORTC |= (1<<en); // en = 1, lets lcd read data
	_delay_ms(10);//wait for small delay 10ms
	PORTC &= ~(1 << en); //en = 0, stops lcd from reading data
	_delay_ms(10);//wait for small delay 10ms
}

//reads out each character in the string individually
void lcd_str(const char *str)
{
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		i++;
	}
}

void check()
{
	
}

#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
//definition for the wire connections
#define rs PC0
#define rw PC1
#define en PC2
#define data PORTB
//functions necessary
void lcd_init(); //to initialize lcd.
void lcd_cmd(char cmd_out); //to send command to lcd.
void lcd_data(char data_out); //to send data to lcd.
void lcd_str(const char *str); //to send string, basically stripping each character and sending.
void check1();
void check2();
void check3();
void check4();

int main()
{
	//set DDR
	DDRB |= 0XFF; //set port b as output
	DDRC |= (1<<rs)| (1<<rw) | (1<<en);
	lcd_init(); // calls init commands
	check1();
	check2();
	check3();
	check4();
	while(1)
	{}
}

//initializes the command
void lcd_init()
{
	
	lcd_cmd(0x38); // Initializing to 2 lines & 5x7 font.
	lcd_cmd(0xE);// Display on, cursor on
	lcd_cmd(0x1);// Clear LCD
	lcd_cmd(0x80);// Set cursor position to top row 0x80
}


void lcd_cmd(char cmd_out)
{
	data = cmd_out; //send the cmd_out to data
	PORTC &= ~(1<<rs);//set rs = 0, data is a cmd
	PORTC &= ~(1<<rw);//rw=0, we are writing
	PORTC |= (1<<en);//en = 1, lets lcd read cmd
	_delay_ms(10);//wait for small delay 10ms
	PORTC &= ~(1<<en);//set en =0, stops reading cmd
	_delay_ms(10);///wait for small delay 10ms
}

void lcd_data(char data_out)
{
	data = data_out;//send the data_out to data
	PORTC |= (1<<rs); // rs = 1 , we are given data not cmd
	PORTC &= ~(1 << rw); //rw = 0, we are writing
	PORTC |= (1<<en); // en = 1, lets lcd read data
	_delay_ms(10);//wait for small delay 10ms
	PORTC &= ~(1 << en); //en = 0, stops lcd from reading data
	_delay_ms(10);//wait for small delay 10ms
}

//reads out each character in the string individually
void lcd_str(const char *str)
{
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		i++;
	}
}

void check()
{
	bool checker = 0;
	PORTD = 0b00000001; // Set Row 1 to high
	_delay_ms(500); // Wait for signal to stabilize
	if((PIND & 0b11110000) == 0b00100000)
	{
		PORTD = 0b00000010; // Set Row 2 to high
		_delay_ms(500); // Wait for signal to stabilize
		if((PIND & 0b11110000) == 0b00100000)
		{
			PORTD = 0b00000100; // Set Row 3 to high
			_delay_ms(500); // Wait for signal to stabilize
			if((PIND & 0b11110000) == 0b00100000)
			{
				PORTD = 0b00001000; // Set Row 4 to high
				_delay_ms(500); // Wait for signal to stabilize
				if((PIND & 0b11110000) == 0b00100000)
				{
					_delay_ms(500); // Wait for signal to stabilize
					if((PIND & 0b11110000) == 0b10000000)
					{
						
						lcd_str("Lock Opened");
					}
				}
			}
		}
	}
	else
	{
		lcd_str("Incorrect Sequence")
	}
}