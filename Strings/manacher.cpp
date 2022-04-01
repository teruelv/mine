int rad[2 * MAX], n;
char s[MAX];
 
void manacher() { /// i%2!=0 par, i%2==0 impar
    int i, j, k; /// i -> 2*i o 2*i+1
    for(i = 0, j = 0; i < 2 * n - 1; i += k) {
        while(i - j >= 0 && i + j + 1 < 2 * n &&
                s[(i - j) / 2] == s[(i + j + 1) / 2])
            j++;
        rad[i] = j;
        for(k = 1; k <= rad[i] && rad[i - k] != rad[i] - k; k++)
            rad[ i + k ] = min(rad[ i - k ], rad[i] - k);
        j = max(j - k, 0);
    }
}
