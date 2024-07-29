Minishell$ << ls << lsa
runm = 123815536
> ls
runm = 123815472
> lsa
data->cmd->fd->fd_in = 11
dup2: Bad file descriptor
Minishell$ 


Minishell$ << $USER
runm = 123819984
> $USER
data->cmd->fd->fd_in = 11
=================================================================
==25145==ERROR: AddressSanitizer: attempting double-free on 0x0001076157d0 in thread T0:
    #0 0x1052cf260 in wrap_free+0x98 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x53260)
    #1 0x104982f7c in ft_lstclear+0xb8 (minishell:arm64+0x10000af7c)
    #2 0x104982ae4 in main+0x908 (minishell:arm64+0x10000aae4)
    #3 0x1912c20dc  (<unknown module>)

0x0001076157d0 is located 0 bytes inside of 6-byte region [0x0001076157d0,0x0001076157d6)
freed by thread T0 here:
    #0 0x1052cf260 in wrap_free+0x98 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x53260)
    #1 0x10497effc in heredoc+0x1d0 (minishell:arm64+0x100006ffc)
    #2 0x10497f240 in check_heredoc+0x1b8 (minishell:arm64+0x100007240)
    #3 0x104982620 in main+0x444 (minishell:arm64+0x10000a620)
    #4 0x1912c20dc  (<unknown module>)