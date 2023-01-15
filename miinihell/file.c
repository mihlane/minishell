/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:28:16 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/11 02:32:02 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// C program to illustrate
// open system call
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
extern int errno;
int main()
{    
    // if file does not have in directory
    // then file foo.txt is created.
    int fd = open("helo", O_RDONLY);
     
    printf("fd = %d\n", fd);
     
    if (fd ==-1)
    {
        // print which type of error have in a code
        printf("Error Number % d\n", errno);
         
        // print program detail "Success or failure"
        perror("Program");                
    }
    return 0;
}