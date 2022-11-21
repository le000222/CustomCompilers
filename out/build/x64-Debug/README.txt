123abc();
1 == 2;
<>
0.123
!
<! BOA Example 4:
  Testing numbers (ex: factorial) !>
main() {
    data {
        int i, n, Vol_num0;
    }
    code() {
        f=1;
        i=1;
	// Prints a message to the user
        print('Write a number:');
        input(n);
        while (i<n) do {
            f = f * i;
            i = i + 1;
        };
        print('Factorial:');
        print(f);
    }
}

