/* 			ROTL_n(x) 
** SHIFT N POSITIONS TO THE LEFT
** AND 32-n POSITIONS TO THE RIGHT
*/
#define rotl(x, n) ((x << n) | (x >> (32 - n)))

/* 			ROTR_n(x) 
** SHIFT N POSITIONS TO THE RIGHT
** AND 32-n POSITIONS TO THE LEFT
*/
#define rotr(x, n) ((x >> n) | (x << (32 - n)))

/*			SHR_n(x) 
** SHIFT N POSITIONS TO THE LEFT
*/
#define shr(x, n) (x >> n)
