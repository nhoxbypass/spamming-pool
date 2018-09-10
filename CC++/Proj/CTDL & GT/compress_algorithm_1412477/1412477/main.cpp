// huffman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lib\huffman.h"


int get_file_size(FILE *fp);

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *source_file, *dest_file;
        unsigned char *sour, *dest;
        int usize, csize;

        if (argc != 4) {
                wprintf(L" bad arguments.\n");
                wprintf(L"  huffman.exe e sourfile destfile\n");
                wprintf(L"  huffman.exe d sourfile destfile\n");
                exit(1);
        } else if ((source_file = _wfopen(argv[2], L"rb")) == NULL) {
                wprintf(L"bad file %s.\n", argv[2]);
                exit(1);
        } else if ((dest_file = _wfopen(argv[3], L"wb")) == NULL) {
                wprintf(L"bad file %s.\n", argv[3]);
                exit(1);
        } else {
                                
                Huffman huffman;

                if (!wcscmp(argv[1], L"e")) 
                {                        
                        usize = get_file_size(source_file);
                        
                        sour = new unsigned char[usize];
                        dest = new unsigned char[usize];
                        usize = (int)fread(sour, 1, usize, source_file);

                        huffman.encode(dest, csize, sour, usize);

                        fwrite(dest, 1, csize, dest_file);
                        wprintf(L" cmpression ration: %.2f\n", (float)usize / (float)csize);
                }
                else if (!wcscmp(argv[1], L"d")) 
                {                        
                        csize = get_file_size(source_file);

                        sour = new unsigned char[csize];
                        csize = fread(sour, 1, csize, source_file);

                        dest = new unsigned char[huffman.get_uncompressed_size(sour)];

                        huffman.decode(dest, usize, sour);                                        

                        fwrite(dest, 1, usize, dest_file);
                }
                else
                {
                        wprintf(L"bad argument %s.\n", argv[4]);
                        exit(1);
                }                

                fclose(source_file);
                fclose(dest_file);
        }        

        return 0;
}

int get_file_size(FILE *fp)
{
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        return size;
}

