CC = gcc
CFLAGS = -Wall
SRC = $(wildcard *.[ch]) #将所有 .C 和 .h加入条件式
#SRC = $(wildcard *.[a-z]) #将所有 .a 到 .z 都加入条件式
OBJ = $(SRC:%.c=%.o)

# func 
TEST = $(subst c, o, $(SRC))
T2   = $(patsubst %.h, %.o, $(SRC))

STRIP = $(strip hello aka    world       )
FIND = $(findstring aka, hello      aka       world  )
HEADER = $(filter %.c, $(SRC))
HEADEROUT = $(filter-out %.c, $(SRC))
SRC2 = $(filter-out %-ok.c, $(SRC)) #多版main.c 去掉 main-ok.c
SRC3 = $(filter-out m%n.c, $(SRC)) #多版main.c 去掉 main-ok.c
SORT = $(sort $(STRIP))

all: $(TARGET)
	@echo $(SRC)
	@echo h $(HEADER)
	@echo h-out $(HEADEROUT)
	@echo src2 $(SRC2)
	@echo src3 $(SRC3)
	@echo $(OBJ)
	@echo $(TEST)
	@echo $(T2)
	@echo strip $(STRIP)  # ?
	@echo find  $(FIND)
	@echo $(SORT)


$(TARGET): $(OBJ)
	gcc $^ -o $@

main.o: main.c add_sub.h
add.o: add.c
sub.o: sub.c

clean:
	rm *.o
	rm main
