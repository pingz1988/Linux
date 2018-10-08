TARGET = libsum.a
OBJ = sum.o
SRC = sum.c
INCLUDE = -I/usr/include/sys

$(TARGET):$(OBJ)
	ar -cr $(TARGET) $(OBJ)

$(OBJ):$(SRC)
	gcc -c $(INCLUDE) $(SRC) -o $(OBJ)

clean:
	rm -f *.o
	rm -f *.a
