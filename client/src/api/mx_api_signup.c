/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, char **parameters, int query_id) {
    query[0] = 0;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = (int)313;
    memcpy(&query[9], parameters[0], mx_strlen(parameters[0]));
    memcpy(&query[60], parameters[1], mx_strlen(parameters[1]));
    memcpy(&query[111], parameters[2], mx_strlen(parameters[2]));
    memcpy(&query[212], parameters[3], 64);
    return 0;
}

/* 
* parameters[0] = first name
* parameters[1] = second name
* parameters[2] = nickname
* parameters[3] = password
*/
int mx_api_signup(char **parameters, t_info *info) {
    char *query = malloc(sizeof(char) * 313);

    memset(query, 0, 313);
    get_query(query, parameters, info->query_id);
    mx_tsend_msg_(info->sock, query, 313, info);
    return 0;
}
