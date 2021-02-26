#include "../String/LString.h"


Status is_symmetric(LString &str)
{
    size_t len = (str.curlen-1)*CHUNKSIZE;
    int i;
    for (i = 0; i < CHUNKSIZE; i++)
    {
        if (str.tail->ch[i] == '\0')
        {
            len += i;
            break;
        }
    }

    int left = 0, right = i;
    Chunk *cur_right = str.tail;
    Chunk *cur_left = str.head;
    while ((cur_left-str.head)*CHUNKSIZE+left < (len+1)/2)
    {
        if (cur_left->ch[left] != cur_right->ch[right]) return FALSE;
        else
        {
            left++;
            right--;
            if (left == CHUNKSIZE) cur_left = cur_left->next;
            if (right == -1)
            {
                Chunk *p = cur_left;
                while (p->next != cur_right) p = p->next;
                cur_right = p;
                right = CHUNKSIZE-1;
            }
            left %= CHUNKSIZE;
        }
    }
    return TRUE;
}
