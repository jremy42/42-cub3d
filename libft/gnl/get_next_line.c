/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:20:24 by jremy             #+#    #+#             */
/*   Updated: 2022/03/25 12:30:19 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include <stdlib.h> 
 #include <unistd.h> 
 #include "libft.h" 
  
 char        *find_nl(char *str) 
 { 
         int        i; 
  
         i = 0; 
         while (str[i]) 
         { 
                 if (str[i] == '\n') 
                         return (str + i); 
                 i++; 
         } 
         return (NULL); 
 } 
  
 int        load_input(int fd, char **line, char *buf, int buffer_size) 
 { 
         int                read_ret; 
         int                line_size; 
         char        *appended_line; 
         int                i; 
  
         read_ret = read(fd, buf, buffer_size); 
         if (read_ret <= 0) 
                 return (read_ret); 
         line_size = __strlen(*line); 
         appended_line = malloc((line_size + read_ret + 1) * sizeof(char)); 
         if (!appended_line) 
                 return (-2); 
         appended_line[line_size + read_ret] = '\0'; 
         i = -1; 
         while (++i < line_size) 
                 appended_line[i] = (*line)[i]; 
         while (read_ret--) 
                 appended_line[i + read_ret] = buf[read_ret]; 
         free(*line); 
         *line = appended_line; 
         return (1); 
 } 
  
 void        tailor_and_assign(char **line, char *buf, int buf_size, char **nxt_line) 
 { 
         int                i; 
         char        *start_new_buf; 
  
         start_new_buf = find_nl(*line) + 1; 
         i = 0; 
         while (i < buf_size && start_new_buf[i]) 
         { 
                 buf[i] = start_new_buf[i]; 
                 i++; 
         } 
         while (i < buf_size) 
         { 
                 buf[i] = '\0'; 
                 i++; 
         } 
         find_nl(*line)[1] = '\0'; 
         *nxt_line = *line; 
 } 
  
 int        sget_next_line(char **next_line, int fd) 
 { 
         static char        buf[BUFFER_SIZE] = {}; 
         char                *line; 
         int                        load_ret; 
         int                        cumul_read; 
  
         line = __strndup(buf, BUFFER_SIZE); 
         if (!line) 
                 return (-2); 
         load_ret = 1; 
         cumul_read = 0; 
         while (load_ret > 0 && !find_nl(line + cumul_read - 1)) 
         { 
                 load_ret = load_input(fd, &line, buf, BUFFER_SIZE); 
                 cumul_read += load_ret; 
         } 
         if (load_ret < 0 || (!find_nl(line) && __strlen(line) == 0)) 
                 return (free(line), load_ret); 
         if (!find_nl(line)) 
         { 
                 __bzero(buf, BUFFER_SIZE); 
                 *next_line = line; 
                 return (1); 
         } 
         return (tailor_and_assign(&line, buf, BUFFER_SIZE, next_line), 1); 
 } 