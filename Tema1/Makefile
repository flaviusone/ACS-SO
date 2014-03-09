# Tema 1 SO - Makefile
# Flavius Tirnacop 331CA
 
CFLAGS = /W3 /nologo /EHsc /Za -D_CRT_SECURE_NO_DEPRECATE
build: tema1.exe
tema1.exe: tema1.obj  functii.obj
	cl /Fetema1.exe tema1.obj functii.obj
tema1.obj:       
	cl $(CFLAGS) /Fotema1.obj /c tema1.c
functii.obj:       
	cl $(CFLAGS) /Fofunctii.obj /c functii.c
clean:
	del *.obj *.exe