# copy using hardlinks
rm -rf src/supaplex
mkdir -p src/supaplex
cp -al ../src/* src/supaplex
echo "This folder will contain hardlinks to sources" > src/supaplex/README.txt

# remove unneeded files
rm -rf src/supaplex/3ds \
    src/supaplex/apple \
    src/supaplex/nds \
    src/supaplex/nx \
    src/supaplex/ps3 \
    src/supaplex/ps2 \
    src/supaplex/psp \
    src/supaplex/psp2 \
    src/supaplex/sdl1 \
    src/supaplex/wii \
    src/supaplex/wiiu