
#foo := 123
foo += $(bar)
bar = test2

null := 
B := $(null) # before #, should be a space
A := aaa$(B)ttt

.PHONY: all
all: abc 123 890
	echo $^
	echo $<
	echo $@
	echo $?
	echo $(foo)
	echo $(bar)
	echo $(A)
	echo $(B)



