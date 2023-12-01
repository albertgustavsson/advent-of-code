CC= gcc
CFLAGS= -c -std=gnu11 -Wall -Wextra -Werror -Wmissing-declarations -Wmissing-prototypes -Werror-implicit-function-declaration -Wreturn-type -Wparentheses -Wunused -Wold-style-definition -Wundef -Wshadow -Wstrict-prototypes -Wswitch-default -Wunreachable-code
LDFLAGS= -std=gnu11 -Wall -Wextra -Werror -Wmissing-declarations -Wmissing-prototypes -Werror-implicit-function-declaration -Wreturn-type -Wparentheses -Wunused -Wold-style-definition -Wundef -Wshadow -Wstrict-prototypes -Wswitch-default -Wunreachable-code

DAYNUM=9

all: day$(DAYNUM)

day$(DAYNUM)p1: day$(DAYNUM).o
	$(CC) $(LDFLAGS) $^ -o day$(DAYNUM)

day$(DAYNUM).o: day$(DAYNUM).c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o ./day$(DAYNUM)
