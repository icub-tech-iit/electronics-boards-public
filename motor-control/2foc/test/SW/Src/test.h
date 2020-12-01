

#ifndef __TEST_H
#define __TEST_H

extern int TestReadOvercurr();
extern void TestTris(int command_get, int *command_ok, unsigned char *txlen, tCanData *txpayload, unsigned char rxlen, tCanData *rxpayload);
extern void TestPort(int command_get, int *command_ok, unsigned char *txlen, tCanData *txpayload, unsigned char rxlen, tCanData *rxpayload);

#endif

