# Secure Hash Algorithm V2

This is a program that calculates the Secure Hash Algorithm Version 2 (SHA-256 to be specific) of a text file input. 
The users can use the already provided test files from the "**test**" folder or use a text file of their own by copying it onto the "**test**" folder. </br>
The program outputs the content from the file as long as the file is not empty - as there is nothing to output - and doesn't have a size bigger than 5 MB. If a file too big is outputted then the Secure Hash Algorithm will end up running slower than intended.

***

## [About The SHA-256](https://www.google.ie/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=2ahUKEwiY4O2Vpa3hAhXhQxUIHRNRCTgQFjAAegQIAxAC&url=https%3A%2F%2Fwww.researchgate.net%2Ffile.PostFileLoader.html%3Fid%3D534b393ad3df3e04508b45ad%26assetKey%3DAS%253A273514844622849%25401442222429260&usg=AOvVaw1TvK13udFN1J1ZwmfGiRWs)
This is a cryptographic hash function in which the output has a length of 256 bits. </br>
Key properties:
1. It's a one way function. You can only get the output from the input but you cannot get the input from the output.
2. The same input will always have the same output.

***

## [Steps](https://en.wikipedia.org/wiki/SHA-2)
1. Initialize hash values: </br>
The first step is to initialize the first 32 bits of the fractional part - **H[8]** - into 8 variables or primes of 4 bits each.

2. Initialize array of round constants: </br>
The 2nd step is to initialize the 64 binary words - **K[64]** - into characterised by the first 32 bits of the fractional parts of the cube roots of the first 64 prime numbers. In other words, the cube roots of the first 64 prime numbers is found as well as the fractional parts of those values. From those fractional parts, the first 32 bits are used for the 64 binary words.

3. Pre-processing (Padding): </br>
The original message starts with a length of **L** bits. A single 1 bit is added at the end followed by a **K** number of *'0'* bits in which K is the *smallest positive integer* such that **L + 1 + K = 448 mod 512**. Finally, add **L** at the end of the message, the original bits with which we started, represented by exactly 64 bits.

4. Process the message in successive 512-bit chunks: </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Break the message into 512-bit blocks and for each blocks create a create 64 words - **W[64]** - of 32 bits each as follows:*
* ***first 16*** - split M in 32 bit blocks
* ***remaining 48*** - obtained with the formula found on the [Archived NIST Technical Series Publication](https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977) in **Section 6.2.2, Step 1**

5. Working variables: </br>
Initialize the working variables to the current hash value as per **[Section 6.2.2, Step 2](https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977)**

6. Compression function: </br>
Do 64 rounds consisting of the initializations in **[Section 6.2.2, Step 3](https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977)**

7. Current hash value: </br>
Add the compressed chunk to the current hash value as per **[Section 6.2.2, Step 4](https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977)**

9. Produce the final hash value (big-endian): </br>
Implement the cryptographic hash function just described by converting the little endians to big endians to allow bigger values to be outputted.

***

## Run
First and foremost, you will need to install [the GCC Compiler](http://www.codebind.com/cprogramming/install-mingw-windows-10-gcc/) (you might need to restart your computer after the installation is completed and [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) (if not already installed).

1. **Clone Repo**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Open your terminal/cmd in the folder you wish to download the repository and execute the following </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```> git clone https://github.com/cristina1997/ElizaChatbot```

2. **Command Prompt**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Navigate into the folder you decided to download the repository using the terminal/cmd </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```> cd FolderLocation```

3. **Compile**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Now compile the code using the following command </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```> gcc -o <executable-name> <file-name.c>``` 

4. **Run**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Now, run the code

#### On Windows (gcc needs to be installed)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```> <executable-name>test<text-file-name.txt>``` </br>

#### On Google Cloud Linux Instance
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;First make sure the file content in the file you wish to run does not contain a new line at the end of the file </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```echo -n <file-content> > test/<file-name.txt>```</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Then you can run the file as follows: </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```> ./<executable-name>test<file-name.txt>``` </br>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;If there is a file that wish to test yourself, you can copy the file in the **test-text-files** folder and then use the above code to execute it

***

## Output for the provided files
![alt text](https://github.com/cristina1997/Secure-Hash-Algorithm/blob/master/SHA256/images/sha256-outputs.PNG)
