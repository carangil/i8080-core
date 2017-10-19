#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	FILE* in=NULL;
	FILE* out=NULL;
	char* inname= NULL;
	char* outname= NULL;
	char* varname= NULL;
	int c;
	int cnt=0;
	int first = 1;
        int total=0;
        int start=0;
        int pos=0;

	if (argc <4)
       	{
		printf("Usage: ./%s input.bin output.c varname\n", argv[0]);
		exit(1);
	}

	inname = argv[1]; 
	outname = argv[2]; 
	varname = argv[3]; 
        if (argc >=5)
                start= strtol( argv[4], NULL, 16);
        
        if (argc >=6)
                total = strtol( argv[5], NULL, 16);
        
        printf(" Start at 0x%x and make array size 0x%x\n", start, total);
        
        
	
	in = fopen(inname, "rb");

	if (in)
		out = fopen(outname, "wb");

	if (in && out) 
	{

		fprintf(out, "unsigned char %s [] = \n{", varname);
		for(;;)
		{
                        
                        
                        
                        if (pos < start ) {
                                c=0x00;
                        }
                        
                        
                        else {
                                c = fgetc(in);
                                
                                if (feof(in)) {
                                        if (total)
                                                c=0x00;
                                        else
                                                break;
                                }
                        }
                        
                        if ( (total) && (pos >=total) ) {
                         
                                if (!feof(in))
                                        printf(" Warning: input file longer than requested memory image\n");
                                break;
                                
                        }
                        
			pos++;

			if (!first)
				fprintf(out, ",");

			first = 0;
		
			if ( (cnt & 15 ) == 0 )
				fprintf(out, "\n\t");

			fprintf(out, "0x%02x", c);

			cnt++;


		}

		fprintf(out, "\n};\n");


	}

	if (in)
		fclose(in);

	if (out)
		fclose(out);


	return 0;

}
