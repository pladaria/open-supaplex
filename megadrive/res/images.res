# IMAGE
# -----
# Take an image as input and transform it into SGDK Image structure.
# Image is used to directly draw image in background plane, it internally contains a Palette, TileSet and TileMap structure.
# IMAGE resource isn't meant to be used to store large background level (eat too much space), use MAP resource for that.
#
# Syntax:
# IMAGE name img_file [compression [map_opt [map_base]]]
#
#     name            name of the output Image structure
#     img_file        path of the input image file (BMP or PNG image)
#                         See the note about image format at the beginning of the file
#     compression     compression type (use unpackImage(..) to unpack), accepted values:
#                        -1 / BEST / AUTO = use best compression
#                         0 / NONE        = no compression (default)
#                         1 / APLIB       = aplib library (good compression ratio but slow)
#                         2 / FAST / LZ4W = custom lz4 compression (average compression ratio but fast)
#     map_opt         define the tilemap optimisation level, accepted values:
#                         0 / NONE        = no optimisation (each tile is unique)
#                         1 / ALL         = find duplicated and flipped tile (default)
#                         2 / DUPLICATE   = find duplicated tile only
#     map_base        define the base tilemap value, useful to set a default priority, palette and base tile index offset.
#                     Using a base tile index offset (static tile allocation) allow to use the faster VDP_xxxTileMapxxx(..) functions.
#
# Tips:
# When using a 8bpp indexed image as input you can use the extra bits of palette to provide extra information for the TILEMAP data but you have to
# ensure that all pixels from a same tile (block of 8x8 pixels) use the same value otherwise rescomp will generate an error.
#     bit 4-5: palette index (0-3) so it allows to use the 4 available palettes to draw the tilemap / MAP.
#     bit 6: not used (ignored)
#     bit 7: priority information (0=LOW 1=HIGH)
#
IMAGE imgTitle images/title.png BEST ALL
