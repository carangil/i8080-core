
COCOINC=../coco-programming/cmoc/cmoc-0.1.40/src/support 

pc:
	gcc -o pcmain -g pcmain.c

pc100:
	gcc -DSTART0100 -o pcmain -g pcmain.c

conv:
	gcc -o conv conv.c

8080pre: conv
	./conv tests/8080PRE.COM prog8080.c memory 100 800

test: conv
	./conv tests/TEST.COM prog8080.c memory 100 1000

8080ex1: conv
	./conv tests/8080EX1.COM prog8080.c memory 100 2000


coco100:
	cmoc -I$(COCOINC) --a09=a09   --limit=7800 -DSTART0100  cocomain.c 

coco:
	cmoc -I$(COCOINC) --a09=a09   --limit=7800 cocomain.c


4kbas32:
	wget -O 4kbas32 https://github.com/companje/Altair8800/raw/master/data/4kbas32.bin

altbas: 4kbas32 conv
	./conv 4kbas32 prog8080.c memory 0 1000

