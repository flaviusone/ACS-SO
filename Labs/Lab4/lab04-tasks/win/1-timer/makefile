CFLAGS = /nologo /W4 /EHsc /I../util/

all: mytimer.exe

mytimer.exe: mytimer.obj
	$(CC) $(CFLAGS) /Fe$@ $**

clean:
	del /Q /S *.obj mytimer.exe *~
