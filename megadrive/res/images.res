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
IMAGE imgTitle images/title-224p.png BEST ALL
IMAGE imgTitle1 images/title1-224p.png BEST ALL
IMAGE imgTitle2 images/title2-224p.png BEST ALL
IMAGE fontChars8  "images/chars8.png" BEST NONE

# SPRITE
# ------
# Take an image as input and transform it into SGDK SpriteDefinition structure.
# SpriteDefinition is used to draw, animate and manage sprites, it internally contains severals TileSet, Palette and Animation structures.
#
# Syntax:
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
#
# Some informations about how SpriteDefinition is generated from the input image:
# - input image dimension should be aligned on tile (multiple of 8).
# - input image is a grid where each cell represents a single animation frame and where each row define a complete sprite animation.
# - an animation cannot contains more than 255 frames.
# - cell size (frame size) = width * height (in tile) where width and height should be < 32 (maximum = 248 pixels for both width and height).
# - a frame can be composed of several internal VDP (hardware) sprites but it stricly limited to a maximum of 16 hardware sprites.
#   If the sprite is too large to fit in 16 hardware sprites (rescomp will complain about it), then you may reduce its size or split it in 2 parts.
# - rescomp detects flipped frame to avoid redundant sprite tiles.
# - rescomp detects empty frame at end of animation row to not store empty frame data.
# - rescomp try to optimize hardware sprites and vRAM usage by detecting empty areas in sprite frames.
# - rescomp detects frame copy inside an animation to generate the according animation sequence.
# - by default collision bounds are calculated by using 75% of the original sprite frame.
#
# Tips: When the 'opt_level' is set (non empty value) then rescomp will automatically generate an image saved as <input_image>_opt.png
# representing the processed sprite cutting operation.
SPRITE sprTitleEdge images/title-edge.png 14 10 BEST 0 NONE SPRITE FAST
