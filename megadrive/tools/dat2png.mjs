// @ts-check
import fs from "fs";
import Jimp from "jimp";

const SCREEN_WIDTH = 320;
const SCREEN_HEIGHT = 200;

const TitlePaletteData = [
    0x02, 0x03, 0x05, 0x00, 0x0D, 0x0A, 0x04, 0x0C, 0x02, 0x06, 0x06, 0x02, 0x03, 0x09, 0x09, 0x03,
    0x0B, 0x08, 0x03, 0x06, 0x02, 0x07, 0x07, 0x0A, 0x08, 0x06, 0x0D, 0x09, 0x06, 0x04, 0x0B, 0x01,
    0x09, 0x01, 0x00, 0x04, 0x0B, 0x01, 0x00, 0x04, 0x0D, 0x01, 0x00, 0x0C, 0x0F, 0x01, 0x00, 0x0C,
    0x0F, 0x06, 0x04, 0x0C, 0x02, 0x05, 0x06, 0x08, 0x0F, 0x0C, 0x06, 0x0E, 0x0C, 0x0C, 0x0D, 0x0E,
];

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

    // return u32 view from outPalette
    const result =  new Uint32Array(outPalette.buffer);
    console.log(outPalette.buffer);
    console.log(result.buffer);
    return result;
};

/**
 * Read file into buffer
 * @param {string} file
 */
const readDat = (file = "../../resources/TITLE.DAT") => {
    const raw = new Uint8Array(fs.readFileSync(file));

    const bytesPerRow = SCREEN_WIDTH / 2;
    const rowData = new Uint8Array(bytesPerRow);
    const screenPixels = new Uint8Array(SCREEN_WIDTH * SCREEN_HEIGHT);

    const pal = convertPaletteDataToPalette(TitlePaletteData);
    console.log('>>>', pal)

    for (let y = 0; y < SCREEN_HEIGHT; y++) {
        rowData.set(raw.slice(y * bytesPerRow, (y + 1) * bytesPerRow));
        for (let x = 0; x < SCREEN_WIDTH; x++) {
            const destPixelAddress = y * SCREEN_WIDTH + x;

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
    console.log(screenPixels);

    new Jimp(SCREEN_WIDTH, SCREEN_HEIGHT, (err, image) => {
        if (err) throw err;

        for (let y = 0; y < SCREEN_HEIGHT; y++) {
            for (let x = 0; x < SCREEN_WIDTH; x++) {
                const c = pal[screenPixels[y * SCREEN_WIDTH + x]];
                image.setPixelColor(c, x, y);
            }
        }

        image.write("test.png", (err) => {
            if (err) throw err;
        });
    });

};

async function main() {
    const buffer = readDat();
}

main();
