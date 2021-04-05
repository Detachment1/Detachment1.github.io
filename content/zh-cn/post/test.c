int func4(int ax, int si, int edi)
{
    //dx=14, si=0, edi=第一个数
    ax = ax - si;
    ax = ax + (ax >> 31);
    ax = ax >> 1;
    int cx = ax + si;
    if (cx <= edi)
    {
        ax = 0;
        if (cx >= edi)
        {
            return ax;
        }
        else
        {
            si = cx + 1;
            return 2 * func4(ax, si, edi) + 1;
        }
    }
    else
    {
        ax = cx - 1;
        return 2 * func4(ax, si, edi);
    }
}