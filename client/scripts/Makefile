CC := gcc
CFLAGS := -Wall -O3
Libs = -lpthread
Target := client
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += main menu my_strcmp my_strcpy function reg log out screen chat_room_func read_message my_face change admin_screen admin_room_func my_time 
AllObjs := $(addsuffix /src/*.o,$(Modules))

