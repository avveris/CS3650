hw3.out: hw3.asm
        java -jar rars1_6.jar nc hw3.asm > hw3.out

collatz.out: collatz.py
        python3 collatz.py > collatz.out

check: collatz.out hw3.out
        diff collatz.out hw3.out
clean:
        rm -f collatz.out hw3.out 

dist: clean
        dir=`basename $$PWD`; cd ..; tar czvf $$dir.tar.gz ./$$dir
        dir=`basename $$PWD`; ls -l ../$$dir.tar.gz
