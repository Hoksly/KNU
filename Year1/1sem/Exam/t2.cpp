int MAX_SIZE = 100;
char* convert_2(int a)
{
    char *mas = new char[MAX_SIZE];

    int step = 0;
    for(int i = 1; i<a; i*=10, ++step);


    int n, a_cp, pos = 0;
    for(int a_cp = a ; step > 0; ++pos)
    {

        for(int q = 0, s = 1; q < step; ++q, s *= 10)
            n = (a / s) % 10;
        
        
        mas[pos] = '0' + n;
        pos++;
        --step;
        for(int i = 0; i < step; ++i, ++pos)
        {
            mas[pos] = '0';
        }
        mas[pos] = '+';
        
    }

    mas[pos-1] = '\0';
    
    return mas;

}