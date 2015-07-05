CC := gcc
CFLAGS := -Wall -O3
Libs = -lpthread
Libq = -lsqlite3
Target := server
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += main find_fd insert_online log my_strcmp my_strcpy read_msg my_sqlite server_change delete_online insert_ban find_ban delete_ban read_unlog_msg reserve_unlog_msg read_chat_msg reserve_chat_msg find_id 
AllObjs := $(addsuffix /src/*.o,$(Modules))

