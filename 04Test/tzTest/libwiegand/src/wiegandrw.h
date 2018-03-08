#ifndef WIEGANGRW_H
#define WIEGANGRW_H
#include <string>
using namespace std;


// the wrong code
#define FORMAT_WRONG -1   //the data string's farmat is wrong
#define MODE_WRONG -2       //the mode is not contained by the current formats



//the mode code
#define MODE_DECIMAL 1      //8 decimal datas for the wiegand data and the first 3 datas are for the hid ,and the largest number is 255, the last 5 datas are for the pid ,and the largest number is 65536
#define MODE_HEX 2              //6 hex datas for the wiegand data and the first 2 datas are for the hid ,and the largest number is 0xff, the last 4 datas are for the pid ,and the largest number is 0xffff
#define MODE_HEX_DEC 3      //2 hex datas and 5 dec datas  for the wiegand data and the first 2 datas are for the hid ,and the largest number is 0xff, the last 5 datas are for the pid ,and the largest number is 65535
#define MODE_DEC_HEX 4      //3 dec datas and 4 hex datas  for the wiegand data and the first 3 datas are for the hid ,and the largest number is 255, the last 4 datas are for the pid ,and the largest number is 0xffff




class wiegandrw{
	public:
		char outwieganddata[26];
		int fd;
		wiegandrw();
		~wiegandrw();
		int wiegandint(void);
		int wiegandread(int &hid,int &pid);
		int wiegangwrite(const string &inputstr,const int &mode);
        void convert_to_wiegand(int hid,int pid);
};



















#endif


