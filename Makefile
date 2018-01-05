#
#Makefile
#

TARGET = miniGame.exe

SRCDIR = src
RCDIR  = resource
OUTDIR = build

HEADERS = $(SRCDIR)/commonHeader.h

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OUTDIR)/%.o,$(SRCS))

ICON_RESOURCE = $(RCDIR)/windowIcon.rc
ICON_ICO = $(patsubst $(RCDIR)/%.rc,$(RCDIR)/%.ico,$(ICON_RESOURCE))
ICON_OBJS = $(patsubst $(RCDIR)/%.rc,$(OUTDIR)/%.o,$(ICON_RESOURCE))

CC = gcc
CCFLAGS = -Wall -I/usr/include/opengl
LD = gcc
LDFLAGS =
LIBS = -lglpng -lglut32 -lglu32 -lopengl32 -lm
WINDRES = windres

#実行ファイルはソースコードとアイコンデータのオブジェクトファイルに依存
$(TARGET) : $(OBJS) $(ICON_OBJS)
	$(LD) $(OBJS) $(ICON_OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

#アイコンのオブジェクトファイルはリソースファイルとアイコンデータとMakefileに依存
$(ICON_OBJS) : $(ICON_RESOUSE) $(ICON_ICO) Makefile
	$(WINDRES) -i $(ICON_RESOURCE) -o $(ICON_OBJS)

#ソースコードのオブジェクトファイル作成時はこのコマンドを用いる
$(OUTDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c -o $(@) $(<)

#ソースコードのオブジェクトファイルはヘッダーファイルとMakefileに依存
$(OBJS) : $(HEADERS) Makefile

#make cleanと入力された時にはこのコマンドを用いる
clean:
	rm -f $(OUTDIR)/*
