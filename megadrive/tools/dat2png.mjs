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

const Title1PaletteData = [
    0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x0a, 0x0a, 0x0a, 0x07, 0x0a, 0x0a, 0x0a,
    0x07, 0x0b, 0x0b, 0x0b, 0x07, 0x0e, 0x01, 0x01, 0x04, 0x09, 0x09, 0x09, 0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x09, 0x00, 0x00, 0x04, 0x0b, 0x00, 0x00, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x05, 0x05, 0x05, 0x08, 0x06,
    0x06, 0x06, 0x08, 0x08, 0x08, 0x08, 0x08,
];

const Title2PaletteData = [
    0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x06, 0x06, 0x06, 0x08, 0x0a, 0x0a, 0x0a, 0x07, 0x0a, 0x0a, 0x0a,
    0x07, 0x0b, 0x0b, 0x0b, 0x07, 0x0e, 0x01, 0x01, 0x04, 0x09, 0x09, 0x09, 0x07, 0x01, 0x03, 0x07, 0x00, 0x08, 0x08,
    0x08, 0x08, 0x09, 0x00, 0x00, 0x04, 0x0b, 0x00, 0x00, 0x0c, 0x00, 0x02, 0x0a, 0x01, 0x05, 0x05, 0x05, 0x08, 0x06,
    0x06, 0x06, 0x08, 0x08, 0x08, 0x08, 0x07,
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

    return new Uint32Array(outPalette.buffer);
};

const readDat = ({ name, palette, width, height, out }) => {
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

const tasks = [
    { name: "TITLE.DAT", palette: TitlePaletteData, width: 320, height: 200, out: "out/title.png" },
    { name: "TITLE1.DAT", palette: Title1PaletteData, width: 320, height: 200, out: "out/title1.png" },
    { name: "TITLE2.DAT", palette: Title2PaletteData, width: 320, height: 200, out: "out/title2.png" },
];

async function main() {
    for (const task of tasks) {
        readDat(task);
    }
}

main();
