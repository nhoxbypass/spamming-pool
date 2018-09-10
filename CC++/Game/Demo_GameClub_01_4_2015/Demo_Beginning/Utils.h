#ifndef _UTILS
#define _UTILS

int SeekToNumber(char* buffer, int iStart);

int ScanNumberInt32(char* buffer, int *iNumber, int iStart);

int ScanNumberUInt32(char* buffer, unsigned int *iNumber, int iStart);

int ScanNumberFloat32(char* buffer, float *iNumber, int iStart);

int SeekToQuote(char* buffer, int iStart);

int ScanPath(char* buffer, char* Path, int iStart);

#endif