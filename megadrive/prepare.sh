# copy using hardlinks
# rm -rf src/supaplex
# mkdir -p src/supaplex
cp -al ../src/* src/supaplex
echo "This folder will contain hardlinks to sources" > src/supaplex/README.txt

# remove unwanted files
rm -rf src/supaplex/3ds \
    src/supaplex/apple \
    src/supaplex/config.c \
    src/supaplex/graphics.c \
    src/supaplex/savegame.c \
    src/supaplex/null/video.c \
    src/supaplex/null/virtualKeyboard.c \
    src/supaplex/lib \
    src/supaplex/nds \
    src/supaplex/nx \
    src/supaplex/ps2 \
    src/supaplex/ps3 \
    src/supaplex/psp \
    src/supaplex/psp2 \
    src/supaplex/sdl_common \
    src/supaplex/sdl1 \
    src/supaplex/sdl2 \
    src/supaplex/wii \
    src/supaplex/wiiu