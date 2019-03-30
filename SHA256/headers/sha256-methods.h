

/*			SHA METHODS 
** THESE METHODS ARE USED TO CALCULATE THE SHA ALGORITHM
*/
#define Ch(x, y, z) ((x & y) ^ (~(x) & z ))
#define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define EP0(x) (rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22))
#define EP1(x) (rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25))
#define SIG_0(x) (rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3))
#define SIG_1(x) (rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10))