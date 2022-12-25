


typedef struct t_red
{
    enum {
        IN,
        OUT,
        APP,
        HERE,
    } e_type;
    char            *f_name;
    int                amg;
    struct t_red    *next;
}    t_red;

typedef struct t_data
{
    char            **args;
    t_red            *red;
    struct t_data    *next;
}    t_data;