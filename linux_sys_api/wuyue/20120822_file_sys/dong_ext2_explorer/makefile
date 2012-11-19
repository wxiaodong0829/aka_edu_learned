src= $(wildcard *.c)
obj= $(patsubst %.c, %.o, $(src))
target= app

$(target): $(obj)
	gcc $(obj) -o $(target)
%.o: %.c
	gcc $< -o $@ -c
clean:
	rm $(target)
	rm $(obj)
.PHONY: clean	
