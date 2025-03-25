*** Instructions to run the filter ***
1. clone repo.
2. In stm32programmer Download "combine.bin" to address 0x8020000
3. Import project to the stm32ide.
4. Flash device (Optional: Comment out or include the OPTIMIZED define)
5. In stm32programmer at address 0x802f000 with size 0xf000 download the data as "test.bin"
6. Run "binary_to_image.py"
7. Repeat steps 2-6 if you need to rebuild and/or generate a different image.
