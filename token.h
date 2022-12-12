/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:52:41 by mhabibi-          #+#    #+#             */
/*   Updated: 2022/12/12 23:52:22 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef    TOKEN_H
# define    TOKEN_H

typedef struct token
{
    int i;
    enum
    {
        TOKEN_ID,
        TOKEN_RD2,
        // TOKEN_STRING,
        TOKEN_RD1,
        TOKEN_RD3,
        TOKEN_RD4,
        TOKEN_PIPE,
        // TOKEN_LBRACE,
        // TOKEN_COMMA,
        TOKEN_EOF
    } tkn;
    int type;
    char *value;
    struct token *next;
}t_token;



#endif