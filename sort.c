#include "ft_ls.h"

void print_list_int(t_list *head)
{
    t_list *tmp = head;
    while (tmp)
    {
        ft_printf("%d ", *(int *)tmp->content);
        tmp = tmp->next;
    }
    ft_printf("\n");
}

void sort(t_list *list, int (*cmp)(int *, int *))
{
    if (!list)
        return;

    int swapped = 1;
    
    while (swapped)
    {
        swapped = 0;
        t_list *tmp = list;
        while (tmp)
        {
            if (tmp->next && cmp(tmp->content, tmp->next->content) > 0)
            {
                void  *value = tmp->content;
                tmp->content = tmp->next->content;
                tmp->next->content = value;
                swapped = 1;
            }
            tmp = tmp->next;
        }
    }
    print_list_int(list);
}

int cmp(int *n, int *m)
{
    return *n - *m;
}

int main()
{
    t_list *list = NULL;
    int a = 43;
    t_list *n1 = ft_lstnew(&a);

    int b= 39;
    t_list *n2 = ft_lstnew(&b);

    int c = 23;
    t_list *n3 = ft_lstnew(&c);

    int d = 21;
    t_list *n4 = ft_lstnew(&d);

    int e = 4;
    t_list *n5 = ft_lstnew(&e);

    int f = 1;
    t_list *n6 = ft_lstnew(&f);

    ft_lstadd_back(&list, n1);
    ft_lstadd_back(&list, n2);
    ft_lstadd_back(&list, n3);
    ft_lstadd_back(&list, n4);
    ft_lstadd_back(&list, n5);
    ft_lstadd_back(&list, n6);

    print_list_int(list);
    sort(list, cmp);
}

