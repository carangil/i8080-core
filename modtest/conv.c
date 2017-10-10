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
	int cnt;
	int first = 1;

	if (argc !=4)
       	{
		printf("Usage: ./%s input.bin output.c varname\n", argv[0]);
		exit(1);
	}

	inname = argv[1]; 
	outname = argv[2]; 
	varname = argv[3]; 
	
	in = fopen(inname, "rb");

	if (in)
		out = fopen(outname, "wb");

	if (in && out) 
	{

		fprintf(out, "unsigned char %s [] = \n{", varname);
		for(;;)
		{
			c = fgetc(in);
			if (feof(in))
				break;

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
