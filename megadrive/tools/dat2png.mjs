// @ts-check
import fs from "fs";
import Jimp from "jimp";
import path from "path";

const TitlePaletteData = [
    0x02, 0x03, 0x05, 0x00, 0x0d, 0x0a, 0x04, 0x0c, 0x02, 0x06, 0x06, 0x02, 0x03, 0x09, 0x09, 0x03, 0x0b, 0x08, 0x03,
    0x06, 0x02, 0x07, 0x07, 0x0a, 0x08, 0x06, 0x0d, 0x09, 0x06, 0x04, 0x0b, 0x01, 0x09, 0x01, 0x00, 0x04, 0x0b, 0x01,
    0x00, 0x04, 0x0d, 0x01, 0x00, 0x0c, 0x0f, 0x01, 0x00, 0x0c, 0x0f, 0x06, 0x04, 0x0c, 0x02, 0x05, 0x06, 0x08, 0x0f,
    0x0c, 0x06, 0x0e, 0x0c, 0x0c, 0x0d, 0x0e,
];

const title1PaletteData = [
    0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x0a, 0x0a, 0x0a, 0x07, 0x0a, 0x0a, 0x0a,
    0x07, 0x0b, 0x0b, 0x0b, 0x07, 0x0e, 0x01, 0x01, 0x04, 0x09, 0x09, 0x09, 0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x09, 0x00, 0x00, 0x04, 0x0b, 0x00, 0x00, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x05, 0x05, 0x05, 0x08, 0x06,
    0x06, 0x06, 0x08, 0x08, 0x08, 0x08, 0x08,
];

const title2PaletteData = [
    0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x06, 0x06, 0x06, 0x08, 0x0a, 0x0a, 0x0a, 0x07, 0x0a, 0x0a, 0x0a,
    0x07, 0x0b, 0x0b, 0x0b, 0x07, 0x0e, 0x01, 0x01, 0x04, 0x09, 0x09, 0x09, 0x07, 0x01, 0x03, 0x07, 0x00, 0x08, 0x08,
    0x08, 0x08, 0x09, 0x00, 0x00, 0x04, 0x0b, 0x00, 0x00, 0x0c, 0x00, 0x02, 0x0a, 0x01, 0x05, 0x05, 0x05, 0x08, 0x06,
    0x06, 0x06, 0x08, 0x08, 0x08, 0x08, 0x07,
];

const pal0 = new Uint8Array(64);
const pal1 = new Uint8Array(64);
const pal2 = new Uint8Array(64);
const pal3 = new Uint8Array(64);

const convertPaletteDataToPalette = (paletteData) => {
    const outPalette = new Uint8Array(16 * 4);
    const kExponent = 4;

    for (let i = 0; i < 16; ++i) {
        outPalette[i * 4 + 3] = paletteData[i * 4 + 0] << kExponent; // r
        outPalette[i * 4 + 2] = paletteData[i * 4 + 1] << kExponent; // g
        outPalette[i * 4 + 1] = paletteData[i * 4 + 2] << kExponent; // b
        outPalette[i * 4 + 0] = 255;
        //outPalette[i * 4 + 3] = paletteData[i * 4 + 3] << kExponent; // intensity, for now
    }

    return new Uint32Array(outPalette.buffer);
};

const readPalettes = () => {
    const palettes = new Uint8Array(fs.readFileSync("../../resources/PALETTES.DAT"));
    pal0.set(palettes.slice(0, 64));
    pal1.set(palettes.slice(64, 128));
    pal2.set(palettes.slice(128, 192));
    pal3.set(palettes.slice(192, 256));
};

const readBitmap = ({ name, palette, width, height, out }) => {
    const raw = new Uint8Array(fs.readFileSync(path.join("../../resources", name)));

    const bytesPerRow = width / 2;
    const rowData = new Uint8Array(bytesPerRow);
    const screenPixels = new Uint8Array(width * height);

    const pal = convertPaletteDataToPalette(palette);

    for (let y = 0; y < height; y++) {
        rowData.set(raw.slice(y * bytesPerRow, (y + 1) * bytesPerRow));
        for (let x = 0; x < width; x++) {
            const destPixelAddress = y * width + x;

            const sourcePixelAddress = Math.floor(x / 8);
            const sourcePixelBitPosition = 7 - (x % 8);

            const b = (rowData[sourcePixelAddress + 0] >> sourcePixelBitPosition) & 0x1;
            const g = (rowData[sourcePixelAddress + 40] >> sourcePixelBitPosition) & 0x1;
            const r = (rowData[sourcePixelAddress + 80] >> sourcePixelBitPosition) & 0x1;
            const i = (rowData[sourcePixelAddress + 120] >> sourcePixelBitPosition) & 0x1;

            const finalColor = (b << 0) | (g << 1) | (r << 2) | (i << 3);

            // Copy directly to the screen too
            screenPixels[destPixelAddress] = finalColor;
        }
    }

    new Jimp(width, height, (err, image) => {
        if (err) throw err;

        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                const c = pal[screenPixels[y * width + x]];
                image.setPixelColor(c, x, y);
            }
        }

        image.write(out, (err) => {
            if (err) throw err;
        });
    });
};

const readFont = ({ name, charHeight, charWidth, out }) => {
    const tileSize = 8;
    const data = fs.readFileSync(path.join("../../resources", name));
    const numberOfCharactersInBitmapFont = 64;
    const imageWidth = tileSize * numberOfCharactersInBitmapFont;

    new Jimp(imageWidth, tileSize, (err, image) => {
        image.opaque();
        if (err) throw err;
        for (let i = 0; i < numberOfCharactersInBitmapFont; ++i) {
            for (let w = 0; w < charWidth; ++w) {
                for (let h = 0; h < charHeight; ++h) {
                    const row = data[i + h * numberOfCharactersInBitmapFont];
                    const pixel = (row >> (7 - w)) & 0x1;

                    image.setPixelColor(pixel ? 0xffffffff : 0x000000ff, i * tileSize + w + (tileSize - charWidth), h);
                }
            }
        }
        image.write(out, (err) => {
            if (err) throw err;
        });
    });
};

const bitmaps = [
    { name: "TITLE.DAT", palette: TitlePaletteData, width: 320, height: 200, out: "out/title.png" },
    { name: "TITLE1.DAT", palette: title1PaletteData, width: 320, height: 200, out: "out/title1.png" },
    { name: "TITLE2.DAT", palette: title2PaletteData, width: 320, height: 200, out: "out/title2.png" },
    { name: "MOVING.DAT", palette: pal1, width: 320, height: 462, out: "out/moving.png" },
    { name: "MENU.DAT", palette: pal1, width: 320, height: 200, out: "out/menu.png" },
];

const fonts = [
    { name: "CHARS8.DAT", charHeight: 8, charWidth: 8, out: "out/chars8.png" },
    { name: "CHARS6.DAT", charHeight: 7, charWidth: 6, out: "out/chars6.png" },
];

async function main() {
    readPalettes();
    for (const params of bitmaps) {
        readBitmap(params);
    }
    for (const params of fonts) {
        readFont(params);
    }
}

main();
