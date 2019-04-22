# define directory
SQLITE_UPDATE_DIR = ./Src/update/sqlite_update
NDS_UPDATE_DIR = ./Src/update/nds_update
BASE_LIB_DIR = ./Src/baselib
THRDPARTY_LIB_DIR = ./Lib/ubuntu-64
NDS_SQLITE3_H = ./include

# source object target
SOURCE = 
OBJS   = NDSUpdate.o sqlite3rbu.o sqlite3.o
TARGET = libndsupdate.so

# compile and lib parameter
CC      = gcc
LIBS    = libnds_sqlite3.a
LDFLAGS = -L$(SQLITE3_A_DIR)
DEFINES =
INCLUDE = -I$(BASE_LIB_DIR) -I/usr/include/sys -I$(NDS_SQLITE3_H) -I$(NDS_UPDATE_DIR)
CFLAGS  = -Wall -g -O -fPIC
CXXFLAGS= 

# link
$(TARGET):$(OBJS)
	#$(CC) -o $(TARGET) $(OBJS) -shared -fPIC -g -lsqlite3 -L$(THRDPARTY_LIB_DIR) -Bstatic -lnds_sqlite3 -Bstatic -L$(THRDPARTY_LIB_DIR) -Bstatic -lzstd
	#$(CC) -o $(TARGET) $(OBJS) -shared -fPIC -g -Wl,--whole-archive -L$(THRDPARTY_LIB_DIR) -lnds_sqlite3 -Wl,--no-whole-archive -lsqlite3 -Wl,--whole-archive -L$(THRDPARTY_LIB_DIR) -lzstd
	$(CC) -o $(TARGET) $(OBJS) -shared -fPIC -g -L$(THRDPARTY_LIB_DIR) -lzstd -lpthread

# compile
$(OBJS):$(SOURCE)
	$(CC) -c $(CFLAGS) $(LDFLAGS)/$(LIBS) $(INCLUDE) $(SQLITE_UPDATE_DIR)/sqlite3rbu.c -o sqlite3rbu.o
	$(CC) -c $(CFLAGS) $(INCLUDE) $(BASE_LIB_DIR)/sqlite3.c -o sqlite3.o
	$(CC) -c $(CFLAGS) $(INCLUDE) $(NDS_UPDATE_DIR)/NDSUpdate.c -o NDSUpdate.o

# clean
clean:
	rm -fr *.o
	rm -fr $(TARGET)
