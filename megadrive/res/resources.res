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
IMAGE imgTitle images/title-224p.png BEST ALL
IMAGE imgTitle1 images/title1-224p.png BEST ALL
IMAGE imgTitle2 images/title2-224p.png BEST ALL
IMAGE imgMenu "images/menu-224p.png" BEST ALL
IMAGE imgKeyboard "images/keyboard.png" BEST ALL

IMAGE fontChars8 "images/chars8.png" BEST NONE

# SPRITE name img_file width height [compression [time [collision [opt_type [opt_level]]]]]
#
#     name            name of the output SpriteDefinition structure
#     img_file        path of the input image file (BMP or PNG image)
#                         See the note about image format at the beginning of the file
#     width           width of a single sprite frame in tile (should be < 32)
#     height          height of a single sprite frame in tile (should be < 32)
#     compression     compression type, accepted values:
#                        -1 / BEST / AUTO = use best compression
#                         0 / NONE        = no compression (default)
#                         1 / APLIB       = aplib library (good compression ratio but slow, don't use it for streamed sprite)
#                         2 / FAST / LZ4W = custom lz4 compression (average compression ratio but fast, recommended for streamed sprite)
#     time            display frame time in 1/60 of second (time between each animation frame)
#                        If this value is set to 0 (default) then auto animation is disabled
#     collision       collision type: CIRCLE, BOX or NONE (NONE by default)
#     opt_type        sprite cutting optimization strategy, accepted values:
#                         0 / BALANCED  = balance between used tiles and hardware sprites (default)
#                         1 / SPRITE    = reduce the number of hardware sprite (using bigger sprite) at the expense of more used tiles
#                         2 / TILE      = reduce the number of tiles at the expense of more hardware sprite (using smaller sprite)
#                         3 / NONE      = no optimization (cover the whole sprite frame)
#     opt_level       optimization level for the sprite cutting operation:
#                         0 / FAST      = fast optimisation, good enough in general (default)
#                         1 / MEDIUM    = intermediate optimisation level, provide better results than FAST but ~10 time slower
#                         2 / SLOW      = advanced optimisation level using a genetic algorithm (80000 iterations), ~20 time slower than FAST
#                         3 / MAX       = maximum optimisation level, genetic algorithm (500000 iterations), ~100 time slower than FAST
SPRITE sprTitleEdge images/title-edge.png 14 10 BEST 0 NONE BALANCED FAST
SPRITE sprCursor images/cursor.png 1 1 FAST 2 NONE BALANCED FAST
SPRITE sprKeyboardKeys images/keyboard-keys.png 2 2 FAST 0 NONE BALANCED FAST

# BIN name file [align [size_align [fill [compression [far]]]]]
#
#     name            BIN data variable name
#     file            path of the data file to convert to binary data array
#     align           memory address alignment for generated data array (default is 2)
#     size_align      size alignment for the generated data array (default is 2)
#     fill            fill value for the size alignment (default is 0)
#     compression     compression type, accepted values:
#                         0 / NONE        = no compression
#                         1 / APLIB       = aplib library (good compression ratio but slow)
#                         2 / FAST / LZ4W = custom lz4 compression (average compression ratio but fast)
#     far             'far' binary data flag to put it at the end of the ROM (useful for bank switch, default = TRUE)
# BIN binPalettes bin/PALETTES.DAT 2 2 0 NONE
BIN binLevelLst bin/LEVEL.LST 2 2 0 NONE
BIN binLevelsDat bin/LEVELS.DAT 2 2 0 NONE