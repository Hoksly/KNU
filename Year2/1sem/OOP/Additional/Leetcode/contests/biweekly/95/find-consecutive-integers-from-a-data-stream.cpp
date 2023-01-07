class DataStream
{
    int val, k, counter = 0;

public:
    DataStream(int value, int _k) : val(value), k(_k)
    {
    }

    bool consec(int num)
    {
        if (num == val)
            counter++;
        else
            counter = 0;
        if (counter >= k)
            return true;

        return false;
    }
};

/**
 * Your DataStream object will be instantiated and called as such:
 * DataStream* obj = new DataStream(value, k);
 * bool param_1 = obj->consec(num);
 */