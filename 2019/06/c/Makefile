CC= gcc
CFLAGS= -c -std=gnu11 -Wall -Wextra -Werror -Wmissing-declarations -Wmissing-prototypes -Werror-implicit-function-declaration -Wreturn-type -Wparentheses -Wunused -Wold-style-definition -Wundef -Wshadow -Wstrict-prototypes -Wswitch-default -Wunreachable-code
LDFLAGS= -std=gnu11 -Wall -Wextra -Werror -Wmissing-declarations -Wmissing-prototypes -Werror-implicit-function-declaration -Wreturn-type -Wparentheses -Wunused -Wold-style-definition -Wundef -Wshadow -Wstrict-prototypes -Wswitch-default -Wunreachable-code

DAYNUM=6

all: day$(DAYNUM)p1 day$(DAYNUM)p2

day$(DAYNUM)p1: day$(DAYNUM)p1.o
	$(CC) $(LDFLAGS) $^ -o day$(DAYNUM)p1
	
day$(DAYNUM)p2: day$(DAYNUM)p2.o
	$(CC) $(LDFLAGS) $^ -o day$(DAYNUM)p2

day$(DAYNUM)p1.o: day$(DAYNUM)p1.c
	$(CC) $(CFLAGS) $<

day$(DAYNUM)p2.o: day$(DAYNUM)p2.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o ./day$(DAYNUM)p1 ./day$(DAYNUM)p2
