#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_MATCHES (64)

typedef struct {
    uint32_t ptr;
    uint32_t fail;
    uint32_t success;
} Match;

typedef struct {
    uint32_t offs;
    uint32_t value;
    uint32_t mask;
} FuncSig;

typedef struct {
    const char *name;
    FuncSig *sig;
} FuncsList;

typedef struct bufrange {
    uint32_t *p;
    int len;
    struct bufrange* next;
} BufRange;

BufRange *br, *last;

void addBufRange(uint32_t *p, int l)
{
    BufRange *n = malloc(sizeof(BufRange));
    n->p = p;
    n->len = l;
    n->next = 0;
    if (br == 0)
    {
        br = n;
    }
    else
    {
        last->next = n;
    }
    last = n;
}

#if defined(PLATFORMOS_vxworks)
#include "signatures_vxworks.h"
#elif defined(PLATFORMOS_dryos)
#include "signatures_dryos.h"
#else
#error Undefined platform OS
#endif

int match_compare(const Match *p1, const Match *p2)
{
    /* NOTE: If a function has *more* matches, it will be prefered, even if it has a lower percent matches */
    if (p1->success > p2->success){
        return -1;
    } else
        if (p1->success < p2->success){
            return 1;
        } else {
            if (p1->fail < p2->fail){
                return -1;
            } else
                if (p1->fail > p2->fail){
                    return 1;
                }
        }

        /* scores are equal. prefer lower address */

        if (p1->ptr < p2->ptr){
            return -1;
        } else
            if (p1->ptr > p2->ptr){
                return 1;
            }

            return 0;
}

void usage()
{
    printf("finsig <primary> <base>\n");
    exit(1);
}

int main(int argc, char **argv)
{
    Match matches[MAX_MATCHES];
    uint32_t *buf, *p;
    FILE *f;
    int size;
    int i,j,k;
    int fail, success;
    uint32_t base;
    FuncSig *sig, *s;
    int count;
    int ret = 0;
    const char *curr_name;
    BufRange *n;

    clock_t t1 = clock();

    if (argc != 3)
        usage();

    f = fopen(argv[1], "r+b");

    if (f == NULL)
        usage();

    base = strtoul(argv[2], NULL, 0);

    printf("// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!\n");
    printf("#include \"stubs_asm.h\"\n\n");

    fseek(f,0,SEEK_END);
    size=ftell(f)/4;
    fseek(f,0,SEEK_SET);

    // Max sig size if 32, add extra space at end of buffer and fill with 0xFFFFFFFF
    // Allows sig matching past end of firmware without checking each time in the inner loop
    buf=malloc((size+32)*4);
    fread(buf, 4, size, f);
    fclose(f);
    memset(&buf[size],0xff,32*4);

    // Find all the valid ranges for checking (skips over large blocks of 0xFFFFFFFF)
    br = 0; last = 0;
    k = -1; j = 0;
    for (i = 0; i < size; i++)
    {
        if (buf[i] == 0xFFFFFFFF)   // Possible start of block to skip
        {
            if (k == -1)            // Mark start of possible skip block
            {
                k = i;
            }
        }
        else                        // Found end of block ?
        {
            if (k != -1)
            {
                if (i - k > 32)     // If block more than 32 words then we want to skip it
                {
                    if (k - j > 8)
                    {
                        // Add a range record for the previous valid range (ignore short ranges)
                        addBufRange(&buf[j],k - j);
                    }
                    j = i;          // Reset valid range start to current position
                }
                k = -1;             // Reset marker for skip block
            }
        }
    }
    // Add range for last valid block
    if (k != -1)    
    {
        if (i - k > 32)
        {
            if (k - j > 8)
            {
                addBufRange(&buf[j],k - j);
            }
        }
    }
    else
    {
        if (i - j > 8)
        {
            addBufRange(&buf[j], i - j);
        }
    }

    for (k = 0; func_list[k].name; k++){

        count = 0;
        curr_name = func_list[k].name;

        while (1) {
            sig = func_list[k].sig;

            for (n = br; n != 0; n = n->next){
                for (p = n->p, i = 0; i < n->len; p++, i++){
                    fail = 0;
                    success = 0;
                    for (s = sig; s->offs != -1; s++){
                        if ((p[s->offs] & s->mask) != s->value){
                            fail++;
                        } else {
                            success++;
                        }
                    }
                    if (success > fail){
                        matches[count].ptr = base+(i<<2);
                        matches[count].success = success;
                        matches[count].fail = fail;
                        count ++;
                        if (count >= MAX_MATCHES){
                            printf("// WARNING: too many matches for %s!\n", func_list[k].name);
                            break;
                        }
                    }
                }
            }

            // same name, so we have another version of the same function
            if ((func_list[k+1].name == NULL) || (strcmp(curr_name, func_list[k+1].name) != 0)) {
                break;
            }
            k++;
        }

        // find best match and report results
        if (count == 0){
            printf("// ERROR: %s is not found!\n", curr_name);
            ret = 1;
        } else {
            if (count > 1){
                qsort(matches, count, sizeof(Match), (void*)match_compare);
            }

            if (matches->fail > 0)
                printf("// Best match: %d%%\n", matches->success*100/(matches->success+matches->fail));

            printf("NSTUB(%s, 0x%x)\n", curr_name, matches->ptr);

            for (i=1;i<count && matches[i].fail==matches[0].fail;i++){
                printf("// ALT: NSTUB(%s, 0x%x) // %d/%d\n", curr_name, matches[i].ptr, matches[i].success, matches[i].fail);
            }
        }
    }

    clock_t t2 = clock();

    fprintf(stderr,"Time to generate stubs %.2f seconds\n",(double)(t2-t1)/(double)CLOCKS_PER_SEC);

    return ret;
}

