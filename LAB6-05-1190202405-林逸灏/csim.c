#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "cachelab.h"
//#define DEBUG_ON
#define ADDRESS_LENGTH 64
 
/* Type: Memory address */
typedef unsigned long long int mem_addr_t;
/* Type: Cache line
   LRU is a counter used to implement LRU replacement policy  */
typedef struct cache_line {
    char valid;      
    mem_addr_t tag;     
    int lru; 
} cache_line_t;
typedef struct
{
    cache_line_t *lines;
}cache_set_t;  
typedef struct
{
    cache_set_t *sets;   
}cache_t;
 
/* Globals set by command line args */
int verbosity = 0; /* print trace if set */
int s = 0; /* set index bits */
int b = 0; /* block offset bits */
int E = 0; /* associativity */
char* trace_file = NULL;
/* Derived from command line args */
int S; /* number of sets */
int B; /* block size (bytes) */
/* Counters used to record cache statistics */
int miss_count = 0;
int hit_count = 0;
int eviction_count = 0;
unsigned long long int lru_counter = 1;
/* The cache we are simulating */
cache_t cache;
mem_addr_t set_index_mask;  
mem_addr_t tag_mask; 
/*
 * initCache - Allocate memory, write 0's for valid and tag and LRU
 * also computes the set_index_mask
 */
void initCache()
{
    int i,j;
    if(s<0)
    {
        printf("error!\n");
        exit(0);
    }
    cache.sets = (cache_set_t*)malloc(S*sizeof(cache_set_t));
    if(!cache.sets)
    {
        printf("No set memory!\n");
        exit(0);
    }
    for(i=0;i<S;i++)
    {
        cache.sets[i].lines = (cache_line_t*)malloc(E*sizeof(cache_line_t));
        if(!cache.sets)
        {
            printf("No line memory!\n");
            exit(0);
        }
        for(j=0;j<E;j++)
        {
           cache.sets[i].lines[j].lru=0;
            cache.sets[i].lines[j].tag=0;
            cache.sets[i].lines[j].valid=0;
        }
    }
}
 
 
/*
 * freeCache - free allocated memory
*/
void freeCache()
{
    int i;
    for(i=0;i<S;i++)
    {
        free(cache.sets[i].lines);
    }
    free(cache.sets);
}
 
 
/*
 * accessData - Access data at memory address addr.
 *   If it is already in cache, increast hit_count
 *   If it is not in cache, bring it in cache, increase miss count.
 *   Also increase eviction_count if a line is evicted.
 */
void accessData(mem_addr_t addr)
{
    int i, isfull, j ,k , flag , minlru;
    isfull=1;
    for(i=0;i<E;i++)
    {
        if(cache.sets[set_index_mask].lines[i].valid==1\
           &&cache.sets[set_index_mask].lines[i].tag==tag_mask)
            {
            hit_count++;
            cache.sets[set_index_mask].lines[i].lru=lru_counter;
            for(k=0;k<E;k++)
            {
                if(k!=i)
                cache.sets[set_index_mask].lines[k].lru--;
            }
            return;
            }
    }
    miss_count++;
    for(i=0;i<E;i++)
    {
        if(cache.sets[set_index_mask].lines[i].valid==0)
        {
            isfull=0;
            break;
        }
    }
    if(isfull==0) 
    {
        cache.sets[set_index_mask].lines[i].valid=1;
        cache.sets[set_index_mask].lines[i].tag=tag_mask;
        cache.sets[set_index_mask].lines[i].lru=lru_counter;
        for(k=0;k<E;k++)
        {
            if(k!=i)
            cache.sets[set_index_mask].lines[k].lru--;
        }
    }
    else
    {
        eviction_count++;
        flag = 0;
        minlru = cache.sets[set_index_mask].lines[0].lru;
        for(j=0;j<E;j++)
        {
            if(minlru>cache.sets[set_index_mask].lines[j].lru)
            {
                minlru = cache.sets[set_index_mask].lines[j].lru;
                flag  = j;
            }
        }
        cache.sets[set_index_mask].lines[flag].valid=1;
        cache.sets[set_index_mask].lines[flag].tag = tag_mask;
        cache.sets[set_index_mask].lines[flag].lru=lru_counter;
        for(k=0;k<E;k++)
        {
            if(k!=flag)
            cache.sets[set_index_mask].lines[k].lru--;
        }
    }
}
 
/*
 * replayTrace - replays the given trace file against the cache
 */
void replayTrace(char* trace_fn)
{
    char buf[1000];
    mem_addr_t addr=0;
    tag_mask=0;
    unsigned int len=0;
    FILE* trace_fp = fopen(trace_fn, "r");
    if(!trace_fp){
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }
    while( fgets(buf, 1000, trace_fp) != NULL) {
        if(buf[1]=='S' || buf[1]=='L' || buf[1]=='M') {
            sscanf(buf+3, "%llx,%u", &addr, &len);
            set_index_mask =(addr>>b)&((1<<s)-1);  
            tag_mask = (addr>>b)>>s;           
            if(verbosity) 
                printf("%c %llx,%u ", buf[1], addr, len);
            accessData(addr);
            /* If the instruction is R/W then access again */
            if(buf[1]=='M')
                accessData(addr);
            if (verbosity)  
                printf("\n");
        }
    }
    fclose(trace_fp);
}
/*
 * printUsage - Print usage info
 */
void printUsage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}
/*
 * main - Main routine
 */
int main(int argc, char* argv[])
{
    char c;
    while( (c=getopt(argc,argv,"s:E:b:t:vh")) != -1){
        switch(c){
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            verbosity = 1;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }
    /* Make sure that all required command line args were specified*/
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }
    /* Compute S, E and B from command line args*/
    S = 1<<s;   
    B = 1<<b;   
    E = E;
    /* Initialize cache */
    initCache();
    replayTrace(trace_file);
    /* Free allocated memory */
    freeCache();
    /* Output the hit and miss statistics for the autograder */
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
