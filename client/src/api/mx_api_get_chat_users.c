/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, int chat_id, int query_id, int size) {
    query[0] = 7;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    *(int*)(&query[9]) = chat_id;
    return 0;
}

int mx_api_get_chat_users(int chat_id, t_info *info) {
    int size = 13;
    char *query = malloc(sizeof(char) * size);

    memset(query, 0, size);
    get_query(query, chat_id, info->query_id, size);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
