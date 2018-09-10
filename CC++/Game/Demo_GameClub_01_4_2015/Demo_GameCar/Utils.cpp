#include "Utils.h"

int SeekToNumber(char* buffer, int iStart)
{
	while (true)
	{
		if (buffer[iStart] == '-' && buffer[iStart + 1] >= '0' && buffer[iStart + 1] <= '9')
			return iStart;

		if (buffer[iStart] >= '0' && buffer[iStart] <= '9')
			return iStart;

		// End buffer
		if (buffer[iStart] == '\n')
			return -1;
		++iStart;
	}
}

int ScanNumberInt32(char* buffer, int *iNumber, int iStart)
{
	iStart = SeekToNumber(buffer, iStart);
	if (iStart == -1)
		return -1;

	int iSign = 1;
	if (buffer[iStart] == '-')
	{
		iSign = -1;
		++iStart;
	}

	*iNumber = 0;
	while (buffer[iStart] >= '0' && buffer[iStart] <= '9')
	{
		*iNumber = (*iNumber) * 10 + buffer[iStart++] - '0';
	}

	*iNumber *= iSign;

	return iStart;
}

int ScanNumberUInt32(char* buffer, unsigned int *iNumber, int iStart)
{
	int iTmp;
	int iPos = ScanNumberInt32(buffer, &iTmp, iStart);
	*iNumber = iTmp;

	return iPos;
}

int ScanNumberFloat32(char* buffer, float *iNumber, int iStart)
{
	iStart = SeekToNumber(buffer, iStart);
	if (iStart == -1)
		return -1;

	int iSign = 1;
	if (buffer[iStart] == '-')
	{
		iSign = -1;
		++iStart;
	}

	*iNumber = 0.0f;
	while (buffer[iStart] >= '0' && buffer[iStart] <= '9')
	{
		*iNumber = (*iNumber) * 10 + buffer[iStart++] - '0';
	}

	if (buffer[iStart] != '.')
		return iStart;

	float fTmp2 = 1.0f;
	++iStart;

	while (buffer[iStart] >= '0' && buffer[iStart] <= '9')
	{
		fTmp2 /= 10.0f;
		*iNumber += (buffer[iStart] - '0')*fTmp2;
		++iStart;
	}

	*iNumber *= iSign;

	return iStart;
}

int SeekToQuote(char* buffer, int iStart)
{
	while (true)
	{
		if (buffer[iStart] == '\"')
			return iStart;

		// End buffer
		if (buffer[iStart] == '\n')
			return -1;
		++iStart;
	}
}

int ScanPath(char* buffer, char* Path, int iStart)
{
	iStart = SeekToQuote(buffer, iStart);
	if (iStart == -1)
		return -1;
	iStart++;
	int i = 0;
	while (buffer[iStart] != '\n' && buffer[iStart] != '\"')
	{
		Path[i] = buffer[iStart];
		iStart++;
		i++;
	}
	Path[i] = '\0';
	return iStart;
}