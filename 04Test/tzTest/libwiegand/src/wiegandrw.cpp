#include "wiegandrw.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory.h>



using namespace std;


wiegandrw::wiegandrw(){
	memset(outwieganddata,0,26);
    wiegandint();
}
wiegandrw::~wiegandrw(){
    close(fd);
}
int wiegandrw::wiegandint(void){
    fd = open("/dev/wiegand",O_RDWR);
    if(fd == -1){
        cout << "open /dev/wiegand failed!" << endl;
        return -1;
    }
	return 0;
}
int wiegandrw::wiegandread(int &hid,int &pid){
    int res = 0;
    int i = 0;
    char wiegandreaddata[26];
    if(fd != -1){
        res = read(fd,wiegandreaddata,26);
        for(i = 1;i < 9;i++){
            hid |= ((int)wiegandreaddata[i] << (8-i));
        }
        for(i = 9;i < 25;i++){
            pid |= ((int)wiegandreaddata[i] << (16 - (i -8)));
        }
		printf("have read the data,hid = %d,pid = %d",hid,pid);
    }
    else{
        cout << "the fd is invalid" << endl;
        return -1;
    }
	return 0;
}
void wiegandrw::convert_to_wiegand(int hid,int pid){
    if((hid > 0)&&(hid <=0xff)&&(pid > 0)&&(pid <=0xffff)){
        int i = 0;
        for(i = 1;i < 9;i++){
            outwieganddata[i] = (hid >> (8-i)) & 0x01;
        }
        for(i = 9; i < 25;i++){
            outwieganddata[i] = (pid >> (16 - (i -8))) & 0x01;
        }
        bool w0 = 0;
        for(i = 1;i < 13;i++){
            if(outwieganddata[i]){
                w0 = ~w0;
            }
        }
        outwieganddata[0] = w0;
        w0 = 1;
        for(i = 13;i < 25;i++){
            if(outwieganddata[i]){
                w0 = ~w0;
            }
        }
        outwieganddata[25] = w0;
    }else{
        printf("the data is error\n");
        return;
    }
}
int is_dec_asc(char num){
    return ((num >= 0x30)&&(num <= 0x39));
}
int is_hex_asc(char num){
    return (((num >= 0x30)&&(num <= 0x39))||((num >= 0x41)&&(num <= 0x46))||((num >= 0x61)&&(num <= 0x66)));
}
int wiegandrw::wiegangwrite(const string &inputstr,const int &mode){
    int num;
    int hid;
    int pid;
    int i = 0;
    const char *p = inputstr.data();
    const char *q = inputstr.data();
    switch (mode) {
    case MODE_DECIMAL:{                         // the hid is 3 decimal datas,and the pid is 5 decimal datas, then the length is 8.
        if(inputstr.length() != 8){
            printf("the data format is wrong!\n");
            return FORMAT_WRONG;
        }else{
            for(i = 0;i < 8;i++){
                if(!is_dec_asc(q[i])){
                    printf("the data format is wrong\n");
                }
            }
        }
        printf("%s\n",p);
        hid = (*p++-0x30) * 100 + (*p++-0x30) * 10 + (*p++-0x30);
        pid = (*p++-0x30) * 10000 + (*p++-0x30) * 1000 + (*p++-0x30) * 100 + (*p++-0x30) *10 + (*p++-0x30);
        break;
    }
    case MODE_HEX:{
        if(inputstr.length() != 6){
            printf("the hex data format is wrong\n");
            return FORMAT_WRONG;
        }else{
            for(i = 0;i < 6;i++){
                if(!is_hex_asc(q[i])){
                    printf("the num you enter is wrong \n");
                    return FORMAT_WRONG;
                }
            }
        }
        hid = (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*1) + \
                (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*0);
        pid = (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87)))  << 4*3) + \
                (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*2) +\
                (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*1) +\
                (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*0);
        break;
    }
    case MODE_HEX_DEC:{
        if(inputstr.length() != 7){
            printf("the hex data format is wrong\n");
            return FORMAT_WRONG;
        }else{
            for(i = 0;i < 2;i++){
                if(!is_hex_asc(q[i])){
                    printf("the num you enter is wrong \n");
                    return FORMAT_WRONG;
                }
            }
            for(i = 2;i < 7;i++){
                if(!is_dec_asc(q[i])){
                    printf("the data format is wrong\n");
                }
            }
        }
        hid = (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*1) + \
                (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*0);
        pid = (*p++-0x30) * 10000 + (*p++-0x30) * 1000 + (*p++-0x30) * 100 + (*p++-0x30) *10 + (*p++-0x30);
        break;
    }
    case MODE_DEC_HEX:{
        if(inputstr.length() != 7){
            printf("the hex data format is wrong\n");
            return FORMAT_WRONG;
        }else{
            for(i = 0;i < 3;i++){
                if(!is_dec_asc(q[i])){
                    printf("the data format is wrong\n");
                }
            }
            for(i = 3;i < 7;i++){
                if(!is_hex_asc(q[i])){
                    printf("the num you enter is wrong \n");
                    return FORMAT_WRONG;
                }
            }
        }
        hid = (*p++-0x30) * 100 + (*p++-0x30) * 10 + (*p++-0x30);
        pid = (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87)))  << 4*3) + \
                (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*2) +\
                (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*1) +\
                (((*p>= 0x30)&&(*p <= 0x39)?(*p++-0x30):((*p >= 0x41)&&(*p <= 0x46) ? (*p++ - 55):(*p++ - 87))) << 4*0);
        break;
    }
    default:
        return MODE_WRONG;
        break;
    }
    if((hid > 0xff)||(pid > 0xffff)){
        printf("the data is to large\n");
        return FORMAT_WRONG;
    }
    convert_to_wiegand(hid,pid);
    if(fd == -1)
    {
        printf("creat file wrong!");
        return FORMAT_WRONG;
    }
        printf("beginwrite\n");
        num = write(fd,outwieganddata,26);
        printf("the num is %d\n",num);
	return 0;
}
