# === Build config (MSYS2 UCRT64) ===========================================
CC       := gcc
BINDIR   := bin
OBJDIR   := build

# Tenta usar pkg-config para SDL2; se não tiver, usa paths padrão do UCRT64
PKG_CFLAGS := $(shell pkg-config --cflags sdl2 2>/dev/null)
PKG_LIBS   := $(shell pkg-config --libs   sdl2 2>/dev/null)
ifeq ($(strip $(PKG_CFLAGS)),)
  PKG_CFLAGS := -I/ucrt64/include/SDL2
  PKG_LIBS   := -L/ucrt64/lib -lSDL2
endif

CFLAGS   := -O2 -Wall -Isrc -Isrc/libs -DSDL_MAIN_HANDLED $(PKG_CFLAGS)
LDFLAGS  := -lraylib -lopengl32 -lgdi32 -lwinmm $(PKG_LIBS)

# === Sources/Objects =======================================================
SRCS := $(wildcard src/*.c) $(wildcard src/libs/*.c)
OBJS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

TARGET := $(BINDIR)/jogo.exe

# === Targets ===============================================================
.PHONY: all run clean rebuild

all: $(TARGET)

run: $(TARGET)
	@echo ">> Running from project root so assets/ are found..."
	./$(TARGET)

rebuild: clean all

clean:
	@echo ">> Cleaning build artifacts"
	@if [ -d $(OBJDIR) ]; then rm -rf $(OBJDIR); fi
	@if [ -d $(BINDIR) ]; then rm -f  $(TARGET); fi

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile objects (src/*.c)
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)
