/*  		ENDIAN_SWAP_UINT64
** CONVERTS 64 BIT INTEGERS TO BIG INTS
**
** SOURCE CODE: 
**  -> https://ubuntuforums.org/showthread.php?t=1190710
*/
#define ENDIAN_SWAP_UINT64(x) ( \
    (( (x) &  0x00000000000000ff) << 56) | \
    (( (x) &  0x000000000000ff00) << 40) | \
    (( (x) &  0x0000000000ff0000) << 24) | \
    (( (x) &  0x00000000ff000000) <<  8) | \
    (( (x) &  0x000000ff00000000) >>  8) | \
    (( (x) &  0x0000ff0000000000) >> 24) | \
    (( (x) &  0x00ff000000000000) >> 40) | \
    (( (x) &  0xff00000000000000) >> 56))

/* 			ENDIAN_SWAP_UINT32
** CONVERTS 32 BIT INTEGERS TO BIG INTS
**
** SOURCE CODE: 
**  -> http://www.firmcodes.com/write-c-program-convert-little-endian-big-endian-integer/
**  -> https://codereview.stackexchange.com/questions/151049/endianness-conversion-in-c
*/
#define ENDIAN_SWAP_UINT32(x)  ( \
	(((x) & 0xff000000) >> 24) | \
	(((x) & 0x00FF0000) >> 8 ) | \
	(((x) & 0x0000FF00) << 8 ) | \
	(((x) & 0x000000ff) << 24))
