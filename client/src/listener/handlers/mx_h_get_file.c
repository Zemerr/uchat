#include "client.h"

bool check(char *response) {
    if (*(int*)&response[5] < 12) {
        return false;
    }
    return true;
}

t_file *get_file_with_msg_id(t_list *list, int id) {
    t_list *tmp = list;

    while (tmp) {
        if (((t_file*)tmp->data)->msg_of_file->msg_id == id)
            return (t_file*)tmp->data;
        tmp = tmp->next;
    }
    return 0;
}

int mx_h_get_file(char *response, t_info *info) {
    t_file *file = 0;
    int size = *(int*)&response[5];
    char *buff = malloc(size);

    if (check(response) == false)
        return 1;
    // get file with id from msg
    pthread_mutex_lock(&info->m_file_recv_list);
    file = get_file_with_msg_id(info->list_of_recv_files, 
        *(int*)&response[9]);
    pthread_mutex_unlock(&info->m_file_recv_list);
    if (file == 0) {
        printf("ERR mx_h_get_file\n");
        return 0;
    }
    memcpy(buff, &response[21], size - 21);
    // lseek(file->fd, file->pos, SEEK_SET);
    write(file->fd, buff, size - 21);
    // FILE DOWNLOADED
    if (*(int*)&response[13] == file->size) {
        printf("file downloaded\n");
        close(file->fd);
        return 0;
    }

    int a[2] = {*(int*)&response[13], 1024};
    void *parameters[4] = {&file->msg_of_file->msg_id, &file->msg_of_file->msg_id, &a[0], &a[1]};
    mx_api_get_file(parameters, info);
    return 0;
}
