CXX=gcc
CFLAGS=
ODIR=../obj
IDIR=../include
LDFLAGS=-L../lib -L/usr/lib -lallegro -lallegro_dialog -lallegro_primitives -lallegro_image
INCLUDE=-I$(IDIR) -I/usr/include/allegro5

#OBJS=$(ODIR)/megaman.o
OUT=megaman

_OBJS = commom.o moveableObject.o bullet.o player.o platform.o scenarium.o megaman.o 
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

_DEPS = commom.h moveableObject.h bullet.h player.h platform.h scenarium.h megaman.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.cpp $(DEPS)
		$(CC) -c -o $@ $< $(INCLUDE) $(CFLAGS) $(LDFLAGS)


all: megaman_rule
megaman_rule: $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(ODIR)/*.o megaman
