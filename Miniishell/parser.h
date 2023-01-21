/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:25:19 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/19 19:25:20 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# ifndef    PARSER_H
# define    PARSER_H

#include "lexer.h"

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

# endif