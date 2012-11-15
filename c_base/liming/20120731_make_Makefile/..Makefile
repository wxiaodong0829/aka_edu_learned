all		:
	#echo "--> compiling c files ..."
	@echo "--> compiling c files ..."  # 符号 @ ,使此句不显示出来，但仍执行
	echo "--> compiling c files ..."
	@gcc -c main.c
	@ls -l
	#ls								#显示，但不执行，因为已经注释掉了
#	ls								#不显示，不执行, 因为已经注释掉了
	gcc -c main.c
	gcc -c add.c
	gcc -c sub.c
	gcc main.o add.o sub.o -o main

clean	:
	echo "--> deleting files..."
	rm *.o
	rm main
