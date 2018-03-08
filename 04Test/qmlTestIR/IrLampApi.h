#ifndef IKIRLAMPAPI_H_
#define IKIRLAMPAPI_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define MAX_PATH                260

char G_IrLamp_Version[MAX_PATH] = "IKIRLAMPAPI.V1.0.0.20171126";

#define   PATH_DEVICE_NAME		"/dev/ir-lamp"

#define IR_LAMP_MAGIC  0x58

#define IR_LAMP_SET_LOW_NS_CMD						(_IO(IR_LAMP_MAGIC, 0x1))//0x01
#define IR_LAMP_GET_LOW_NS_CMD						(_IO(IR_LAMP_MAGIC, 0x2))//0x02
#define IR_LAMP_SET_HIGHR_NS_CMD					(_IO(IR_LAMP_MAGIC, 0x3))//0x04
#define IR_LAMP_GET_HIGHR_NS_CMD					(_IO(IR_LAMP_MAGIC, 0x4))//0x08
#define IR_LAMP_READ_REG_CMD						(_IO(IR_LAMP_MAGIC, 0x5))//0x10
#define IR_LAMP_WRITE_REG_CMD					    	(_IO(IR_LAMP_MAGIC, 0x6))//0x11
#define IR_LAMP_ENABLE_CMD						(_IO(IR_LAMP_MAGIC, 0x7))//0x12
#define IR_LAMP_DISABLE_CMD						(_IO(IR_LAMP_MAGIC, 0x8))//0x14
#define IR_LAMP_GET_LOW_HIGHR_NS_CMD					(_IO(IR_LAMP_MAGIC, 0x9))
#define IR_LAMP_GET_IR_STATE_CMD					(_IO(IR_LAMP_MAGIC, 0xa))

typedef struct
{
	unsigned int low_ns;
	unsigned int hight_ns;
	unsigned short reg;
        unsigned char val;
	unsigned char ir_state;
}ir_lamp_ctl_t;

int IKIRLAMP_OpenIrLamp(void);
int IKIRLAMP_CloseIrLamp(void);
int IKIRLAMP_EnableIrLamp(void);
int IKIRLAMP_DisableIrLamp(void);
int IKIRLAMP_GetIrLampState(unsigned char *val);
int IKIRLAMP_Setlowns(unsigned int low);
int IKIRLAMP_Sethightns(unsigned int hight);
int IKIRLAMP_Getlowhightns(unsigned int *low,unsigned int *hight);
int IKIRLAMP_ReadReg(unsigned short reg,unsigned char *val);
int IKIRLAMP_WriteReg(unsigned short reg,unsigned char val);
int IKIRLAMP_GetVersion(char *version);

#ifdef __cplusplus
}
#endif

#endif





