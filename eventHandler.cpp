#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <iostream>

#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */

struct joyStickEvent	{
	unsigned int time;
	short value;
	unsigned char type;
	unsigned char number;
};

bool pos = false;

int getNum(int,bool);

int main(int argc,char** argv)	{
	
	int fdj = open("/dev/input/js0", O_RDONLY);
	int fdk = open("/dev/input/event4", O_WRONLY);
 
	struct joyStickEvent in;
 	struct input_event out; 	

 	int mapping [2][12][2];

 	mapping[1][0][0] = 15;
 	mapping[1][1][0] = 29;
 	mapping[1][2][0] = 56;
 	mapping[1][3][0] = 15;
 	mapping[1][4][0] = 1;
 	mapping[1][5][0] = 62;
 	mapping[1][6][0] = 158;
 	mapping[1][7][0] = 159;
 	mapping[1][8][0] = 182;
 	mapping[1][9][0] = 116;
 	mapping[1][10][0] = 113;
 	mapping[1][11][0] = 164;

 	mapping[1][0][1] = 15;
 	mapping[1][1][1] = 29;
 	mapping[1][2][1] = 56;
 	mapping[1][3][1] = 15;
 	mapping[1][4][1] = 1;
 	mapping[1][5][1] = 62;
 	mapping[1][6][1] = 158;
 	mapping[1][7][1] = 159;
 	mapping[1][8][1] = 182;
 	mapping[1][9][1] = 116;
 	mapping[1][10][1] = 113;
 	mapping[1][11][1] = 164;
 	
 	mapping[2][0][0] = 105;
 	mapping[2][1][0] = 103;
 	mapping[2][2][0] = 115;
 	mapping[2][3][0] = 165;
 	mapping[2][4][0] = 105;
 	mapping[2][5][0] = 103;
 	
 	mapping[2][0][1] = 106;
 	mapping[2][1][1] = 108;
 	mapping[2][2][1] = 114;
 	mapping[2][3][1] = 163;
 	mapping[2][4][1] = 106;
 	mapping[2][5][1] = 108;

	while(1)	{
 	
		read(fdj,&in,sizeof(in));

		if(in.type == JS_EVENT_BUTTON || in.type == JS_EVENT_AXIS)	{

				out.type = 1;
				out.code = mapping[in.type][in.number][getNum(in.value,&pos)];
				out.value = (in.value != 0);
				write(fdk,&out,sizeof(out));

				out.type = 0;
				out.code = 0;
				out.value = 0;
				write(fdk,&out,sizeof(out));
		}
		
 	}
	return 0;
 }


int getNum(int val,bool out)	{
	
	if(val < 0)	{
		pos = false;
		return (int) pos;
	}

	else if(val > 0)	{
		pos = true;
		return (int) pos;
	}
	return (int) pos;
}
